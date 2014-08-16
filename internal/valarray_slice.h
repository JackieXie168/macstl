/*
 *  valarray_slice.h
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

namespace std
	{
		class slice
			{
				public:
					// 26.3.4.1 lib.slice.cons
					
					slice (): start_ (0), size_ (0), stride_ (0) { }
					slice (size_t start, size_t size, size_t stride): start_ (start), size_ (size), stride_ (stride) { }
					
					// 26.3.4.2 lib.slice.access
					
					size_t start () const	{ return start_; }
					size_t size () const	{ return size_; }
					size_t stride () const	{ return stride_; }
					
				private:
					const size_t start_;
					const size_t size_;
					const size_t stride_;
			};
	};
	
namespace impl
	{
		template <typename ExprIt> class slice_iterator
			{
				public:
					typedef typename std::iterator_traits <ExprIt>::iterator_category iterator_category;
					typedef typename std::iterator_traits <ExprIt>::value_type value_type;
					typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
					typedef typename std::iterator_traits <ExprIt>::pointer pointer;
					typedef typename std::iterator_traits <ExprIt>::reference reference;
					
					typedef typename dereference <reference>::type dereference;
					
					slice_iterator (ExprIt exprit, size_t start, size_t stride): exprit_ (exprit), stride_ (stride)
						{
							std::advance (exprit_, start);
						}
						
					dereference operator* () const						{ return *exprit_; }
					dereference operator[] (difference_type n) const	{ return exprit_ [n * stride_]; }
					
					slice_iterator& operator++ ()						{ std::advance (exprit_, stride_); return *this; }
					slice_iterator operator++ (int)						{ slice_iterator copy (*this); return ++copy; }
					slice_iterator& operator+= (difference_type n)		{ exprit_ += n * stride_; return *this; }
	
					slice_iterator& operator-- ()						{ std::advance (exprit_, -stride_); return *this; }
					slice_iterator operator-- (int)						{ slice_iterator copy (*this); return --copy; }
					slice_iterator& operator-= (difference_type n)		{ exprit_ -= n * stride_; return *this; }
						
					friend slice_iterator operator+ (const slice_iterator& left, difference_type right)
						{
							return slice_iterator (left.exprit_, right * left.stride_, left.stride_);
						}
	
					friend slice_iterator operator+ (difference_type left, const slice_iterator& right)
						{
							return slice_iterator (right.exprit_, left * right.stride_, right.stride_);
						}
	
					friend slice_iterator operator- (const slice_iterator& left, difference_type right)
						{
							return slice_iterator (left.exprit_, -right * left.stride_, left.stride_);
						}
					
					friend difference_type operator- (const slice_iterator& left, const slice_iterator& right)
						{
							return (left.exprit_ - right.exprit_) / left.stride_;
						}
						
					friend bool operator== (const slice_iterator& left, const slice_iterator& right)
						{
							return left.exprit_ == right.exprit_;
						}
						
					friend bool operator!= (const slice_iterator& left, const slice_iterator& right)
						{
							return left.exprit_ != right.exprit_;
						}

					friend bool operator< (const slice_iterator& left, const slice_iterator& right)
						{
							return left.exprit_ < right.exprit_;
						}
						
				private:
					ExprIt exprit_;
					const size_t stride_;
			};
			
		template <typename Expr> class slice_term_base
			{
				public:
					typedef typename Expr::value_type value_type;					
					typedef slice_iterator <typename Expr::const_iterator> const_iterator;
					
					value_type operator[] (size_t index) const	{ return expr_ [index * slice_.stride () + slice_.start ()]; }
					size_t size () const						{ return slice_.size (); }

					const_iterator begin () const				{ return const_iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
										
				protected:
					const Expr& expr_;
					const std::slice slice_;
					
					slice_term_base (const Expr& expr, const std::slice& sliced): expr_ (expr), slice_ (sliced) { }
			};
			
		template <typename Expr, typename Val, bool is_const_chunkable> class slice_term_dispatch: public slice_term_base <Expr>
			{
				protected:
					slice_term_dispatch (const Expr& expr, const std::slice& sliced):
						slice_term_base <Expr> (expr, sliced) { }
			};
			
		template <typename Expr> class slice_term:
			public term <typename Expr::value_type, slice_term <Expr> >,
			public slice_term_dispatch <Expr, typename Expr::value_type, const_chunkable <Expr>::value>
			{
				public:
					slice_term (const Expr& expr, const std::slice& sliced):
						slice_term_dispatch <Expr, typename Expr::value_type, const_chunkable <Expr>::value> (expr, sliced) { }
			};
			
		template <typename Expr> class slice_array_base
			{
				public:
					typedef typename Expr::value_type value_type;
					typedef slice_iterator <typename Expr::const_iterator> const_iterator;
					typedef slice_iterator <typename Expr::iterator> iterator;
					
					size_t size () const			{ return slice_.size (); }
						
					const_iterator begin () const	{ return const_iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
					iterator begin ()				{ return iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
					
				protected:
					Expr& expr_;
					const std::slice slice_;

					slice_array_base (Expr& expr, const std::slice& slice): expr_ (expr), slice_ (slice)
						{
						}
			};
			
		template <typename Expr, typename Val, bool is_const_chunkable> class slice_array_dispatch: public slice_array_base <Expr>
			{
				protected:
					slice_array_dispatch (Expr& expr, const std::slice& slice): slice_array_base <Expr> (expr, slice)
						{
						}
			};

	};
	
namespace std
	{
		template <typename Val> class slice_array:
			public impl::subset <Val, slice_array <Val> >,
			public impl::slice_array_dispatch <impl::array <Val>, Val, impl::const_chunkable <impl::array <Val> >::value>
			{
				private:
					friend class impl::array <Val>;

					slice_array (impl::array <Val>& expr, const slice& slice):
						impl::slice_array_dispatch <impl::array <Val>, Val, impl::const_chunkable <impl::array <Val> >::value> (expr, slice)
						{
						}
						
					// to allow valarray subsetters to return slice_arrays
					slice_array (const slice_array& other):
						impl::slice_array_dispatch <impl::array <Val>, Val, impl::const_chunkable <impl::array <Val> >::value> (other)
						{
						}

			};
	};

