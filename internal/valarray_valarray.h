/*
 *  valarray_valarray.h
 *  macstl
 *
 *  Created by Glen Low on Sun Jun 22 2003.
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

namespace impl
	{
		template <typename Val> class valarray_base: public array <Val>
			{
				public:
					~valarray_base ()
						{
							free (begin ());
						}
			
				protected:
					valarray_base (size_t n):
						array <Val> (reinterpret_cast <Val*> (malloc (sizeof (Val) * n)), n)
						{
						}
			};
			
	};
	
namespace std
	{
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
																									\
		valarray& FUNC (const value_type& other)													\
			{																						\
				for_each_array (*this, impl::right_scalar <OPER>::operation <value_type> (other));	\
				return *this;																		\
			}																						\
																									\
		template <typename Expr> valarray& FUNC (const impl::term <value_type, Expr>& other)	\
			{																						\
				for_each_array (*this, other.expr (), impl::function <OPER>::operation <value_type> ());	\
				return *this;																		\
			}

		template <typename Val> class valarray: public impl::valarray_base <Val>
			{
				public:
					typedef typename valarray::value_type value_type;
					
					// 26.3.2.1 lib.valarray.cons
					
					valarray (): impl::valarray_base <Val> (0)
						{
						}
						
					explicit valarray (size_t n): impl::valarray_base <Val> (n)
						{
							impl::uninitialized_fill_array (*this, value_type ());
						}
						
					valarray (const value_type& x, size_t n): impl::valarray_base <Val> (n)
						{
							impl::uninitialized_fill_array (*this, x);
						}
		
					valarray (const value_type* x, size_t n): impl::valarray_base <Val> (n)
						{
							stdext::uninitialized_copy_n (x, n, begin ());
						}
		
					valarray (const valarray& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
		
					template <typename Expr> valarray (const impl::term <value_type, Expr>& other):
						impl::valarray_base <Val> (other.expr ().size ())
						{
							impl::uninitialized_copy_array (*this, other.expr ());
						}
						
					valarray (const slice_array <Val>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
					
					template <typename BExpr> valarray (const mask_array <Val, BExpr>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
					
					template <typename InExpr> valarray (const indirect_array <Val, InExpr>& other): impl::valarray_base <Val> (other.size ())
						{
							impl::uninitialized_copy_array (*this, other);
						}
		
					~valarray ()
						{
							std::_Destroy (begin (), begin () + size ());
						}
						
					// 26.3.2.2 lib.valarray.assign
					
					valarray& operator= (const valarray& other)
						{
							if (this != &other)
								impl::copy_array (*this, other);
							return *this;
						}
						
					template <typename Expr> valarray& operator= (const impl::term <value_type, Expr>& other)
						{
							impl::copy_array (*this, other.expr ());
							return *this;
						}
						
					valarray& operator= (const value_type& x)				{ impl::fill_array (*this, x); return *this; }		

					valarray& operator= (const slice_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
					valarray& operator= (const gslice_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
					valarray& operator= (const mask_array <Val>& other)		{ impl::copy_array (*this, other); return *this; }
					valarray& operator= (const indirect_array <Val>& other)	{ impl::copy_array (*this, other); return *this; }
		
					// 26.3.2.6 lib.valarray.cassign
					
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
		
					// 26.3.2.7 lib.valarray.members
					
					void resize (size_t size, const value_type& x = value_type ())
						{
							valarray resized (x, size);
							swap (resized);
						}

			};
	};
