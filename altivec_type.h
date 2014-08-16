/*
 *  altivec_type
 *  macstl
 *
 *  Created by Glen Low on Tue Sep 10 2002.
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
 
/**
 * @file altivec_type.h
 * @ingroup altivec_public
 * @brief Altivec class
 *
 * Declares the macstl::altivec class.
 */
 
#ifndef MACSTL_ALTIVEC_TYPE_H
#define MACSTL_ALTIVEC_TYPE_H

#include <functional>
#include <iosfwd>
#include <iomanip>

#include <boolean.h>
#include <pixel.h>
#include <altivec_traits.h>

#define __DEFINE_ALTIVEC_MEMBER_FUNCTION(FUNC, OPER, RSLT)																			\
/** Returns the result of applying @c FUNC to each element. */															\
RSLT FUNC () const										{ return altivec_traits::OPER (data ()); }

#define __DEFINE_ALTIVEC_UNARY_FUNCTION(FUNC, OPER, RSLT)																			\
/** Returns the result of applying @c FUNC to each element of @a x. */													\
template <typename Type> inline RSLT FUNC (const altivec <Type>& x)						{ return altivec_traits <Type>::OPER (x.data ()); }

#define __DEFINE_ALTIVEC_BINARY_FUNCTION(FUNC, OPER, RSLT)																			\
/** Returns the result of applying @c FUNC to each element of @a x and the corresponding element of @a y. */				\
template <typename Type> inline RSLT FUNC (const altivec <Type>& x, const altivec <Type>& y)	{ return altivec_traits <Type>::OPER (x.data (), y.data ()); }						\
template <typename Type> inline RSLT FUNC (const altivec <Type>& x, typename altivec <Type>::vector_type y)		{ return altivec_traits <Type>::OPER (x.data (), y); }								\
template <typename Type> inline RSLT FUNC (typename altivec <Type>::vector_type x, const altivec <Type>& y)		{ return altivec_traits <Type>::OPER (x, y.data ()); }								\
/** Returns the result of applying @c FUNC to each element of @a x and scalar @a y. */									\
template <typename Type> inline RSLT FUNC (const altivec <Type>& x, typename altivec <Type>::value_type y)		{ return altivec_traits <Type>::OPER (x.data (), altivec_traits <Type>::splat (y)); }		\
/** Returns the result of applying @c FUNC to scalar @a x and each element of @a y. */									\
template <typename Type> inline RSLT FUNC (typename altivec <Type>::value_type x, const altivec <Type>& y)		{ return altivec_traits <Type>::OPER (altivec_traits <Type>::splat (x), y.data ()); }

#define __DEFINE_ALTIVEC_CASSIGN_FUNCTION(FUNC, OPER)																				\
/** Performs @c FUNC on each element of @a x and the corresponding element of @a y. */									\
template <typename Type> inline altivec <Type>& FUNC (altivec <Type>& x, altivec <Type> y)		{ return x = altivec_traits <Type>::OPER (x.data (), y.data ()); }					\
template <typename Type> inline altivec <Type>& FUNC (altivec <Type>& x, typename altivec <Type>::vector_type y)		{ return x = altivec_traits <Type>::OPER (x.data (), y); }							\
/** Performs @c FUNC on each element of @a x and scalar @a y. */															\
template <typename Type> inline altivec <Type>& FUNC (altivec <Type>& x, typename altivec <Type>::value_type y)			{ return x = altivec_traits <Type>::OPER (x.data (), altivec_traits <Type>::splat (y)); }

namespace macstl
	{
		/**
		 * @ingroup altivec_public
		 * @brief A valarray in an Altivec register.
		 * @param Type The element type i.e. char, short, long, float or a boolean type.
		 * @par Models:
		 * Default Constructible, Copy Constructible, Assignable.
		 * @par Type Traits:
		 * Trivial Copy Constructor, Trivial Destructor, Trivial Assignment Operator.
		 * 
		 * The altivec class encapsulates the Altivec vector types with a valarray-like interface.
		 * If you use this template instead of the Altivec C Programming Interface, you can code a more
		 * natural <code>v1 + v2 + v3</code> instead of <code>vec_add (vec_add (v1, v2), v3)</code>.
		 * A modern, agressive compiler like gcc 3.x also means the object doesn't have any overheads:
		 * local variables and temporaries live inside of CPU registers, and an object copy compiles
		 * into a register move.
		 *
		 * The <em>conversion constructor</em> creates an altivec object from its raw vector form.
		 * This lets you treat the vector type as a literal, e.g.
		 * @code macstl::altivec <float> v1 = (vector float) (1.0f, 2.0f, 3.0f, 4.0f); @endcode
		 *
		 * To prevent overload ambiguities, there isn't a <em>conversion operator</em>. However, the raw
		 * vector can still be retrieved through data(), e.g.
		 * @code vector float f1 = v1.data(); @endcode
		 *
		 * The class also provides single instruction Altivec instructions given the object-oriented
		 * treatment. Their names parallel the original raw instruction names e.g. @c mergeh is the
		 * object version of @c vec_mergeh. A complete list of instructions can be found at Apple's
		 * <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html">Altivec Instruction Cross-Reference</a>.
		 */
		 
		template <typename Type> class altivec
			{
				public:
					typedef altivec_traits <Type> altivec_traits;	/**< The traits class that serves as the implementation. */
					
					typedef typename altivec_traits::vector_type vector_type;	/**< The Altivec vector type. */
					typedef typename altivec_traits::value_type value_type;		/**< The element type. */
					typedef typename altivec_traits::union_type union_type;		/**< The union of the raw vector type and an array of element type. */
					
					typedef altivec <typename altivec_traits::bool_value_type> altivec_bool;	/**< The boolean type with the same size. */
					
					static const size_t length = altivec_traits::length;	/**< The number of elements. */
					
					/** @name constructors */
					
					//@{
					
					/** Construct with each element set to zero. */
					altivec (): data_ (altivec_traits::zero ())
						{
						}
					
					/** Construct with each element set to @a scalar. */
					explicit altivec (value_type scalar): data_ (altivec_traits::splat (scalar))
						{
						}
						
					/** Construct entire object from @a vector. */
					altivec (vector_type vector): data_ (vector)
						{
						}
					
					//@}
					
					// trivial destructor
					// ~altivec ();
							
					// trivial copy constructor
					// altivec (const altivec&);
					
					/** @name assignments */
					
					//@{
									
					/** Assigns @a scalar to each element. */
					altivec& operator= (value_type scalar)
						{
							data_ = altivec_traits::splat (scalar);
							return *this;
						}
						
					/** Assigns raw @a vector to entire object. */
					altivec& operator= (vector_type vector)
						{
							data_ = vector;
							return *this;
						}
						
					//@}
						
					// trivial assignment operator
					// altivec& operator= (const altivec& other);
															
					/** @name sizer */
					
					//@{
					
					/**
					 * Returns the number of elements.
					 * @note Since Altivec vector types are fixed length, this is a static member
					 * function which returns the same value as altivec::length.
					 */
					static size_t size ()
						{
							return altivec_traits::length;
						}

					//@}
					
					/** @name indexers */
					
					// DANGER WILL ROBINSON!! If this is to work under -fstrict-aliasing, an vector_type should be allowed
					// to alias its value_type e.g. vector float* can alias float*. We don't use a union since carrying that
					// baggage around in the type seems to spoil further alias analysis optimizations. In any case, this seems
					// to be true of gcc 3.1 but isn't explicitly sanctioned by the Standard...
					
					//@{
											
					/** Returns the element at index @a n. */
					value_type operator[] (size_t n) const
						{
							return reinterpret_cast <const value_type*> (&data_) [n];
						}

					/** Returns a reference to the element at index @a n. */
					value_type& operator[] (size_t n)
						{
							return reinterpret_cast <value_type*> (&data_) [n];
						}
					
					//@}
					
					/** @name data */
					
					//@{
					
					/** Returns the raw vector. */
					vector_type data () const
						{
							return data_;
						}
					
					//@}
					
					/** @name scalarizers */
					
					//@{
					
					/** Returns the sum of all the elements. */						
					value_type sum () const
						{
							return altivec_traits::sum (data_);
						}
						
					/** Returns the minimum element. */
					value_type min () const
						{
							return altivec_traits::min (data_);
						}
						
					/** Returns the maximum element. */
					value_type max () const
						{
							return altivec_traits::max (data_);
						}

					//@}
					
					/** @name shifters */
					
					/** Returns the result of circularly shifting each element left @a n places. */
					altivec cshift (int n) const
						{
							return altivec_traits::cshift (data_, n);
						}

					/** Returns the result of shifting each element left @a n places with zero fill. */
					altivec shift (int n) const
						{
							return altivec_traits::shift (data_, n);
						}
						
					/** @name appliers */
					
					//@{
					
					/** Returns the result of applying @a function to each element. */
					altivec apply (value_type function (value_type)) const
						{
							union_type un;
							for (size_t index = 0; index != altivec_traits::length; ++index)
								un.val [index] = function ((*this) [index]);
							return un.vec;
						}
						
					/** Returns the result of applying @a function to each element. */
					altivec apply (value_type function (const value_type&)) const
						{
							union_type un;
							for (size_t index = 0; index != altivec_traits::length; ++index)
								un.val [index] = function ((*this) [index]);
							return un.vec;
						}
					
					//@}
					
					/** @name unary operators */
					
					//@{
					
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator-, negate, altivec)
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator~, bitwise_not, altivec)
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator!, logical_not, altivec_bool)
					
					//@}
										
				private:
					vector_type data_;
			};
			
		/** @name binary operators */
		
		//@{
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator+, plus, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator-, minus, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator*, multiplies, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator/, divides, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator%, modulus, altivec <Type>)            
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator&, bitwise_and, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator|, bitwise_or, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator^, bitwise_xor, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<<, left_shift, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>>, right_shift, altivec <Type>)            
		//@}
		
		/** @name computed assignments */
		
		//@{
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator+=, plus)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator-=, minus)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator*=, multiplies)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator/=, divides)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator%=, modulus)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator&=, bitwise_and)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator|=, bitwise_or)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator^=, bitwise_xor)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator<<=, left_shift)
		__DEFINE_ALTIVEC_CASSIGN_FUNCTION (operator>>=, right_shift)
		//@}
		
		/** @name logical operators */
		
		//@{
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator==, equal_to, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator!=, not_equal_to, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>, greater, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>=, greater_equal, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<, less, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<=, less_equal, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator&&, logical_and, typename altivec <Type>::altivec_bool)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (operator||, logical_or, typename altivec <Type>::altivec_bool)
		//@}
		
		/** @name transcendental functions */
		
		//@{
		__DEFINE_ALTIVEC_UNARY_FUNCTION (abs, abs, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (cos, cos, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (acos, acos, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (cosh, cosh, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (sin, sin, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (asin, asin, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (sinh, sinh, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (tan, tan, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (tanh, tanh, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (atan, atan, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (exp, exp, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (log, log, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (log10, log10, altivec <Type>)
		__DEFINE_ALTIVEC_UNARY_FUNCTION (sqrt, sqrt, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (atan2, atan2, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (pow, pow, altivec <Type>)
		//@}
		
		/** @name max and min functions */
		
		//@{
		__DEFINE_ALTIVEC_BINARY_FUNCTION (max, max, altivec <Type>)
		__DEFINE_ALTIVEC_BINARY_FUNCTION (min, min, altivec <Type>)
		//@}		
			
		/** @name stream I/O */
		
		//@{

		/**
		 * @relates altivec 
		 * Inserts altivec @a vec into a standard output stream @a os.
		 */
		template <typename Type, typename CharT, typename Traits> std::basic_ostream <CharT, Traits>&
			operator<< (std::basic_ostream <CharT, Traits>& os, const altivec <Type>& vec)
			{
				std::streamsize subwidth = os.width () / altivec <Type>::length;
				if (subwidth)
					for (size_t i = 0; i < altivec <Type>::length; ++i)
						os << std::setw (subwidth) << vec [i];
				else
					{
						os << vec [0];
						for (size_t i = 1; i < altivec <Type>::length; ++i)
							os << os.fill () << vec [i];
					}
				return os;
			}
		
		/**
		 * @relates altivec
		 * Extracts altivec @a vec from a standard input stream @a is.
		 */
		template <typename Type, typename CharT, typename Traits> std::basic_istream <CharT, Traits>&
			operator>> (std::basic_istream <CharT, Traits>& is, altivec <Type>& vec)
			{
				for (size_t i = 0; i < altivec <Type>::length; ++i)
					is >> vec [i];
				
				return is;
			}

		//@}
		
		// more Dewhurstian SFINAE concepts: a partial typeof implementation, to help
		// keep in sync the object interface and the underlying Altivec operators
		
		namespace impl
			{
				enum typetag
					{
						vector_unsigned_char = 1,
						vector_signed_char = 2,
						vector_bool_char = 3,
						vector_unsigned_short = 4,
						vector_signed_short = 5,
						vector_bool_short = 6,
						vector_unsigned_int = 7,
						vector_signed_int = 8,
						vector_bool_int = 9,
						vector_float = 10,
						vector_pixel = 11				
					};
					
				char (*type_to_tag (__vector unsigned char)) [vector_unsigned_char];
				char (*type_to_tag (__vector signed char)) [vector_signed_char];
				char (*type_to_tag (__vector bool char)) [vector_bool_char];
				char (*type_to_tag (__vector unsigned short)) [vector_unsigned_short];
				char (*type_to_tag (__vector signed short)) [vector_signed_short];
				char (*type_to_tag (__vector bool short)) [vector_bool_short];
				char (*type_to_tag (__vector unsigned int)) [vector_unsigned_int];
				char (*type_to_tag (__vector signed int)) [vector_signed_int];
				char (*type_to_tag (__vector bool int)) [vector_bool_int];
				char (*type_to_tag (__vector float)) [vector_float];
				char (*type_to_tag (__vector __pixel)) [vector_pixel];
			
				template <size_t n> struct tag_to_type;
				
				template <> struct tag_to_type <vector_unsigned_char> { typedef altivec <unsigned char> type; };
				template <> struct tag_to_type <vector_signed_char> { typedef altivec <char> type; };
				template <> struct tag_to_type <vector_bool_char> { typedef altivec <boolean <char> > type; };
				template <> struct tag_to_type <vector_unsigned_short> { typedef altivec <unsigned short> type; };
				template <> struct tag_to_type <vector_signed_short> { typedef altivec <short> type; };
				template <> struct tag_to_type <vector_bool_short> { typedef altivec <boolean <short> > type; };
				template <> struct tag_to_type <vector_unsigned_int> { typedef altivec <unsigned long> type; };
				template <> struct tag_to_type <vector_signed_int> { typedef altivec <long> type; };
				template <> struct tag_to_type <vector_bool_int> { typedef altivec <boolean <long> > type; };
				template <> struct tag_to_type <vector_float> { typedef altivec <float> type; };
				template <> struct tag_to_type <vector_pixel> { typedef altivec <pixel> type; };
			}

		// Altivec operators with 0 arguments

		#define __DEFINE_ALTIVEC_GENERATOR(FUNC, OPER)											\
		/** @relates altivec Returns the result of @c OPER. */									\
		inline impl::tag_to_type <sizeof (*impl::type_to_tag (OPER ()))>::type FUNC () { return OPER (); }

		// Altivec operators with 1 argument
		
		#define __DEFINE_ALTIVEC_UNARY_OPERATION(FUNC, OPER)									\
																								\
		namespace impl																			\
			{																					\
				template <typename Type> struct OPER##_result									\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type>::vector_type*) NULL)))>::type type;	\
					};																			\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x. */					\
		template <typename Type>																\
			inline typename impl::OPER##_result <Type>::type FUNC (const altivec <Type>& x)		\
			{																					\
				return OPER (x.data ());														\
			}
			
		// Altivec operators with 2 arguments
		
		#define __DEFINE_ALTIVEC_BINARY_OPERATION(FUNC, OPER)									\
																								\
		namespace impl																			\
			{																					\
				template <typename Type1, typename Type2> struct OPER##_result					\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type1>::vector_type*) NULL,				\
							*(typename altivec <Type2>::vector_type*) NULL)))>::type type;		\
					};																			\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x and @a y. */		\
		template <typename Type1, typename Type2>												\
			inline typename impl::OPER##_result <Type1, Type2>::type							\
			FUNC (const altivec <Type1>& x, const altivec <Type2>& y)							\
			{																					\
				return OPER (x.data (), y.data ());												\
			}

		// Altivec operators with 2 arguments, overload defined already when argument types are same
		
		#define __DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(FUNC, OPER)						\
																								\
		namespace impl																			\
			{																					\
				template <typename Type1, typename Type2> struct OPER##_result					\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type1>::vector_type*) NULL,				\
							*(typename altivec <Type2>::vector_type*) NULL)))>::type type;		\
					};																			\
				template <typename Type> struct OPER##_result <Type, Type>;						\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x and @a y. */		\
		template <typename Type1, typename Type2>												\
			inline typename impl::OPER##_result <Type1, Type2>::type							\
			FUNC (const altivec <Type1>& x, const altivec <Type2>& y)							\
			{																					\
				return OPER (x.data (), y.data ());												\
			}
			
		// Altivec operators with 3 arguments
		
		#define __DEFINE_ALTIVEC_TERNARY_OPERATION(FUNC, OPER)									\
																								\
		namespace impl																			\
			{																					\
				template <typename Type1, typename Type2, typename Type3> struct OPER##_result	\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type1>::vector_type*) NULL,				\
							*(typename altivec <Type2>::vector_type*) NULL,						\
							*(typename altivec <Type3>::vector_type*) NULL)))>::type type;		\
					};																			\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x, @a y and @a z. */	\
		template <typename Type1, typename Type2, typename Type3>								\
			inline typename impl::OPER##_result <Type1, Type2, Type3>::type						\
			FUNC (const altivec <Type1>& x, const altivec <Type2>& y, const altivec <Type3>& z)	\
			{																					\
				return OPER (x.data (), y.data (), z.data ());									\
			}
		
		// Altivec operator with 2 arguments, 2nd is integer literal
		
		#define __DEFINE_ALTIVEC_BINARY_OPERATION_WITH_LITERAL(FUNC, OPER, LIT)					\
																								\
		namespace impl																			\
			{																					\
				template <typename Type> struct OPER##_result									\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type>::vector_type*) NULL,				\
							0)))>::type type;													\
					};																			\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x and @a i. */		\
		template <LIT i, typename Type>															\
			inline typename impl::OPER##_result <Type>::type FUNC (const altivec <Type>& x)		\
			{																					\
				return OPER (x.data (), i);														\
			}

		// Altivec operator with 3 arguments, 3rd is integer literal
		
		#define __DEFINE_ALTIVEC_TERNARY_OPERATION_WITH_LITERAL(FUNC, OPER, LIT)				\
																								\
		namespace impl																			\
			{																					\
				template <typename Type1, typename Type2> struct OPER##_result					\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (*(typename altivec <Type1>::vector_type*) NULL, 				\
							*(typename altivec <Type2>::vector_type*) NULL, 0)))>::type type;	\
					};																			\
			}																					\
																								\
		/** @relates altivec Returns the result of applying	@c OPER to @a x, @a y and @a i. */	\
		template <LIT i, typename Type1, typename Type2>										\
			inline typename impl::OPER##_result <Type1, Type2>::type							\
			FUNC (const altivec <Type1>& x, const altivec <Type2>& y)							\
			{																					\
				return OPER (x.data (), y.data (), i);											\
			}

		// Altivec predicate with 1 argument
		
		#define __DEFINE_ALTIVEC_UNARY_PREDICATE(FUNC, OPER)									\
		/** @relates altivec Returns the result of applying	@c OPER to @a x. */					\
		template <typename Type> inline bool FUNC (const altivec <Type>& x)						\
			{																					\
				return OPER (x.data ());														\
			}

		// Altivec predicate with 2 arguments
		
		#define __DEFINE_ALTIVEC_BINARY_PREDICATE(FUNC, OPER)									\
		/** @relates altivec Returns the result of applying	@c OPER to @a x and @a y. */		\
		template <typename Type1, typename Type2>												\
			inline bool FUNC (const altivec <Type1>& x, const altivec <Type2>& y)				\
			{																					\
				return OPER (x.data (), y.data ());												\
			}
			
		// Altivec load for alignment
		
		#define __DEFINE_ALTIVEC_LOAD_FOR_ALIGN(FUNC, OPER)										\
		/** @relates altivec Returns the result of applying @c OPER to @a i and @a p. */		\
		template <typename Type> inline altivec <unsigned char> FUNC (int i, Type* p)			\
			{																					\
				return OPER (i, p);																\
			}

		// Altivec load
		
		#define __DEFINE_ALTIVEC_LOAD(FUNC, OPER)												\
																								\
		namespace impl																			\
			{																					\
				template <typename Type> struct OPER##_result									\
					{																			\
						typedef typename tag_to_type <sizeof (*type_to_tag (					\
							OPER (0, (Type*) NULL)))>::type type;								\
					};																			\
			}																					\
																								\
		/** @relates altivec Loads from @a p by @a i using @c OPER. */							\
		template <typename Type>																\
			inline typename impl::OPER##_result <Type>::type FUNC (int i, Type* p)				\
			{																					\
				return OPER (i, p);																\
			}
			
		// Altivec store

		#define __DEFINE_ALTIVEC_STORE(FUNC, OPER)												\
		/** @relates altivec Stores @a x into @a p by @a i using @c OPER. */					\
		template <typename Type1, typename Type2>												\
			inline void FUNC (const altivec <Type1>& x, int i, Type2* p)						\
			{																					\
				OPER (x.data (), i, p);															\
			}

		/** @name load and store */
		//@{
		__DEFINE_ALTIVEC_LOAD(ld,vec_ld)
		__DEFINE_ALTIVEC_LOAD(ldl,vec_ldl)
		__DEFINE_ALTIVEC_LOAD(lde,vec_lde)
		__DEFINE_ALTIVEC_LOAD_FOR_ALIGN(lvsl,vec_lvsl)
		__DEFINE_ALTIVEC_LOAD_FOR_ALIGN(lvsr,vec_lvsr)
		__DEFINE_ALTIVEC_STORE(st, vec_st)
		__DEFINE_ALTIVEC_STORE(stl, vec_stl)
		__DEFINE_ALTIVEC_STORE(ste, vec_ste)
		//@}
		
		/** @name data manipulation */
		//@{
		__DEFINE_ALTIVEC_TERNARY_OPERATION(perm,vec_perm)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(sel,vec_sel)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sr,vec_sr)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator>>,vec_sra)
		__DEFINE_ALTIVEC_BINARY_OPERATION(srl,vec_srl)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sro,vec_sro)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator<<,vec_sl)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sll,vec_sll)
		__DEFINE_ALTIVEC_BINARY_OPERATION(slo,vec_slo)
		__DEFINE_ALTIVEC_TERNARY_OPERATION_WITH_LITERAL(sld,vec_sld,unsigned int)
		__DEFINE_ALTIVEC_BINARY_OPERATION(rl,vec_rl)
		__DEFINE_ALTIVEC_BINARY_OPERATION(mergeh,vec_mergeh)
		__DEFINE_ALTIVEC_BINARY_OPERATION(mergel,vec_mergel)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_LITERAL(splat,vec_splat,unsigned int)
		__DEFINE_ALTIVEC_GENERATOR(mfvscr,vec_mfvscr)
		__DEFINE_ALTIVEC_UNARY_OPERATION(mtvscr,vec_mtvscr)
		__DEFINE_ALTIVEC_BINARY_OPERATION(pack,vec_pack)
		__DEFINE_ALTIVEC_BINARY_OPERATION(packpx,vec_packpx)
		__DEFINE_ALTIVEC_BINARY_OPERATION(packs,vec_packs)
		__DEFINE_ALTIVEC_BINARY_OPERATION(packsu,vec_packsu)
		__DEFINE_ALTIVEC_UNARY_OPERATION(unpackh,vec_unpackh)
		__DEFINE_ALTIVEC_UNARY_OPERATION(unpackl,vec_unpackl)		
		//@}
		
		/** @name arithmetic */
		//@{
		__DEFINE_ALTIVEC_UNARY_OPERATION(abs,vec_abs)
		__DEFINE_ALTIVEC_UNARY_OPERATION(abss,vec_abss)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator+,vec_add)
		__DEFINE_ALTIVEC_BINARY_OPERATION(addc,vec_addc)
		__DEFINE_ALTIVEC_BINARY_OPERATION(adds,vec_adds)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator-,vec_sub)
		__DEFINE_ALTIVEC_BINARY_OPERATION(subc,vec_subc)
		__DEFINE_ALTIVEC_BINARY_OPERATION(subs,vec_subs)
		__DEFINE_ALTIVEC_BINARY_OPERATION(mule,vec_mule)
		__DEFINE_ALTIVEC_BINARY_OPERATION(mulo,vec_mulo)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(madd,vec_madd)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(madds,vec_madds)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(mladd,vec_mladd)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(mradds,vec_mradds)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(msum,vec_msum)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(msums,vec_msums)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sum4s,vec_sum4s)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sum2s,vec_sum2s)
		__DEFINE_ALTIVEC_BINARY_OPERATION(sums,vec_sums)
		__DEFINE_ALTIVEC_TERNARY_OPERATION(nmsub,vec_nmsub)
		__DEFINE_ALTIVEC_BINARY_OPERATION(avg,vec_avg)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(max,vec_max)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(min,vec_min)
		__DEFINE_ALTIVEC_UNARY_OPERATION(round,vec_round)
		__DEFINE_ALTIVEC_UNARY_OPERATION(ceil,vec_ceil)
		__DEFINE_ALTIVEC_UNARY_OPERATION(floor,vec_floor)		
		__DEFINE_ALTIVEC_UNARY_OPERATION(trunc,vec_trunc)
		__DEFINE_ALTIVEC_UNARY_OPERATION(re,vec_re)
		__DEFINE_ALTIVEC_UNARY_OPERATION(rsqrte,vec_rsqrte)
		__DEFINE_ALTIVEC_UNARY_OPERATION(loge,vec_loge)
		__DEFINE_ALTIVEC_UNARY_OPERATION(expte,vec_expte)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_LITERAL(ctf,vec_ctf,unsigned int)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_LITERAL(cts,vec_cts,unsigned int)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_LITERAL(ctu,vec_ctu,unsigned int)
		//@}

		/** @name logical and compare */
		//@{
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator&,vec_and)
		__DEFINE_ALTIVEC_BINARY_OPERATION(andc,vec_andc)
		__DEFINE_ALTIVEC_BINARY_OPERATION(cmpb,vec_cmpb)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator==,vec_cmpeq)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator>=,vec_cmpge)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator>,vec_cmpgt)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator<=,vec_cmple)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator<,vec_cmplt)
		__DEFINE_ALTIVEC_BINARY_OPERATION(nor,vec_nor)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator|,vec_or)
		__DEFINE_ALTIVEC_BINARY_OPERATION_WITH_OVERLOAD(operator^,vec_xor)
		//@}

		/** @name predicates */
		//@{
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_eq,vec_all_eq)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_ne,vec_all_ne)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_eq,vec_any_eq)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_ne,vec_any_ne)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_ge,vec_all_ge)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_le,vec_all_le)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_ge,vec_any_ge)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_le,vec_any_le)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_gt,vec_all_gt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_lt,vec_all_lt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_gt,vec_any_gt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_lt,vec_any_lt)
		__DEFINE_ALTIVEC_UNARY_PREDICATE(all_nan,vec_all_nan)
		__DEFINE_ALTIVEC_UNARY_PREDICATE(all_numeric,vec_all_numeric)
		__DEFINE_ALTIVEC_UNARY_PREDICATE(any_nan,vec_any_nan)
		__DEFINE_ALTIVEC_UNARY_PREDICATE(any_numeric,vec_any_numeric)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_nge,vec_all_nge)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_nle,vec_all_nle)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_nge,vec_any_nge)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_nle,vec_any_nle)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_ngt,vec_all_ngt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_nlt,vec_all_nlt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_ngt,vec_any_ngt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_nlt,vec_any_nlt)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(all_in,vec_all_in)
		__DEFINE_ALTIVEC_BINARY_PREDICATE(any_out,vec_any_out)
		//@}
	}
	
// specializations for type traits

template <typename Type> struct __type_traits <macstl::altivec <Type> >
	{
		typedef __false_type	has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __false_type	is_POD_type;
	};

// specializations for boolean-valued functors

namespace std
	{
		template <class Type> struct equal_to <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x == y;
					}
			};

		template <class Type> struct not_equal_to <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x != y;
					}
			};
		
		template <class Type> struct greater <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x > y;
					}
			};
		
		template <class Type> struct less <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x < y;
					}
			};
		
		template <class Type> struct greater_equal <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x >= y;
					}
			};

		
		template <class Type> struct less_equal <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x <= y;
					}
			};
		
		template <class Type> struct logical_and <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x && y;
					}
			};

		
		template <class Type> struct logical_or <macstl::altivec <Type> >:
			public binary_function <macstl::altivec <Type>, macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool> 
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x, const macstl::altivec <Type>& y) const
					{
						return x || y;
					}
			};
		
		template <class Type> struct logical_not <macstl::altivec <Type> >:
			public unary_function <macstl::altivec <Type>, typename macstl::altivec <Type>::altivec_bool>
			{
				typename macstl::altivec <Type>::altivec_bool operator()
					(const macstl::altivec <Type>& x) const
					{
						return !x;
					}
			};
			
	}
	
#endif
