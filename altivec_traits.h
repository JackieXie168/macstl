/*
 *  altivec_traits
 *  macstl
 *
 *  Created by Glen Low on Fri Aug 30 2002.
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
 * @file altivec_traits.h
 * @ingroup altivec_public
 * @brief Altivec type traits
 *
 * Declares the macstl::altivec_traits class.
 */

#ifndef MACSTL_ALTIVEC_TRAITS_H
#define MACSTL_ALTIVEC_TRAITS_H
 
#include <functional>

#include <vecLib/vfp.h>

namespace macstl
	{
		namespace impl
			{
				// traits for numeric types
				enum specifier
					{
						bool_spec,
						signed_spec,
						unsigned_spec,
						float_spec
					};
					
				template <typename Val> struct from_value;
				
				template <> struct from_value <char>
					{
						typedef __vector signed char vector_type;
					};

				template <> struct from_value <unsigned char>
					{
						typedef __vector unsigned char vector_type;
					};

				template <> struct from_value <boolean <char> >
					{
						typedef __vector bool char vector_type;
					};

				template <> struct from_value <short>
					{
						typedef __vector signed short vector_type;
					};

				template <> struct from_value <unsigned short>
					{
						typedef __vector unsigned short vector_type;
					};

				template <> struct from_value <boolean <short> >
					{
						typedef __vector bool short vector_type;
					};

				template <> struct from_value <long>
					{
						typedef __vector signed int vector_type;
					};

				template <> struct from_value <unsigned long>
					{
						typedef __vector unsigned int vector_type;
					};

				template <> struct from_value <boolean <long> >
					{
						typedef __vector bool int vector_type;
					};
					
				template <> struct from_value <float>
					{
						typedef __vector float vector_type;
					};
				
				template <specifier spec, size_t size> struct to_vector;
				
				template <> struct to_vector <signed_spec, 1>
					{
						typedef __vector signed char vector_type;
					};

				template <> struct to_vector <unsigned_spec, 1>
					{
						typedef __vector unsigned char vector_type;
					};
				
				template <> struct to_vector <bool_spec, 1>
					{
						typedef __vector bool char vector_type;
					};
				
				template <> struct to_vector <signed_spec, 2>
					{
						typedef __vector signed short vector_type;
					};

				template <> struct to_vector <unsigned_spec, 2>
					{
						typedef __vector unsigned short vector_type;
					};
				
				template <> struct to_vector <bool_spec, 2>
					{
						typedef __vector bool short vector_type;
					};
				
				template <> struct to_vector <signed_spec, 4>
					{
						typedef __vector signed int vector_type;
					};

				template <> struct to_vector <unsigned_spec, 4>
					{
						typedef __vector unsigned int vector_type;
					};
				
				template <> struct to_vector <bool_spec, 4>
					{
						typedef __vector bool int vector_type;
					};

				template <> struct to_vector <float_spec, 4>
					{
						typedef __vector float vector_type;
					};
					
				template <typename Vec> struct from_vector;
				
				template <> struct from_vector <__vector signed char>
					{
						static const specifier spec = signed_spec;
						static const size_t size = 1;
						
						typedef char value_type;
						
						static __vector signed char zero ()
							{
								return (__vector signed char) (0);
							}
					};

				template <> struct from_vector <__vector unsigned char>
					{
						static const specifier spec = unsigned_spec;
						static const size_t size = 1;
						
						typedef unsigned char value_type;

						static __vector unsigned char zero ()
							{
								return (__vector unsigned char) (0);
							}

					};

				template <> struct from_vector <__vector bool char>
					{
						static const specifier spec = bool_spec;
						static const size_t size = 1;
						
						typedef boolean <char> value_type;

						static __vector bool char zero ()
							{
								return (__vector bool char) (0);
							}
					};
				
				template <> struct from_vector <__vector signed short>
					{
						static const specifier spec = signed_spec;
						static const size_t size = 2;
						
						typedef short value_type;

						static __vector signed short zero ()
							{
								return (__vector signed short) (0);
							}
					};

				template <> struct from_vector <__vector unsigned short>
					{
						static const specifier spec = unsigned_spec;
						static const size_t size = 2;
						
						typedef unsigned short value_type;

						static __vector unsigned short zero ()
							{
								return (__vector unsigned short) (0);
							}
					};

				template <> struct from_vector <__vector bool short>
					{
						static const specifier spec = bool_spec;
						static const size_t size = 2;
						
						typedef boolean <short> value_type;

						static __vector bool short zero ()
							{
								return (__vector bool short) (0);
							}
					};
				
				template <> struct from_vector <__vector signed int>
					{
						static const specifier spec = signed_spec;
						static const size_t size = 4;
						
						typedef long value_type;

						static __vector signed int zero ()
							{
								return (__vector signed int) (0);
							}
					};

				template <> struct from_vector <__vector unsigned int>
					{
						static const specifier spec = unsigned_spec;
						static const size_t size = 4;
						
						typedef unsigned long value_type;

						static __vector unsigned int zero ()
							{
								return (__vector unsigned int) (0);
							}
					};

				template <> struct from_vector <__vector bool int>
					{
						static const specifier spec = bool_spec;
						static const size_t size = 4;
						
						typedef boolean <long> value_type;

						static __vector bool int zero ()
							{
								return (__vector bool int) (0);
							}
					};

				template <> struct from_vector <__vector float>
					{
						static const specifier spec = float_spec;
						static const size_t size = 4;
						
						typedef float value_type;

						static __vector float zero ()
							{
								return (__vector float) (0.0f);
							}
					};

				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for all Altivec types.
				 * @param Type The scalar type.
				 */
				template <typename Type> struct altivec_base_traits
					{
						typedef Type value_type;										/**< The scalar type. */
						typedef typename from_value <Type>::vector_type vector_type;	/**< The Altivec vector type. */

						/** The size in bytes of the vector. */
						static const size_t width = sizeof (vector_type);
						
						/** The number of scalars in the vector. */
						static const size_t length = sizeof (vector_type) / sizeof (value_type);
						
						typedef typename to_vector <bool_spec, from_vector <vector_type>::size>::vector_type bool_vector_type;
						typedef typename from_vector <bool_vector_type>::value_type bool_value_type;

						typedef typename to_vector <unsigned_spec, from_vector <vector_type>::size>::vector_type unsigned_vector_type;

						union union_type
							{
								vector_type vec;
								value_type val [length];
							};
							
						/** Returns the zero vector. @note This is a function because we cannot define static const vectors. */
						static vector_type zero () { return from_vector <vector_type>::zero (); }
						
						/** Returns the one's complement of each element of @a x. */
						static vector_type bitwise_not (vector_type x)					{ return vec_nor (x, x); }
							
						/** Returns the bitwise AND of each element of @a x and the corresponding element of @a y. */
						static vector_type bitwise_and (vector_type x, vector_type y)	{ return vec_and (x, y); }
						
						/** Returns the bitwise inclusive OR of each element of @a x and the corresponding element of @a y. */
						static vector_type bitwise_or (vector_type x, vector_type y)	{ return vec_or (x, y); }
						
						/** Returns the bitwise exclusive OR of each element of @a x and the corresponding element @a y. */
						static vector_type bitwise_xor (vector_type x, vector_type y)	{ return vec_xor (x, y); }
						
						/** Returns the result of circularly shifting each element of @a x left @a n places. */
						static vector_type cshift (vector_type x, int n)
							{
								return vec_perm (x, x, vec_lvsl (n * from_vector <vector_type>::size, (int*) NULL));
							}
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for all builtin Altivec types.
				 * @param Type The scalar type.
				 */
				template <typename Type> struct altivec_builtin_traits: public altivec_base_traits <Type>
					{
						typedef Type value_type;
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::union_type union_type;

						static vector_type load (const value_type* address, size_t offset)
							{
								return vec_ld (offset * sizeof (value_type), address);
							}
				
						static void store (vector_type x, value_type* address, size_t offset)
							{
								return vec_st (x, offset * sizeof (value_type), address);
							}
						
						/** Returns each element set to @a x. */
						static vector_type splat (value_type x)
							{
								union_type both;
								both.val [0] = x;
								return vec_splat (both.vec, 0);
							}						
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for Altivec number types.
				 * @param Type The scalar type.
				 */
				template <typename Type> struct altivec_number_traits: public altivec_builtin_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::bool_vector_type bool_vector_type;
						
						/** Returns the absolute value of each element of @a x. */
						static vector_type abs (vector_type x)					{ return vec_abs (x); }

						/** Returns the negation of each element of @a x. */
						static vector_type negate (vector_type x) 				{ return vec_sub (zero (), x); }
						
						/** Returns each element of @a x added to the corresponding element of @a y. */
						static vector_type plus (vector_type x, vector_type y) 	{ return vec_add (x, y); }

						/** Returns each element of @a x subtracted by the corresponding element of @a y. */
						static vector_type minus (vector_type x, vector_type y) { return vec_sub (x, y); }
												
						/** Returns the maximum of each element of @a x and the corresponding element of @a y. */
						static vector_type max (vector_type x, vector_type y)	{ return vec_max (x, y); }
						
						/** Returns the minimum of each element of @a x and the corresponding element of @a y. */
						static vector_type min (vector_type x, vector_type y)	{ return vec_min (x, y); }

						/** Returns the logical NOT of each element of @a x. */
						static bool_vector_type logical_not (vector_type x)		{ return vec_cmpeq (x, zero ()); }
						
						/** Returns the logical AND of each element of @a x and the corresponding element of @a y. */
						static bool_vector_type logical_and (vector_type x, vector_type y)
							{
								return vec_nor (vec_cmpeq (x, zero ()), vec_cmpeq (y, zero ()));
							}
							
						/** Returns the logical OR of each element of @a x and the corresponding element of @a y. */
						static bool_vector_type logical_or (vector_type x, vector_type y)
							{
								vector_type anded = vec_and (vec_cmpeq (x, zero ()), vec_cmpeq (y, zero ()));
								return vec_nor (anded, anded);
							}
				
						/** Returns each element of @a x compared not equal to the corresponding element of @a y. */
						static bool_vector_type not_equal_to (vector_type x, vector_type y)
							{
								bool_vector_type equal = vec_cmpeq (x, y);
								return vec_nor (equal, equal);
							}
				
						/** Returns each element of @a x compared equal to the corresponding element of @a y. */
						static bool_vector_type equal_to (vector_type x, vector_type y)	{ return vec_cmpeq (x, y); }
						
						/** Returns each element of @a x compared less than the corresponding element of @a y. */
						static bool_vector_type less (vector_type x, vector_type y)		{ return vec_cmplt (x, y); }
						
						/** Returns each element of @a x compared greater than the corresponding element of @a y. */
						static bool_vector_type greater (vector_type x, vector_type y) 	{ return vec_cmpgt (x, y); }
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for Altivec integer types.
				 * @param Type The scalar type.
				 */
				template <typename Type> struct altivec_integer_traits: public altivec_number_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::bool_vector_type bool_vector_type;
						typedef typename altivec_base_traits <Type>::unsigned_vector_type unsigned_vector_type;

						/*
						static vector_type divides (vector_type x, vector_type y)
							{
								return divider (x, y, NULL);
							}
							
						static vector_type modulus (vector_type x, vector_type y)
							{
								vector_type mod;
								divider (x, y, &mod);
								return mod;
							}
						*/

						/** Returns each element of @a x shifted left by the corresponding element of @a y. */
						static vector_type left_shift (vector_type x, vector_type y)
							{
								return vec_sl (x, (unsigned_vector_type) y);
							}
													
						/** Returns each element of @a x compared less than or equal to the corresponding element of @a y. */
						static bool_vector_type less_equal (vector_type x, vector_type y)
							{
								bool_vector_type greater = vec_cmpgt (x, y);
								return vec_nor (greater, greater);
							}
						
						/** Returns each element of @a x compared greater than or equal to the corresponding element of @a y. */
						static bool_vector_type greater_equal (vector_type x, vector_type y)
							{
								bool_vector_type less = vec_cmplt (x, y);
								return vec_nor (less, less);
							}
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for all Altivec char types.
				 * @param Type The scalar type, either <code>char</code> or <code>unsigned char</code>.
				 */
				template <class Type> struct altivec_char_traits: public altivec_integer_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::value_type value_type;
						typedef typename altivec_base_traits <Type>::union_type union_type;
						
						typedef typename to_vector <from_vector <vector_type>::spec, 2>::vector_type short_vector_type;
						typedef typename to_vector <from_vector <vector_type>::spec, 4>::vector_type long_vector_type;
						
						/** Returns each element of @a x multiplied by the corresponding element of @a y. */
						static vector_type multiplies (vector_type x, vector_type y)
							{
								short_vector_type p1 = vec_mule (x, y);
								short_vector_type p2 = vec_mulo (x, y);
								return static_cast <vector_type> (vec_mergel (vec_pack (p1, p1), vec_pack (p2, p2)));
							}
							
						/** Returns the sum of the elements of @a x. */
						static value_type sum (vector_type x)
							{
								union_type result;
								result.vec = static_cast <vector_type> (vec_sums (
									static_cast <__vector signed int> (vec_sum4s (x, from_vector <long_vector_type>::zero ())),
									(__vector signed int) (0)));
								
								return result.val [15];
							}

						using impl::altivec_number_traits <Type>::max;
						using impl::altivec_number_traits <Type>::min;

						/** Returns the maximum element of @a x. */
						static value_type max (vector_type x)
							{
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (8)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (16)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
				
						/** Returns the minimum element of @a x. */
						static value_type min (vector_type x)
							{
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (8)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (16)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
					};
				
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for all Altivec short types.
				 * @param Type The scalar type, either <code>short</code> or <code>unsigned short</code>.
				 */
				template <class Type> struct altivec_short_traits: public altivec_integer_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::value_type value_type;
						typedef typename altivec_base_traits <Type>::union_type union_type;
						
						/** Returns each element of @a x multiplied by the corresponding element of @a y. */
						static vector_type multiplies (vector_type x, vector_type y)
							{
								return vec_mladd (x, y, zero ());
							}
							
						using impl::altivec_number_traits <Type>::max;
						using impl::altivec_number_traits <Type>::min;

						/** Returns the maximum element of @a x. */
						static value_type max (vector_type x)
							{
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (16)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
				
						/** Returns the minimum element of @a x. */
						static value_type min (vector_type x)
							{
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (16)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}

					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for Altivec long types.
				 * @param Type The scalar type, either <code>long</code> or <code>unsigned long</code>.
				 */
				template <class Type> struct altivec_long_traits: public altivec_integer_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::value_type value_type;
						typedef typename altivec_base_traits <Type>::union_type union_type;

						/** Returns the sum of the elements of @a x. */
						static value_type sum (vector_type x)
							{
								x = vec_add (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_add (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
				
						using impl::altivec_integer_traits <Type>::max;
						using impl::altivec_integer_traits <Type>::min;

						/** Returns the maximum element of @a x. */
						static value_type max (vector_type x)
							{
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_max (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
				
						/** Returns the minimium element of @a x. */
						static value_type min (vector_type x)
							{
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (32)));
								x = vec_min (x, vec_slo (x, (__vector unsigned char) (64)));
				
								union_type result;
								result.vec = x;
								return result.val [0];
							}
						
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Traits base for Altivec boolean types.
				 * @param Type The scalar type, one of macstl::boolean.
				 */
				template <class Type> struct altivec_bool_traits: public altivec_builtin_traits <Type>
					{
						typedef typename altivec_base_traits <Type>::vector_type vector_type;
						typedef typename altivec_base_traits <Type>::value_type value_type;
						
						/** Returns the absolute value of each element of @a x. */
						static vector_type abs (vector_type x)							{ return x; }
						
						/** Returns the negation of each element of @a x. */
						static vector_type negate (vector_type x)						{ return x; }
				
						/** Returns each element of @a x added to the corresponding element of @a y. */
						static vector_type plus (vector_type x, vector_type y)			{ return vec_or (x, y); }
						
						/** Returns each element of @a x subtracted by the corresponding element of @a y. */
						static vector_type minus (vector_type x, vector_type y)			{ return vec_xor (x, y); }
				
						/** Returns the maximum of each element of @a x and the corresponding element of @a y. */
						static vector_type max (vector_type x, vector_type y)			{ return vec_or (x, y); }
						
						/** Returns the minimum of each element of @a x and the corresponding element of @a y. */
						static vector_type min (vector_type x, vector_type y)			{ return vec_and (x, y); }
					
						/** Returns the logical NOT of each element of @a x. */
						static vector_type logical_not (vector_type x)					{ return vec_nor (x, x); }
						
						/** Returns the logical AND of each element of @a x and the corresponding element of @a y. */
						static vector_type logical_and (vector_type x, vector_type y)	{ return vec_and (x, y); }
						
						/** Returns the logical OR of each element of @a x and the corresponding element of @a y. */
						static vector_type logical_or (vector_type x, vector_type y)	{ return vec_or (x, y); }
				
						/** Returns each element of @a x compared equal to the corresponding element of @a y. */
						static vector_type equal_to (vector_type x, vector_type y)
							{
								vector_type unequal = vec_xor (x, y);
								return vec_nor (unequal, unequal);
							}
						
						/** Returns each element of @a x compared not equal to the corresponding element of @a y. */
						static vector_type not_equal_to (vector_type x, vector_type y)	{ return vec_xor (x, y); }
				
						/** Returns each element of @a x compared less than the corresponding element of @a y. */
						static vector_type less (vector_type x, vector_type y)			{ return vec_andc (y, x); }
						
						/** Returns each element of @a x compared greater than the corresponding element of @a y. */
						static vector_type greater (vector_type x, vector_type y)		{ return vec_andc (x, y); }
				
						/** Returns each element of @a x compared less than or equal to the corresponding element of @a y. */
						static vector_type less_equal (vector_type x, vector_type y)	{ return vec_or (vec_nor (x, x), y); }
						
						/** Returns each element of @a x compared greater than or equal to the corresponding element of @a y. */
						static vector_type greater_equal (vector_type x, vector_type y)	{ return vec_or (x, vec_nor (y, y)); }
						
						/** Returns sum of the elements of @a x. */
						static value_type sum (vector_type x)	{ value_type result; result = vec_any_ne (x, zero ()); return result; }
						
						/** Returns the minimum element of @a x. */
						static value_type min (vector_type x)	{ value_type result; result = vec_all_ne (x, zero ()); return result; }
						
						/** Returns the maximum element of @a x. */
						static value_type max (vector_type x)	{ value_type result; result = vec_any_ne (x, zero ()); return result; }
					};
		
			}
			
		// altivec_traits
		
		template <class Type> struct altivec_traits;
				
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec floats.
		 *
		 * A traits class for <code>vector float</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<float\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <float>: public impl::altivec_number_traits <float>
			{
				/** Returns the reciprocal of each element of @a x. */
				static __vector float r (__vector float x)
					{
						// estimate reciprocal then do one pass of Newton-Raphson
						__vector float estimate = vec_re (x);
						return vec_madd (vec_nmsub (estimate, x, (__vector float) (1.0)), estimate, estimate);
					}
					
				/** Returns the reciprocal square root of each element of @a x. */
				static __vector float rsqrt (__vector float x)
					{
						// estimate reciprocal square root then do one pass of Newton-Raphson
						__vector float estimate = vec_rsqrte (x);
						return vec_madd (
							vec_nmsub (x, vec_madd (estimate, estimate, (__vector float) (0.0)), (__vector float) (1.0)),
							vec_madd (estimate, (__vector float) (0.5), (__vector float) (0.0)),
							estimate);
					}
				
				/** Returns each element of @a x multiplied by the corresponding element of @a y. */
				static __vector float multiplies (__vector float x, __vector float y)
					{
						return vec_madd (x, y, (__vector float) (0.0));
					}
					
				/** Returns each element of @a x divided by the corresponding element of @a y. */
				static __vector float divides (__vector float x, __vector float y)
					{
						return vec_madd (x, r (y), (__vector float) (0.0));
					}
					
				/** Returns each element of @a x compared less than or equal to the corresponding element of @a y. */
				static __vector bool int less_equal (__vector float x, __vector float y)	{ return vec_cmple (x, y); }
				
				/** Returns each element of @a x compared greater than or equal to the corresponding element of @a y. */
				static __vector bool int greater_equal (__vector float x, __vector float y)	{ return vec_cmpge (x, y); }
				
				/** Returns the square root of each element of @a x. */
				static __vector float sqrt (__vector float x)
					{
						return vec_madd (x, rsqrt (x), (__vector float) (0.0));
					}

				using impl::altivec_number_traits <float>::max;
				using impl::altivec_number_traits <float>::min;

				/** Returns the sum of the elements of @a x. */
				static float sum (__vector float x)
					{
						x = vec_add (x, vec_slo (x, (__vector unsigned char) (32)));
						x = vec_add (x, vec_slo (x, (__vector unsigned char) (64)));
		
						union_type result;
						result.vec = x;
						return result.val [0];
					}
					
				/** Returns the maximum element of @a x. */
				static float max (__vector float x)
					{
						x = vec_sel (static_cast <__vector float> ((vector unsigned int) (0xFF800000)), x, vec_cmpeq (x, x));
						x = vec_max (x, vec_slo (x, (__vector unsigned char) (32)));
						x = vec_max (x, vec_slo (x, (__vector unsigned char) (64)));
		
						union_type result;
						result.vec = x;
						return result.val [0];
					}
		
				/** Returns the minimum element of @a x. */
				static float min (__vector float x)
					{
						x = vec_sel (static_cast <__vector float> ((vector unsigned int) (0x7F800000)), x, vec_cmpeq (x, x));
						x = vec_min (x, vec_slo (x, (__vector unsigned char) (32)));
						x = vec_min (x, vec_slo (x, (__vector unsigned char) (64)));
		
						union_type result;
						result.vec = x;
						return result.val [0];
					}
					
					// hopefully we can replace some of these with inline versions...
					
				static __vector float cos (__vector float x)	{ return vcosf (x); }
				static __vector float acos (__vector float x)	{ return vacosf (x); }
				static __vector float cosh (__vector float x)	{ return vcoshf (x); }
				static __vector float sin (__vector float x)	{ return vsinf (x); }
				static __vector float asin (__vector float x)	{ return vasinf (x); }
				static __vector float sinh (__vector float x)	{ return vsinhf (x); }
				static __vector float tan (__vector float x)	{ return vtanf (x); }
				static __vector float tanh (__vector float x)	{ return vtanhf (x); }
				static __vector float atan (__vector float x)	{ return vatanf (x); }
				static __vector float exp (__vector float x)	{ return vexpf (x); }
				static __vector float log (__vector float x)	{ return vlogf (x); }
				
				static __vector float atan2 (__vector float x, __vector float y)	{ return vatan2f (x, y); }
				static __vector float pow (__vector float x, __vector float y)		{ return vpowf (x, y); }
			};
			
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec unsigned chars.
		 *
		 * A traits class for <code>vector unsigned char</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<unsigned char\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <unsigned char>: public impl::altivec_char_traits <unsigned char>
			{
				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector unsigned char right_shift (__vector unsigned char x, __vector unsigned char y)
					{
						return vec_sr (x, y);
					}
			};
		
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec chars.
		 *
		 * A traits class for <code>vector signed char</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<char\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <char>: public impl::altivec_char_traits <char>
			{
				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector signed char right_shift (__vector signed char x, __vector signed char y)
					{
						return vec_sra (x, (__vector unsigned char) y);
					}
			};
		
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec unsigned shorts.
		 *
		 * A traits class for <code>vector unsigned short</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<unsigned short\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <unsigned short>: public impl::altivec_short_traits <unsigned short>
			{
				typedef impl::altivec_base_traits <unsigned short>::union_type union_type;

				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector unsigned short right_shift (__vector unsigned short x, __vector unsigned short y)
					{
						return vec_sr (x, y);
					}
				
				/** Returns the sum of the elements of @a x. */
				static unsigned short sum (__vector unsigned short x)
					{
						union_type result;
						result.vec = static_cast <__vector unsigned short> (vec_sums (vec_sum4s (
							vec_sub (static_cast <__vector signed short> (x), (__vector signed short) (-0x8000)),
							(__vector signed int) (0)), 
							(__vector signed int) (0x40000)));
						return result.val [7];
					}
			};
		
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec signed shorts.
		 *
		 * A traits class for <code>vector signed short</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<short\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <short>: public impl::altivec_short_traits <short>
			{
				typedef union_type union_type;

				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector signed short right_shift (__vector signed short x, __vector signed short y)
					{
						return vec_sra (x, static_cast <__vector unsigned short> (y));
					}
				
				/** Returns each element of @a x divided by the corresponding element of @a y. */
				static __vector signed short divide (__vector signed short x, __vector signed short y)
					{
						// calculate signed 0.15 fixed point representation of reciprocal of y
						// then multiply x by it
						__vector signed short reciprocal = vec_packs (
								vec_cts (altivec_traits <float>::r (vec_ctf (vec_unpackh (y), 0)), 15),
								vec_cts (altivec_traits <float>::r (vec_ctf (vec_unpackl (y), 0)), 15));
							
						return vec_mradds (x, reciprocal, (__vector signed short) (0));
					}
		
				/** Returns the sum of the elements of @a x. */
				static short sum (__vector signed short x)
					{
						union_type result;
						result.vec = static_cast <__vector signed short> (vec_sums (
							vec_sum4s (x, (__vector signed int) (0)), (__vector signed int) (0)));
						return result.val [7];
					}
			};
		
		/**
		 * @brief Traits for Altivec unsigned longs.
		 *
		 * A traits class for <code>vector unsigned int</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<unsigned long\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <unsigned long>: public impl::altivec_long_traits <unsigned long>
			{
				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector unsigned int right_shift (__vector unsigned int x, __vector unsigned int y)
					{
						return vec_sr (x, y);
					}

				/** Returns each element of @a x multiplied by the corresponding element of @a y. */
				static __vector unsigned int multiplies (__vector unsigned int x, __vector unsigned int y)
					{
						__vector unsigned int sixteen = vec_splat_u32 (-16);
						
						// low order of result = low order of x * low order of y
						__vector unsigned int low = vec_mulo (
							static_cast <__vector unsigned short> (x),
							static_cast <__vector unsigned short> (y));
								
						// high order of result = low order of x * high order of y + low order of y * high order of x
						__vector unsigned int high = vec_msum (
							static_cast <__vector unsigned short> (x),
							static_cast <__vector unsigned short> (vec_rl (y, sixteen)), (__vector unsigned int) (0));
								
						return vec_add (vec_sl (high, sixteen), low);
					}
			};
		
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec signed longs.
		 *
		 * A traits class for <code>vector signed int</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<long\> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <long>: public impl::altivec_long_traits <long>
			{
				/** Returns each element of @a x shifted right by the corresponding element of @a y. */
				static __vector signed int right_shift (__vector signed int x, __vector signed int y)
					{
						return vec_sra (x, static_cast <__vector unsigned int> (y));
					}

				/** Returns each element of @a x multiplied by the corresponding element of @a y. */
				static __vector signed int multiplies (__vector signed int x, __vector signed int y)
					{
						// unsigned multiply
						__vector signed int result = static_cast <__vector signed int>
							(altivec_traits <unsigned long>::multiplies (
							static_cast <__vector unsigned int> (vec_abs (x)),
							static_cast <__vector unsigned int> (vec_abs (y))));
							
						// if both signs negative or positive, select the unsigned result
						// if one sign negative and the other positive, select the negative of the unsigned result
						return vec_sel (result,
							vec_sub ((__vector signed int) (0), result),
							vec_cmpgt ((__vector signed int) (0), vec_xor (x, y)));
					}
			};
			
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec boolean chars.
		 *
		 * A traits class for <code>vector bool char</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<macstl::boolean \<char\> \> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <boolean <char> >: public impl::altivec_bool_traits <boolean <char> >
			{
			};
			
		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec boolean shorts.
		 *
		 * A traits class for <code>vector bool short</code>. It organizes related data types and systematically names available operations, thus
		 * It provides the implementation of the macstl::altivec \<macstl::boolean \<short\> \> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <boolean <short> >: public impl::altivec_bool_traits <boolean <short> >
			{
			};

		/**
		 * @ingroup altivec_public
		 * @brief Traits for Altivec boolean longs.
		 *
		 * A traits class for <code>vector bool int</code>. It organizes related data types and systematically names available operations, thus
		 * providing the implementation of the macstl::altivec \<macstl::boolean \<long\> \> interface. You may use this class for direct operations on Altivec vectors.
		 */
		template <> struct altivec_traits <boolean <long> >: public impl::altivec_bool_traits <boolean <long> >
			{
			};

	}
	
#endif