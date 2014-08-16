/*
 *  macvalarray.h
 *  macstl
 *
 *  Created by Glen Low on Fri Mar 14 2003.
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

#include <functional>
#include <algorithm.h>
#include <functional.h>

namespace std
	{
		// each valarray transcendental function must call the identically named function on its scalar value; since the valarray functions
		// are defined in namespace std, they could resolve those scalar versions to std namespace, global namespace or by Koenig lookup.
		// Since we're using function objects to abstract them, the objects have to be declared within std to get the required lookup behavior.
		
		#define __MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION(FUNC)			\
																				\
		template <typename Val> struct __##FUNC: std::unary_function <Val, Val>	\
			{																	\
				Val operator() (const Val& x) const { return FUNC (x); }		\
			};
		
		#define __MACSTL_DEFINE_VALARRAY_BINARY_SCALAR_FUNCTION(FUNC)						\
																							\
		template <typename Val> struct __##FUNC: std::binary_function <Val, Val, Val>		\
			{																				\
				Val operator() (const Val& x, const Val& y) const { return FUNC (x, y); }	\
			};
		
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (abs)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (acos)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (asin)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (atan)
		__MACSTL_DEFINE_VALARRAY_BINARY_SCALAR_FUNCTION (atan2)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (cos)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (cosh)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (exp)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (log)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (log10)
		__MACSTL_DEFINE_VALARRAY_BINARY_SCALAR_FUNCTION (pow)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (sin)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (sinh)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (sqrt)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (tan)
		__MACSTL_DEFINE_VALARRAY_UNARY_SCALAR_FUNCTION (tanh)
		
		class slice;
		class gslice;
		
		template <typename Val> class valarray;
		template <typename Val> class slice_array;
		template <typename Val> class gslice_array;
		template <typename Val, typename BExpr = std::valarray <bool> > class mask_array;
		template <typename Val, typename InExpr = std::valarray <size_t> > class indirect_array;
	};
	
namespace impl
	{
		template <typename Expr, template <typename> class UOp> class unary_term;
		template <typename LExpr, typename RExpr, template <typename> class BOp> class binary_term;

		template <typename Expr> class shift_term;
		template <typename Expr> class cshift_term;
		
		template <typename Expr> class slice_term;
		template <typename Expr> class gslice_term;
		template <typename Expr, typename BExpr> class mask_term;
		template <typename Expr, typename InExpr> class indirect_term;
		
		// ranking iterator categories: given 2 iterator categories we want to know which is least refined
		
		template <typename Cat> struct iterator_category_rank;
		
		template <> struct iterator_category_rank <std::input_iterator_tag>			{ static const int value = 1; };
		template <> struct iterator_category_rank <std::forward_iterator_tag>		{ static const int value = 2; };
		template <> struct iterator_category_rank <std::bidirectional_iterator_tag>	{ static const int value = 3; };
		template <> struct iterator_category_rank <std::random_access_iterator_tag> { static const int value = 4; };
			
		template <int Rank> struct iterator_rank_category;
		
		template <> struct iterator_rank_category <1>	{ typedef std::input_iterator_tag type; };
		template <> struct iterator_rank_category <2>	{ typedef std::forward_iterator_tag type; };
		template <> struct iterator_rank_category <3>	{ typedef std::bidirectional_iterator_tag type; };
		template <> struct iterator_rank_category <4>	{ typedef std::random_access_iterator_tag type; };

		template <typename Cat1, typename Cat2> struct iterator_ranker
			{
				static const int first_category_rank = iterator_category_rank <Cat1>::value;
				static const int second_category_rank = iterator_category_rank <Cat2>::value;
				
				typedef typename iterator_rank_category
					<first_category_rank < second_category_rank ? first_category_rank : second_category_rank>::type	type;
			};

		// whether two types are compatible i.e. assignable or copy constructible from each other
		
		template <typename Type1, typename Type2> struct compatible		{ typedef __false_type type; };
		template <typename Type> struct compatible <Type, Type>			{ typedef __true_type type; };

		// logic on type traits
		
		template <
			typename Type1 = __true_type,
			typename Type2 = __true_type,
			typename Type3 = __true_type,
			typename Type4 = __true_type> struct ander
			{
				typedef __false_type type;
			};
		
		template <> struct ander <__true_type, __true_type, __true_type, __true_type>
			{
				typedef __true_type type;
			};

		// dereferences: used in iterators whose operator* and operator[] could either return a value or a reference
		
		template <typename Type> class dereference
			{
				typedef Type type;
			};
			
		template <typename Type> class dereference <const Type&>
			{
				typedef Type type;
			};
					
		// chunk_traits
		
		template <typename Val> struct chunk_traits
			{
				typedef __false_type const_chunkable;
				typedef __false_type chunkable;
				
				typedef const Val* const_iterator;
				typedef Val* iterator;
				
				static Val* allocate (size_t n)
					{
						return reinterpret_cast <Val*> (malloc (sizeof (Val) * n));
					}
					
				static void deallocate (Val* mem, size_t)
					{
						free (mem);
					}
			};
	};

#include <valarray_algorithm.h>
#include <valarray_base.h>
#include <valarray_function.h>
#include <valarray_shift.h>

#ifdef __VEC__
#include <valarray_altivec.h>
#endif

#include <valarray_valarray.h>
#include <valarray_slice.h>
#include <valarray_gslice.h>
#include <valarray_mask.h>
#include <valarray_indirect.h>


	
