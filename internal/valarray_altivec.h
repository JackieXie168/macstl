/*
 *  valarray_altivec.h
 *  macstl
 *
 *  Created by Glen Low on Wed May 14 2003.
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

#ifndef MACSTL_INTERNAL_VALARRAY_ALTIVEC_H
#define MACSTL_INTERNAL_VALARRAY_ALTIVEC_H

#include <altivec_type.h>

namespace std
	{
		namespace impl
			{
				template <typename Val> class altivec_array_dispatch: public array_base <Val>
					{
						public:
							enum
								{
									chunk_length = sizeof (macstl::altivec <Val>) / sizeof (Val)
								};
								
							typedef const macstl::altivec <Val>* const_chunk_iterator;
							typedef macstl::altivec <Val>* chunk_iterator;
						
							const_chunk_iterator chunk_begin () const
								{
									return reinterpret_cast <const_chunk_iterator> (data_);
								}
		
							chunk_iterator chunk_begin ()
								{
									return reinterpret_cast <chunk_iterator> (data_);
								}
																
						public:
							altivec_array_dispatch (Val* data, size_t size): array_base <Val> (data, size)
								{
									// data must be aligned to 16 byte boundary
									assert ((reinterpret_cast <int> (data) & 0xF) == 0);
								}
					};
		
				template <> class array_dispatch <char>: public altivec_array_dispatch <char>
					{
						protected:
							array_dispatch (char* data, size_t size): altivec_array_dispatch <char> (data, size) { }
					};
					
				template <> class array_dispatch <unsigned char>: public altivec_array_dispatch <unsigned char>
					{
						protected:
							array_dispatch (unsigned char* data, size_t size): altivec_array_dispatch <unsigned char> (data, size) { }
					};
					
				template <> class array_dispatch <short>: public altivec_array_dispatch <short>
					{
						protected:
							array_dispatch (short* data, size_t size): altivec_array_dispatch <short> (data, size) { }
					};
					
				template <> class array_dispatch <unsigned short>: public altivec_array_dispatch <unsigned short>
					{
						protected:
							array_dispatch (unsigned short* data, size_t size): altivec_array_dispatch <unsigned short> (data, size) { }
					};
					
				template <> class array_dispatch <long>: public altivec_array_dispatch <long>
					{
						protected:
							array_dispatch (long* data, size_t size): altivec_array_dispatch <long> (data, size) { }
					};
					
				template <> class array_dispatch <unsigned long>: public altivec_array_dispatch <unsigned long>
					{
						protected:
							array_dispatch (unsigned long* data, size_t size): altivec_array_dispatch <unsigned long> (data, size) { }
					};
					
				template <> class array_dispatch <float>: public altivec_array_dispatch <float>
					{
						protected:
							array_dispatch (float* data, size_t size): altivec_array_dispatch <float> (data, size) { }
					};
				
							
				// boolean specializations: (1) for C++ bool, it is chunkable but not const-chunkable; (2) for altivec-sized booleans,
				// they are both chunkable and const-chunkable
					
				template <> class array_dispatch <bool>: public array_base <bool>
					{
						public:
							/** The sized boolean that has the size same as @c bool. */
							typedef macstl::boolean <
								macstl::impl::from_vector <
								macstl::impl::to_vector <macstl::impl::signed_spec, sizeof (bool)>::vector_type>::value_type>
								boolean;
								
							enum
								{
									chunk_length = sizeof (macstl::altivec <boolean>) / sizeof (bool)
								};
								
							typedef macstl::altivec <boolean>* chunk_iterator;
						
							chunk_iterator chunk_begin ()
								{
									return reinterpret_cast <chunk_iterator> (data_);
								}
								
						protected:
							array_dispatch (bool* data, size_t size): array_base <bool> (data, size)
								{
									// data must be aligned to 16 byte boundary
									assert ((reinterpret_cast <int> (data) & 0xF) == 0);
								}
					};
					
		
				template <typename Type> class array_dispatch <macstl::boolean <Type> >: public altivec_array_dispatch <macstl::boolean <Type> >
					{
						protected:
							array_dispatch (macstl::boolean <Type>* data, size_t size): altivec_array_dispatch <macstl::boolean <Type> > (data, size) { }				
					};

				// optimizations for expressions of the form (v1 == v2).min () to use altivec predicates
				
				// functors that encapsulate the altivec predicate operation
		
				template <typename Type> struct all_equal_to: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_eq (x, y); }
					};
							
				template <typename Type> struct any_equal_to: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_eq (x, y); }
					};
				
				template <typename Type> struct all_not_equal_to: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_ne (x, y); }
					};
					
				template <typename Type> struct any_not_equal_to: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_ne (x, y); }
					};
				
				template <typename Type> struct all_less: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_lt (x, y); }
					};
					
				template <typename Type> struct any_less: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_lt (x, y); }
					};
			
				template <typename Type> struct all_greater: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_gt (x, y); }
					};
					
				template <typename Type> struct any_greater: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_gt (x, y); }
					};
				
				template <typename Type> struct all_less_equal: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_le (x, y); }
					};
					
				template <typename Type> struct any_less_equal: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_le (x, y); }
					};
			
				template <typename Type> struct all_greater_equal: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return all_ge (x, y); }
					};
					
				template <typename Type> struct any_greater_equal: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return any_ge (x, y); }
					};
					
				// bases for specializations of accumulator that compute the predicate over an entire expression
					
				template <typename Expr> struct all_predicator
					{
						static bool call (const Expr& expr)
							{
								const size_t size = expr.size ();
								const size_t chunks = size / Expr::chunk_length;
								
								if (chunks)
									{
										// if there are any chunks, scalarize over each chunk
										if (accumulate_all (expr.all_begin (), chunks, 
											typename std::iterator_traits <typename Expr::all_iterator>::iterator_category ()))
											{
												const size_t tail = size % Expr::chunk_length;
												typename Expr::const_iterator iter = expr.begin ();
												std::advance (iter, size - tail);
												return accumulate_all (iter, tail,
													typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
											}
										else
											return false;
									}
								else
									return accumulate_all (expr.begin (), size,
										typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
							}
					};
		
				template <typename Expr> struct any_predicator
					{
						static bool call (const Expr& expr)
							{
								const size_t size = expr.size ();
								const size_t chunks = size / Expr::chunk_length;
								
								if (chunks)
									{
										// if there are any chunks, scalarize over each chunk
										if (accumulate_any (expr.any_begin (), chunks, 
											typename std::iterator_traits <typename Expr::any_iterator>::iterator_category ()))
											return true;
										else
											{
												const size_t tail = size % Expr::chunk_length;
												typename Expr::const_iterator iter = expr.begin ();
												std::advance (iter, size - tail);
												return accumulate_any (iter, tail,
													typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
											}
									}
								else
									return accumulate_any (expr.begin (), size,
										typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
									
							}
					};
			
				// bases for specializations of unary_term and binary_term to inject all_iterator and any_iterator, for above algorithms
				
				template <typename Expr, template <typename> class UOp, template <typename> class All, template <typename> class Any>				
					class unary_predicate: public unary_term_base <Expr, UOp, true>
					{
						public:
							typedef unary_iterator <typename Expr::const_chunk_iterator, All> all_iterator;
							typedef unary_iterator <typename Expr::const_chunk_iterator, Any> any_iterator;
								
							typedef typename std::iterator_traits <typename Expr::const_chunk_iterator>::value_type chunk_type;
							
							all_iterator all_begin () const
								{
									return all_iterator (expr_.chunk_begin (), All <chunk_type> (static_cast <chunk_type> (bound ())));
								}
		
							any_iterator any_begin () const
								{
									return any_iterator (expr_.chunk_begin (), Any <chunk_type> (static_cast <chunk_type> (bound ())));
								}
								
						protected:
							unary_predicate (const Expr& rexpr, const UOp <typename Expr::value_type>& op):
								unary_term_base <Expr, UOp, true> (rexpr, op)  { }
					};
							
				template <typename LExpr, typename RExpr, template <typename> class BOp, template <typename> class All, template <typename> class Any>				
					class binary_predicate: public binary_term_base <LExpr, RExpr, BOp, true>
					{
						public:
							typedef binary_iterator <typename LExpr::const_chunk_iterator, typename RExpr::const_chunk_iterator, All> all_iterator;
							typedef binary_iterator <typename LExpr::const_chunk_iterator, typename RExpr::const_chunk_iterator, Any> any_iterator;
								
							typedef typename std::iterator_traits <typename LExpr::const_chunk_iterator>::value_type chunk_type;
							
							all_iterator all_begin () const
								{
									return all_iterator (lexpr_.chunk_begin (), rexpr_.chunk_begin (), All <chunk_type> ());
								}
		
							any_iterator any_begin () const
								{
									return any_iterator (lexpr_.chunk_begin (), rexpr_.chunk_begin (), Any <chunk_type> ());
								}
								
						protected:
							binary_predicate (const LExpr& lexpr, const RExpr& rexpr, const BOp <typename LExpr::value_type>& op):
								binary_term_base <LExpr, RExpr, BOp, true> (lexpr, rexpr, op)  { }
					};
					
				// for each predicatable binary expression: binary_term_dispatch -> binary_predicate
				// for each predicatable unary expression: unary_term_dispatch -> unary_predicate
				// accumulator <minimize> -> all_predicator
				// accumulator <maximize> -> any_predicator
					
				#define __MACSTL_DEFINE_VALARRAY_PREDICATION(FUNC,ALL,ANY)												\
																														\
				template <typename LExpr, typename RExpr, typename Val> class binary_term_dispatch <LExpr, RExpr, FUNC, Val, true>:	\
					public binary_predicate <LExpr, RExpr, FUNC, ALL, ANY>												\
					{																									\
						protected:																						\
							binary_term_dispatch (const LExpr& lexpr, const RExpr& rexpr, const FUNC <Val>& op):		\
								binary_predicate <LExpr, RExpr, FUNC, ALL, ANY> (lexpr, rexpr, op) {}					\
					};																									\
																														\
				template <typename RExpr, typename Val>	class unary_term_dispatch <RExpr, left_scalar <FUNC>::operation, Val, true>:						\
					public unary_predicate <RExpr, left_scalar <FUNC>::operation, left_scalar <ALL>::operation, left_scalar <ANY>::operation> \
					{																									\
						protected:																						\
							unary_term_dispatch (const RExpr& rexpr, const left_scalar <FUNC>::operation <Val>& op):	\
								unary_predicate <RExpr, left_scalar <FUNC>::operation, left_scalar <ALL>::operation, left_scalar <ANY>::operation>	\
								(rexpr, op) {}							\
					};																									\
																														\
				template <typename LExpr, typename Val> class unary_term_dispatch <LExpr, right_scalar <FUNC>::operation, Val, true>:						\
					public unary_predicate <LExpr, right_scalar <FUNC>::operation, right_scalar <ALL>::operation, right_scalar <ANY>::operation>	\
					{																									\
						protected:																						\
							unary_term_dispatch (const LExpr& lexpr, const right_scalar <FUNC>::operation <Val>& op):		\
								unary_predicate <LExpr, right_scalar <FUNC>::operation, right_scalar <ALL>::operation, right_scalar <ANY>::operation> \
								(lexpr, op) {}							\
					};																									\
																														\
				template <typename LExpr, typename RExpr>																\
					struct accumulator <maximize, binary_term <LExpr, RExpr, FUNC>, bool, true>:	\
					public any_predicator <binary_term <LExpr, RExpr, FUNC> > { };				\
																														\
				template <typename LExpr, typename RExpr>																\
					struct accumulator <minimize, binary_term <LExpr, RExpr, FUNC>, bool, true>:	\
					public all_predicator <binary_term <LExpr, RExpr, FUNC> > { };				\
																														\
				template <typename RExpr>																				\
					struct accumulator <maximize, unary_term <RExpr, left_scalar <FUNC>::operation>, bool, true>:		\
					public any_predicator <unary_term <RExpr, left_scalar <FUNC>::operation> > { };						\
																														\
				template <typename RExpr>																				\
					struct accumulator <minimize, unary_term <RExpr, left_scalar <FUNC>::operation>, bool, true>:		\
					public all_predicator <unary_term <RExpr, left_scalar <FUNC>::operation> > { };						\
																														\
				template <typename LExpr>																				\
					struct accumulator <maximize, unary_term <LExpr, right_scalar <FUNC>::operation>, bool, true>:		\
					public any_predicator <unary_term <LExpr, right_scalar <FUNC>::operation> > { };					\
																														\
				template <typename LExpr>																				\
					struct accumulator <minimize, unary_term <LExpr, right_scalar <FUNC>::operation>, bool, true>:		\
					public all_predicator <unary_term <LExpr, right_scalar <FUNC>::operation> > { };
						
																																				
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::equal_to,all_equal_to,any_equal_to)
				
				// Metrowerks fails to disambiguate partial specializations that differ on an embedded template template param,
				// so we have to disable these other optimizations for them
				
				#ifndef __MWERKS__
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::not_equal_to,all_not_equal_to,any_not_equal_to)
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::less,all_less,any_less)
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::greater,all_greater,any_greater)
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::less_equal,all_less_equal,any_less_equal)
				__MACSTL_DEFINE_VALARRAY_PREDICATION(std::greater_equal,all_greater_equal,any_greater_equal)
				#endif
				
				// optimizations for expressions of the form v1 [slice]
		
				// stuff four vectors into one, selecting particular indices from each
				template <typename Vec>
					inline Vec stuff4 (Vec v1, Vec v2, Vec v3, Vec v4, size_t i1, size_t i2, size_t i3, size_t i4)
						{
							return
								mergeh
									(perm (v3, v1, macstl::sld <12> (macstl::lvsr (12 - (i1 * 4), (int*) NULL),
										macstl::lvsl (i3 * 4, (int*) NULL))),
									perm (v4, v2, macstl::sld <12> (macstl::lvsr (12 - (i2 * 4), (int*) NULL),
										macstl::lvsl (i4 * 4, (int*) NULL))));
						}
				
				template <typename ExprIt> class slice4_iterator
					{
						public:
							typedef typename std::iterator_traits <ExprIt>::iterator_category iterator_category;
							typedef typename std::iterator_traits <ExprIt>::value_type value_type;
							typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
							typedef typename std::iterator_traits <ExprIt>::pointer pointer;
							typedef typename std::iterator_traits <ExprIt>::reference reference;
							
							slice4_iterator (ExprIt exprit, size_t start, size_t stride): exprit_ (exprit), start_ (start), stride_ (stride)
								{
								}
								
							value_type operator* () const
								{
									// the neat thing about this is the compiler generally hoists all the invariants
									// out of any loop, so all the start_ + n * stride_ stuff gets evaluated outside the loop!!
									ExprIt iter1 = exprit_;
									ExprIt iter2 = exprit_;
									ExprIt iter3 = exprit_;
									ExprIt iter4 = exprit_;
									std::advance (iter1, start_ / 4);
									std::advance (iter2, (start_ + stride_) / 4);
									std::advance (iter3, (start_ + 2 * stride_) / 4);
									std::advance (iter4, (start_ + 3 * stride_) / 4);
									return stuff4 (
										*iter1,
										*iter2,
										*iter3,
										*iter4,
										start_ % 4,
										(start_ + stride_) % 4,
										(start_ + 2 * stride_) % 4,
										(start_ + 3 * stride_) % 4);
								}
								
							value_type operator[] (difference_type n) const
								{
									// the neat thing about this is the compiler generally hoists all the invariants
									// out of any loop, so all the start_ + n * stride_ stuff gets evaluated outside the loop!!
									ExprIt iter = exprit_;
									std::advance (iter, n * stride_);
									ExprIt iter1 = iter;
									ExprIt iter2 = iter;
									ExprIt iter3 = iter;
									ExprIt iter4 = iter;
									std::advance (iter1, start_ / 4);
									std::advance (iter2, (start_ + stride_) / 4);
									std::advance (iter3, (start_ + 2 * stride_) / 4);
									std::advance (iter4, (start_ + 3 * stride_) / 4);
									
									return stuff4 (
										*iter1,
										*iter2,
										*iter3,
										*iter4,
										start_ % 4,
										(start_ + stride_) % 4,
										(start_ + 2 * stride_) % 4,
										(start_ + 3 * stride_) % 4);
								}
							
							slice4_iterator& operator++ ()						{ std::advance (exprit_, stride_); return *this; }
							slice4_iterator operator++ (int)					{ slice4_iterator copy (*this); return ++copy; }
							slice4_iterator& operator+= (difference_type n)		{ exprit_ += n * stride_; return *this; }
			
							slice4_iterator& operator-- ()						{ std::advance (exprit_, -stride_); return *this; }
							slice4_iterator operator-- (int)					{ slice4_iterator copy (*this); return --copy; }
							slice4_iterator& operator-= (difference_type n)		{ exprit_ -= n * stride_; return *this; }
								
							friend slice4_iterator operator+ (const slice4_iterator& left, difference_type right)
								{
									return slice4_iterator (left.exprit_, right * left.stride_, left.stride_);
								}
			
							friend slice4_iterator operator+ (difference_type left, const slice4_iterator& right)
								{
									return slice4_iterator (right.exprit_, left * right.stride_, right.stride_);
								}
			
							friend slice4_iterator operator- (const slice4_iterator& left, difference_type right)
								{
									return slice4_iterator (left.exprit_, -right * left.stride_, left.stride_);
								}
							
							friend difference_type operator- (const slice4_iterator& left, const slice4_iterator& right)
								{
									return (left.exprit_ - right.exprit_) / left.stride_;
								}
								
							friend bool operator== (const slice4_iterator& left, const slice4_iterator& right)
								{
									return left.exprit_ == right.exprit_;
								}
								
							friend bool operator!= (const slice4_iterator& left, const slice4_iterator& right)
								{
									return left.exprit_ != right.exprit_;
								}
		
							friend bool operator< (const slice4_iterator& left, const slice4_iterator& right)
								{
									return left.exprit_ < right.exprit_;
								}
								
						private:
							ExprIt exprit_;
							const size_t start_;
							const size_t stride_;
							
					};
					
				template <typename Expr, template <typename> class Base> class slicer4: public Base <Expr>
					{
						public:
							typedef slice4_iterator <typename Expr::const_chunk_iterator> const_chunk_iterator;
							
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (expr_.chunk_begin (), slice_.start (), slice_.stride ());
								}
								
						protected:
							slicer4 (const Expr& expr, const std::slice& sliced): Base <Expr> (expr, sliced) { }
							slicer4 (Expr& expr, const std::slice& sliced): Base <Expr> (expr, sliced) { }
					};
					
				#define __MACSTL_DEFINE_VALARRAY_SLICING4(VAL)								\
																							\
				template <typename Expr> class slice_term_dispatch <Expr, VAL, true>:		\
					public slicer4 <Expr, slice_term_base>									\
					{																		\
						protected:																\
							typedef slicer4 <Expr, slice_term_base> base;						\
																								\
							slice_term_dispatch (const Expr& expr, const std::slice& sliced): base (expr, sliced) {} 						\
					};																		\
																							\
				template <typename Expr> class slice_array_dispatch <Expr, VAL, true>:			\
					public slicer4 <Expr, slice_array_base>									\
					{																		\
						protected:										\
							typedef slicer4 <Expr, slice_array_base> base;					\
																							\
							slice_array_dispatch (Expr& expr, const std::slice& sliced): base (expr, sliced) {}			\
					};
		
				__MACSTL_DEFINE_VALARRAY_SLICING4(long)
				__MACSTL_DEFINE_VALARRAY_SLICING4(unsigned long)
				__MACSTL_DEFINE_VALARRAY_SLICING4(float)
				
			}
	}
	
#endif
		

	