/*
 *  valarray_base.h
 *  macstl
 *
 *  Created by Glen Low on Mon Jun 23 2003.
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

#ifndef MACSTL_INTERNAL_VALARRAY_BASE_H
#define MACSTL_INTERNAL_VALARRAY_BASE_H

namespace std
	{
		namespace impl
			{
				template <typename Type> class apply_value
					{
						public:
							typedef Type argument_type;
							typedef Type result_type;
							
							apply_value (Type (*fn) (Type)): fn_ (fn)	{}						
							Type operator() (const Type& x) const		{ return fn_ (x); }
								
						private:
							Type (*fn_) (Type);
					};
		
				template <typename Type> class apply_reference
					{
						public:
							typedef Type argument_type;
							typedef Type result_type;
							
							apply_reference (Type (*fn) (const Type &)): fn_ (fn)	{}
							Type operator() (const Type& x) const					{ return fn_ (x); }
								
						private:
							Type (*fn_) (const Type &);
					};
		
				template <template <typename> class Op> struct left_scalar
					{
						template <typename Type> class operation: public stdext::binder1st <Op <Type> >
							{
								public:
									operation (const Type& bound): stdext::binder1st <Op <Type> > (Op <Type> (), bound) {}
									operation (const stdext::binder1st <Op <Type> >& op): stdext::binder1st <Op <Type> > (op) {}
																	
									const Type& bound () const	{ return bound_; }
		
							};
					};
		
				template <template <typename> class Op> struct right_scalar
					{
						template <typename Type> class operation: public stdext::binder2nd <Op <Type> >
							{
								public:
									operation (const Type& bound): stdext::binder2nd <Op <Type> > (Op <Type> (), bound) {}
									operation (const stdext::binder2nd <Op <Type> >& op): stdext::binder2nd <Op <Type> > (op) {}
										
									const Type& bound () const	{ return bound_; }
							};
					};
				
				
				// term: base of all terms substitutable for a const valarray
					
				#define __MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION(FUNC, OPER)								\
				/** Returns the result of applying <code>FUNC</code> to each element. */						\
				unary_term <Expr, OPER> FUNC () const									\
					{																						\
						return unary_term <Expr, OPER> (expr (), OPER <Val> ());									\
					}
		
				#define __MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION(FUNC, OPER)									\
				/** @relates term Returns the result of applying <code>FUNC</code> to each element of @a x. */																							\
				template <typename Val, typename Expr> unary_term <Expr, OPER> FUNC	\
					(const term <Val, Expr>& x)																\
					{																						\
						return unary_term <Expr, OPER> (x.expr (), OPER <Val> ());								\
					}
		
				#define __MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION(FUNC, OPER)								\
																											\
				/** @relates term Returns the result of applying <code>FUNC</code> to each element of @a x and the matching element of @a y. */	\
				template <typename Val, typename LExpr, typename RExpr>										\
					binary_term <LExpr, RExpr, OPER> FUNC								\
					(const term <Val, LExpr>& left, const term <Val, RExpr>& right)							\
					{																						\
						return binary_term <LExpr, RExpr, OPER>						\
							(left.expr (), right.expr (), OPER <Val> ());				\
					}																						\
																											\
				/** @relates term Returns the result of applying <code>FUNC</code> to scalar @a x and each element of @a y. */		\
				template <typename Val, typename RExpr>														\
					unary_term <RExpr, left_scalar <OPER>::operation> FUNC									\
					(const Val& left, const term <Val, RExpr>& right)										\
					{																						\
						return unary_term <RExpr, left_scalar <OPER>::operation>							\
							(right.expr (), left_scalar <OPER>::operation <Val> (left)); 					\
					}																						\
																											\
				/** @relates term Returns the result of applying <code>FUNC</code> to each element of @a x and scalar @a y. */		\
				template <typename Val, typename LExpr>														\
					unary_term <LExpr, right_scalar <OPER>::operation> FUNC									\
					(const term <Val, LExpr>& left, const Val& right)										\
					{																						\
						return unary_term <LExpr, right_scalar <OPER>::operation>							\
							(left.expr (), right_scalar <OPER>::operation <Val> (right));					\
					}														
				
				/**
				* @internal
				* @ingroup valarray_internal
				* @brief Substitute for a const valarray
				* @param Val The element type, see std::valarray.
				* @param Expr The term expression, which should be the subclass.
				*
				* The standard allows any function returning a valarray to substitute objects of other
				* types, so this class serves as the base class for those types:
				* - Defines all the const member and free functions of std::valarray, except for index and size.
				* - Limits templated operator overloads to its subclasses.
				* .
				* In the usual <em>expression template</em> technique, this class would contain the expression
				* instance. However, to minimize redundant copying and memory overhead, and allow expressions to
				* share code, the class uses <em>curiously recursive inheritance</em> to keep the expression.
				* For example:
				* @code
				* template <typename Val> class slice_term: public term <Val, slice_term <Val> >, public ...
				* @endcode
				* Thus in the scope of term, a simple static_cast to Expr will retreive the expression.
				*/
				template <typename Val, typename Expr> class term
					{
						public:
							/**
							* @name subsetters
							* 26.3.2.4 [lib.valarray.sub], const
							*/
							
							//@{
							
							/** Returns a BLAS-like slice @a sub out of the term. */
							slice_term <Expr> operator[] (slice sub) const
								{
									return slice_term <Expr> (expr (), sub);
								}
								
							/** Returns a generalized slice @a sub out of the term. */
							gslice_term <Expr> operator[] (const gslice& sub) const
								{
									return gslice_term <Expr> (expr (), sub);
								}
							
							/** Returns a boolean mask @a sub out of the term. */
							template <typename BExpr> mask_term <Expr, BExpr>
								operator[] (const term <bool, BExpr>& sub) const
								{
									return mask_term <Expr, BExpr> (expr (), sub.expr ());
								}
		
							/** Returns an index indirection @a sub out of the term. */
							template <typename InExpr> indirect_term <Expr, InExpr>
								operator[] (const term <size_t, InExpr>& sub) const
								{
									return indirect_term <Expr, InExpr> (expr (), sub.expr ());
								}
							
							//@}
							
							/**
							* @name unary operators
							* 26.3.2.5 [lib.valarray.unary]
							*/
							
							//@{
							
							__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator+, stdext::identity)
							__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator-, negate)
							__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator~, stdext::bitwise_not)
							__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator!, logical_not)
								
							//@}
							
							/**
							* @name scalarizers
							* 26.3.2.7/2,3,4 [lib.valarray.member]
							*/
							
							//@{
							
							/** Returns the sum of all the elements. */
							Val sum () const	{ return accumulate_array <summate> (expr ()); }
							
							/** Returns the minimum element. */
							Val min () const	{ return accumulate_array <minimize> (expr ()); }
							
							/** Returns the maximum element. */
							Val max () const	{ return accumulate_array <maximize> (expr ()); }
							
							//@}
							
							/**
							* @name shifters
							* 26.3.2.7/5,6,7 [lib.valarray.member]
							*/
							
							//@{
							
							/** Returns the result of shifting each element left @a n places and filling with default-constructed elements. */
							shift_term <Expr> shift (int n) const		{ return shift_term <Expr> (expr (), n); }
							
							/** Returns the result of circularly shifting each element left @a n places. */
							cshift_term <Expr> cshift (int n) const		{ return cshift_term <Expr> (expr (), n); }
							
							//@}
							
							/**
							* @name appliers
							* 26.3.2.7/8 [lib.valarray.member]
							*/
							
							//@{
							
							/** Returns the result of applying @a func to each element. */
							unary_term <Expr, apply_value> apply (Val func (Val)) const
								{
									return unary_term <Expr, apply_value> (expr (), apply_value <Val> (func));
								}
								
							/** Returns the result of applying @a func to each element. */
							unary_term <Expr, apply_reference> apply (Val func (const Val&)) const
								{
									return unary_term <Expr, apply_reference> (expr (), apply_reference <Val> (func));
								}
		
							//@}
							
							const Expr& expr () const
								{
									return static_cast <const Expr&> (*this);
								}
					};
					
				/**
				* @name binary operators
				* 26.3.3.1 [lib.valarray.binary]
				*/
				
				//@{
		
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator*, multiplies)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator/, divides)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator%, modulus)            
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator+, plus)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator-, minus)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator^, stdext::bitwise_xor)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator&, stdext::bitwise_and)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator|, stdext::bitwise_or)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<<, stdext::left_shift)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>>, stdext::right_shift) 
				
				//@}
				
				/**
				* @name logical operators
				* 26.3.3.2 [lib.valarray.comparison]
				*/
				
				//@{
				
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator==, equal_to)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator!=, not_equal_to)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<, less)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>, greater)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<=, less_equal)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>=, greater_equal)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator&&, logical_and)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator||, logical_or)
				
				//@}
				
				/**
				* @name transcendental functions
				* 26.3.3.3 [lib.valarray.transcend]
				*/
		
				//@{
				
				// note: we match these valarray functions to the appropriate function object templates in
				// std namespace declared previously
				
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (abs, __abs)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (acos, __acos)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (asin, __asin)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (atan, __atan)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (atan2, __atan2)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (cos, __cos)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (cosh, __cosh)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (exp, __exp)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (log, __log)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (log10, __log10)
				__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (pow, __pow)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sin, __sin)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sinh, __sinh)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sqrt, __sqrt)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (tan, __tan)
				__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (tanh, __tanh)
				
				//@}
				
				/**
				* @internal
				* @ingroup valarray_internal
				* @brief Array base.
				* @param Val The element type, see std::valarray.
				*
				* This class serves as a base for arrays. It defines the minimal interface necessary
				* to access elements of the array.
				*/
				template <typename Val> class array_base
					{
						public:
							typedef Val value_type;					/**< The element type, see std::valarray. */
		
							typedef const Val* const_iterator;		/**< Constant iterator into the array. */
							typedef Val* iterator;					/**< Mutable iterator into the array. */
							
							/**
							 * @name indexers
							 * 26.3.2.3 [lib.valarray.access]
							 */
							
							//@{
							
							/** Returns the element at index @a n. */
							value_type operator[] (size_t n) const	{ return data_ [n]; }
							
							/** Returns a reference to the element at index @a n. */
							value_type& operator[] (size_t n)		{ return data_ [n]; }
							
							//@}
							
							/**
							 * @name sizer
							 * 26.3.2.7/1 [lib.valarray.members]
							 */
							
							//@{
							
							/** Returns the number of elements. */
							size_t size () const			{ return size_; }
				
							//@}
							
							/** @name iterators */
							
							//@{
							
							/** Returns a constant iterator to the first element. */
							const_iterator begin () const	{ return data_; }
							
							/** Returns a mutable iterator to the first element. */
							iterator begin ()				{ return data_; }
							
							//@}
							
						protected:
							Val* data_;
							size_t size_;
							
							array_base (Val* data, size_t size): data_ (data), size_ (size)	{}
		
							void swap (array_base& other)
								{
									swap (data_, other.data_);
									swap (size_, other.size_);
								}
					};		
		
				template <typename Val> class array_dispatch: public array_base <Val>
					{
						public:
							array_dispatch (Val* data, size_t size): array_base <Val> (data, size)
								{
								}
					};		
		
				/**
				* @ingroup valarray_internal
				* @brief Substitute for a mutable valarray
				* @param Val The element type, see std::valarray.
				*
				* Currently, std::valarray is the only subclass, but other types may subclass array and thus participate in
				* the valarray arithmetic. impl::array does not explicitly specify copy semantics; a copy thus behaves like a
				* reference to the original.
				*
				* An array is const chunkable or chunkable depending on its element type.
				*/
				template <typename Val> class array: public array_dispatch <Val>, public term <Val, array <Val> >
					{
						public:
							using array_dispatch <Val>::operator[];
							using term <Val, array <Val> >::operator[];
							
							/**
							* @name subsetters
							* 26.3.2.4 [lib.valarray.subset], mutable
							*/
							
							//@{
							
							/** Returns a BLAS-like slice @a sub out of the array. */
							slice_array <Val> operator[] (slice sub)
								{
									return slice_array <Val> (*this, sub);
								}
							
							/** Returns a generalized slice @a sub out of the array. */
							gslice_array <Val> operator[] (const gslice& sub)
								{
									return gslice_array <Val> (*this, sub);
								}
							
							/** Returns a boolean mask @a sub out of the array. */
							template <typename BExpr> mask_array <Val, BExpr> operator[] (const term <bool, BExpr>& sub)
								{
									return mask_array <Val, BExpr> (*this, sub.expr ());
								}
								
							/** Returns a index indirection @a sub out of the array. */
							template <typename InExpr> indirect_array <Val, InExpr> operator[] (const term <size_t, InExpr>& sub)
								{
									return indirect_array <Val, InExpr> (*this, sub.expr ());
								}
								
							//@}
							
						protected:
							array (Val* data, size_t size): array_dispatch <Val> (data, size)	{}
					};
								
				#define __MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION(FUNC, OPER)								\
				/** Performs @c FUNC with term @a other to entire subset. */					\
				template <typename Expr2> void FUNC (const term <Val, Expr2>& other) const				\
					{																					\
						for_each_array (expr (), other.expr (), OPER <Val> ());	\
					}
		
				/**
				* @internal
				* @brief Subset of valarray.
				* @param Val The element type, see std::valarray.
				* @param Expr The subset expression, which should be the subclass.
				*
				* This class serves as the base for all subset arrays, for sharing code.
				*/
				template <typename Val, typename Expr> class subset
					{
						public:
							/**
							* @name assignment
							* 26.3.5.2 [lib.slice.array.assign] @n
							* 26.3.7.2 [lib.gslice.array.assign] @n
							* 26.3.8.2 [lib.mask.array.assign] @n
							* 26.3.9.2 [lib.indirect.array.assign]
							*/
							
							//@{
							
							/** Assigns term @a other to entire subset. */
							template <typename Expr2> void operator= (const term <Val, Expr2>& other) const
								{
									copy_array (expr (), other);
								}
					
							//@}
							
							/**
							* @name computed assignments
							* 26.3.5.3 [lib.slice.array.comp.assign] @n
							* 26.3.7.3 [lib.gslice.array.comp.assign] @n
							* 26.3.8.3 [lib.mask.array.comp.assign] @n
							* 26.3.9.3 [lib.indirect.array.comp.assign]
							*/
							
							//@{
							
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator*=, stdext::multiplies_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator/=, stdext::divides_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator%=, stdext::modulus_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator+=, stdext::plus_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator-=, stdext::minus_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator^=, stdext::bitwise_xor_assign)			
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator&=, stdext::bitwise_and_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator|=, stdext::bitwise_or_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator<<=, stdext::left_shift_assign)
							__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator>>=, stdext::right_shift_assign)
							
							//@}
							
							/**
							* @name fill
							* 26.3.5.4 [lib.slice.array.fill] @n
							* 26.3.7.4 [lib.gslice.array.fill] @n
							* 26.3.8.4 [lib.mask.array.fill] @n
							* 26.3.9.4 [lib.indirect.array.fill]
							*/
							
							//@{
							
							/** Assigns @a x to each element. */
							void operator= (const Val& x)
								{
									fill_array (expr (), x);
								}
							
							//@}
								
						private:
							Expr& expr ()
								{
									return static_cast <Expr&> (*this);
								}
					};
			
			}
	}
	
#endif

