/*
 *  core_allocator.h
 *  macstl
 *
 *  Created by Glen Low on Fri Dec 27 2002.
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

#ifndef MACSTL_CORE_ALLOCATOR_H
#define MACSTL_CORE_ALLOCATOR_H

#include <CoreFoundation/CoreFoundation.h>

#include <internal/allocator_base.h>

namespace macstl
	{
		// core_allocator
		
			// Wraps Core Foundation allocators as Standard C++ allocators. Wrappers of distinct CF
			// allocators are distinct instances themselves.
				
		template <class Type> class core_allocator;
		
		template <typename Type1, typename Type2> inline bool operator==
			(const core_allocator <Type1>& left, const core_allocator <Type2>& right)
			{
				return left.alloc_ == right.alloc_;
			}
		
		template <typename Type> inline bool operator==
			(const core_allocator <Type>& left, const core_allocator <void>& right)
			{
				return false;
			}
		
		template <typename Type> inline bool operator==
			(const core_allocator <void>& left, const core_allocator <Type>& right)
			{
				return false;
			}
		
		inline bool operator==
			(const core_allocator <void>& left, const core_allocator <void>& right)
			{
				return true;
			}
			
		template <typename Type1, typename Type2> inline bool operator!=
			(const core_allocator <Type1>& left, const core_allocator <Type2>& right)
			{
				return left.alloc_ != right.alloc_;
			}
		
		template <typename Type> inline bool operator!=
			(const core_allocator <Type>& left, const core_allocator <void>& right)
			{
				return true;
			}
		
		template <typename Type> inline bool operator!=
			(const core_allocator <void>& left, const core_allocator <Type>& right)
			{
				return true;
			}
		
		inline bool operator!=
			(const core_allocator <void>& left, const core_allocator <void>& right)
			{
				return false;
			}
		
		template <> class core_allocator <void>: public void_allocator_base
			{
				public:
					template <class ReType> struct rebind
						{
							typedef core_allocator <ReType> other;
						};
			};
			
		template <typename Type> class core_allocator: public allocator_base <Type>
			{
				public:
					typedef typename core_allocator::pointer pointer;
					typedef typename core_allocator::size_type size_type;
					
					template <class ReType> struct rebind
						{
							typedef core_allocator <ReType> other;
						};
		
					core_allocator (CFAllocatorRef alloc = NULL): alloc_ (alloc)
						{
						}
						
					template <class ReType> core_allocator (const core_allocator <ReType>& other):
						alloc_ (other.alloc_)
						{
						}
						
					pointer allocate (size_type n, core_allocator <void>::const_pointer = 0)
						{
							if (n)
								{
									void* addr = CFAllocatorAllocate (alloc_, n * sizeof (Type), 0);
									if (addr)
										return reinterpret_cast <pointer> (addr);
									else
										throw std::bad_alloc ();
								}
							else
								return NULL;
						}
					
					void deallocate (pointer ptr, size_type)
						{
							CFAllocatorDeallocate (alloc_, ptr);
						}
						
					template <typename Type1, typename Type2> friend bool operator==
						(const core_allocator <Type1>& left, const core_allocator <Type2>& right);
						
					template <typename Type1, typename Type2> friend bool operator!=
						(const core_allocator <Type1>& left, const core_allocator <Type2>& right);
														
				private:
					const CFAllocatorRef alloc_;
			};
	};
	
#endif
