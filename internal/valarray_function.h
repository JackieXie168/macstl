/*
 *  valarray_function.h
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

#ifndef MACSTL_INTERNAL_VALARRAY_FUNCTION_H
#define MACSTL_INTERNAL_VALARRAY_FUNCTION_H

namespace std
	{
		namespace impl
			{
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Unary expression iterator.
				 * @param ExprIt The argument expression iterator.
				 * @param UOp The unary operator.
				 * @par Models:
				 * Same iterator category as @a ExprIt.
				 *
				 * Serves as an iterator for unary terms.
				 */
				template <typename ExprIt, template <typename> class UOp> class unary_iterator:
					private UOp <typename std::iterator_traits <ExprIt>::value_type>
					{
						public:
							typedef UOp <typename std::iterator_traits <ExprIt>::value_type> operation;
							
							typedef typename std::iterator_traits <ExprIt>::iterator_category iterator_category;
							typedef typename operation::result_type value_type; 
							typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
							typedef const value_type* pointer;
							typedef const value_type& reference;
							
							unary_iterator (ExprIt exprit, const operation& uop): operation (uop), exprit_ (exprit)
								{
								}
								
							value_type operator* () const					{ return (*this) (*exprit_); }
							value_type operator[] (difference_type n) const	{ return (*this) (exprit_ [n]); }
							
							unary_iterator& operator++ ()					{ ++exprit_; return *this; }
							unary_iterator operator++ (int)					{ return unary_iterator (*this, exprit_++); }
							unary_iterator& operator+= (difference_type n)	{ exprit_ += n; return *this; }
		
							unary_iterator& operator-- ()					{ --exprit_; return *this; }
							unary_iterator operator-- (int)					{ return unary_iterator (*this, exprit_--); }
							unary_iterator& operator-= (difference_type n)	{ exprit_ -= n; return *this; }
								
							friend unary_iterator operator+ (const unary_iterator& left, difference_type right)
								{
									return unary_iterator (left.exprit_ + right, left);
								}
		
							friend unary_iterator operator+ (difference_type left, const unary_iterator& right)
								{
									return unary_iterator (left + right.exprit_, right);
								}
		
							friend unary_iterator operator- (const unary_iterator& left, difference_type right)
								{
									return unary_iterator (left.exprit_ - right, left);
								}
							
							friend difference_type operator- (const unary_iterator& left, const unary_iterator& right)
								{
									return left.exprit_ - right.exprit_;
								}
								
							friend bool operator== (const unary_iterator& left, const unary_iterator& right)
								{
									return left.exprit_ == right.exprit_;
								}
								
							friend bool operator!= (const unary_iterator& left, const unary_iterator& right)
								{
									return left.exprit_ != right.exprit_;
								}
		
							friend bool operator< (const unary_iterator& left, const unary_iterator& right)
								{
									return left.exprit_ < right.exprit_;
								}
		
						private:
							ExprIt exprit_;
					};
					
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Unary expression term base.
				 * @param Expr The argument expression.
				 * @param UOp The unary operator.
				 * @param is_const_chunkable Whether the expression is to be const chunkable.
				 *
				 * This class serves as a base for unary terms. The partial specialization with
				 * is_const_chunkable = true defines additional members for chunking.
				 */
				template <typename Expr, template <typename> class UOp, bool is_const_chunkable> class unary_term_base:
					protected UOp <typename Expr::value_type>
					{
						public:
							/** The element type, see std::valarray. */
							typedef typename UOp <typename Expr::value_type>::result_type value_type;
							
							/** Constant iterator into the term. */
							typedef unary_iterator <typename Expr::const_iterator, UOp> const_iterator;
							
							/** Returns the element at index @a n. */
							value_type operator[] (size_t n) const	{ return (*this) (expr_ [n]); }
							
							/** Returns the number of elements. */
							size_t size () const					{ return expr_.size (); }
								
							/** Returns a const iterator to the first element. */
							const_iterator begin () const
								{
									return const_iterator (expr_.begin (), *this);
								}
								
						protected:
							const Expr& expr_;
		
							unary_term_base (const Expr& expr, const UOp <typename Expr::value_type>& op):
								UOp <typename Expr::value_type> (op), expr_ (expr) { }		
					};
					
				template <typename Expr, template <typename> class UOp> class unary_term_base <Expr, UOp, true>:
					public unary_term_base <Expr, UOp, false>
					{
						public:
							enum { chunk_length = Expr::chunk_length };
							
							typedef unary_iterator <typename Expr::const_chunk_iterator, UOp> const_chunk_iterator;
						
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (expr_.chunk_begin (),
										enchunk <typename std::iterator_traits <typename Expr::const_chunk_iterator>::value_type>
										(static_cast <const UOp <typename Expr::value_type>&> (*this)));
								}
								
						protected:
							unary_term_base (const Expr& expr, const UOp <typename Expr::value_type>& op):
								unary_term_base <Expr, UOp, false> (expr, op)
								{
								}
					};
					
				template <typename Expr, template <typename> class UOp, typename Val, bool is_const_chunkable> class unary_term_dispatch:
					public unary_term_base <Expr, UOp, is_const_chunkable>
					{
						protected:
							unary_term_dispatch (const Expr& expr, const UOp <Val>& op):
								unary_term_base <Expr, UOp, is_const_chunkable> (expr, op)
								{
								}
					};
					
				// inhibit chunking for apply value
				template <typename Val, typename Expr> class unary_term_dispatch <Expr, apply_value, Val, true>:
					public unary_term_base <Expr, apply_value, false>
					{
						protected:
							typedef unary_term_base <Expr, apply_value, false> base;
							
							unary_term_dispatch (const Expr& expr, const apply_value <Val>& op): base (expr, op)
								{
								}
					};
		
				// inhibit chunking for apply reference
				template <typename Val, typename Expr> class unary_term_dispatch <Expr, apply_reference, Val, true>:
					public unary_term_base <Expr, apply_reference, false>
					{
						protected:
							typedef unary_term_base <Expr, apply_reference, false> base;
							
							unary_term_dispatch (const Expr& expr, const apply_reference <Val>& op): base (expr, op)
								{
								}
					};
		
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Unary expression term.
				 * @param Expr The argument expression.
				 * @param UOp The unary operator.
				 *
				 * This class represents unary expressions e.g.
				 * @code
				 * std::valarray <float> v1;
				 * std::impl::unary_term <std::valarray <float>, std::negate> t1 = -v1;
				 * @endcode
				 * A unary expression is const chunkable if its argument expression is const chunkable, except
				 * for appliers.
				 */
				template <typename Expr, template <typename> class UOp> class unary_term:
					public unary_term_dispatch <Expr, UOp, typename Expr::value_type, const_chunkable <Expr>::value>,
					public term <typename UOp <typename Expr::value_type>::result_type, unary_term <Expr, UOp> >
					{
						public:
							typedef unary_term_dispatch <Expr, UOp, typename Expr::value_type, const_chunkable <Expr>::value> base;
							typedef term <typename UOp <typename Expr::value_type>::result_type, unary_term <Expr, UOp> > term;
		
							using base::operator[];
							using term::operator[];
							
							unary_term (const Expr& expr, const UOp <typename Expr::value_type>& op):
								base (expr, op)
								{
								}
					};
		
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Binary expression iterator.
				 * @param LExprIt The left argument expression iterator.
				 * @param RExprIt The right argument expression iterator.
				 * @param BOp The binary operator.
				 * @par Models:
				 * Least refined iterator category of @a LExprIt and @a RExprIt.
				 *
				 * Serves as an iterator for binary terms.
				 */
				template <typename LExprIt, typename RExprIt, template <typename> class BOp> class binary_iterator:
					private BOp <typename std::iterator_traits <LExprIt>::value_type>
					{
						public:
							typedef BOp <typename std::iterator_traits <LExprIt>::value_type> operation;
							
							// const_iterator category is the category with the least rank of the two expression's categories
							typedef typename iterator_ranker
								<typename std::iterator_traits <LExprIt>::iterator_category,
								typename std::iterator_traits <RExprIt>::iterator_category>::type iterator_category;
							
							typedef typename operation::result_type value_type;
							typedef typename std::iterator_traits <LExprIt>::difference_type difference_type;
							typedef const value_type* pointer;
							typedef const value_type& reference;
							
							binary_iterator (LExprIt lexprit, RExprIt rexprit, const operation& bop):
								operation (bop), lexprit_ (lexprit), rexprit_ (rexprit)
								{
								}
								
							value_type operator* () const					{ return (*this) (*lexprit_, *rexprit_); }
							value_type operator[] (difference_type n) const	{ return (*this) (lexprit_ [n], rexprit_ [n]); }
							
							binary_iterator& operator++ ()					{ ++lexprit_; ++rexprit_; return *this; }
							binary_iterator operator++ (int)				{ return binary_iterator (*this, lexprit_++, rexprit_++); }
							binary_iterator& operator+= (difference_type n)	{ lexprit_ += n; rexprit_ += n; return *this; }
		
							binary_iterator& operator-- ()					{ --lexprit_; --rexprit_; return *this; }
							binary_iterator operator-- (int)				{ return binary_iterator (*this, lexprit_--, rexprit_--); }
							binary_iterator& operator-= (difference_type n)	{ lexprit_ -= n; rexprit_ -= n; return *this; }
								
							friend binary_iterator operator+ (const binary_iterator& left, difference_type right)
								{
									return binary_iterator (left.lexprit_ + right, left.rexprit_ + right, left);
								}
		
							friend binary_iterator operator+ (difference_type left, const binary_iterator& right)
								{
									return binary_iterator (left + right.lexprit_, left + right.rexprit_, right);
								}
		
							friend binary_iterator operator- (const binary_iterator& left, difference_type right)
								{
									return binary_iterator (left.lexprit_ - right, left.rexprit_ - right, left);
								}
							
							friend difference_type operator- (const binary_iterator& left, const binary_iterator& right)
								{
									return left.lexprit_ - right.lexprit_;
								}
								
							friend bool operator== (const binary_iterator& left, const binary_iterator& right)
								{
									return left.lexprit_ == right.lexprit_;
								}
								
							friend bool operator!= (const binary_iterator& left, const binary_iterator& right)
								{
									return left.lexprit_ != right.lexprit_;
								}
		
							friend bool operator< (const binary_iterator& left, const binary_iterator& right)
								{
									return left.lexprit_ < right.lexprit_;
								}
								
						private:
							LExprIt lexprit_;
							RExprIt rexprit_;
					};
		
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Binary expression term base.
				 * @param LExpr The first argument expression.
				 * @param RExpr The second argument expression.
				 * @param BOp The binary operator.
				 * @param is_const_chunkable Whether the expression is to be const chunkable.
				 *
				 * This class serves as a base for binary terms. The partial specialization with
				 * is_const_chunkable = true declares additional members for chunking.
				 */
				template <typename LExpr, typename RExpr, template <typename> class BOp, bool is_const_chunkable>
					class binary_term_base: protected BOp <typename LExpr::value_type>
					{
						public:
							/** The element type, see std::valarray. */
							typedef typename BOp <typename LExpr::value_type>::result_type value_type;
							
							/** Constant iterator into the tern. */
							typedef binary_iterator <typename LExpr::const_iterator, typename RExpr::const_iterator, BOp> const_iterator;
							
							/** Returns the element at index @a n. */
							value_type operator[] (size_t index) const	{ return (*this) (lexpr_ [index], rexpr_ [index]); }
							
							/** Returns the number of elements. */
							size_t size () const						{ return lexpr_.size (); }
								
							/** Returns a constant iterator to the first element. */
							const_iterator begin () const
								{
									return const_iterator (lexpr_.begin (), rexpr_.begin (), *this);
								}
		
						protected:
							const LExpr& lexpr_;
							const RExpr& rexpr_;
							
							binary_term_base (const LExpr& lexpr, const RExpr& rexpr, const BOp <typename LExpr::value_type>& op):
								BOp <typename LExpr::value_type> (op), lexpr_ (lexpr), rexpr_ (rexpr)  { }
					};
					
				template <typename LExpr, typename RExpr, template <typename> class BOp>
					class binary_term_base <LExpr, RExpr, BOp, true>: public binary_term_base <LExpr, RExpr, BOp, false>
					{
						public:
							enum { chunk_length = LExpr::chunk_length };
							
							typedef binary_iterator <typename LExpr::const_chunk_iterator, typename RExpr::const_chunk_iterator, BOp>
								const_chunk_iterator;
		
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (lexpr_.chunk_begin (), rexpr_.chunk_begin (),
										enchunk <typename std::iterator_traits <typename LExpr::const_chunk_iterator>::value_type>
										(static_cast <const BOp <typename LExpr::value_type>&> (*this)));
								}
								
						protected:
							binary_term_base (const LExpr& lexpr, const RExpr& rexpr, const BOp <typename LExpr::value_type>& op):
								binary_term_base <LExpr, RExpr, BOp, false> (lexpr, rexpr, op)  { }					
					};
		
				template <typename LExpr, typename RExpr, template <typename> class BOp, typename Val, bool is_const_chunkable>
					class binary_term_dispatch: public binary_term_base <LExpr, RExpr, BOp, is_const_chunkable>
					{
						protected:
							binary_term_dispatch (const LExpr& lexpr, const RExpr& rexpr, const BOp <Val>& op):
								binary_term_base <LExpr, RExpr, BOp, is_const_chunkable> (lexpr, rexpr, op)  { }					
					};
							
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Binary expression term.
				 * @param LExpr The first argument expression.
				 * @param RExpr The second argument expression.
				 * @param BOp The binary operator.
				 *
				 * This class represents binary expressions e.g.
				 * @code
				 * std::valarray <float> v1, v2;
				 * std::impl::binary_term <std::valarray <float>, std::valarray <float>, std::plus> t1 = v1 + v2;
				 * @endcode
				 * A binary expression is const chunkable if both argument expressions are const chunkable,
				 * and the chunks are of the same type.
				 */
				template <typename LExpr, typename RExpr, template <typename> class BOp> class binary_term:
					public binary_term_dispatch <LExpr, RExpr, BOp, typename LExpr::value_type,
						const_chunkable <LExpr>::value && const_chunkable <RExpr>::value && const_rechunkable <LExpr, RExpr>::value>,
					public term <typename BOp <typename LExpr::value_type>::result_type, binary_term <LExpr, RExpr, BOp> >
					{
						public:
							typedef binary_term_dispatch <LExpr, RExpr, BOp, typename LExpr::value_type,
								const_chunkable <LExpr>::value && const_chunkable <RExpr>::value && const_rechunkable <LExpr, RExpr>::value> base;
							typedef term <typename BOp <typename LExpr::value_type>::result_type, binary_term <LExpr, RExpr, BOp> > term;
							
							using base::operator[];
							using term::operator[];
							
							binary_term (const LExpr& lexpr, const RExpr& rexpr, const BOp <typename LExpr::value_type>& op):
								base (lexpr, rexpr, op)  { }
					};
					
			}
	}

#endif
