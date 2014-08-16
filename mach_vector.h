/*
 *  mach_vector.h
 *  macstl
 *
 *  Created by Glen Low on Thu Dec 26 2002.
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

#include <vector>

#include "mach_allocator.h"
#include "internal/vector_core.h"

namespace std
	{
		template <typename Alloc> class vector_alloc_base: private Alloc
			{
				protected:
					typedef Alloc::pointer pointer;
					typedef Alloc::value_type value_type;
					
					Alloc get_allocator () const
						{
							return *this;
						}
						
					vector_alloc_base (const Alloc& alloc):
						Alloc (alloc), start_ (NULL), end_of_storage_ (NULL)
						{
						}
						
					vector_alloc_base (const Alloc& alloc, size_t size):
						Alloc (alloc), start_ (NULL), end_of_storage_ (NULL)
						{
							start_ = allocate (size);
							end_of_storage_ = start_ + size;
						}
					
					~vector_alloc_base ()
						{
							if (start_)
								deallocate (start_, end_of_storage_ - start_);
						}
						
					void swap (vector_alloc_base& other)
						{
							std::swap (start_, other.start_);
							std::swap (end_of_storage_, other.end_of_storage_);
						}
					
				protected:
					pointer start_;
					pointer end_of_storage_;			
			};
			
		template <typename Type> class mach_vector_base: protected vector_alloc_base <macstl::mach_allocator <Type> >
			{
				public:
					typedef macstl::mach_allocator <Type>::value_type		value_type;
					
					typedef macstl::mach_allocator <Type>::pointer			pointer;
					typedef macstl::mach_allocator <Type>::const_pointer	const_pointer;
					typedef macstl::mach_allocator <Type>::reference		reference;
					typedef macstl::mach_allocator <Type>::const_reference	const_reference;
					typedef macstl::mach_allocator <Type>::size_type		size_type;
					typedef macstl::mach_allocator <Type>::difference_type	difference_type;
			
					typedef pointer			iterator;
					typedef const_pointer	const_iterator;
					
					iterator begin () 				{ return start_; }
					const_iterator begin () const	{ return start_; }
					iterator end ()					{ return finish_; }
					const_iterator end () const		{ return finish_; }

				protected:
					pointer finish_;

					template <typename InIter> void copy_end (InIter first, InIter last)
						{
							finish_ = std::uninitialized_copy (first, last, end ());
						}
						
					void fill_end (size_type count, const value_type& val)
						{
							finish_ = std::uninitialized_fill_n (end (), count, val);
						}
						
					void erase_end (iterator pos)
						{
							std::_Destroy (pos, end ());
							finish_ = pos;
						}

			};

		// vector <Type, mach_alloc>
		
			// Specialization of vector tuned for the Mach allocator:
			// 1. If the type has a trivial default constructor, the constructor vector (count) doesn't need to initialize
			//    elements since the Mach allocator allocates zero-filled memory.
			// 2. If the type has a trivial copy constructor, the vector's copy constructor, assignment operator and any
			//    capacity-increasing member functions (e.g. reserve) use the Mach copy-on-write when reallocating. Since
			//    reallocations are less intensive under this regime, the vector is allowed to grow linearly instead of
			//    exponentially.
			// Overall, this will increase the speed of copying vectors (e.g. returning vectors from a function) and reduce
			// memory impact (i.e. doesn't require twice vector's memory for copy).
									
		template <class Type> class vector <Type, macstl::mach_allocator <Type> >:
			public impl::vector_core <vector <Type, macstl::mach_allocator <Type> >,
			private vector_alloc_base <macstl::mach_allocator <Type> >
			{
				private:
					typedef vector_alloc_base <macstl::mach_allocator <Type> > base;
					typedef typename __type_traits <Type>::has_trivial_default_constructor has_trivial_default_constructor;
					static typename __type_traits <Type>::has_trivial_copy_constructor has_trivial_copy_constructor;
					
				public:
					typedef Type					value_type;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;
					typedef value_type*				iterator;
					typedef const value_type*		const_iterator;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef size_t					size_type;
					typedef ptrdiff_t				difference_type;
					typedef macstl::mach_allocator	allocator_type;
					typedef reverse_iterator <const_iterator>	const_reverse_iterator;
				//	typedef reverse_iterator <iterator>			reverse_iterator;
					
					using base::get_allocator;
					
					explicit vector (const allocator_type& alloc = allocator_type ()): base (0, alloc), finish_ (NULL)
						{
						}
						
					vector (size_type count, const value_type& value, const allocator_type& alloc = allocator_type ()):
						base (count, alloc), finish_ (start_)
						{
							finish_ = std::uninitialized_fill_n (start_, count, value);
						}
			
					explicit vector (size_type count): base (count, allocator_type ()), finish_ (start_)
						{
							zero_init (count, has_trivial_default_constructor ());
						}
						
					vector (const vector& other): base (other.size (), other.get_allocator ()), finish_ (start_)
						{
							copy_init (other, other.size (), has_trivial_copy_constructor ());
						}
						
					~vector ()
						{
							std::_Destroy (start_, finish_);
						}
						
					vector& operator= (const vector& other)
						{
							if (this != &other)
								vector (other).swap (*this);
						}
												

					void reserve (size_type new_capacity)
						{
							if (new_capacity > capacity ())
								{
									vector copy (*this, length, new_capacity);
									copy.swap (*this);
								}
						}
			
				private:
					pointer finish_;
					
					vector (const vector& other, size_type length, size_type new_capacity):
						base (new_capacity, other.get_allocator ()), finish_ (start_)
						{
							copy_init (other, length, __trivial_copy_constructor ());
						}

												
					static size_type __round_to_pages (size_type count)
						{
							return round_page (n * sizeof (value_type)) * vm_page_size / sizeof (value_type);
						}

					void zero_init (size_type count, __true_type)
						{
							// trivial default constructor: zero is a no-op
							finish_ += count;
						}

					void zero_init (size_type count, __false_type)
						{
							// no trivial default constructor: zero is an uninitialized fill of default constructed values
							finish_ = std::uninitialized_fill_n (finish_, count, value_type ());
						}
						
					void copy_init (const vector& other, size_type length, __true_type)
						{
							// trivial copy constructor: copy is simply a vm_copy of leading values, memcpy for the rest
							size_t bytes = length * sizeof (value_type);
							size_t trailing = bytes % vm_page_size;
							size_t leading = bytes - trailing;
							if (leading)
								vm_copy (mach_task_self (),
									reinterpret_cast <vm_address_t> (other.start_),
									leading,
									reinterpret_cast <vm_address_t> (start_));
								// hmm... do we need to handle vm_copy errors??
							if (trailing)
								memcpy (reinterpret_cast <char*> (start_) + leading,
									reinterpret_cast <char*> (other.start_) + leading,
									trailing);
							finish_ += length;
						}

					void copy_init (const vector& other, size_type length, __false_type)
						{
							// no trivial copy constructor: copy uses uninitialized_copy algorithm
							finish_ = std::uninitialized_copy
								(other.start_, other.start_ + length, finish_);
						}
			};
	
	
	
	
	};

