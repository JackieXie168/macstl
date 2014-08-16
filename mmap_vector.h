/*
 *  mmap_vector.h
 *  macstl
 *
 *  Created by Glen Low on Wed Dec 11 2002.
 *
 *  Copyright (c) 2003, Pixelglow Software.
 *  http://www.pixelglow.com/macstl/
 *
 *  You may copy, modify, distribute and sell this software and its
 *  documentation without fee, provided that the above copyright notice
 *  appear in all copies and that both the copyright notice and these
 *  permission notices appear in supporting documentation. You may modify
 *  this software without further permission from the copyright holders,
 *  but all such modified files must carry prominent notices stating
 *  that you changed the files and the date of any change.
 *
 *  If you register this software with the copyright holders, you may
 *  compile any part of it from source code to object code. If you
 *  do not register, you may only compile it within 30 days of the first
 *  compilation, and must ensure that all the compiled code and its copies,
 *  modifications, distributions and sales are deleted within the 30 days.
 *
 *  The copyright holders make no representations about the suitability
 *  of this software for any purpose.  It is provided "as is" without
 *  express or implied warranty.
 */

#include <ios>
#include <iterator>

#include <bits/stl_construct.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

namespace macstl
	{
		template <typename Type> class mmap_vector;
		
		class fd_base
			{
				protected:
					int fd_;
					
					fd_base (): fd_ (-1)
						{
						}
						
					fd_base (const char* path, int flags, mode_t mode): fd_ (open (path, flags, mode))
						{
							if (fd_ == -1)
								throw std::ios_base::failure ("file open");
						}
						
					~fd_base ()
						{
							if (fd_ != -1)
								close (fd_);
						}
						
					void swap (fd_base& other)
						{
							std::swap (fd_, other.fd_);
						}
		
					template <typename Type> friend class mmap_vector;
			};
		
		template <class Type> class mmap_base
			{
				protected:
					Type* start_;
					Type* end_of_storage_;
		
					mmap_base (): start_ (NULL), end_of_storage_ (NULL)
						{
						}
						
					mmap_base (size_t capacity, int prot, int flags, int fd, off_t offset):
						start_ (NULL), end_of_storage_ (NULL)
						{
							void* mapped = mmap (0, capacity * sizeof (Type), prot, flags, fd, offset);
							if (mapped == MAP_FAILED)
								throw std::bad_alloc ();
							else
								{
									start_ = reinterpret_cast <Type*> (mapped);
									end_of_storage_ = start_ + capacity;
								}
						}
					
					~mmap_base ()
						{
							if (start_)
								munmap (start_, (end_of_storage_ - start_) * sizeof (Type));
						}
					
					void swap (mmap_base& other)
						{
							std::swap (start_, other.start_);
							std::swap (end_of_storage_, other.end_of_storage_);
						}
		
					friend class mmap_vector <Type>;
				};
				
		template <class Type> class mmap_vector: private fd_base, private mmap_base <Type>
			{
				public:
					typedef Type				value_type;
					typedef value_type*			pointer;
					typedef const value_type*	const_pointer;
					typedef value_type*			iterator;
					typedef const value_type*	const_iterator;
					typedef value_type&			reference;
					typedef const value_type&	const_reference;
					typedef size_t				size_type;
					typedef ptrdiff_t			difference_type;
					typedef std::reverse_iterator <const_iterator>	const_reverse_iterator;
					typedef std::reverse_iterator <iterator>		reverse_iterator;
					
					enum mapping
						{
							priv,
							shared
						};
					
					mmap_vector (): finish_ (NULL), prot_ (0), flags_ (0), blksize_ (0)
						{
						}
						
					mmap_vector (const char* filename,
						std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out,
						mapping map = shared,
						off_t offset = 0):
						finish_ (NULL), prot_ (0), flags_ (0), blksize_ (0)
						{
							open (filename, mode, map, offset);
						}
						
					~mmap_vector ()
						{
							// close but swallow all exceptions thrown
							try
								{
									close ();
								}
							catch (...)
								{
								}
						}
						
					bool is_open () const
						{
							return fd_ != -1;
						}
						
					void open (const char* filename, 
						std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out,
						mapping map = shared,
						off_t offset = 0)
						{
							if (!is_open ())
								{
									bool read = mode & std::ios_base::in;
									bool write = mode & std::ios_base::out;
		
									// figure out mmap protection and flags from params
									int prot = (read ? PROT_READ : 0) | (write ? PROT_WRITE : 0);
									int flags = map == shared ? MAP_SHARED : 0;
		
									// open file with minimum permissions to get the job done
									int mode;
									if (write && (map == shared))
										mode = (read ? O_RDWR : O_WRONLY) | O_CREAT;
									else
										mode = read ? O_RDONLY : 0;
									fd_base file (filename, mode, S_IRWXU);
									
									// get the file stats for size of file and block size
									struct stat sb;
									if (fstat (file.fd_, &sb) == -1)
										throw std::ios_base::failure  ("fstat");
									size_type new_size = (sb.st_size - offset) / sizeof (value_type);
									
									// map the file
									mmap_base <Type> map (new_size, prot, flags, file.fd_, offset);
									
									// non-throwing commits
									map.swap (*this);
									file.swap (*this);
									finish_ = start_ + new_size;
									prot_ = prot;
									flags_ = flags;
									offset_ = offset;
									blksize_ = sb.st_blksize;
								}
						}
						
					void close ()
						{
							if (is_open ())
								{
									size_type old_size = size ();
									
									// close file descriptor and mapping
									fd_base file;
									mmap_base <Type> map;
									map.swap (*this);
									file.swap (*this);

									// truncate file to the last size
									if (ftruncate (file.fd_, offset_ + old_size * sizeof (value_type)) == -1)
										throw std::ios_base::failure ("ftruncate");
								}
						}
		
					iterator begin () 				{ return start_; }
					const_iterator begin () const	{ return start_; }
					iterator end ()					{ return finish_; }
					const_iterator end () const		{ return finish_; }
					
					reverse_iterator rbegin ()				{ return reverse_iterator (finish_); }
					const_reverse_iterator rbegin () const	{ return const_reverse_iterator (finish_); }
					reverse_iterator rend ()				{ return reverse_iterator (start_); }
					const_reverse_iterator rend () const	{ return const_reverse_iterator (start_); }
			
					size_type size () const			{ return finish_ - start_; }
					size_type max_size () const		{ return size_type (-1) / sizeof (Type); }
					size_type capacity () const		{ return end_of_storage_ - start_; }
					bool empty () const				{ return start_ == finish_; }
					
					reference operator[] (size_type n)				{ return start_ [n]; }
					const_reference operator[] (size_type n) const	{ return start_ [n]; }
					
					reference at (size_type n)				{ insert_check (n); return start_ [n]; }
					const_reference at (size_type n) const	{ insert_check (n); return start_ [n]; }
		
					void reserve (size_type new_capacity)
						{
							if (capacity () < new_capacity)
								{
									// calculate enough values to fit into a multiple of the block size
									const size_type old_size = size ();
									const size_type blocked_capacity = (
										((new_capacity * sizeof (value_type) - 1 + offset_) / blksize_ + 1)
										* blksize_ - offset_) / sizeof (value_type);
									
									// remap to the new capacity
									// NOTE: this actually maps new capacity first before unmapping old capacity, so
									// blocked_capacity must be > capacity, else ftruncate pull the rug underneath existing map
									if (ftruncate (fd_, offset_ + blocked_capacity * sizeof (value_type)) == -1)
										throw std::ios_base::failure ("file truncate");
									mmap_base <Type> map (blocked_capacity, prot_, flags_, fd_, offset_);
									
									// non-throwing commits
									map.swap (*this);
									finish_ = start_ + old_size;
								}
						}
						
					void assign (size_type n, const value_type& val)
						{
							fill_assign (n, val);
						}
						
					template <class InputIterator> void assign (InputIterator first, InputIterator last)
						{
							assign_dispatch (first, last, typename _Is_integer <InputIterator>::_Integral ());
						}
		
					reference front()				{ return *start_; }
					const_reference front() const	{ return *start_; }
					reference back()				{ return *(finish_ - 1); }
					const_reference back() const	{ return *(finish_ - 1); }
		
					void push_back (const value_type& x)
						{
							// append a single element
							if (finish_ == end_of_storage_)
								reserve (size () + 1);
							new (finish_) value_type (x);
							++__finish;
						}
						
					iterator insert (iterator pos, const value_type& val = value_type ())
						{
							size_type before = pos - start_;
							fill_insert (pos, 1, val);
							return start_ + before;
						}
		
					template <class InputIterator> void insert(iterator pos, InputIterator first, InputIterator last)
						{
							insert_dispatch (pos, first, last, _Is_integer <InputIterator>::_Integral ());
						}
						
					void insert (iterator pos, size_type n, const value_type& x)
						{
							fill_insert (pos, n, x);
						}
						
					void pop_back ()
						{
							--finish_;
							finish_->~value_type ();
						}
		
					iterator erase (iterator first, iterator last)
						{
							do_erase (first, last);
							return first;
						}
						
					void resize (size_type new_size, const value_type& val = value_type ())
						{
							if (new_size < size ()) 
								do_erase (start_ + new_size, finish_);
							else
								fill_insert (finish_, new_size - size (), val);
						}
		
					void clear ()
						{
							std::_Destroy (start_, finish_);
							finish_ = start_;
						}
		
				private:
					Type* finish_;
					
					int prot_;
					int flags_;
					off_t offset_;
					unsigned long blksize_;
		
					void insert_check (size_type n) const
						{
							if (n < 0 || n >= size ())
								throw out_of_range ("mmap_vector");
						}
		
					template <class Integer> void insert_dispatch (iterator pos, Integer n, Integer val, __true_type)
						{
							fill_insert (pos, static_cast <size_type> (n), static_cast <value_type> (val));
						}
						
					template <class InputIterator> void insert_dispatch
						(iterator pos, InputIterator first, InputIterator last, __false_type)
						{
							insert_insert (pos, first, last, typename std::iterator_traits <InputIterator>::iterator_category ());
						}
				
					template <class InputIterator> void insert_insert (iterator position,
						InputIterator first, InputIterator last, std::input_iterator_tag)
						{
							// insert a input iterator range:
							// because the iteration may not be stable, we have to insert them one at a time
							size_type offset = position - start_;
							size_type size = size () + 1;
							for (; first != last; ++first, ++offset, ++size)
								{
									reserve (size);
									const iterator place = start_ + offset;
									construct (finish_, *(finish_ - 1));
									++finish_;
									std::copy_backward (place, finish_ - 1, finish_);
									*place = *first;
								}
						}
		
					template <class ForwardIteratorator> void insert_insert (iterator position,
						ForwardIteratorator first, ForwardIteratorator last, std::forward_iterator_tag)
						{
							// insert a forward iterator range:
							// because the iteration is stable, we open the required space in the vector and copy straight in
							const size_type count = distance (first, last);
							const size_type before = position - start_;
							const size_type after = finish_ - position;
							
							// ensure sufficient allocated space
							reserve (size () + count);
							
							const iterator place = start_ + before;
							if (after == 0)
								{
									// append elements after end
									std::uninitialized_copy (first, last, finish_);
									finish_ += count;
								}
							else
								{
									const iterator old_finish = finish_;
									if (after > count)
										{
											// insert elements away from end
											std::uninitialized_copy (finish_ - count, finish_, finish_);
											finish_ += count;
											std::copy_backward (place, old_finish - count, old_finish);
											std::copy (first, last, place);
										}
									else
										{
											// insert elements close to end
											ForwardIteratorator mid = first;
											std::advance (mid, after);
											std::uninitialized_copy (mid, last, finish_);
											finish_ += count - after;
											std::uninitialized_copy (place, old_finish, finish_);
											finish_ += after;
											std::copy (first, mid, place);
										}
								}
						}
						
					void fill_insert (iterator position, size_type count, const value_type& value)
						{
							// insert an element fill
							const size_type before = position - start_;
							const size_type after = finish_ - position;
							
							// ensure sufficient allocated space
							reserve (size () + count);
							
							const iterator place = start_ + before;
							if (after == 0)
								{
									// append elements after end
									std::uninitialized_fill_n (finish_, count, value);
									finish_ += count;
								}
							else
								{
									const iterator old_finish = finish_;
									if (after > count)
										{
											// insert elements away from end
											std::uninitialized_copy (finish_ - count, finish_, finish_);
											finish_ += count;
											std::copy_backward (place, old_finish - count, old_finish);
											std::fill_n (place, count, value);
										}
									else
										{
											// insert elements close to end
											std::uninitialized_fill_n (finish_, count - after, value);
											finish_ += count - after;
											std::uninitialized_copy (place, old_finish, finish_);
											finish_ += after;
											std::fill (place, old_finish, value);
										}
								}
						}
		
					template <class Integer> void assign_dispatch (Integer n, Integer val, __true_type)
						{
							fill_assign ((size_type) n, (value_type) val);
						}
					
					template <class InputIterator> void assign_dispatch (InputIterator first, InputIterator last, __false_type)
						{
							insert_assign (first, last, typename std::iterator_traits <InputIterator>::iterator_category ());
						}
		
					template <class InputIterator> void insert_assign (
						InputIterator first, InputIterator last, std::input_iterator_tag)
						{
							iterator current = begin ();
							for (; first != last && current != end (); ++cur, ++first)
								*current = *first;
							if (first == last)
								erase (current, end ());
							else
								insert_insert (end (), first, last, std::input_iterator_tag ());
						}
		
					template <class ForwardIterator> void insert_assign (
						ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
						{
							size_type count = std::distance (first, last);
							
							// ensure sufficient allocated space
							reserve (count);
							size_type len = size ();
					
							if (len >= count)
								{
									// assign few elements
									const iterator new_finish = std::copy (first, last, start_);
									std::_Destroy (new_finish, finish_);
									finish_ = new_finish;
								}
							else
								{
									// assign many elements
									ForwardIterator mid = first;
									std::advance (mid, len);
									std::copy (first, mid, start_);
									finish_ = std::uninitialized_copy (mid, last, finish_);
								}
						}
		
					void fill_assign (size_type count, const value_type& value)
						{
							reserve (count);
							size_type len = size ();
							if (count > len)
								{
									// assign many elements
									std::fill (begin (), end (), value);
									finish_ = std::uninitialized_fill_n (finish_, count - len, value);
								}
							else
								// assign few elements
								erase (std::fill_n (begin (), count, value), end ());
						}
					
					void do_erase (iterator first, iterator last)
						{
							// erase range
							iterator leftover = std::copy (last, finish_, first);
							std::_Destroy (leftover, finish_);
							finish_ = leftover;
						}
		
			};
	};