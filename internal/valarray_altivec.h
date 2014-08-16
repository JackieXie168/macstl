/*
 *  valarray_altivec.h
 *  macstl
 *
 *  Created by Glen Low on Wed May 14 2003.
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

#include <altivec_type.h>

namespace impl
	{
		template <typename Val> struct altivec_chunk_traits
			{
				typedef macstl::altivec <Val> type;
				static const size_t length = sizeof (type) / sizeof (Val);
				static const size_t max_length = 16;
				
				typedef __true_type const_chunkable;
				typedef __true_type chunkable;
				
				typedef const type* const_iterator;
				typedef type* iterator;
				
				// NOTE: we allocate to a multiple of max_length values to handle possible chunker and/or factor
				static Val* allocate (size_t n)
					{
						return reinterpret_cast <Val*> (malloc (chunk (n) * sizeof (type)));
					}
					
				static void deallocate (Val* mem, size_t)
					{
						free (mem);
					}
					
				static size_t chunk (size_t n)
					{
						return (n + length - 1) / length;
					}
					
				static const_iterator enchunk (const Val* ptr)
					{
						return reinterpret_cast <const_iterator> (ptr);
					}

				static iterator enchunk (Val* ptr)
					{
						return reinterpret_cast <iterator> (ptr);
					}
			};
			
		// specializations of chunk_traits for altivec types
		
		template <> struct chunk_traits <char>: public altivec_chunk_traits <char> {};
		template <> struct chunk_traits <unsigned char>: public altivec_chunk_traits <unsigned char> {};
		template <> struct chunk_traits <short>: public altivec_chunk_traits <short> {};
		template <> struct chunk_traits <unsigned short>: public altivec_chunk_traits <unsigned short> {};
		template <> struct chunk_traits <long>: public altivec_chunk_traits <long> {};
		template <> struct chunk_traits <unsigned long>: public altivec_chunk_traits <unsigned long> {};
		template <> struct chunk_traits <float>: public altivec_chunk_traits <float> {};

		template <> struct chunk_traits <bool>
			{
				typedef macstl::altivec <macstl::boolean <long> > type;
				static const size_t length = sizeof (type) / sizeof (macstl::boolean <long>);
				static const size_t max_length = 16;
				
				// NOTE: since you can store an arbitrary "bool" (0, 1 or anything else!) into a valarray <bool>,
				// but const_chunkable expressions require you to stick to 0 or -1, we disallow reading chunks but allow writing chunks

				typedef __false_type const_chunkable;
				typedef __true_type chunkable;
				
				typedef const type* const_iterator;
				typedef type* iterator;
				
				// NOTE: we allocate to a multiple of max_length values to handle possible chunker and/or factor
				static bool* allocate (size_t n)
					{
						return reinterpret_cast <bool*> (malloc (chunk (n) * sizeof (type)));
					}
					
				static void deallocate (bool* mem, size_t)
					{
						free (mem);
					}
					
				static size_t chunk (size_t n)
					{
						return (n + length - 1) / length;
					}

				static iterator enchunk (bool* ptr)
					{
						return reinterpret_cast <iterator> (ptr);
					}
			};
		
		// accumulate_array overloads to match altivec predicates

		template <typename Operation> struct predication
			{
				template <typename Type> struct all: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return vec_all_eq (x.data (), y.data ()); }
					};
					
				template <typename Type> struct any: public std::binary_function <Type, Type, bool>
					{
						bool operator() (const Type& x, const Type& y) const	{ return vec_any_eq (x.data (), y.data ()); }
					};
			};

		template <typename LExpr, typename RExpr, typename Pred>
			inline bool all_predicate (const LExpr& lexpr, const RExpr& rexpr, Pred pred)
			{
				typedef typename std::iterator_traits <typename LExpr::const_chunk_iterator>::value_type chunk_type;
				
				const size_t values = lexpr.size ();
				const size_t length = 4;
				const size_t chunks = values / length;
				
				if (chunks)
					{
						// if there are any chunks, scalarize over each chunk
						typename LExpr::const_chunk_iterator left_chunker = lexpr.chunk_begin ();
						typename RExpr::const_chunk_iterator right_chunker = rexpr.chunk_begin ();
						size_t index;
						for (left_chunker = lexpr.chunk_begin (), right_chunker = rexpr.chunk_begin (), index = 0;
							index != chunks; ++index)
							if (!typename predication <Pred>::all <chunk_type> () (left_chunker [index], right_chunker [index]))
								return false;
						
						for (size_t leftover = chunks * length; leftover != values; ++leftover)
							if (!pred (lexpr [leftover], rexpr [leftover]))
								return false;
						
						return true;
					}
				else
					{
						// if there are no chunks, 
						for (size_t leftover = 0; leftover != values; ++leftover)
							if (!pred (lexpr [leftover], rexpr [leftover]))
								return false;
						return true;
					}
			}

		template <typename LExpr, typename RExpr, typename Pred>
			inline bool any_predicate (const LExpr& lexpr, const RExpr& rexpr, Pred pred)
			{
				typedef typename std::iterator_traits <typename LExpr::const_chunk_iterator>::value_type chunk_type;
				
				const size_t values = lexpr.size ();
				const size_t length = 4;
				const size_t chunks = values / length;
				
				if (chunks)
					{
						// if there are any chunks, scalarize over each chunk
						typename LExpr::const_chunk_iterator left_chunker = expr.chunk_begin ();
						typename RExpr::const_chunk_iterator right_chunker = rexpr.chunk_begin ();
						size_t index;
						for (left_chunker = lexpr.chunk_begin (), right_chunker = rexpr.chunk_begin (), index = 0;
							index != chunks; ++index)
							if (typename predication <Pred>::any <chunk_type> () (*lexpr, *rexpr))
								return true;
						
						for (size_t leftover = chunks * length; leftover != values; ++leftover)
							if (pred (lexpr [leftover], rexpr [leftover]))
								return true;
						
						return false;
					}
				else
					{
						// if there are no chunks, 
						for (size_t leftover = 0; leftover != values; ++leftover)
							if (pred (lexpr [leftover], rexpr [leftover]))
								return true;
						return false;
					}
			}
		
			
		template <typename Type> struct any_equal_to: public std::binary_function <Type, Type, bool>
			{
				bool operator() (const Type& x, const Type& y) const	{ return vec_any_eq (x.data (), y.data ()); }
			};

		template <typename Expr1, typename Expr2> inline bool accumulate_array_dispatch
			(const binary_term <Expr1, Expr2, function <std::equal_to>::operation>& expr, minimize, __true_type)
			{
				std::cout << "ho.";
				return all_predicate (expr.lexpr_, expr.rexpr_, std::equal_to <typename Expr1::value_type> ());
			}

			/*	
		template <typename Expr1, typename Expr2, typename Expr3> struct chunk_base <float,
			binary_term <binary_term <Expr1, Expr2, function <std::multiplies>::operation>, Expr3, function <std::plus>::operation> >
			{
				public:
					typedef __false_type const_chunkable;
					typedef __false_type chunkable;

					typedef const float* chunk_iterator;
					typedef float* mutable_chunk_iterator;
			};
		*/
	};


	