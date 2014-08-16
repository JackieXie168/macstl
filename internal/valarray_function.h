/*
 *  valarray_function.h
 *  macstl
 *
 *  Created by Glen Low on Mon Jun 23 2003.
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
							return unary_iterator (left - right.exprit_, left);
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
			
		template <typename Expr, template <typename> class UOp> class unary_term:
			public term_base <typename UOp <typename Expr::value_type>::result_type, unary_term <Expr, UOp> >,
			private UOp <typename Expr::value_type>
			{
				public:
					typedef UOp <typename Expr::value_type> operation;
					
					typedef typename operation::result_type value_type;
					typedef unary_iterator <typename Expr::const_iterator, UOp> const_iterator;
					
					unary_term (const Expr& expr, const operation& op): operation (op), expr_ (expr) { }
		
					value_type operator[] (size_t index) const	{ return *this (expr_ [index]); }
					size_t size () const						{ return expr_.size (); }
						
					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), *this);
						}
						
				private:
					const Expr& expr_;
					
					friend class chunk_base <value_type, unary_term>;
			};
			
		template <typename Val, typename Expr, template <typename> class UOp> class chunk_base <Val, unary_term <Expr, UOp> >
			{
				public:
					typedef typename ander <
						typename Expr::const_chunkable,
						typename UOp <typename Expr::value_type>::retypeable>::type const_chunkable;

					typedef unary_iterator <typename Expr::const_chunk_iterator, UOp> const_chunk_iterator;
					
					const_chunk_iterator chunk_begin () const
						{
							const unary_term <Expr, UOp>& expr = static_cast <const unary_term <Expr, UOp>&> (*this);
							return const_chunk_iterator (expr.expr_.chunk_begin (), expr);
						}
			};
			

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
							return binary_iterator (left - right.lexprit_, left - right.rexprit_, left);
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
						
		template <typename LExpr, typename RExpr, template <typename> class BOp> class binary_term:
			public term_base <typename BOp <typename LExpr::value_type>::result_type, binary_term <LExpr, RExpr, BOp> >,
			private BOp <typename LExpr::value_type>
			{
				public:
					typedef BOp <typename LExpr::value_type> operation;
					
					typedef typename operation::result_type value_type;
					typedef binary_iterator <typename LExpr::const_iterator, typename RExpr::const_iterator, BOp> const_iterator;
					
					binary_term (const LExpr& lexpr, const RExpr& rexpr, const operation& op):
						operation (op), lexpr_ (lexpr), rexpr_ (rexpr)  { }
		
					value_type operator[] (size_t index) const	{ return (*this) (lexpr_ [index], rexpr_ [index]); }
					size_t size () const						{ return lexpr_.size (); }
						
					const_iterator begin () const
						{
							return const_iterator (lexpr_.begin (), rexpr_.begin (), *this);
						}

				public:
					const LExpr& lexpr_;
					const RExpr& rexpr_;
					
					friend class chunk_base <value_type, binary_term>;
			};

		template <typename Val, typename LExpr, typename RExpr, template <typename> class BOp>
			class chunk_base <Val, binary_term <LExpr, RExpr, BOp> >
			{
				public:
					typedef typename ander <
						typename LExpr::const_chunkable,
						typename RExpr::const_chunkable,
						typename BOp <typename LExpr::value_type>::retypeable,
						typename compatible <
							typename std::iterator_traits <typename LExpr::const_chunk_iterator>::value_type,
							typename std::iterator_traits <typename RExpr::const_chunk_iterator>::value_type>::type>::type const_chunkable;
						
					typedef binary_iterator <typename LExpr::const_chunk_iterator, typename RExpr::const_chunk_iterator, BOp> const_chunk_iterator;
					
					const_chunk_iterator chunk_begin () const
						{
							const binary_term <LExpr, RExpr, BOp>& expr = static_cast <const binary_term <LExpr, RExpr, BOp>&> (*this);
							return const_chunk_iterator (expr.lexpr_.chunk_begin (), expr.rexpr_.chunk_begin (), expr);
						}
			};
			
	};

