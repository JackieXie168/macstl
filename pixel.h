/*
 *  pixel.h
 *  macstl
 *
 *  Created by Glen Low on Sat Sep 13 2003.
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
 * @file pixel.h
 * @ingroup altivec_public
 * @brief Pixel class
 *
 * Declares the macstl::pixel class.
 */

#ifndef MACSTL_PIXEL_H
#define MACSTL_PIXEL_H

namespace macstl
	{
		/**
		 * @ingroup altivec_public
		 * @brief 1/5/5/5 ARGB pixel.
		 * @par Models:
		 * Assignable, Copy Constructible, Default Constructible, Equality Comparable.
		 * @par Type Traits:
		 * Trivial Default Constructor, Trivial Copy Constructor, Trivial Assignment Operator, Trivial Destructor.
		 *
		 * Stores a 16-bit ARGB color value, where the alpha occupies 1 bit, and each color channel occupies 5 bits.
		 * The type corresponds to the scalar type of an Altivec <code>vector pixel</code>.
		 */
		struct pixel
			{
				unsigned int a: 1;	/**< The alpha value, 0 or 1. */
				unsigned int r: 5;	/**< The red value, 0 to 31. */
				unsigned int g: 5;	/**< The green value, 0 to 31. */
				unsigned int b: 5;	/**< The blue value, 0 to 31. */
			};
			
		/** @relates pixel Returns @a left compared equal to @a right. */
		inline bool operator== (pixel left, pixel right)
			{
				return *reinterpret_cast <unsigned short*> (&left) == *reinterpret_cast <unsigned short*> (&right);
			}

		/** @relates pixel Returns @a left compared equal to @a right. */
		inline bool operator!= (pixel left, pixel right)
			{
				return *reinterpret_cast <unsigned short*> (&left) != *reinterpret_cast <unsigned short*> (&right);
			}

	}
	
#endif

