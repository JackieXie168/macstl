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
		
		template <typename Expr, typename Func>
			inline typename Expr::value_type accumulate_array_dispatch (const Expr& expr, Func, __true_type)
			{
				typedef typename Expr::value_type value_type;
				typedef typename std::iterator_traits <typename Expr::const_chunk_iterator>::value_type chunk_type;
				
				const size_t values = expr.size ();
				const size_t length = sizeof (chunk_type) / sizeof (value_type);
				const size_t chunks = values / length;
				
				if (chunks)
					{
						// if there are any chunks, scalarize over each chunk
						typename Expr::const_chunk_iterator chunker = expr.chunk_begin ();
						chunk_type chunk = *chunker;
						typename Func::operation <value_type> func = stdext::for_each_n (++chunker, chunks - 1,
							typename Func::operation <chunk_type> (chunk));
							
						for (size_t leftover = chunks * length; leftover != values; ++leftover)
							func (expr [leftover]);
						
						return func.result ();
					}
				else
					{
						// if there are no chunks, 
						typename Func::operation <value_type> func = expr [0];
						for (size_t leftover = 1; leftover != values; ++leftover)
							func (expr [leftover]);
						return func.result ();
					}
			}
		
		template <typename Expr, typename Func>
			inline typename Expr::value_type accumulate_array_dispatch (const Expr& expr, Func, __false_type)
			{
		//		std::cout << "not chunker.\n";
				
				typename Expr::const_iterator valuer = expr.begin ();
				typename Expr::value_type value = *valuer;
				return stdext::for_each_n (++valuer, expr.size () - 1,
					typename Func::operation <typename Expr::value_type> (value)).result ();
			}
			
		template <typename Expr, typename Func>
			inline typename Expr::value_type accumulate_array (const Expr& expr, Func func)
			{
				return accumulate_array_dispatch (expr, func, typename ander <
					typename Expr::const_chunkable,
					typename Func::operation <typename Expr::value_type>::retypeable>::type ());
			}

		// copy_array
		// uninitialized_copy_array
		
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __true_type, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::copy_n (expr2.chunk_begin (), expr1.chunk_size (), expr1.chunk_begin ());
			}
		
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __false_type, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::uninitialized_copy_n (expr2.chunk_begin (), expr1.chunk_size (), expr1.chunk_begin ());
			}
	
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __true_type, __false_type)
			{
		//		std::cout << "not chunker.\n";
				stdext::copy_n (expr2.begin (), expr1.size (), expr1.begin ());
			}
			
		template <typename Expr1, typename Expr2> void copy_array_dispatch (Expr1& expr1, const Expr2& expr2, __false_type, __false_type)
			{
				std::cout << "not chunker.\n";
				stdext::uninitialized_copy_n (expr2.begin (), expr1.size (), expr1.begin ());
			}
			
		template <typename Expr1, typename Expr2> void uninitialized_copy_array (Expr1& expr1, const Expr2& expr2)
			{
				copy_array_dispatch (expr1, expr2, typename __type_traits <typename Expr1::value_type>::has_trivial_destructor (),
					typename ander <
						typename Expr1::chunkable,
						typename Expr2::const_chunkable,
						typename compatible <
							typename std::iterator_traits <typename Expr1::chunk_iterator>::value_type,
							typename std::iterator_traits <typename Expr2::const_chunk_iterator>::value_type>::type>::type ());
			}

		template <typename Expr1, typename Expr2> void copy_array (Expr1& expr1, const Expr2& expr2)
			{
				copy_array_dispatch (expr1, expr2, __true_type (),
					typename ander <
						typename Expr1::chunkable,
						typename Expr2::const_chunkable,
						typename compatible <
							typename std::iterator_traits <typename Expr1::chunk_iterator>::value_type,
							typename std::iterator_traits <typename Expr2::const_chunk_iterator>::value_type>::type>::type ());
			}

		// fill_array
		// uninitialized_fill_array

		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __true_type, __true_type)
			{
				stdext::fill_n (expr.chunk_begin (), expr.chunk_size (),
					static_cast <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (val));
			}
			
		template <typename Expr> void fill_array_dispatch (Expr& expr, typename Expr::value_type val, __false_type, __true_type)
			{
				stdext::uninitialized_fill_n (expr.chunk_begin (), expr.chunk_size (),
					static_cast <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (val));
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
					typename Expr::chunkable ());
			}
			
		template <typename Expr> void fill_array (Expr& expr, typename Expr::value_type val)
			{
				fill_array_dispatch (expr, val, __true_type (),
					typename Expr::chunkable ());
			}

		// for_each_array
	
		template <typename Expr1, typename Expr2, template <typename> class Func> void for_each_array_dispatch
			(Expr1& expr1, const Expr2& expr2, Func <typename Expr1::value_type> func, __true_type)
			{
			//	std::cout << "chunker.\n";
				stdext::for_each_n (expr1.chunk_begin (), expr1.chunk_size (), expr2.chunk_begin (),
					Func <typename std::iterator_traits <typename Expr1::chunk_iterator>::value_type> (func));
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
				for_each_array_dispatch (expr1, expr2, func, typename ander <
					typename Expr1::chunkable,
					typename Expr2::const_chunkable,
					typename Func <typename Expr1::value_type>::retypeable,
					typename compatible <
						typename std::iterator_traits <typename Expr1::chunk_iterator>::value_type,
						typename std::iterator_traits <typename Expr2::const_chunk_iterator>::value_type>::type>::type ());								
			}
		
		template <typename Expr, template <typename> class Func> void for_each_array_dispatch (Expr& expr, Func <typename Expr::value_type> func, __true_type)
			{
		//		std::cout << "chunker.\n";
				
				stdext::for_each_n (expr.chunk_begin (), expr.chunk_size (),
					Func <typename std::iterator_traits <typename Expr::chunk_iterator>::value_type> (func));
			}
	
		template <typename Expr, template <typename> class Func> void for_each_array_dispatch (Expr& expr, Func <typename Expr::value_type> func, __false_type)
			{
		//		std::cout << "not chunker.\n";
				stdext::for_each_n (expr.begin (), expr.size (), func);
			}
	
		template <template <typename> class Func, typename Expr> void for_each_array (Expr& expr, Func <typename Expr::value_type> func)
			{
				for_each_array_dispatch (expr, func, typename ander <
					typename Expr::chunkable,
					typename Func <typename Expr::value_type>::retypeable>::type ());
			}
	
	};

