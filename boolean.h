/*
 *  boolean.h
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

/**
 * @file boolean.h
 * @ingroup altivec_public
 * @brief Boolean class
 *
 * Declares the macstl::boolean class.
 */
 
#ifndef MACSTL_BOOLEAN_H
#define MACSTL_BOOLEAN_H

#include <internal/retraits.h>

namespace macstl
	{
		/**
		 * @ingroup altivec_public
		 * @brief Sized boolean.
		 * @param Type The integral type with the same size e.g char, short, long.
		 * @par Models:
		 * Assignable, Copy Constructible, Default Constructible, Equality Comparable.
		 * @par Type Traits:
		 * Trivial Default Constructor, Trivial Copy Constructor, Trivial Assignment Operator, Trivial Destructor.
		 *
		 * A bool-valued object with a definite size, where <code>sizeof (boolean \<Type\>) == sizeof (Type)</code>.
		 * It either has all bits zero, representing false, or all bits one, representing true. The type corresponds
		 * to the scalar type of an Altivec vector bool type e.g. <code>macstl::boolean \<char\></code> corresponds
		 * to the scalar type of <code>vector bool char</code>.
		 *
		 * There are no constructors since this type may appear as part of a union.
		 */
		
		template <typename Type> class boolean
			{
				public:
					/** Assigns @a value to object. */
					boolean& operator= (bool value)				{ value_ = -value; return *this; }
					
					/** Converts to a bool. */
					operator bool () const						{ return value_; }
		
				private:
					Type value_;	
			};
	}

template <typename Type> struct __type_traits <macstl::boolean <Type> >
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __false_type	is_POD_type;
	};
	
#endif