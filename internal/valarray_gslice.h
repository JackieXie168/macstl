/*
 *  valarray_gslice.h
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
 
#ifndef MACSTL_INTERNAL_VALARRAY_GSLICE_H
#define MACSTL_INTERNAL_VALARRAY_GSLICE_H

namespace std
	{
		namespace impl
			{
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Gslice expression iterator.
				 * @param ExprIt The subsetted expression iterator.
				 * @par Models:
				 * Least refined iterator category of Bidirectional Iterator and @a ExprIt.
				 *
				 * Serves as an iterator for gslice terms and subsets.
				 */
				template <typename ExprIt> class gslice_iterator
					{
						public:
							typedef typename iterator_ranker <
								std::bidirectional_iterator_tag,
								typename std::iterator_traits <ExprIt>::iterator_category>::type iterator_category;
								
							typedef typename std::iterator_traits <ExprIt>::value_type value_type;
							typedef typename std::iterator_traits <ExprIt>::difference_type difference_type;
							typedef typename std::iterator_traits <ExprIt>::pointer pointer;
							typedef typename std::iterator_traits <ExprIt>::reference reference;
							
							typedef typename dereference <reference>::type dereference;
							
							gslice_iterator (ExprIt exprit, const std::gslice& slice):
								lengther_ (slice.length_.begin ()),
								strider_ (slice.stride_.begin ()),
								exprit_ (exprit),
								indexer_ (slice.length_.size ())
								{
									std::advance (exprit_, slice.start_);
								}
								
							dereference operator* () const
								{
									return *exprit_;
								}
								
							gslice_iterator& operator++ ()
								{
									for (size_t dim = indexer_.size (); dim; --dim)
										{
											if (++(indexer_ [dim - 1]) != lengther_ [dim - 1])
												{
													std::advance (exprit_, strider_ [dim - 1]);
													break;
												}
											else
												{
													indexer_ [dim - 1] = 0;
													std::advance (exprit_, (1 - lengther_ [dim - 1]) * strider_ [dim - 1]);
												}
										}
									return *this;
								}
								
							gslice_iterator operator++ (int)
								{
									gslice_iterator copy (*this);
									return ++copy;
								}
								
							gslice_iterator& operator-- ()
								{
									for (size_t dim = index_.size (); dim; --dim)
										{
											if (indexer_ [dim - 1])
												{
													--(indexer_ [dim - 1]);
													std::advance (exprit_, -strider_ [dim - 1]);
													break;
												}
											else
												{
													indexer_ [dim - 1] = lengther_ [dim - 1] - 1;
													std::advance (exprit_, (lengther_ [dim - 1] - 1) * strider_ [dim - 1]);
												}
										}
									return *this;						
								}
							
							friend bool operator== (const gslice_iterator& left, const gslice_iterator& right)
								{
									return left.exprit_ == right.exprit_;
								}
								
							friend bool operator!= (const gslice_iterator& left, const gslice_iterator& right)
								{
									return left.exprit_ != right.exprit_;
								}
								
						private:
							const std::valarray <size_t>::const_iterator lengther_;
							const std::valarray <size_t>::const_iterator strider_;
							
							ExprIt exprit_;
							std::valarray <size_t> indexer_;
					};
					
				/**
				 * @internal
				 * @ingroup valarray_internal
				 * @brief Gslice expression term.
				 * @param Expr The subsetted expression.
				 *
				 * Represents gslice expressions e.g.
				 * @code
			 	 * std::valarray <float> v1;
				 * std::impl::gslice_term <std::valarray <float> > t1 = v1 [std::gslice (i, vj, vk)];
				 * @endcode
				 * A gslice expression is not const chunkable.
				 */
				template <typename Expr> class gslice_term:
					public term <typename Expr::value_type, gslice_term <Expr> >
					{
						public:
							typedef typename Expr::value_type value_type;
							typedef gslice_iterator <typename Expr::const_iterator> const_iterator;
								
							gslice_term (const Expr& expr, const std::gslice& slice): expr_ (expr), slice_ (slice),
								size_ (std::accumulate (slice.length_, slice.length_ + slice.length_.size (), 1, std::multiplies <size_t> ()))
								{
								}
		
							value_type operator[] (size_t n) const
								{
									size_t index = slice_.start_;
									
									std::valarray <size_t>::const_iterator lengther = slice_.length_.begin ();
									std::valarray <size_t>::const_iterator strider = slice_.stride_.begin ();
									
									for (size_t dim = slice_.length_.size (); dim; --dim)
										{
											size_t len = lengther [dim - 1];
											index += (n % len) * strider [dim - 1];
										
											n /= len;
										}
									
									return expr_ [index];							
								}
							
							size_t size () const
								{
									return size_;
								}
		
							const_iterator begin () const
								{
									return const_iterator (expr_.begin (), slice_);
								}
		
						private:
							const Expr& expr_;
							const std::gslice& slice_;
							const size_t size_;
					};
		
			}
			
		/**
		 * @class gslice macvalarray.h
		 * @ingroup valarray_public
		 * @brief Generalized slice.
		 *
		 * Represents a generalized slice out of an array. It specifies a starting index, a set of lengths and a set of strides;
		 * the number of lengths shall equal the number of strides. The gslice is useful for building multidimensional arrays out
		 * of the one-dimensional std::valarray.
		 *
		 * In order to step through each element selected by a gslice:
		 * - Suppose <code>size</code> and <code>stride</code> have <code>n</code> elements.
		 * - Make <code>index</code> with <code>n</code> elements, all set to 0.
		 * - Increment the last index. Each <code>index [i]</code> may range from <code>0</code> to <code>size [i] - 1</code>, and if incrementing
		 *   <code>index [i]</code> would exceed that range, set to 0 and increment <code>index [i - 1]</code> instead.
		 * - The actual address is <code>start</code> + sum of <code>index [i] * stride [i]</code> for all i.
		 * .
		 * An example that appears in the Standard:
		 * - Suppose <code>start</code> = 3, <code>length</code> = {2, 4, 3}, <code>stride</code> = {19, 4, 1}.
		 * - Make <code>index</code> with 3 elements.
		 * - Increment the last index. This yields {0, 0, 0}, {0, 0, 1}, {0, 0, 2}, {0, 1, 0}, {0, 1, 1}, {0, 1, 2}, {0, 2, 0},
		 *   {0, 2, 1}, {0, 2, 2}, {0, 3, 0}, {0, 3, 1}, {0, 3, 2}, {1, 0, 0}, {1, 0, 1} ...
		 * - The actual address are then: 3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 16, 17, 22, 23 ...
		 * .
		 */
		class gslice
			{
				public:
					/**
					 * @name constructors
					 * 26.3.6.1 [lib.gslice.cons]
					 */
					 
					//@{
					
					/** Constructs a degenerate gslice. */
					gslice (): start_ (0), length_ (), stride_ ()
						{
						}
						
					/** Constructs a gslice with @a start, a set of @a length and a set of @a stride. */
					gslice (size_t start, const valarray <size_t>& length, const valarray <size_t>& stride):
						start_ (start), length_ (length), stride_ (stride)
						{
							// assert (length.size () == stride.size ());
						}
						
					//@}
						
					/**
					 * @name accessors
					 * 26.3.6.2 [lib.gslice.access]
					 */
					 
					//@{
					
					/** Returns the start index of the gslice. */
					size_t start () const					{ return start_; }
					
					/** Returns the lengths of the gslice. */
					impl::array <size_t> size () const		{ return length_; }
					
					/** Returns the strides of the gslice. */
					impl::array <size_t> stride () const	{ return stride_; }
					
					//@}
					
				private:
					const size_t start_;
					const valarray <size_t> length_;
					const valarray <size_t> stride_;
					
					template <typename ExprIt> friend class impl::gslice_iterator;
					template <typename Expr> friend class impl::gslice_term;
					template <typename Val> friend class gslice_array;
			};
	
		/**
		 * @class gslice_array macvalarray.h
		 * @ingroup valarray_public
		 * @brief Gslice array subset.
		 * @param Val The element type, see std::valarray.
		 *
		 * Helper class used by the gslice subsetter. It references a subset of an array specified by
		 * a std::gslice object.
		 *
		 * C++ programs should not instantiate this class directly.
		 */
		template <typename Val> class gslice_array: public impl::subset <Val, gslice_array <Val> >
			{
				public:
					/** The element type, see std::valarray. */
					typedef Val value_type;
					
					using impl::subset <Val, gslice_array <Val> >::operator=;
					
					/** Constant iterator into the subset. */
					typedef impl::gslice_iterator <typename impl::array <Val>::const_iterator> const_iterator;

					/** Mutable iterator into the subset. */
					typedef impl::gslice_iterator <typename impl::array <Val>::iterator> iterator;
					
					/** Returns the number of elements. */
					size_t size () const
						{
							return size_;
						}
						
					/** Returns a constant iterator to the first element. */
					const_iterator begin () const
						{
							return const_iterator (expr_.begin (), slice_);
						}

					/** Returns a mutable iterator to the first element. */
					iterator begin ()
						{
							return iterator (expr_.begin (), slice_);
						}
						
				private:
					impl::array <Val>& expr_;
					const gslice& slice_;
					const size_t size_;

					friend class impl::array <Val>;

					gslice_array (impl::array <Val>& expr, const gslice& slice): expr_ (expr), slice_ (slice),
						size_ (std::accumulate (slice.length_, slice.length_ + slice.length_.size (), 1, std::multiplies <size_t> ()))
						{
						}
						
					// to allow valarray subsetters to return slice_arrays
					gslice_array (const gslice_array& other): expr_ (other.expr_), slice_ (other.slice_), size_ (other.size_)
						{
						}

			};
			
	}
	
#endif
