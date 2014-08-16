/*
 *  valarray_base.h
 *  macstl
 *
 *  Created by Glen Low on Mon Jun 23 2003.
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
		struct summate
			{
				template <typename Type> class operation
					{
						public:
							typedef __true_type retypeable;
							
							operation (const Type& init): result_ (init)
								{
								}
							
							template <typename ReType> operation (const operation <ReType>& other):
								result_ (other.result ().sum ())
								{
								}
								
							void operator() (const Type& val)			{ result_ += val; }
							Type result () const						{ return result_; }
							
						private:
							Type result_;
					};
			};

		struct minimize
			{
				template <typename Type> class operation
					{
						public:
							typedef __true_type retypeable;
							
							operation (const Type& init): result_ (init)
								{
								}	
												
							template <typename ReType> operation (const operation <ReType>& other):
								result_ (other.result ().min ())
								{
								}
							
							void operator() (const Type& val)			{ result_ = std::min (result_, val); }
							Type result () const						{ return result_; }
		
						private:
							Type result_;
					};
			};

		struct maximize
			{
				template <typename Type> class operation
					{
						public:
							typedef __true_type retypeable;
							
							operation (const Type& init): result_ (init)
								{
								}
		
							template <typename ReType> operation (const operation <ReType>& other):
								result_ (other.result ().max ())
								{
								}
							
							void operator() (const Type& val)		{ result_ = std::max (result_, val); }
							Type result () const					{ return result_; }
							
						private:
							Type result_;
					};
					
			};
			

		template <template <typename> class Op> struct function
			{
				template <typename Type> class operation: public Op <Type>
					{
						public:
							typedef __true_type retypeable;
							
							operation (): Op <Type> ()
								{
								}
								
							template <typename ReType> operation (const operation <ReType>& op): Op <Type> ()
								{
								}
					};
			};
			
		template <typename Type> class apply_value
			{
				public:
					typedef __false_type retypeable;
					
					typedef Type argument_type;
					typedef Type result_type;
					
					apply_value (Type (*fn) (Type)): fn_ (fn)	{}						
					Type operator() (const Type& x) const		{ return fn_ (x); }
						
				private:
					Type (*fn_) (Type);
			};

		template <typename Type> class apply_reference
			{
				public:
					typedef __false_type retypeable;
					
					typedef Type argument_type;
					typedef Type result_type;
					
					apply_reference (Type (*fn) (const Type &)): fn_ (fn)	{}
					Type operator() (const Type& x) const					{ return fn_ (x); }
						
				private:
					Type (*fn_) (const Type &);
			};

		template <template <typename> class Op> struct left_scalar
			{
				template <typename Type> class operation: public stdext::binder1st <Op <Type> >
					{
						public:
							typedef __true_type retypeable;
							
							operation (const Type& bound): stdext::binder1st <Op <Type> > (Op <Type> (), bound)
								{
								}
								
							template <typename ReType> operation (const operation <ReType>& op):
								stdext::binder1st <Op <Type> > (Op <Type> (), static_cast <Type> (op.bound_))
								{
								}
								
						private:
							template <typename ReType> friend class operation;

					};
			};

		template <template <typename> class Op> struct right_scalar
			{
				template <typename Type> class operation: public stdext::binder2nd <Op <Type> >
					{
						public:
							typedef __true_type retypeable;
							
							operation (const Type& bound): stdext::binder2nd <Op <Type> > (Op <Type> (), bound)
								{
								}
								
							template <typename ReType> operation (const operation <ReType>& op):
								stdext::binder2nd <Op <Type> > (Op <Type> (), static_cast <Type> (op.bound_))
								{
								}
								
						private:
							template <typename ReType> friend class operation;
					};
			};
			
		// chunk_base: base of all chunkable items, default does not chunk but may allow chunking in the specializations
			
		template <typename Val, typename Expr> class chunk_base
			{
				public:
					typedef __false_type const_chunkable;
					typedef __false_type chunkable;

					typedef const Val* const_chunk_iterator;
					typedef Val* chunk_iterator;
			};
			
		// term_base: base of all terms substitutable for a const valarray
			
		#define __MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION(FUNC, OPER)								\
		unary_term <Expr, function <OPER>::operation> FUNC () const									\
			{																						\
				return unary_term <Expr, function <OPER>::operation>								\
					(expr (), function <OPER>::operation <Val> ());									\
			}

		#define __MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION(FUNC, OPER)									\
																									\
		template <typename Val, typename Expr> unary_term <Expr, function <OPER>::operation> FUNC	\
			(const term_base <Val, Expr>& x)														\
			{																						\
				return unary_term <Expr, function <OPER>::operation>								\
					(x.expr (), function <OPER>::operation <Val> ());								\
			}

		#define __MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION(FUNC, OPER)								\
																									\
		template <typename Val, typename LExpr, typename RExpr>										\
			binary_term <LExpr, RExpr, function <OPER>::operation> FUNC								\
			(const term_base <Val, LExpr>& left, const term_base <Val, RExpr>& right)				\
			{																						\
				return binary_term <LExpr, RExpr, function <OPER>::operation>						\
					(left.expr (), right.expr (), function <OPER>::operation <Val> ());				\
			}																						\
																									\
		template <typename Val, typename RExpr>														\
			unary_term <RExpr, left_scalar <OPER>::operation> FUNC									\
			(const Val& left, const term_base <Val, RExpr>& right)									\
			{																						\
				return unary_term <RExpr, left_scalar <OPER>::operation>							\
					(right.expr (), left_scalar <OPER>::operation <Val> (left)); 					\
			}																						\
																									\
		template <typename Val, typename LExpr>														\
			unary_term <LExpr, right_scalar <OPER>::operation> FUNC									\
			(const term_base <Val, LExpr>& left, const Val& right)									\
			{																						\
				return unary_term <LExpr, right_scalar <OPER>::operation>							\
					(left.expr (), right_scalar <OPER>::operation <Val> (right));					\
			}														
		
		template <typename Val, typename Expr> class term_base: public chunk_base <Val, Expr>
			{
				public:
					// 26.3.2.4 lib.valarray.sub, const
					
					slice_term <Expr> operator[] (std::slice subset) const
						{
							return slice_term <Expr> (expr (), subset);
						}
						
					gslice_term <Expr> operator[] (const std::gslice& subset) const
						{
							return gslice_term <Expr> (expr (), subset);
						}
					
					template <typename BExpr> mask_term <Expr, BExpr>
						operator[] (const term_base <bool, BExpr>& subset) const
						{
							return mask_term <Expr, BExpr> (expr (), subset.expr ());
						}

					template <typename InExpr> indirect_term <Expr, InExpr>
						operator[] (const term_base <size_t, InExpr>& subset) const
						{
							return indirect_term <Expr, InExpr> (expr (), subset.expr ());
						}
						
					// 26.3.2.5 lib.valarray.unary
					
					__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator+, std::_Identity)
					__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator-, std::negate)
					__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator~, stdext::bitwise_not)
					__MACSTL_DEFINE_VALARRAY_MEMBER_FUNCTION (operator!, std::logical_not)
											
					// 26.3.2.7 lib.valarray.member, const
					Val sum () const	{ return accumulate_array (expr (), summate ()); }
					Val min () const	{ return accumulate_array (expr (), minimize ()); }
					Val max () const	{ return accumulate_array (expr (), maximize ()); }
					
					shift_term <Expr> shift (int offset) const		{ return shift_term <Expr> (expr (), offset); }
					cshift_term <Expr> cshift (int offset) const	{ return cshift_term <Expr> (expr (), offset); }
					
					unary_term <Expr, apply_value> apply (Val func (Val)) const
						{
							return unary_term <Expr, apply_value> (expr (), apply_value <Val> (func));
						}
						
					unary_term <Expr, apply_reference> apply (Val func (const Val&)) const
						{
							return unary_term <Expr, apply_reference> (expr (), apply_reference <Val> (func));
						}

					const Expr& expr () const
						{
							return static_cast <const Expr&> (*this);
						}
			};

		// 26.3.3.1 lib.valarray.binary

		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator*, std::multiplies)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator/, std::divides)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator%, std::modulus)            
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator+, std::plus)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator-, std::minus)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator^, stdext::bitwise_xor)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator&, stdext::bitwise_and)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator|, stdext::bitwise_or)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<<, stdext::left_shift)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>>, stdext::right_shift) 
		
		// 26.3.3.2 lib.valarray.comparison
		
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator==, std::equal_to)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator!=, std::not_equal_to)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<, std::less)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>, std::greater)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator<=, std::less_equal)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator>=, std::greater_equal)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator&&, std::logical_and)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (operator||, std::logical_or)
		
		// 26.3.3.3 lib.valarray.transcend
		
		// note: we match these valarray functions to the appropriate function object templates in
		// std namespace declared previously
		
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (abs, std::__abs)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (acos, std::__acos)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (asin, std::__asin)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (atan, std::__atan)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (atan2, std::__atan2)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (cos, std::__cos)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (cosh, std::__cosh)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (exp, std::__exp)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (log, std::__log)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (log10, std::__log10)
		__MACSTL_DEFINE_VALARRAY_BINARY_FUNCTION (pow, std::__pow)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sin, std::__sin)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sinh, std::__sinh)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (sqrt, std::__sqrt)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (tan, std::__tan)
		__MACSTL_DEFINE_VALARRAY_UNARY_FUNCTION (tanh, std::__tanh)
		
		// array_base: base of all arrays substitutable for a mutable valarray
		// currently, std::valarray is the only subclass, but other types may subclass array_base and thus participate in
		// the valarray arithmetic. array_base does not explicitly specify copy semantics; a copy thus behaves like a
		// reference to the original.
		
		template <typename Val> class array_base: public term_base <Val, array_base <Val> >
			{
				public:
					typedef Val value_type;
					
					typedef impl::chunk_traits <Val> chunk_traits;
					
					typedef const Val* const_iterator;
					typedef Val* iterator;
		
					// 26.3.2.3 lib.valarray.access
					
					value_type operator[] (size_t index) const	{ return data_ [index]; }
					value_type& operator[] (size_t index)		{ return data_ [index]; }
					
					// 26.3.2.4 lib.valarray.subset
					
					using impl::term_base <Val, array_base <Val> >::operator[];
					
					std::slice_array <value_type> operator[] (std::slice subset)
						{
							return std::slice_array <Val> (*this, subset);
						}
					
					std::gslice_array <value_type> operator[] (const std::gslice& subset)
						{
							return std::gslice_array <Val> (*this, subset);
						}
					
					template <typename BExpr> std::mask_array <value_type, BExpr>
						operator[] (const term_base <bool, BExpr>& subset)
						{
							return std::mask_array <value_type, BExpr> (*this, subset.expr ());
						}
						
					template <typename InExpr> std::indirect_array <value_type, InExpr>
						operator[] (const term_base <size_t, InExpr>& subset)
						{
							return std::indirect_array <value_type, InExpr> (*this, subset.expr ());
						}
							
					// 26.3.2.7 lib.valarray.members
					
					size_t size () const			{ return size_; }
		
					const_iterator begin () const	{ return data_; }
					iterator begin ()				{ return data_; }
																		
				protected:
					array_base (value_type* data, size_t size): data_ (data), size_ (size)	{}

					void swap (array_base& other)
						{
							std::swap (data_, other.data_);
							std::swap (size_, other.size_);
						}
						
				private:
					value_type* data_;
					size_t size_;
					
					friend class chunk_base <value_type, array_base>;
			};		

		template <typename Val> class chunk_base <Val, array_base <Val> >
			{
				public:
					typedef chunk_traits <Val> chunk_traits;
					
					typedef typename chunk_traits::const_chunkable const_chunkable;
					typedef typename chunk_traits::chunkable chunkable;
					
					typedef typename chunk_traits::const_iterator const_chunk_iterator;
					typedef typename chunk_traits::iterator chunk_iterator;
					
					const_chunk_iterator chunk_begin () const
						{
							const array_base <Val>& expr = static_cast <const array_base <Val>&> (*this);
							return chunk_traits::enchunk (expr.data_);
						}

					chunk_iterator chunk_begin ()
						{
							array_base <Val>& expr = static_cast <array_base <Val>&> (*this);
							return chunk_traits::enchunk (expr.data_);
						}
						
					size_t chunk_size () const
						{
							const array_base <Val>& expr = static_cast <const array_base <Val>&> (*this);
							return chunk_traits::chunk (expr.size_);
						}

			};

		// subset_base: base of all subset arrays i.e. slice_array, gslice_array, mask_array and indirect_array
			
		#define __MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION(FUNC, OPER)							\
																							\
		template <typename Expr2> void FUNC (const term_base <Val, Expr2>& other) const		\
			{																				\
				for_each_array (expr (), other.expr (), function <OPER>::operation <Val> ());				\
			}

		template <typename Val, typename Expr> class subset_base: public chunk_base <Val, Expr>
			{
				public:
					// 26.3.5.2 lib.slice.array.assign
					// 26.3.7.2 lib.gslice.array.assign
					// 26.3.8.2 lib.mask.array.assign
					// 26.3.9.2 lib.indirect.array.assign
					
					template <typename Expr2> void operator= (const term_base <Val, Expr2>& other) const
						{
							copy_array (expr (), other);
						}
			
					// 26.3.5.3 lib.slice.array.comp.assign
					// 26.3.7.3 lib.gslice.array.comp.assign
					// 26.3.8.3 lib.mask.array.comp.assign
					// 26.3.9.3 lib.indirect.array.comp.assign

					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator*=, stdext::multiplies_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator/=, stdext::divides_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator%=, stdext::modulus_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator+=, stdext::plus_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator-=, stdext::minus_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator^=, stdext::bitwise_xor_assign)			
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator&=, stdext::bitwise_and_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator|=, stdext::bitwise_or_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator<<=, stdext::left_shift_assign)
					__MACSTL_DEFINE_SUBSET_CASSIGN_FUNCTION (operator>>=, stdext::right_shift_assign)
					
					// 26.3.5.4 lib.slice.array.fill
					// 26.3.7.4 lib.gslice.array.fill
					// 26.3.8.4 lib.mask.array.fill
					// 26.3.9.4 lib.indirect.array.fill
					
					void operator= (const Val& x)
						{
							fill_array (expr (), x);
						}
						
				private:
					Expr& expr ()
						{
							return static_cast <Expr&> (*this);
						}
			};
		
	};

