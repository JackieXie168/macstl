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
			
		template <typename Expr, template <typename> class UOp, bool is_const_chunkable> class unary_term_base;
		
		template <typename Expr, template <typename> class UOp> class unary_term_base <Expr, UOp, false>:
			protected UOp <typename Expr::value_type>
			{
				public:
					typedef typename UOp <typename Expr::value_type>::result_type value_type;
					typedef unary_iterator <typename Expr::const_iterator, UOp> const_iterator;
					
					value_type operator[] (size_t index) const	{ return (*this) (expr_ [index]); }
					size_t size () const						{ return expr_.size (); }
						
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
							return const_chunk_iterator (expr_.chunk_begin (), *this);
						}
						
				protected:
					unary_term_base (const Expr& expr, const UOp <typename Expr::value_type>& op): unary_term_base <Expr, UOp, false> (expr, op)
						{
						}
			};
			
		template <typename Expr, template <typename> class UOp, typename Val, bool is_const_chunkable>
			class unary_term_dispatch: public unary_term_base <Expr, UOp, is_const_chunkable>
			{
				protected:
					unary_term_dispatch (const Expr& expr, const UOp <Val>& op): unary_term_base <Expr, UOp, is_const_chunkable> (expr, op)
						{
						}
			};

		template <typename Expr, typename Val>
			class unary_term_dispatch <Expr, apply_value, Val, true>: public unary_term_base <Expr, apply_value, false>
			{
				protected:
					unary_term_dispatch (const Expr& expr, const apply_value <Val>& op):
						unary_term_base <Expr, apply_value, false> (expr, op)
						{
						}
			};

		template <typename Expr, typename Val>
			class unary_term_dispatch <Expr, apply_reference, Val, true>: public unary_term_base <Expr, apply_reference, false>
			{
				protected:
					unary_term_dispatch (const Expr& expr, const apply_reference <Val>& op):
						unary_term_base <Expr, apply_reference, false> (expr, op)
						{
						}
			};

		template <typename Expr, template <typename> class UOp> class unary_term:
			public term <typename UOp <typename Expr::value_type>::result_type, unary_term <Expr, UOp> >,
			public unary_term_dispatch <Expr, UOp, typename Expr::value_type, const_chunkable <Expr>::value>
			{
				public:
					using term <typename UOp <typename Expr::value_type>::result_type, unary_term <Expr, UOp> >::operator[];
					using unary_term_dispatch <Expr, UOp, typename Expr::value_type, const_chunkable <Expr>::value>::operator[];

					unary_term (const Expr& expr, const UOp <typename Expr::value_type>& op):
						unary_term_dispatch <Expr, UOp, typename Expr::value_type, const_chunkable <Expr>::value> (expr, op)
						{
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

		template <typename LExpr, typename RExpr, template <typename> class BOp, bool is_const_chunkable> class binary_term_base;
		
		template <typename LExpr, typename RExpr, template <typename> class BOp>
			class binary_term_base <LExpr, RExpr, BOp, false>: protected BOp <typename LExpr::value_type>
			{
				public:
					typedef typename BOp <typename LExpr::value_type>::result_type value_type;
					typedef binary_iterator <typename LExpr::const_iterator, typename RExpr::const_iterator, BOp> const_iterator;
					
					value_type operator[] (size_t index) const	{ return (*this) (lexpr_ [index], rexpr_ [index]); }
					size_t size () const						{ return lexpr_.size (); }
						
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
					
					typedef binary_iterator <typename LExpr::const_chunk_iterator, typename RExpr::const_chunk_iterator, BOp> const_chunk_iterator;

					const_chunk_iterator chunk_begin () const
						{
							return const_chunk_iterator (lexpr_.chunk_begin (), rexpr_.chunk_begin (), *this);
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

		template <typename LExpr, typename RExpr, template <typename> class BOp> class binary_term:
			public term <typename BOp <typename LExpr::value_type>::result_type, binary_term <LExpr, RExpr, BOp> >,
			public binary_term_dispatch <LExpr, RExpr, BOp, typename LExpr::value_type,
				const_chunkable <LExpr>::value &&
				const_chunkable <RExpr>::value &&
				const_rechunkable <LExpr, RExpr>::value>
			{
				public:
					using term <typename BOp <typename LExpr::value_type>::result_type, binary_term <LExpr, RExpr, BOp> >::operator[];
					using binary_term_dispatch <LExpr, RExpr, BOp, typename LExpr::value_type,
						const_chunkable <LExpr>::value &&
						const_chunkable <RExpr>::value &&
						const_rechunkable <LExpr, RExpr>::value>::operator[];
					
					binary_term (const LExpr& lexpr, const RExpr& rexpr, const BOp <typename LExpr::value_type>& op):
						binary_term_dispatch <LExpr, RExpr, BOp, typename LExpr::value_type,
							const_chunkable <LExpr>::value &&
							const_chunkable <RExpr>::value &&
							const_rechunkable <LExpr, RExpr>::value> (lexpr, rexpr, op)  { }
			};
			
	};

