/*
 *  valarray_indirect.h
 *  macstl
 *
 *  Created by Glen Low on Mon Jun 09 2003.
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

#include <Carbon/Carbon.h>

namespace impl
	{
		template <typename ExprIt, typename InExprIt> class indirect_iterator
			{
				public:
					typedef typename std::iterator_traits <InExprIt>::iterator_category iterator_category;
					typedef typename std::iterator_traits <ExprIt>::value_type value_type;
					typedef typename std::iterator_traits <InExprIt>::difference_type difference_type;
					typedef typename std::iterator_traits <ExprIt>::pointer pointer;
					typedef typename std::iterator_traits <ExprIt>::reference reference;
					
					typedef typename dereference <reference>::type dereference;
					
					indirect_iterator (ExprIt exprit, InExprIt inexprit): exprit_ (exprit), inexprit_ (inexprit)
						{
						}
						
					dereference operator* () const
						{
							ExprIt it = exprit_;
							std::advance (it, *inexprit_);
							return *it;
						}
						
					dereference operator[] (difference_type n) const
						{
							ExprIt it = exprit_;
							std::advance (it, inexprit_ [n]);
							return *it;
						}
					
					indirect_iterator& operator++ ()					{ ++inexprit_; return *this; }
					indirect_iterator operator++ (int)					{ return const_iterator (exprit_, inexprit_++); }
					indirect_iterator& operator+= (difference_type n)	{ inexprit_ += n; return *this; }

					indirect_iterator& operator-- ()					{ --inexprit_; return *this; }
					indirect_iterator operator-- (int)					{ return const_iterator (exprit_, inexprit_--); }
					indirect_iterator& operator-= (difference_type n)	{ inexprit_ -= n; return *this; }
						
					friend indirect_iterator operator+ (const indirect_iterator& left, difference_type right)
						{
							return indirect_iterator (left.exprit_, left.inexprit_ + right);
						}

					friend indirect_iterator operator+ (difference_type left, const indirect_iterator& right)
						{
							return indirect_iterator (right.exprit_, right.inexprit_ + left);
						}

					friend indirect_iterator operator- (const indirect_iterator& left, difference_type right)
						{
							return indirect_iterator (left.exprit_, left.inexprit_ - right);
						}
					
					friend difference_type operator- (const indirect_iterator& left, const indirect_iterator& right)
						{
							return left.inexprit_ - right.inexprit_;
						}
						
					friend bool operator== (const indirect_iterator& left, const indirect_iterator& right)
						{
							return left.inexprit_ == right.inexprit_;
						}
						
					friend bool operator!= (const indirect_iterator& left, const indirect_iterator& right)
						{
							return left.inexprit_ != right.inexprit_;
						}

					friend bool operator< (const indirect_iterator& left, const indirect_iterator& right)
						{
							return left.inexprit_ < right.inexprit_;
						}
						
				private:
					const ExprIt exprit_;
					InExprIt inexprit_;
			};

		template <typename Expr, typename InExpr> class indirect_term:
			public term_base <typename Expr::value_type, indirect_term <Expr, InExpr> >
			{
				public:
					typedef typename Expr::value_type value_type;
					typedef indirect_iterator <typename Expr::const_iterator, typename InExpr::const_iterator> const_iterator;
						
					indirect_term (const Expr& expr, const InExpr& inexpr): expr_ (expr), inexpr_ (inexpr) { }

					value_type operator[] (size_t n) const		{ return expr_ [inexpr_ [n]]; }
					size_t size () const						{ return inexpr_.size (); }

					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), inexpr_.begin ());
						}

				private:
					const Expr& expr_;
					const InExpr& inexpr_;
			};
	};
	
namespace std
	{
		template <typename Val, typename InExpr> class indirect_array:
			public impl::subset_base <Val, indirect_array <Val, InExpr> >
			{
				public:
					typedef Val value_type;
					
					typedef impl::indirect_iterator <typename impl::array_base <Val>::const_iterator,
						typename InExpr::const_iterator> const_iterator;
					typedef impl::indirect_iterator <typename impl::array_base <Val>::iterator,
						typename InExpr::const_iterator> iterator;
						
					using impl::subset_base <Val, indirect_array <Val, InExpr> >::operator=;

					size_t size () const
						{
							return inexpr_.size ();
						}
						
					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), inexpr_.begin ());
						}

					iterator begin ()
						{
							return iterator (expr_.begin (), inexpr_.begin ());
						}
						
				private:
					impl::array_base <Val>& expr_;
					const InExpr& inexpr_;
					
					friend class impl::array_base <Val>;
					
					indirect_array (impl::array_base <Val>& expr, const InExpr& inexpr): expr_ (expr), inexpr_ (inexpr)
						{
						}
						
					// to allow valarray subsetters to return indirect_arrays
					indirect_array (const indirect_array& other): expr_ (other.expr_), inexpr_ (other.inexpr_)
						{
						}
			};
	};