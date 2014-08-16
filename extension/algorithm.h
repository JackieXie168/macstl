/*
 *  algorithm.h
 *  macstl
 *
 *  Created by Glen Low on Sat Apr 19 2003.
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

#ifndef MACSTL_EXTENSION_ALGORITHM_H
#define MACSTL_EXTENSION_ALGORITHM_H

#include <algorithm>

namespace stdext
	{
		template <typename InIter, typename Size, typename InCat> inline void destroy_n_dispatch (InIter, Size, InCat, __true_type)
			{
			}

		template <typename InIter, typename Size> inline void destroy_n_dispatch (InIter first, Size n, std::random_access_iterator_tag, __false_type)
			{
				typedef typename std::iterator_traits <InIter>::value_type value_type;
				for (Size count = 0; count != n; ++count)
					(&first [count])->~value_type ();
			}
			
		template <typename InIter, typename Size, typename InCat> inline void destroy_n_dispatch (InIter first, Size n, InCat, __false_type)
			{
				typedef typename std::iterator_traits <InIter>::value_type value_type;
				for (; n > 0; --n)
					{
						(&*first)->~value_type ();
						++first;
					}
			}
			
		template <typename InIter, typename Size> inline void destroy_n (InIter first, Size n)
			{
				typedef std::iterator_traits <InIter> in_traits;
				destroy_n_dispatch (first, n,
					typename in_traits::iterator_category (),
					typename __type_traits <typename std::iterator_traits <InIter>::value_type>::has_trivial_destructor ());
			}
			
		// both in & out iterators are random access
		// optimization: use explicit loop count, index into instead of incrementing iterators
		// unwind already constructed values if any construction throws
		template <typename InIter, typename Size, typename OutIter>
			inline std::pair <InIter, OutIter> uninitialized_copy_n_dispatch (InIter first, Size n, OutIter result,
				std::random_access_iterator_tag, std::random_access_iterator_tag)
			{
				typedef typename std::iterator_traits <OutIter>::value_type value_type;
				Size index = 0;
				try
					{
						for (; index != n; ++index)
							new (&result [index]) value_type (first [index]);
						return std::pair <InIter, OutIter> (first + n, result + n);
					}
				catch (...)
					{
						for (Size unwind = 0; unwind != index; ++unwind)
							result [unwind].~value_type ();
						throw;
					}
			}

		// default: use standard uninitialized copy
		template <typename InIter, typename Size, typename OutIter, typename InCat, typename OutCat>
			inline std::pair <InIter, OutIter> uninitialized_copy_n_dispatch (InIter first, Size n, OutIter result,
				InCat, OutCat)
			{
				typedef typename std::iterator_traits <OutIter>::value_type value_type;
				Size index = 0;
				try
					{
						for (; n > 0; --n)
							{
								new (&*result) value_type (*first);
								++first;
								++result;
							}
						return std::pair <InIter, OutIter> (first + n, result + n);
					}
				catch (...)
					{
						for (Size unwind = 0; unwind != index; ++unwind)
							result [unwind].~value_type ();
						throw;
					}
			}
		
		template <typename InIter, typename Size, typename OutIter>
			inline std::pair <InIter, OutIter> uninitialized_copy_n (InIter first, Size n, OutIter result)
			{
				typedef std::iterator_traits <InIter> in_traits;
				typedef std::iterator_traits <OutIter> out_traits;
				return uninitialized_copy_n_dispatch (first, n, result,
					typename in_traits::iterator_category (),
					typename out_traits::iterator_category ());
			}

/*			
		// out iterator is pointer, type has trivial destructor
		// optimization: restrict iterator and value, use explicit count, index into instead of incrementing iterators
		// assign instead of copy construct
		// note: we can do pointer restriction, instead of pass by value which may incur the overhead of copying,
		// since the range is uninitialized and cannot alias the initialized value
		template <typename Val>
			inline void uninitialized_fill_dispatch (Val* first, Val* last, const Val& val,
			std::random_access_iterator_tag, __true_type)
			{
				std::cout << "hey i came here.";
				const ptrdiff_t distance = last - first;
				const Val& __restrict__ unaliased_val = val;
				Val* __restrict__ unaliased_first = first;
				for (ptrdiff_t index = 0; index != distance; ++index)
					unaliased_first [index] = unaliased_val;
			}
*/

		// out iterators is random access
		// optimization: pass by value, use explicit loop count, index into instead of incrementing iterators
		// unwind already constructed values if any construction throws
		template <typename OutIter, typename Size, typename Val>
			inline OutIter uninitialized_fill_n_dispatch (OutIter first, Size n, const Val& val,
				std::random_access_iterator_tag)
			{
				Size index = 0;
				try
					{
						for (; index != n; ++index)
							new (&first [index]) Val (val);
						return first + n;
					}
				catch (...)
					{
						for (Size unwind = 0; unwind != index; ++unwind)
							(&first [unwind])->~Val ();
						throw;
					}
			}

		// default case
		template <typename OutIter, typename Size, typename Val, typename OutCat, typename TrivialDtor>
			inline OutIter uninitialized_fill_n_dispatch (OutIter first, Size n, const Val& val,
			OutCat)
			{
				return std::uninitialized_fill_n (first, n, val);
			}

		template <typename OutIter, typename Size, typename Val>
			inline OutIter uninitialized_fill_n (OutIter first, Size n, Val val)
			{
				typedef std::iterator_traits <OutIter> out_traits;
				return uninitialized_fill_n_dispatch (first, n, val,
					typename out_traits::iterator_category ());
			}
			
		template <typename InIter, typename Size, typename Type>
			inline Size count_n (InIter first, Size n, const Type& value)
			{
				Size counter = 0;
				for (Size index = 0; index != n; ++index)
					if (first [index] == value)
						++counter;
				return counter;
			}

		template <typename InIter, typename Size, typename OutIter>
			inline void copy_n_core (InIter first, Size n, OutIter result)
			{
				for (Size index = 0; index != n; ++index)
					result [index] = first [index];
			}
			
		// both in & out iterators are random access
		// optimization: use explicit loop count, index into instead of incrementing iterators,
		template <typename InIter, typename Size, typename OutIter>
			inline std::pair <InIter, OutIter> copy_n_dispatch (InIter first, Size n, OutIter result,
				std::random_access_iterator_tag, std::random_access_iterator_tag)
			{
				copy_n_core (first, n, result);
				return std::pair <InIter, OutIter> (first + n, result + n);
			}

		// default: use the standard copy
		template <typename InIter, typename Size, typename OutIter, typename InCat, typename OutCat>
			inline std::pair <InIter, OutIter> copy_n_dispatch (InIter first, Size n, OutIter result, InCat, OutCat)
			{
				for (; n > 0; --n)
					{
						*result = *first;
						++first;
						++result;
					}
				return std::pair <InIter, OutIter> (first, result);
			}
			

		template <typename InIter, typename Size, typename OutIter>
			inline std::pair <InIter, OutIter> copy_n (InIter first, Size n, OutIter result)
			{
				typedef std::iterator_traits <InIter> in_traits;
				typedef std::iterator_traits <OutIter> out_traits;
				return copy_n_dispatch (first, n, result,
					typename in_traits::iterator_category (),
					typename out_traits::iterator_category ());
			}
		
		template <typename OutIter, typename Size, typename Val>
			inline void fill_n_core (OutIter first, Size n, const Val& val)
			{
				for (Size index = 0; index != n; ++index)
					first [index] = val;
			}

		// out iterators is random access
		// optimization: pass by value, use explicit loop count, index into instead of incrementing iterators
		template <typename OutIter, typename Size, typename Val>
			inline OutIter fill_n_dispatch (OutIter first, Size n, const Val& val,
				std::random_access_iterator_tag)
			{
				fill_n_core (first, n, val);
				return first + n;
			}

		// default case
		template <typename OutIter, typename Size, typename Val, typename OutCat>
			inline OutIter fill_n_dispatch (OutIter first, Size n, const Val& val,
			OutCat)
			{
				return std::fill_n (first, n, val);
			}

		template <typename OutIter, typename Size, typename Val>
			inline OutIter fill_n (OutIter first, Size n, const Val& val)
			{
				typedef std::iterator_traits <OutIter> out_traits;
				return fill_n_dispatch (first, n, val,
					typename out_traits::iterator_category ());		
			}
			
		template <typename InIter, typename Size, typename UOp>
			inline UOp for_each_n_dispatch (InIter first, Size n, UOp op, std::random_access_iterator_tag)
			{
				for (Size index = 0; index != n; ++index)
					op (first [index]);
				return op;
			}
			
		template <typename InIter, typename Size, typename UOp, typename InCat>
			inline UOp for_each_n_dispatch (InIter first, Size n, UOp op, InCat)
			{
				for (; n > 0; --n)
					{
						op (*first);
						++first;
					}
				return op;
			}
			
		template <typename InIter, typename Size, typename UOp>
			inline UOp for_each_n (InIter first, Size n, UOp op)
			{
				typedef std::iterator_traits <InIter> in_traits;
				return for_each_n_dispatch (first, n, op,
					typename in_traits::iterator_category ());
			}
			
		template <typename InIter1, typename Size, typename InIter2, typename BOp>
			inline BOp for_each_n_dispatch (InIter1 first1, Size n, InIter2 first2, BOp op, std::random_access_iterator_tag, std::random_access_iterator_tag)
			{
				for (Size index = 0; index != n; ++index)
					op (first1 [index], first2 [index]);
				return op;
			}
			
		template <typename InIter1, typename Size, typename InIter2, typename BOp,
			typename InCat1, typename InCat2>
			inline BOp for_each_n_dispatch (InIter1 first1, Size n, InIter2 first2, BOp op,
			InCat1, InCat2)
			{
				for (; n > 0; --n)
					{
						op (*first1, *first2);
						++first1;
						++first2;
					}
				return op;
			}
			
		template <typename InIter1, typename Size, typename InIter2, typename BOp>
			inline BOp for_each_n (InIter1 first1, Size n, InIter2 first2, BOp op)
			{
				typedef std::iterator_traits <InIter1> in_traits1;
				typedef std::iterator_traits <InIter2> in_traits2;
				return for_each_n_dispatch (first1, n, first2, op,
					typename in_traits1::iterator_category (),
					typename in_traits2::iterator_category ());
			}

	}

#endif