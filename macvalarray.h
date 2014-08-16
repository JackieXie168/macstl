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
		template <typename Expr> class slice_array;
		template <typename Val> class gslice_array;
		template <typename Val, typename BExpr = std::valarray <bool> > class mask_array;
		template <typename Val, typename InExpr = std::valarray <size_t> > class indirect_array;
	};
	
namespace impl
	{
		// forward declares
		
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

		// whether a term is const chunkable or chunkable (SFINAE...)

		struct yes { char ch [1]; };
		struct no {char ch [100]; };
		struct nothing { };
		
		template <typename Term> yes has_const_chunk_iterator (typename Term::const_chunk_iterator*);
		template <typename Term> no has_const_chunk_iterator (...);
		
		template <typename Term> yes has_chunk_iterator (typename Term::chunk_iterator*);
		template <typename Term> no has_chunk_iterator (...);
		
		template <typename Type> yes same_type (Type, Type);
		template <typename Type1, typename Type2> no same_type (Type1, Type2);
		template <typename Term> typename std::iterator_traits <typename Term::chunk_iterator>::value_type
			chunk_type (typename Term::chunk_iterator*);
		template <typename Term> nothing chunk_type (...);
		template <typename Term> typename std::iterator_traits <typename Term::const_chunk_iterator>::value_type
			const_chunk_type (typename Term::const_chunk_iterator*);
		template <typename Term> nothing const_chunk_type (...);
		
		template <typename Term> struct const_chunkable
			{
				enum { value = sizeof (has_const_chunk_iterator <Term> (NULL)) == sizeof (yes) };
			};

		template <typename Term> struct chunkable
			{
				enum { value = sizeof (has_chunk_iterator <Term> (NULL)) == sizeof (yes) };
			};
			
		template <typename Term1, typename Term2> struct const_rechunkable
			{
				enum { value = sizeof (same_type (const_chunk_type <Term1> (NULL), const_chunk_type <Term2> (NULL))) == sizeof (yes) };
			};

		template <typename Term1, typename Term2> struct rechunkable
			{
				enum { value = sizeof (same_type (chunk_type <Term1> (NULL), const_chunk_type <Term2> (NULL))) == sizeof (yes) };
			};
			
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
			
		// dereferences: used in iterators whose operator* and operator[] could either return a value or a reference
		
		template <typename Type> struct dereference
			{
				typedef Type type;
			};
			
		template <typename Type> struct dereference <const Type&>
			{
				typedef Type type;
			};
		
		// scalarizations
		
		template <typename Type> class summate
			{
				public:
					summate (const Type& init): result_ (init)
						{
						}
					
					template <typename ReType> summate (const summate <ReType>& other):
						result_ (other.result ().sum ())
						{
						}
						
					void operator() (const Type& val)			{ result_ += val; }
					Type result () const						{ return result_; }
					
				private:
					Type result_;
			};
			

		template <typename Type> class minimize
			{
				public:
					minimize (const Type& init): result_ (init)
						{
						}	
										
					template <typename ReType> minimize (const minimize <ReType>& other):
						result_ (other.result ().min ())
						{
						}
					
					void operator() (const Type& val)			{ result_ = std::min (result_, val); }
					Type result () const						{ return result_; }

				private:
					Type result_;
			};
			

		template <typename Type> class maximize
			{
				public:
					maximize (const Type& init): result_ (init)
						{
						}

					template <typename ReType> maximize (const maximize <ReType>& other):
						result_ (other.result ().max ())
						{
						}
					
					void operator() (const Type& val)		{ result_ = std::max (result_, val); }
					Type result () const					{ return result_; }
					
				private:
					Type result_;
			};
					
	};

#include <valarray_algorithm.h>
#include <valarray_base.h>
#include <valarray_function.h>
#include <valarray_shift.h>
#include <valarray_valarray.h>
#include <valarray_slice.h>

#ifdef __VEC__
#include <valarray_altivec.h>
#endif

#include <valarray_gslice.h>
#include <valarray_mask.h>
#include <valarray_indirect.h>
