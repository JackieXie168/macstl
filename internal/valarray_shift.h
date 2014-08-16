/*
 *  valarray_shift.h
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

#ifndef MACSTL_INTERNAL_VALARRAY_SHIFT_H
#define MACSTL_INTERNAL_VALARRAY_SHIFT_H

namespace std
	{
		namespace impl
			{
				template <typename ExprIt> class shift_iterator
					{
						public:
							typedef typename iterator_ranker <std::bidirectional_iterator_tag,
								typename std::iterator_traits <ExprIt>::iterator_category>::type iterator_category;
							
							typedef typename std::iterator_traits <ExprIt>::value_type value_type;
							typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
							typedef value_type* pointer;
							typedef value_type& reference;
							
							shift_iterator (ExprIt exprit, int limit, int offset):
								exprit_ (exprit), limit_ (limit), offset_ (offset)
								{
									if (offset >= 0 && offset < limit)
										std::advance (exprit_, offset);
								}
								
							value_type operator* () const
								{
									return offset_ >= 0 && offset_ < limit_ ? *exprit_ : value_type ();
								}								
		
							shift_iterator& operator++ ()
								{
									if (offset_ >= 0 && offset_ < limit_)
										++exprit_;
									++offset_;
									return *this;
								}
								
							shift_iterator operator++ (int)
								{
									shift_iterator copy (*this);
									return ++copy;
								}
								
							shift_iterator& operator-- ()
								{
									if (offset_ > 0 && offset_ <= limit_)
										--exprit_;
									--offset_;
									return *this;
								}
								
							shift_iterator operator-- (int)
								{
									shift_iterator copy (*this);
									return --copy;
								}
																	
							friend bool operator== (const shift_iterator& left, const shift_iterator& right)
								{
									return left.offset_ == right.offset_;
								}
								
							friend bool operator!= (const shift_iterator& left, const shift_iterator& right)
								{
									return left.offset_ != right.offset_;
								}
								
						private:
							ExprIt exprit_;
							const int limit_;
							int offset_;
					};
					
				template <typename Expr> class shift_term:
					public term <typename Expr::value_type, shift_term <Expr> >
					{
						public:
							typedef typename Expr::value_type value_type;
							
							typedef shift_iterator <typename Expr::const_iterator> const_iterator;
		
							shift_term (const Expr& expr, int offset): expr_ (expr), offset_ (offset) { }
		
							value_type operator[] (size_t n) const
								{
									int index = n + offset_;
									return index >= 0 && index < expr_.size () ? expr_ [index] : value_type ();
								}
								
							size_t size () const	{ return expr_.size (); }
							const_iterator begin () const	{ return const_iterator (expr_.begin (), expr_.size (), offset_); }
					
						private:
							const Expr& expr_;
							size_t offset_;
					};
		
				template <typename ExprIt> class cshift_iterator
					{
						public:
							typedef typename iterator_ranker <std::bidirectional_iterator_tag,
								typename std::iterator_traits <ExprIt>::iterator_category>::type iterator_category;
							typedef typename std::iterator_traits <ExprIt>::value_type value_type;
							typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
							typedef value_type* pointer;
							typedef value_type& reference;
							
							cshift_iterator (ExprIt exprit, size_t size, difference_type offset):
								firstit_ (exprit), lastit_ (exprit), exprit_ (exprit)
								{
									std::advance (lastit_, size);
									std::advance (exprit_, offset % size);
								}
								
							value_type operator* () const
								{
									return *exprit_;
								}
							
							cshift_iterator& operator++ ()
								{
									if (++exprit_ == lastit_)
										exprit_ = firstit_;
										
									return *this;
								}
								
							cshift_iterator operator++ (int)
								{
									cshift_iterator copy (*this);
									return ++copy;
								}
								
							cshift_iterator& operator-- ()
								{
									if (exprit_ == firstit_)
										exprit_ = lastit_;
										
									--exprit_;
		
									return *this;
								}
		
							cshift_iterator operator-- (int)
								{
									cshift_iterator copy (*this);
									return --copy;
								}
							
							friend bool operator== (const cshift_iterator& left, const cshift_iterator& right)
								{
									return left.exprit_ == right.exprit_;
								}
								
							friend bool operator!= (const cshift_iterator& left, const cshift_iterator& right)
								{
									return left.exprit_ != right.exprit_;
								}
								
						private:
							const ExprIt firstit_;
							
							ExprIt lastit_;
							ExprIt exprit_;
					};
		
							
				template <typename Expr> class cshift_term:
					public term <typename Expr::value_type, cshift_term <Expr> >
					{
						public:
							typedef typename Expr::value_type value_type;
							
							typedef cshift_iterator <typename Expr::const_iterator> const_iterator;
		
							cshift_term (const Expr& expr, int offset): expr_ (expr), offset_ (offset) { }
		
							value_type operator[] (size_t n) const		{ return expr_ [(n + offset_) % expr_.size ()]; }
							size_t size () const						{ return expr_.size (); }
		
							const_iterator begin () const
								{
									return const_iterator (expr_.begin (), expr_.size (), offset_);
								}
					
						private:
							const Expr& expr_;
							const int offset_;
					};
			
			}
			
	}
	
#endif