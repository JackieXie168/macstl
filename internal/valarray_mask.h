/*
 *  valarray_mask.h
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

namespace impl
	{
		template <typename ExprIt, typename BExprIt> class mask_iterator
			{
				public:
					typedef typename iterator_ranker <
						std::bidirectional_iterator_tag,
						typename std::iterator_traits <BExprIt>::iterator_category>::type iterator_category;
					typedef typename std::iterator_traits <ExprIt>::value_type value_type;
					typedef typename std::iterator_traits <BExprIt>::difference_type difference_type;
					typedef typename std::iterator_traits <ExprIt>::pointer pointer;
					typedef typename std::iterator_traits <ExprIt>::reference reference;
					
					typedef typename dereference <reference>::type dereference;
					
					mask_iterator (ExprIt exprit, BExprIt bexprit, size_t size): exprit_ (exprit), bexprit_ (bexprit), lastit_ (bexprit)
						{
							std::advance (lastit_, size);
							while (bexprit_ != lastit_ && !*bexprit_)
								{
									++exprit_;
									++bexprit_;
								}
						}
						
					dereference operator* () const
						{
							return *exprit_;
						}
						
					mask_iterator& operator++ ()
						{
							do
								{
									++exprit_;
									++bexprit_;
								}
							while (bexprit_ != lastit_ && !*bexprit_);
							return *this;
						}
						
					mask_iterator operator++ (int)
						{
							mask_iterator copy (*this);
							return ++copy;
						}

					mask_iterator& operator-- ()
						{
							do
								{
									--exprit_;
									--bexprit_;
								}
							while (!*bexprit_);
							return *this;
						}
					
					mask_iterator operator-- (int)
						{
							mask_iterator copy (*this);
							return --copy;
						}

					friend bool operator== (const mask_iterator& left, const mask_iterator& right)
						{
							return left.exprit_ == right.exprit_;
						}
						
					friend bool operator!= (const mask_iterator& left, const mask_iterator& right)
						{
							return left.exprit_ != right.exprit_;
						}
						
				private:
					ExprIt exprit_;
					BExprIt bexprit_;
					BExprIt lastit_;
			};

		template <typename Expr, typename BExpr> class mask_term:
			public term <typename Expr::value_type, mask_term <Expr, BExpr> >
			{
				public:
					typedef typename Expr::value_type value_type;					
					typedef mask_iterator <typename Expr::const_iterator, typename BExpr::const_iterator> const_iterator;
					
					mask_term (const Expr& expr, const BExpr& bexpr):
						expr_ (expr), bexpr_ (bexpr), size_ (stdext::count_n (bexpr.begin (), bexpr.size (), true))
						{
						}

					value_type operator[] (size_t index) const
						{
							size_t indirect;
							for (indirect = 0; index; ++indirect)
								if (bexpr_ [indirect])
									--index;
									
							return expr_ [indirect];							
						}
					
					size_t size () const
						{
							return size_;
						}

					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), bexpr_.begin (), bexpr_.size ());
						}
												
				private:
					const Expr& expr_;
					const BExpr& bexpr_;
					const size_t size_;
			};
	};
	
namespace std
	{
		template <typename Val, typename BExpr> class mask_array: public impl::subset <Val, mask_array <Val, BExpr> >
			{
				public:
					typedef Val value_type;
					
					using impl::subset <Val, mask_array <Val, BExpr> >::operator=;

					typedef impl::mask_iterator <typename impl::array <Val>::const_iterator,
						typename BExpr::const_iterator> const_iterator;
					typedef impl::mask_iterator <typename impl::array <Val>::iterator,
						typename BExpr::const_iterator> iterator;
						
					size_t size () const
						{
							return size_;
						}

					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), bexpr_.begin (), bexpr_.size ());
						}
						
					iterator begin ()
						{
							return iterator (expr_.begin (), bexpr_.begin (), bexpr_.size ());
						}
						
				private:
					impl::array <Val>& expr_;
					const BExpr& bexpr_;
					const size_t size_;
					
					friend class impl::array <Val>;
					
					mask_array (impl::array <Val>& expr, const BExpr& bexpr):
						expr_ (expr), bexpr_ (bexpr), size_ (stdext::count_n (bexpr.begin (), bexpr.size (), true))
						{
						}
						
					// to allow valarray subsetters to return mask_arrays
					mask_array (const mask_array& other): expr_ (other.expr_), bexpr_ (other.bexpr_), size_ (other.size_)
						{
						}
			};	
	};

