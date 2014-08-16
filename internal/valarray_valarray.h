/*
 *  valarray_valarray.h
 *  macstl
 *
 *  Created by Glen Low on Sun Jun 22 2003.
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

#ifndef MACSTL_INTERNAL_VALARRAY_VALARRAY_H
#define MACSTL_INTERNAL_VALARRAY_VALARRAY_H

namespace std
	{
		namespace impl
			{
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Allocating base for valarray.
				 * @param Val The value type, see std::valarray.
				 *
				 * This class allocates but does not initialize memory, so that its subclass std::valarray
				 * will not leak memory if an exception is thrown during construction. Partial specializations
				 * may allocate different amounts of memory.
				 */
				template <typename Val> class valarray_base: public array <Val>
					{
						protected:
							/** Constructs with space for @a n elements. */
							valarray_base (size_t n):
								array <Val> (reinterpret_cast <Val*> (malloc (sizeof (Val) * n)), n)
								{
								}

							/** Destructs entire array. */
							~valarray_base ()
								{
									free (begin ());
								}
					};
					
			}

		// gcc or C++ (?) sometimes has trouble matching a std::valarray <T> with fixed T to these functions,
		// so we bring them into this scope to make life easier for the compiler...
		using impl::operator*;
		using impl::operator/;
		using impl::operator%;            
		using impl::operator+;
		using impl::operator-;
		using impl::operator^;
		using impl::operator&;
		using impl::operator|;
		using impl::operator<<;
		using impl::operator>>; 
		
		using impl::operator==;
		using impl::operator!=;
		using impl::operator<;
		using impl::operator>;
		using impl::operator<=;
		using impl::operator>=;
		using impl::operator&&;
		using impl::operator||;
		
		using impl::abs;
		using impl::acos;
		using impl::asin;
		using impl::atan;
		using impl::atan2;
		using impl::cos;
		using impl::cosh;
		using impl::exp;
		using impl::log;
		using impl::log10;
		using impl::pow;
		using impl::sin;
		using impl::sinh;
		using impl::sqrt;
		using impl::tan;
		using impl::tanh;

		#define __MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION(FUNC, OPER)								\
		/** Peforms <code>FUNC</code> with scalar @a other. */										\
		valarray& FUNC (const value_type& other)													\
			{																						\
				for_each_array (*this, impl::right_scalar <OPER>::operation <value_type> (OPER <value_type> (), other));	\
				return *this;																		\
			}																						\
		/** Performs <code>FUNC</code> with each element of @a other. */							\
		template <typename Expr> valarray& FUNC (const impl::term <value_type, Expr>& other)		\
			{																						\
				for_each_array (*this, other.expr (), OPER <value_type> ());	\
				return *this;																		\
			}

		/**
		 * @class valarray macvalarray.h
		 * @ingroup valarray_public
		 * @brief Numeric (n-at-a-time) arrays.
		 * @param Val The value type, which shall satisfy the following requirements:
		 * - Not an abstract class, reference type or cv-qualified type;
		 * - A class must publicly define: default constructor, copy constructor, destructor and assignment operator;
		 * - Default construction + assignment == copy construction;
		 * - Destruction + copy construction == assignment.
		 * .
		 * For example, built-in arithmetic types like char, short, long, float, double.
		 *
		 * To allow for improved performance, any function returning a valarray may substitute an object
		 * of others types, provided that all functions that accept a const valarray also accept those
		 * types. macstl uses the various subclasses of term as the substituted type; the technique is
		 * known as <em>expression templates</em>.
		 */
		template <typename Val> class valarray: public impl::valarray_base <Val>
			{
				public:
					typedef typename impl::valarray_base <Val>::value_type value_type;	/**< The value type. */
					
					/**
					 * @name constructors
					 * 26.3.2.1 [lib.valarray.cons]
					 */
					
					//@{
					
					/** Constructs a zero-length array. */
					valarray (): impl::valarray_base <Val> (0)
						{
						}
						
					/** Constructs an array of @a n elements, each default-constructed. */
					explicit valarray (size_t n): impl::valarray_base <Val> (n)
						{
							impl::uninitialized_fill_array (*this, Val ());
						}
						
					/** Constructs an array of @a n elements, each copied from @a x. */
					valarray (const Val& x, size_t n): impl::valarray_base <Val> (n)
						{
							impl::uninitialized_fill_array (*this, x);
						}
		
					/** Constructs an array of the first @a n elements copied from @a x. */
					valarray (const Val* x, size_t n): impl::valarray_base <Val> (n)
						{
							stdext::uninitialized_copy_n (x, n, begin ());
						}
		
					/** Constructs a copy of @a other. */
					valarray (const valarray& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
		
					/** Constructs a copy of @a other. */
					template <typename Expr> valarray (const impl::term <Val, Expr>& other):
						impl::valarray_base <Val> (other.expr ().size ())
						{
							impl::uninitialized_copy_array (*this, other.expr ());
						}
						
					/** Constructs from the sliced elements of @a other. */
					valarray (const slice_array <Val>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
					
					/** Constructs from the masked elements of @a other. */
					template <typename BExpr> valarray (const mask_array <Val, BExpr>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
					
					/** Constructs from the indirected elements of @a other. */
					template <typename InExpr> valarray (const indirect_array <Val, InExpr>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
		
					/** Destructs entire array. */
					~valarray ()
						{
							stdext::destroy_n (begin (), size ());
						}
					
					//@}
					
					/**
					 * @name assignments
					 * 26.3.2.2 [lib.valarray.assign]
					 */
					 
					//@{
					
					/** Assigns @a other to entire array. */
					valarray& operator= (const valarray& other)
						{
							if (this != &other)
								impl::copy_array (*this, other);
							return *this;
						}
						
					/** Assigns @a other to entire array. */
					template <typename Expr> valarray& operator= (const impl::term <Val, Expr>& other)
						{
							impl::copy_array (*this, other.expr ());
							return *this;
						}
						
					/** Assigns @a x to each element. */
					valarray& operator= (const value_type& x)				{ impl::fill_array (*this, x); return *this; }		

					/** Assigns sliced elements of @a other to entire array. */
					valarray& operator= (const slice_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
					
					/** Assigns gsliced elements of @a other to entire array. */
					valarray& operator= (const gslice_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
					
					/** Assigns masked elements of @a other to entire array. */
					valarray& operator= (const mask_array <Val>& other)		{ impl::copy_array (*this, other); return *this; }
					
					/** Assigns indirected elements of @a other to entire array. */
					valarray& operator= (const indirect_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
		
					//@}
					
					/**
					 * @name computed assignments
					 * 26.3.2.6 [lib.valarray.cassign]
					 */
					
					//@{
					
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator*=, stdext::multiplies_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator/=, stdext::divides_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator%=, stdext::modulus_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator+=, stdext::plus_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator-=, stdext::minus_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator^=, stdext::bitwise_xor_assign)			
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator&=, stdext::bitwise_and_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator|=, stdext::bitwise_or_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator<<=, stdext::left_shift_assign)
					__MACSTL_DEFINE_VALARRAY_CASSIGN_FUNCTION (operator>>=, stdext::right_shift_assign)
		
					//@}
					
					/**
					 * @name resize
					 * 26.3.2.7/9 [lib.valarray.members]
					 */
					
					//@{
					
					/** Changes the array size to @a n, assigning @a x to each element. */
					void resize (size_t n, const value_type& x = value_type ())
						{
							valarray resized (x, n);
							swap (resized);
						}

					//@}
			};
	}
	
#endif
