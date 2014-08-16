/*
 *  vector_core.h
 *  macstl
 *
 *  Created by Glen Low on Wed May 21 2003.
 *
 *  Copyright (c) 2003, Pixelglow Software.
 *  http://www.pixelglow.com/macstl/
 *  macstl@pixelglow.com
 *
 *  You may copy, modify, distribute and sell this source code and its
 *  documentation without fee, provided that the above copyright notice
 *  appear in all copies and that both the copyright notice and these
 *  permission notices appear in supporting documentation. You may modify
 *  this source code without further permission from the copyright holders,
 *  but all such modified files must carry prominent notices stating
 *  that you changed the files and the date of any change.
 *
 *  If you register this source code with the copyright holders, you may
 *  compile any part of it from source code to object code. If you
 *  do not register, you may only compile it within 30 days of the first
 *  compilation, and must ensure that all the compiled code and its copies,
 *  modifications, distributions and sales are deleted within the 30 days.
 *
 *  The copyright holders make no representations about the suitability
 *  of this software for any purpose.  It is provided "as is" without
 *  express or implied warranty.
 */

#include <Carbon/Carbon.h>

namespace impl
	{
		template <typename Vector> class vector_core
			{
				private:
					typedef typename Vector::reverse_iterator reverse_iterator;
					
				public:
					reverse_iterator rbegin ()				{ return reverse_iterator (end ()); }
					const_reverse_iterator rbegin () const	{ return const_reverse_iterator (end ()); }
					reverse_iterator rend ()				{ return reverse_iterator (begin ()); }
					const_reverse_iterator rend () const 	{ return const_reverse_iterator (begin ()); }

					size_type size () const			{ return end () - begin (); }
					size_type max_size () const		{ return size_type (-1) / sizeof (value_type); }
					bool empty () const				{ return begin () == end (); }
					
					reference operator[] (size_type index)				{ return begin () [index]; }
					const_reference operator[] (size_type index) const	{ return begin () [index]; }
					
					reference at (size_type index)				{ range_check (index); return begin () [index]; }
					const_reference at (size_type index) const	{ range_check (index); return begin () [index]; }
					
					void assign (size_type count, const value_type& val)
						{
							if (count <= capacity ())
								assign_without (count, val);
							else
								assign_within (count, val);
						}
						
					template <typename InIter> void assign (InIter first, InIter last)
						{
							assign_dispatch (first, last, std::iterator_traits <InIter>::iterator_category ());
						}
						
					reference front ()				{ return begin () [0]; }
					const_reference front () const	{ return begin () [0]; }
					reference back ()				{ return end () [-1]; }
					const_reference back () const	{ return end () [-1]; }
					
					void push_back (const value_type& val)
						{
							if (size () < capacity ())
								push_back_within (val);
							else
								push_back_without (val);
						}
						
					iterator insert (iterator pos, const value_type& val = value_type ())
						{
							if (size () < capacity ())
								return insert_within (pos, val);
							else
								return insert_without (pos, val);
						}
						
					void insert (iterator pos, size_type count, const value_type& val)
						{
							if (size () < capacity ())
								insert_within (pos, count, val);
							else
								insert_without (pos, count, val);
						}
						
					template <typename InIter> void insert (iterator pos, InInter first, InIter last)
						{
							insert_dispatch (pos, first, last, std::iterator_traits <InIter>::iterator_category ());
						}
						
					void pop_back ()
						{
							erase_end (end () - 1);
						}
					
					iterator erase (iterator pos)
						{
							return erase (pos, pos + 1);
						}
						
					iterator erase (iterator first, iterator last)
						{
							erase_end (std::copy (last, end (), first));
							return first;							
						}
						
					void resize (size_type new_size, const value_type& filler = value_type ())
						{
							if (new_size < size ())
								erase (begin () + new_size, end ());
							else
								insert (end (), new_size - size (), filler);
						}
						
					void clear ()
						{
							erase (begin (), end ());
						}
						
				private:
					void range_check (size_t index) const
						{
							if (index >= size ())
								throw std::out_of_range ("vector::at");
						}
						
					template <typename InIter> void assign_dispatch (InIter first, InIter last, input_iterator_tag)
						{
							iterator current = begin ();
							iterator finish = end ();
							for (; first != last && current != finish; ++current, ++first)
								*current = *first;
							if (first == last)
								erase (current, finish);
							else
								insert (end (), first, last);
						}

					template <typename InIter> void assign_dispatch (InIter first, InIter last, forward_iterator_tag)
						{
							if (std::distance (first, last) <= capacity ())
								assign_without (first, last);
							else
								assign_within (first, last);
						}

					template <typename InIter> void insert_dispatch (iterator pos, InIter first, InIter last, input_iterator_tag)
						{
							for (; first != last; ++first, ++pos)
								pos = insert (pos, *first);
						}

					template <typename InIter> void insert_dispatch (iterator pos, InIter first, InIter last, forward_iterator_tag)
						{
							size_type old_size = size ();
							size_type length = std::distance (first, last);
							
							if (old_size < capacity ())
								insert_without (pos, first, last);
							else
								insert_within (pos, first, last);
						}
						
					void assign_within (size_type count, const value_type& val)
						{
							size_type old_size = size ();
							if (count < old_size)
								to_vector ().erase_end (std::fill_n (begin (), count, val));
							else
								{
									std::fill_n (begin (), old_size, val);
									fill_end (count - old_size, val);
								}
						}
						
					void assign_without (size_type count, const value_type& val)
						{
							Vector copy (count, val);
							copy.swap (to_vector ());
						}
						
					template <typename InIter> void assign_within (InIter first, InIter last)
						{
							size_type length = std::distance (first, last);
							size_type old_size = size ();
							
							if (length <= old_size)
								to_vector ().erase_end (std::copy_n (first, length, begin ()));
							else
								{
									InIter middle = first;
									std::advance (middle, size ());
									std::copy (first, middle, begin ());
									to_vector ().copy_end (middle, last);
								}
						}

					template <typename InIter> void assign_without (InIter first, InIter last)
						{
							Vector copy (first, last);
							copy.swap (to_vector ());						
						}
						
					void push_back_within (const value_type& val)
						{
							to_vector ().fill_end (1, val);
						}
						
					void push_back_without (const value_type& val)
						{
							size_type old_size = size ();
							Vector copy (to_vector (), old_size, old_size + 1);
							copy.fill_end (1, val);
							copy.swap (*this);
						}
						
					iterator insert_within (iterator pos, const value_type& val)
						{
							fill_end (1, *(end () - 1));
							std::copy_backward (pos, end () - 1, pos + 1);
							*pos = val;
							return pos;
						}
						
					iterator insert_without (iterator pos, const value_type& val)
						{
							size_type place = pos - begin ();
							Vector temp (to_vector (), place, old_size + 1);
							temp.fill_end (1, val);
							temp.copy_end (pos, end ());
							temp.swap (to_vector ());
							return begin () + place;
						}
						
					void insert_within (iterator pos, size_type count, const value_type& val)
						{
							iterator old_end = end ();
							size_type after = old_end - pos;
							if (after > count)
								{
									copy_end (old_end - count, old_end);
									std::copy_backward (pos, old_end - count, old_end);
									std::fill_n (pos, count, val);
								}
							else
								{
									fill_end (count - after, val);
									copy_end (pos, old_end);
									std::fill_n (pos, after, val);
								}
						}
						
					void insert_without (iterator pos, size_type count, const value_type& val)
						{
							size_type place = pos - begin ();
							Vector temp (to_vector (), place, old_size + count);
							temp.fill_end (count, val);
							temp.copy_end (pos, end ());
							temp.swap (to_vector ());								
						}
						
					template <typename InIter> void insert_within (iterator pos, InIter first, InIter last)
						{
							iterator old_end = end ();
							size_type after = old_end - pos;
							size_type length = std::distance (first, last);
							if (after > length)
								{
									copy_end (old_end - length, old_end);
									std::copy_backward (pos, old_end - length, old_end);
									std::copy (first, last, pos);
								}
							else
								{
									InIter middle = first;
									std::advance (middle, after);
									copy_end (middle, last);
									copy_end (pos, old_end);
									std::copy (first, middle, pos);
								}
						}

					template <typename InIter> void insert_without (iterator pos, InIter first, InIter last)
						{
							size_type place = pos - begin ();
							Vector temp (to_vector (), place, old_size + length);
							temp.copy_end (first, last);
							temp.copy_end (pos, end ());
							temp.swap (to_vector ());								
						}
						
					Vector& to_vector ()				{ return static_cast <Vector&> (*this); }
					const Vector& to_vector () const	{ return static_cast <const Vector&> (*this); }
			};
	
	
	
	};