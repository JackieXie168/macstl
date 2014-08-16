/*
 *  boolean.h
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

#include <bits/type_traits.h>

namespace macstl
	{
		// sized booleans: the scalars corresponding to vector bool char etc.
		
		template <typename Type> class boolean
			{
				public:
					// no constructors since these may appear part of a union
					
					boolean& operator= (bool value)			{ value_ = -value; return *this; }
					operator bool () const					{ return value_; }
		
				private:
					Type value_;	
			};
	};

template <typename Type> struct __type_traits <macstl::boolean <Type> >
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __false_type	is_POD_type;
	};