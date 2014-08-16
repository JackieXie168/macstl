/*
 *  valarray_algorithm.h
 *  macstl
 *
 *  Created by Glen Low on Sun Jun 22 2003.
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
		// these versions of the std algorithms take valarray expressions (which expose begin (), size () and possibly chunked
		// versions of these members) instead of iterators, and assume that underlying value types are all "valarrayable" i.e.
		// that destruction + copy construction = assignment. This allows dispatching on whether the type has a trivial destructor,
		// which implies that copy construction = assignment, and also on whether the expressions are chunkable.
		
		// accumulate_array
		
		template <template <typename> class Func, typename Expr, typename Val, bool is_const_chunkable> struct accumulator;		
		
		template <template <typename> class Func, typename Expr, typename Val> struct accumulator <Func, Expr, Val, false>
			{
				static Val call (const Expr& expr)
					{
						typename Expr::const_iterator valuer = expr.begin ();
						Val value = *valuer;
						return stdext::for_each_n (++valuer, expr.size () - 1,
							Func <Val> (value)).result ();
					}
			};
			
		template <template <typename> class Func, typename Expr, typename Val> struct accumulator <Func, Expr, Val, true>
			{
				static Val call (const Expr& expr)
					{
						typedef typename std::iterator_traits <typename Expr::const_chunk_iterator>::value_type chunk_type;
						
						const size_t size = expr.size ();
						const size_t chunks = size / Expr::chunk_length;
						
						if (chunks)
							{
								// if there are any chunks, scalarize over each chunk
								typename Expr::const_chunk_iterator chunker = expr.chunk_begin ();
								chunk_type chunk = *chunker;
								Func <Val> func = stdext::for_each_n (++chunker, chunks - 1,
									Func <chunk_type> (chunk));
									
								const size_t tail = size % Expr::chunk_length;
								typename Expr::const_iterator iter = expr.begin ();
								std::advance (iter, size - tail);
								return stdext::for_each_n (iter, tail, func).result ();
							}
						else
							return accumulator <Func, Expr, Val, false>::call (expr);
					}
			};
			
		// specializations for min and max bool; since the domain only has two values, we optimize by checking whether either true or
		// false is reached, and forgetting about the rest of the array

		template <typename Iter, typename Size> bool accumulate_all (Iter iter, Size n, std::random_access_iterator_tag)
			{
				bool result = true;
				for (Size i = 0; i != n; ++i)
					if (!iter [i])
						{
							result = false;
							break;
						}
				return result;
			}
		
		template <typename Iter, typename Size> bool accumulate_any (Iter iter, Size n, std::random_access_iterator_tag)
			{
				bool result = false;
				for (Size i = 0; i != n; ++i)
					if (iter [i])
						{
							result = true;
							break;
						}
				return result;
			}
			
		template <typename Iter, typename Size, typename Cat> bool accumulate_all (Iter iter, Size n, Cat)
			{
				bool result = true;
				for (; n > 0; --n, ++iter)
					if (!*iter)
						{
							result = false;
							break;
						}
				return result;
			}
		
		template <typename Iter, typename Size, typename Cat> bool accumulate_any (Iter iter, Size n, Cat)
			{
				bool result = false;
				for (; n > 0; --n, ++iter)
					if (*iter)
						{
							result = true;
							break;
						}
				return result;
			}

		template <typename Expr> struct accumulator <minimize, Expr, bool, false>
			{
				static bool call (const Expr& expr)
					{
						return accumulate_all (expr.begin (), expr.size (),
							typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
					}
			
			};

		template <typename Expr> struct accumulator <maximize, Expr, bool, false>
			{
				static bool call (const Expr& expr)
					{
						return accumulate_any (expr.begin (), expr.size (),
							typename std::iterator_traits <typename Expr::const_iterator>::iterator_category ());
					}
			
			};

		template <template <typename> class Func, typename Expr> typename Expr::value_type accumulate_array (const Expr& expr)
			{
				return accumulator <Func, Expr, typename Expr::value_type, const_chunkable <Expr>::value>::call (expr);
			}
			
		// copy_array
		// uninitialized_copy_array
		
		template <typename Expr1, typename Expr2> void copy_array_tail (Expr1& expr1, const Expr2& expr2)
			{
				size_t size = expr1.size ();
				size_t tail = size % Expr1::chunk_length;

				// skip over all the chunked parts
				typename Expr1::iterator iter1 = expr1.begin ();
				typename Expr2::const_iterator iter2 = expr2.begin ();
				std::advance (iter1, size - tail);
				std::advance (iter2, size - tail);
				
				// only copy the part at the tail
				stdext::copy_n (iter2, tail, iter1);
			}

		template <typename Expr1, typename Expr2> void uninitialized_copy_array_tail (Expr1& expr1, const Expr2& expr2)
			{
				size_t size = expr1.size ();
				size_t tail = size % Expr1::chunk_length;

				// skip over all the chunked parts
				typename Expr1::iterator iter1 = expr1.begin ();
				typename Expr2::const_iterator iter2 = expr2.begin ();
				std::advance (iter1, size - tail);
				std::advance (iter2, size - tail);
				
				// only copy the part at the tail
				stdext::uninitialized_copy_n (iter2, tail, iter1);
			}
		
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __true_type, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::copy_n (expr2.chunk_begin (), expr1.size () / Expr1::chunk_length, expr1.chunk_begin ());

				// copy the tail. NOTE: this is in a separate function to minimize aliasing issues
				copy_array_tail (expr1, expr2);
			}
		
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __false_type, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::uninitialized_copy_n (expr2.chunk_begin (), expr1.size () / Expr1::chunk_length, expr1.chunk_begin ());
				
				// copy the tail. NOTE: this is in a separate function to minimize aliasing issues
				uninitialized_copy_array_tail (expr1, expr2);	
			}
	
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __true_type, __false_type)
			{
		//		std::cout << "not chunker.\n";
				stdext::copy_n (expr2.begin (), expr1.size (), expr1.begin ());
			}
			
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __false_type, __false_type)
			{
		//		std::cout << "not chunker.\n";
				stdext::uninitialized_copy_n (expr2.begin (), expr1.size (), expr1.begin ());
			}
			
		template <typename Expr1, typename Expr2> void uninitialized_copy_array (Expr1& expr1, const Expr2& expr2)
			{
				copy_array_dispatch (expr1, expr2, typename __type_traits <typename Expr1::value_type>::has_trivial_destructor (),
					typename to_boolean <
						chunkable <Expr1>::value &&
						const_chunkable <Expr2>::value &&
						rechunkable <Expr1, Expr2>::value>::type ());
			}

		template <typename Expr1, typename Expr2> void copy_array (Expr1& expr1, const Expr2& expr2)
			{
				copy_array_dispatch (expr1, expr2, __true_type (),
					typename to_boolean <
						chunkable <Expr1>::value &&
						const_chunkable <Expr2>::value &&
						rechunkable <Expr1, Expr2>::value>::type ());
			}

		// fill_array
		// uninitialized_fill_array

		template <typename Expr> void fill_array_tail (Expr& expr, typename Expr::value_type val)
			{
				size_t size = expr.size ();
				size_t tail = size % Expr::chunk_length;

				// skip over all the chunked parts
				typename Expr::iterator iter = expr.begin ();
				std::advance (iter, size - tail);
				
				// only copy the part at the tail
				stdext::fill_n (iter, tail, val);
			}

		template <typename Expr> void uninitialized_fill_array_tail (Expr& expr, typename Expr::value_type val)
			{
				size_t size = expr1.size ();
				size_t tail = size % Expr::chunk_length;

				// skip over all the chunked parts
				typename Expr::iterator iter = expr.begin ();
				std::advance (iter, size - tail);
				
				// only copy the part at the tail
				stdext::uninitialized_copy_n (iter, tail, val);
			}

		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __true_type, __true_type)
			{
				stdext::fill_n (expr.chunk_begin (), expr.size () / Expr::chunk_length,
					static_cast <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (val));
				fill_array_tail (expr, val);
			}
			
		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __false_type, __true_type)
			{
				stdext::uninitialized_fill_n (expr.chunk_begin (), expr.size () / Expr::chunk_length,
					static_cast <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (val));
				uninitialized_fill_tail (expr, val);
			}

		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __true_type, __false_type)
			{
				stdext::fill_n (expr.begin (), expr.size (), val);
			}
			
		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __false_type, __false_type)
			{
				stdext::uninitialized_fill_n (expr.begin (), expr.size (), val);
			}
			
		template <typename Expr> void uninitialized_fill_array (Expr& expr, typename Expr::value_type val)
			{
				fill_array_dispatch (expr, val,
					typename __type_traits <typename Expr::value_type>::has_trivial_destructor (),
					typename to_boolean <chunkable <Expr>::value>::type ());
			}
			
		template <typename Expr> void fill_array (Expr& expr, typename Expr::value_type val)
			{
				fill_array_dispatch (expr, val, __true_type (),
					typename Expr::chunkable ());
			}

		// for_each_array
		
		template <typename Expr1, typename Expr2, template <typename> class Func> void for_each_array_tail
			(Expr1& expr1, const Expr2& expr2, Func <typename Expr1::value_type> func)
			{
				size_t size = expr1.size ();
				size_t tail = size % Expr1::chunk_length;

				// skip over all the chunked parts
				typename Expr1::iterator iter1 = expr1.begin ();
				typename Expr2::const_iterator iter2 = expr2.begin ();
				std::advance (iter1, size - tail);
				std::advance (iter2, size - tail);
				
				// only for-each the part at the tail
				stdext::for_each_n (iter1, tail, iter2, func);
			}

		template <typename Expr, template <typename> class Func> void for_each_array_tail
			(Expr& expr, Func <typename Expr::value_type> func)
			{
				size_t size = expr.size ();
				size_t tail = size % Expr::chunk_length;

				// skip over all the chunked parts
				typename Expr::iterator iter = expr.begin ();
				std::advance (iter, size - tail);
				
				// only for-each the part at the tail
				stdext::for_each_n (iter, tail, func);
			}
	
		template <typename Expr1, typename Expr2, template <typename> class Func> void for_each_array_dispatch
			(Expr1& expr1, const Expr2& expr2, Func <typename Expr1::value_type> func, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::for_each_n (expr1.chunk_begin (), expr1.size () / Expr1::chunk_length, expr2.chunk_begin (),
					Func <typename std::iterator_traits <typename Expr1::chunk_iterator>::value_type> (func));
					
				for_each_array_tail (expr1, expr2, func);
			}
			
		template <typename Expr1, typename Expr2, template <typename> class Func> void for_each_array_dispatch
			(Expr1& expr1, const Expr2& expr2, Func <typename Expr1::value_type> func, __false_type)
			{
			//	std::cout << "not chunker.\n";
				stdext::for_each_n (expr1.begin (), expr1.size (), expr2.begin (), func);
			}
			
		template <typename Expr1, typename Expr2, template <typename> class Func> void for_each_array
			(Expr1& expr1, const Expr2& expr2, Func <typename Expr1::value_type> func)
			{
				for_each_array_dispatch (expr1, expr2, func,
					typename to_boolean <
						chunkable <Expr1>::value &&
						const_chunkable <Expr2>::value &&
						rechunkable <Expr1, Expr2>::value>::type ());
			}
		
		template <typename Expr, template <typename> class Func> void for_each_array_dispatch (Expr& expr, Func <typename Expr::value_type> func, __true_type)
			{
		//		std::cout << "chunker.\n";
				stdext::for_each_n (expr.chunk_begin (), expr.size () / Expr::chunk_length,
					Func <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (func));
					
				for_each_array_tail (expr, func);
			}
	
		template <typename Expr, template <typename> class Func> void for_each_array_dispatch (Expr& expr, Func <typename Expr::value_type> func, __false_type)
			{
		//		std::cout << "not chunker.\n";
				stdext::for_each_n (expr.begin (), expr.size (), func);
			}
	
		template <template <typename> class Func, typename Expr> void for_each_array (Expr& expr, Func <typename Expr::value_type> func)
			{
				for_each_array_dispatch (expr, func,
					typename to_boolean <const_chunkable <Expr>::value>::type ());
			}
	
	};

