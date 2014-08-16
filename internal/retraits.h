/*
 *  retraits.h
 *  macstl
 *
 *  Created by Glen Low on Wed Sep 17 2003.
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

#ifndef MACSTL_INTERNAL_RETRAITS_H
#define MACSTL_INTERNAL_RETRAITS_H

#ifdef __GNUC__

#include <bits/type_traits.h>

#endif

#ifdef __MWERKS__

#include <msl_utility>

struct __true_type {};
struct __false_type {};

#endif

namespace std
	{
		namespace impl
			{
				// convert from bool into boolean "type"
				
				template <bool value> struct to_boolean;
						
				template <> struct to_boolean <true>
					{
						typedef __true_type type;
					};
					
				template <> struct to_boolean <false>
					{
						typedef __false_type type;
					};					
			}
	}

#ifdef __MWERKS__

template <class Type> struct __type_traits
	{ 
		typedef typename std::impl::to_boolean <Metrowerks::has_trivial_default_ctor <Type>::value>::type  has_trivial_default_constructor;
		typedef typename std::impl::to_boolean <Metrowerks::has_trivial_copy_ctor <Type>::value>::type    has_trivial_copy_constructor;
		typedef typename std::impl::to_boolean <Metrowerks::has_trivial_assignment <Type>::value>::type    has_trivial_assignment_operator;
		typedef typename std::impl::to_boolean <Metrowerks::has_trivial_dtor <Type>::value>::type    has_trivial_destructor;
		typedef typename std::impl::to_boolean <Metrowerks::is_POD <Type>::value>::type    is_POD_type;
	};

#endif
#endif