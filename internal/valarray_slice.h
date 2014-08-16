/*
 *  valarray_slice.h
 *  macstl
 *
 *  Created by Glen Low on Mon Jun 09 2003.
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
 
#ifndef MACSTL_INTERNAL_VALARRAY_SLICE_H
#define MACSTL_INTERNAL_VALARRAY_SLICE_H

namespace std
	{
		/**
		 * @class slice macvalarray.h
		 * @ingroup valarray_public
		 * @brief BLAS-like slice.
		 *
		 * Represents a BLAS-like slice out of an array. It specifies a starting index, a length and a stride.
		 */
		class slice
			{
				public:
					/**
					 * @name constructors
					 * 26.3.4.1 [lib.slice.cons]
					 */
					 
					//@{
					
					/** Constructs a slice that selects nothing. */
					slice (): start_ (0), size_ (0), stride_ (0) { }
					
					/** Constructs a slice that selects @a start, @a start + @a stride ... [@a size times]. */
					slice (size_t start, size_t size, size_t stride): start_ (start), size_ (size), stride_ (stride) { }
					
					//@}
					
					/**
					 * @name accessors
					 * 26.3.4.2 [lib.slice.access]
					 */
					 
					//@{
					
					/** Returns the start index of the slice. */
					size_t start () const	{ return start_; }
					
					/** Returns the length of the slice. */
					size_t size () const	{ return size_; }
					
					/** Returns the stride of the slice. */
					size_t stride () const	{ return stride_; }
					
					//@}
					
				private:
					const size_t start_;
					const size_t size_;
					const size_t stride_;
			};

		namespace impl
			{
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Slice expression iterator.
				 * @param ExprIt The subsetted expression iterator.
				 * @par Models:
				 * Same iterator category as @a ExprIt.
				 *
				 * Serves as an iterator for slice terms.
				 */
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
					
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Slice expression term base.
				 * @param Expr The subsetted expression.
				 *
				 * This class serves as a base for slice terms.
				 */
				template <typename Expr> class slice_term_base
					{
						public:
							/** The element type, see std::valarray. */
							typedef typename Expr::value_type value_type;					
							
							/** Constant iterator into the term. */
							typedef slice_iterator <typename Expr::const_iterator> const_iterator;
							
							/** Returns the element at index @a n. */
							value_type operator[] (size_t index) const	{ return expr_ [index * slice_.stride () + slice_.start ()]; }
							
							/** Returns the number of elements. */
							size_t size () const						{ return slice_.size (); }
		
							/** Returns a const iterator to the first element. */
							const_iterator begin () const				{ return const_iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
												
						protected:
							const Expr& expr_;
							const std::slice slice_;
							
							slice_term_base (const Expr& expr, const std::slice& sliced): expr_ (expr), slice_ (sliced) { }
					};
					
				template <typename Expr, typename Val, bool is_const_chunkable> class slice_term_dispatch: public slice_term_base <Expr>
					{
						protected:
							slice_term_dispatch (const Expr& expr, const std::slice& sliced): slice_term_base <Expr> (expr, sliced) { }
					};
					
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Slice expression term.
				 * @param Expr The subsetted expression.
				 *
				 * Represents slice expressions e.g.
				 * @code
			 	 * std::valarray <float> v1;
				 * std::impl::slice_term <std::valarray <float> > t1 = v1 [std::slice (i, j, k)];
				 * @endcode
				 * A slice expression is only const chunkable when the argument expression is const chunkable,
				 * and the value_type is long, unsigned long or float.
				 */
				template <typename Expr> class slice_term:
					public slice_term_dispatch <slice_term <Expr>, typename Expr::value_type, const_chunkable <Expr>::value>,
					public term <typename Expr::value_type, slice_term <Expr> >
					{
						public:
							slice_term (const Expr& expr, const std::slice& sliced):
								slice_term_dispatch <slice_term <Expr>, typename Expr::value_type, const_chunkable <Expr>::value>
								(expr, sliced) { }
					};
					
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Slice array subset base.
				 * @param Expr The argument expression.
				 *
				 * This class serves as a base for slice arrays.
				 */
				template <typename Expr> class slice_array_base
					{
						public:
							/** The element type, see std::valarray. */
							typedef typename Expr::value_type value_type;
							
							/** Constant iterator into the subset. */
							typedef slice_iterator <typename Expr::const_iterator> const_iterator;	
							
							/** Mutable iterator into the subset. */
							typedef slice_iterator <typename Expr::iterator> iterator;				
							
							/** Returns the number of elements. */
							size_t size () const			{ return slice_.size (); }
								
							/** Returns a constant iterator to the first element. */
							const_iterator begin () const	{ return const_iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
							
							/** Returns a mutable iterator to the first element. */
							iterator begin ()				{ return iterator (expr_.begin (), slice_.start (), slice_.stride ()); }
							
						protected:
							Expr& expr_;
							const std::slice slice_;
		
							slice_array_base (Expr& expr, const std::slice& slice): expr_ (expr), slice_ (slice)
								{
								}
					};
					
				template <typename Expr, typename Val, bool is_const_chunkable>
					class slice_array_dispatch: public slice_array_base <Expr>
					{
						protected:
							slice_array_dispatch (Expr& expr, const std::slice& slice): slice_array_base <Expr> (expr, slice)
								{
								}
					};
		
			}
	
			
		/**
		 * @class slice_array macvalarray.h
		 * @ingroup valarray_public
		 * @brief Slice array subset.
		 * @param Val The element type, see std::valarray.
		 *
		 * Helper class used by the slice subsetter. It references a subset of an array specified by
		 * a std::slice object, e.g.
		 * @code
		 * v1 [std::slice (1, 5, 3)] = v2; // assigns elements of v2 to v1 [1], v1 [4] ... v1 [13]
		 * @endcode
		 * C++ programs should not instantiate this class directly.
		 */
		template <typename Val> class slice_array:
			public impl::slice_array_dispatch <impl::array <Val>, Val, impl::const_chunkable <impl::array <Val> >::value>,
			public impl::subset <Val, slice_array <Val> >
			{
				private:
					friend class impl::array <Val>;

					slice_array (impl::array <Val>& expr, const slice& slice):
						impl::slice_array_dispatch <impl::array <Val>, Val, impl::const_chunkable <impl::array <Val> >::value> (expr, slice)
						{
						}
						
			};
	}
	
#endif

