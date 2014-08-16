/*
 *  allocator_base.h
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

#include <memory>

namespace macstl
	{
		template <class Type> class allocator_base
			{
				public:
					typedef size_t		size_type;
					typedef ptrdiff_t	difference_type;
					typedef Type*		pointer;
					typedef const Type*	const_pointer;
					typedef Type&		reference;
					typedef const Type&	const_reference;
					typedef Type		value_type;
			
					static pointer address (reference x)				{ return &x; }
					static const_pointer address (const_reference x)	{ return &x; }
			
					static size_type max_size () throw()
						{
							return size_type (-1) / sizeof (value_type);
						}
			
					static void construct (pointer ptr, const Type& val)	{ new (ptr) Type (val); }
					static void destroy (pointer ptr)						{ ptr->~Type(); }
			};
			
		class void_allocator_base
			{
				public:
					typedef void		value_type;
					typedef void*		pointer;
					typedef const void*	const_pointer;
			};
	};


