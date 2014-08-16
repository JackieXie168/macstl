/*
 *  macvalarray.h
 *  macstl
 *
 *  Created by Glen Low on Fri Mar 14 2003.
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
 * @file macvalarray.h
 * @ingroup valarray_public
 * @brief Valarray and lib.numerics classes
 *
 * Declares the std::valarray class and associated lib.numerics classes.
 */

#ifndef MACSTL_MACVALARRAY_H
#define MACSTL_MACVALARRAY_H

#include <functional>

#include <internal/retraits.h>
#include <extension/algorithm.h>
#include <extension/functional.h>

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
		
				enum yes_no
					{
						yes = 1,
						no = 2
					};
					
				struct nothing { };
				
				template <typename Term> char (*has_const_chunk_iterator (typename Term::const_chunk_iterator*)) [yes];
				template <typename Term> char (*has_const_chunk_iterator (...)) [no];
				
				template <typename Term> char (*has_chunk_iterator (typename Term::chunk_iterator*)) [yes];
				template <typename Term> char (*has_chunk_iterator (...)) [no];
								
				template <typename Term> struct const_chunkable
					{
						enum { value = sizeof (*has_const_chunk_iterator <Term> (NULL)) == yes };
					};
		
				template <typename Term> struct chunkable
					{
						enum { value = sizeof (*has_chunk_iterator <Term> (NULL)) == yes };
					};
					
				template <typename Type, bool is_const_chunkable = const_chunkable <Type>::value> struct const_chunk_type;
				
				template <typename Type> struct const_chunk_type <Type, false>
					{
						typedef nothing type;
					};

				template <typename Type> struct const_chunk_type <Type, true>
					{
						typedef typename std::iterator_traits <typename Type::const_chunk_iterator>::value_type type;
					};
					
				template <typename Type, bool is_chunkable = chunkable <Type>::value> struct chunk_type;
				
				template <typename Type> struct chunk_type <Type, false>
					{
						typedef nothing type;
					};

				template <typename Type> struct chunk_type <Type, true>
					{
						typedef typename std::iterator_traits <typename Type::chunk_iterator>::value_type type;
					};
					
				template <typename Type1, typename Type2> struct same_type
					{
						enum { value = false };
					};
					
				template <typename Type> struct same_type <Type, Type>
					{
						enum { value = true };
					};
					
				template <typename Term1, typename Term2> struct const_rechunkable
					{
						enum { value = same_type <typename const_chunk_type <Term1>::type, typename const_chunk_type <Term2>::type>::value };
					};
		
				template <typename Term1, typename Term2> struct rechunkable
					{
						enum { value = same_type <typename chunk_type <Term1>::type, typename const_chunk_type <Term2>::type>::value };
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
							
							void operator() (const Type& val)			{ result_ = min (result_, val); }
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
							
							void operator() (const Type& val)		{ result_ = max (result_, val); }
							Type result () const					{ return result_; }
							
						private:
							Type result_;
					};
				
				template <typename Type1, typename Type2, template <typename> class Func>
					Func <Type1> enchunk (const Func <Type2>&)
					{
						return Func <Type1> ();
					}
		
				template <typename Type1, typename Type2, template <typename> class Func>
					stdext::binder1st <Func <Type1> > enchunk (const stdext::binder1st <Func <Type2> >& unchunked)
					{
						return stdext::bind1st (Func <Type1> (), static_cast <Type1> (unchunked.bound ()));
					}
		
				template <typename Type1, typename Type2, template <typename> class Func>
					stdext::binder2nd <Func <Type1> > enchunk (const stdext::binder2nd <Func <Type2> >& unchunked)
					{
						return stdext::bind2nd (Func <Type1> (), static_cast <Type1> (unchunked.bound ()));
					}

					
			}
	}

#include <internal/valarray_algorithm.h>
#include <internal/valarray_base.h>
#include <internal/valarray_function.h>
#include <internal/valarray_shift.h>
#include <internal/valarray_valarray.h>
#include <internal/valarray_slice.h>

#ifdef __VEC__
#include <internal/valarray_altivec.h>
#endif

#include <internal/valarray_gslice.h>
#include <internal/valarray_mask.h>
#include <internal/valarray_indirect.h>

#endif
