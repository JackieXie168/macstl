/*
 *  mach_allocator.h
 *  macstl
 *
 *  Created by Glen Low on Fri Dec 27 2002.
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

#include <mach/mach.h>

#include "internal/allocator_base.h"

namespace macstl
	{
		// mach_allocator
		
			// Standard C++ allocators based on the Mach VM allocator. This is the fundamental allocator
			// the OS X system, whose main characteristic is that it allocates pages "lazily" i.e. memory
			// is not actually allocated until it is accessed. Also allocated memory is always
			// page-aligned and zero-filled. 
	
		template <typename Type> class mach_allocator;
		
		template <> class mach_allocator <void>: public void_allocator_base
			{
				public:
					template <class ReType> struct rebind
						{
							typedef mach_allocator <ReType> other;
						};
			};
			
		template <typename Type> class mach_allocator: public allocator_base <Type>
			{
				public:
					typedef typename mach_allocator::pointer pointer;
					typedef typename mach_allocator::size_type size_type;
					
					template <class ReType> struct rebind
						{
							typedef mach_allocator <ReType> other;
						};
		
					mach_allocator () throw ()
						{
						}
						
					template <class ReType> mach_allocator (const mach_allocator <ReType>&) throw ()
						{
						}
						
					static pointer allocate (size_type n, mach_allocator <void>::const_pointer = 0)
						{
							if (n)
								{
									vm_address_t addr;
									if (vm_allocate (mach_task_self (),
										&addr, n * sizeof (Type), TRUE) == KERN_SUCCESS)
										return reinterpret_cast <pointer> (addr);
									else
										throw std::bad_alloc ();
								}
							else
								return NULL;
						}
					
					static void deallocate (pointer ptr, size_type n)
						{
							vm_deallocate (mach_task_self (),
								reinterpret_cast <vm_address_t> (ptr), n * sizeof (Type));
						}
			};
			
		template <typename Type1, typename Type2> inline bool operator==
			(const mach_allocator <Type1>&, const mach_allocator <Type2>&)
			{
				return true;
			}
			
		template <typename Type1, typename Type2> inline bool operator!=
			(const mach_allocator <Type1>&, const mach_allocator <Type2>&)
			{
				return false;
			}
	};
