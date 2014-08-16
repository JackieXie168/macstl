/*
 *  vec.h
 *  macstl
 *
 *  Created by Glen Low on Feb 07 2004.
 *
 *  Copyright (c) 2004-2005 Pixelglow Software, all rights reserved.
 *  http://www.pixelglow.com/macstl/
 *  macstl@pixelglow.com
 *
 *  Unless explicitly acquired and licensed from Licensor under the Pixelglow
 *  Software License ("PSL") Version 2.0 or greater, the contents of this file
 *  are subject to the Reciprocal Public License ("RPL") Version 1.1, or
 *  subsequent versions as allowed by the RPL, and You may not copy or use this
 *  file in either source code or executable form, except in compliance with the
 *  terms and conditions of the RPL.
 *
 *  While it is an open-source license, the RPL prohibits you from keeping your
 *  derivations of this file proprietary even if you only deploy them in-house.
 *  You may obtain a copy of both the PSL and the RPL ("the Licenses") from
 *  Pixelglow Software ("the Licensor") at http://www.pixelglow.com/.
 *
 *  Software distributed under the Licenses is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the Licenses
 *  for the specific language governing rights and limitations under the
 *  Licenses. Notwithstanding anything else in the Licenses, if any clause of
 *  the Licenses which purports to disclaim or limit the Licensor's liability
 *  for breach of any condition or warranty (whether express or implied by law)
 *  would otherwise be void, that clause is deemed to be subject to the
 *  reservation of liability of the Licensor to supply the software again or to
 *  repair the software or to pay the cost of having the software supplied again
 *  or repaired, at the Licensor's option. 
 */

#ifndef MACSTL_VEC_H
#define MACSTL_VEC_H

#include "impl/config.h"

#include <sstream>

#include "functional.h"
#include "impl/data.h"
#include "impl/meta.h"

#include "boolean.h"
#include "complex.h"
#include "pixel.h"

namespace macstl
	{
		#ifdef DOXYGEN
		
		/// SIMD type.
		
		/// This platform-independent SIMD type offers valarray-like behavior in a package the size of a single CPU register.
		///
		/// @param	T	The element value type.
		/// @param	n	The number of elements.
		///
		/// @note	The primary template is not actually defined, only the explicit specializations corresponding to actual SIMD
		///			types are e.g. in Altivec, vec <short, 8> is defined (corresponding to __vector signed short on that platform) but vec <short, 16> isn't.
		///			This allows you to use template metaprogramming to determine whether an actual SIMD type exists on a platform.
		///
		/// @header	#include <macstl/vec.h>
		///
		/// @see	macstl::altivec, macstl::mmx
		
		template <typename T, std::size_t n> class vec: public impl::vec_base <D, T, B>
			{
				public:
					/// Type used for static initialization. Usually the same as the value type, but may vary due to C++ template non-type parameter restrictions.
					typedef value_type init_type;

					/// Type used for packing and unpacking elements.
					union union_type
						{
							/// For unpacking elements. This usually has the same as the value type, but may vary due to C++ union data member restrictions.
							value_type val [n];
							
							/// For packing elements.
							data_type vec;
						};
					
						
					/// Constructs with all elements zero.
					vec ()
						{
						}
						
					/// Constructs from the raw vector data.
					vec (data_type data): data_ (data)
						{
						}
					
					/// Sets a vector with n elements, @a v0...
					static vec set (value_type v0...);
										
					/// Fills a vector with the same element @a v.
					static vec fill (value_type v);
											
					/// Sets a vector with n constant elements, @a v0...
					template <init_type v0...> static vec set ();

					/// Fills a vector with the same constant element @a v.
					template <init_type v> static vec fill ();
			
			}
		
		#else
		// forward declare only, we will explicitly specialize particular vec
		template <typename T, std::size_t n> class vec;
		#endif
	}

namespace stdext
	{
		template <typename F> struct accumulator;
		template <typename T> struct shifter;
		template <typename T> struct cshifter;
	}
	
namespace macstl
	{
		namespace impl
			{
				#define DEFINE_VEC_COMMON_CASSIGN_FUNCTION(FN,OP)											\
				vec_value& FN (const vec_value& lhs)	{ return that () = that () OP lhs; }

				/// Base for vec class.
				
				/// @internal
				/// This class defines all the common member and friend functions for vec,
				/// an interface similar to valarray.
				///
				/// @param	D	Raw vector data type e.g. __vector unsigned int (Altivec) or __m128i (SSE2).
				/// @param	T	Scalar element type e.g. unsigned int.
				/// @param	B	Scalar element type for logical function results e.g. boolean <int>.
				///
				/// @note	Uses the Barton-Nackman trick to expose friend functions, so that you can use raw data types
				///			interchangeably with the vector object. Operators are only defined for the vector when they are
				///			defined for the element types, e.g. operator~ is not defined for vec <float, 4> since operator~
				///			is not defined for float.
				
				template <typename D, typename T, typename B> class vec_base
					{
						public:
							/// Raw vector data type.
							typedef D data_type;
							
							/// Scalar element type.
							typedef T value_type;
							
							/// Scalar element type for logical function results.
							typedef B boolean_type;

							/// Number of elements.
							static const size_t length = sizeof (data_type) / sizeof (value_type);

							/// Object vector data type for logical function results.
							typedef vec <B, length> vec_boolean;
							
							/// Object vector data type. This should be the subclass.
							typedef vec <T, length> vec_value;
							
							/// Proxy for accessing and changing vec elements.
							
							/// vec_base::operator[] returns this so that elements can be mutated in an alias-safe manner.
							/// This pessimizes element-by-element access, of course.
							
							class reference
								{
									public:
										/// Stores the referenced element @a lhs.
										reference& operator= (value_type lhs)
											{
												reinterpret_cast <typename vec_value::union_type*> (data_)->val [index_] = data_of (lhs);
												return *this;
											}
											
										/// Returns the referenced element @a lhs.
										operator value_type () const
											{
												return reinterpret_cast <typename vec_value::union_type*> (data_)->val [index_];
											}
											
										friend class vec_base;
								
									private:
										reference (data_type* data, std::size_t index): data_ (data), index_ (index)
											{
											}
											
										data_type* const data_;
										const std::size_t index_;
								};
								
							/// Gets a reference to the element at index @a i.
							reference operator[] (std::size_t i)
								{
									return reference (&that ().data_, i);
								}
								
							/// Assigns the raw data @a lhs.
							void operator= (data_type lhs)		{ that ().data_ = lhs; }
							
							/// @name Computed Assignments
							
							/// @{
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator*=,*)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator/=,/)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator%=,%)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator+=,+)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator-=,-)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator^=,^)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator&=,&)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator|=,|)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator<<=,<<)
							DEFINE_VEC_COMMON_CASSIGN_FUNCTION(operator>>=,>>)
							/// @}
							
							/// Gets the raw vector data.
							data_type data () const		{ return that ().data_; }
							
							/// Gets the number of elements. Same as length.
							static std::size_t size ()		{ return length; }
								
							/// Gets the element at index @a i.
							value_type operator[] (std::size_t i) const
								{
									return value_type (reinterpret_cast <const typename vec_value::union_type&> (that ().data_).val [i]);
								}
								
							/// Gets the maximum element.
							value_type max () const { return stdext::accumulator <stdext::maximum <vec_value> > () (that ()); }
							
							/// Gets the minium element.
							value_type min () const { return stdext::accumulator <stdext::minimum <vec_value> > () (that ()); }
							
							/// Gets the sum of all elements.
							value_type sum () const { return stdext::accumulator <std::plus <vec_value> > () (that ()); }
							
							/// Shifts all elements left by i places.
							const vec_value shift (int i) const		{ return stdext::shifter <vec_value> () (that (), i); }
							
							/// Shifts all elements circularly left by i places.
							const vec_value cshift (int i) const	{ return stdext::cshifter <vec_value> () (that (), i); }
																		
						private:
							vec_value& that ()				{ return static_cast <vec_value&> (*this); }
							const vec_value& that () const	{ return static_cast <const vec_value&> (*this); }
					};

				template <typename T> struct data_vec
					{
						typedef T type;
					};
					
				template <typename T> struct is_vec
					{
						static const int value = 0;
					};

				template <typename T, std::size_t n> struct is_vec <vec <T, n> >
					{
						static const int value = 1;
					};

			}
					
		/// @name I/O
		/// @relates vec
		
		//@{
		
		/// Inserts a @a vector into an output stream @a os.
		template <typename CharT, typename Traits, typename T, std::size_t n>
			inline std::basic_ostream <CharT, Traits>& operator<< (std::basic_ostream <CharT, Traits>& os, const vec <T, n>& vector)
			{
				if (os.good ())
					{
						typename std::basic_ostream <CharT, Traits>::sentry opfx (os);

						if (opfx)
							{
								typedef typename vec <T, n>::value_type value_type;
								typename vec <T, n>::union_type un;
								
								un.vec = vector.data ();
								
								std::basic_ostringstream <CharT, Traits> s;
								s.flags (os.flags ());
								s.imbue (os.getloc ());
								s.precision (os.precision ());
								
								s << value_type (un.val [0]);
								for (std::size_t i = 1; i < n; ++i)
									s << os.fill () << value_type (un.val [i]);

								if (s.fail ())
									os.setstate (std::ios_base::failbit);
								else
									os << s.str();
							}
					}
				return os;
			}
		
		/// Extracts a @a vector from an input stream @a is.
		template <typename CharT, typename Traits, typename T, std::size_t n>
			inline std::basic_istream <CharT, Traits>& operator>> (std::basic_istream <CharT, Traits>& is, vec <T, n>& vector)
			{
				if (is.good ())
					{
						typename std::basic_istream <CharT, Traits>::sentry ipfx (is);

						if (ipfx)
							{
								typedef typename vec <T, n>::value_type value_type;
								typename vec <T, n>::union_type un;
								
								for (std::size_t i = 0; i < n; ++i)
									{
										T val;
										is >> val;
										un.val [i] = data_of (val);
									}
									
								if (!is.fail ())
									vector = vec <T, n> (un.vec);
							}
					}
				return is;
			}

		/// Inserts a vector element into an output stream @a os, through an element proxy.
		template <typename CharT, typename Traits, typename T, std::size_t n>
			inline std::basic_ostream <CharT, Traits>& operator<< (std::basic_ostream <CharT, Traits>& os, const typename vec <T, n>::reference& reference)
			{
				return os << static_cast <typename vec <T, n>::value_type> (reference);
			}
			
		//@}
	}


namespace stdext
	{
		namespace impl
			{
				template <typename T, std::size_t n> struct has_trivial_copy <macstl::vec <T, n> >		{ enum { value = has_trivial_copy <T>::value }; };
				template <typename T, std::size_t n> struct has_trivial_assign <macstl::vec <T, n> >		{ enum { value = has_trivial_assign <T>::value }; };
				template <typename T, std::size_t n> struct has_trivial_destructor <macstl::vec <T, n> >	{ enum { value = has_trivial_destructor <T>::value }; };
			}
	}
	
#define DEFINE_VEC_COMMON_UNARY_FUNCTION(FN,NS,FTR)																		\
																														\
namespace NS																											\
	{																													\
		template <typename T, std::size_t n> struct FTR <macstl::vec <T, n> >;												\
	}																													\
																														\
namespace macstl																										\
	{																													\
		template <typename T> inline const typename stdext::impl::enable_if <											\
			impl::is_vec <typename impl::data_vec <T>::type>::value,													\
			typename NS::FTR <typename impl::data_vec <T>::type>::result_type>::type FN									\
			(const T& lhs)																								\
			{																											\
				return NS::FTR <typename impl::data_vec <T>::type> () (lhs);											\
			}																											\
	}

#define DEFINE_VEC_COMMON_BINARY_FUNCTION(FN,NS,FTR)																	\
																														\
namespace NS																											\
	{																													\
		template <typename T, std::size_t n> struct FTR <macstl::vec <T, n> >;												\
	}																													\
																														\
namespace macstl																										\
	{																													\
		template <typename T1, typename T2> inline const typename stdext::impl::enable_if <								\
			impl::is_vec <typename impl::data_vec <T1>::type>::value != 0												\
			&& stdext::impl::is_same <typename impl::data_vec <T1>::type, typename impl::data_vec <T2>::type>::value != 0,	\
			typename NS::FTR <typename impl::data_vec <T1>::type>::result_type>::type FN								\
			(const T1& lhs, const T2& rhs)																				\
			{																											\
				return NS::FTR <typename impl::data_vec <T1>::type> () (lhs, rhs);										\
			}																											\
	}

#define DEFINE_VEC_COMMON_TERNARY_FUNCTION(FN,NS,FTR)																	\
																														\
namespace NS																											\
	{																													\
		template <typename T, std::size_t n> struct FTR <macstl::vec <T, n> >;												\
	}																													\
																														\
namespace macstl																										\
	{																													\
		template <typename T1, typename T2, typename T3> inline const typename stdext::impl::enable_if <				\
			impl::is_vec <typename impl::data_vec <T1>::type>::value != 0												\
			&& stdext::impl::is_same <typename impl::data_vec <T1>::type, typename impl::data_vec <T2>::type>::value != 0		\
			&& stdext::impl::is_same <typename impl::data_vec <T2>::type, typename impl::data_vec <T3>::type>::value != 0,	\
			typename NS::FTR <typename impl::data_vec <T1>::type>::result_type>::type FN								\
			(const T1& lhs, const T2& mhs, const T3& rhs)																\
			{																											\
				return NS::FTR <typename impl::data_vec <T1>::type> () (lhs, mhs, rhs);									\
			}																											\
	}

/// @name Unary Arithmetic
/// @relates macstl::vec
/// Each returns a new vector with elements of type T.

//@{
DEFINE_VEC_COMMON_UNARY_FUNCTION(operator+,stdext,identity)
DEFINE_VEC_COMMON_UNARY_FUNCTION(operator+,std,negate)
DEFINE_VEC_COMMON_UNARY_FUNCTION(operator~,stdext,bitwise_not)
//@}

/// @name Unary Logic
/// @relates macstl::vec
/// Each returns a new vector with boolean elements.

//@{
DEFINE_VEC_COMMON_UNARY_FUNCTION(operator!,std,logical_not)
//@}

/// @name Binary Arithmetic
/// @relates vec
/// Each returns a new vector with elements of type T. You can also use a raw vector for either lhs or rhs.

//@{
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator*,std,multiplies)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator/,std,divides)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator%,std,modulus)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator+,std,plus)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator-,std,minus)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator^,stdext,bitwise_xor)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator-,stdext,bitwise_and)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator-,stdext,bitwise_or)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator<<,stdext,shift_left)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator>>,stdext,shift_right)
//@}

/// @name Binary Logic
/// @relates macstl::vec
/// Each returns a new vector with boolean elements. You can also use a raw vector for either lhs or rhs.
//@{
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator==,std,equal_to)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator!=,std,not_equal_to)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator<,std,less)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator>,std,greater)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator<=,std,less_equal)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator>=,std,greater_equal)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator&&,std,logical_and)
DEFINE_VEC_COMMON_BINARY_FUNCTION(operator||,std,logical_or)
//@}

/// @name Transcendentals
/// @relates macstl::vec
/// Each returns a new vector with elements of type T. You can also use a raw vector for either lhs or rhs.

//@{
DEFINE_VEC_COMMON_UNARY_FUNCTION(abs,stdext,absolute)
DEFINE_VEC_COMMON_UNARY_FUNCTION(acos,stdext,arc_cosine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(asin,stdext,arc_sine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(atan,stdext,arc_tangent)
DEFINE_VEC_COMMON_BINARY_FUNCTION(atan2,stdext,arc_tangent2)
DEFINE_VEC_COMMON_UNARY_FUNCTION(cos,stdext,cosine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(cosh,stdext,hyperbolic_cosine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(exp,stdext,exponent)
DEFINE_VEC_COMMON_UNARY_FUNCTION(exp2,stdext,exponent2)
DEFINE_VEC_COMMON_TERNARY_FUNCTION(fma,stdext,multiplies_plus)
DEFINE_VEC_COMMON_UNARY_FUNCTION(log,stdext,logarithm)
DEFINE_VEC_COMMON_UNARY_FUNCTION(log2,stdext,logarithm2)
DEFINE_VEC_COMMON_UNARY_FUNCTION(log10,stdext,logarithm10)
DEFINE_VEC_COMMON_BINARY_FUNCTION(max,stdext,maximum)
DEFINE_VEC_COMMON_BINARY_FUNCTION(min,stdext,minimum)
DEFINE_VEC_COMMON_BINARY_FUNCTION(mulhi,stdext,multiplies_high)
DEFINE_VEC_COMMON_BINARY_FUNCTION(pow,stdext,power)
DEFINE_VEC_COMMON_UNARY_FUNCTION(sin,stdext,sine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(sinh,stdext,hyperbolic_sine)
DEFINE_VEC_COMMON_UNARY_FUNCTION(sqrt,stdext,square_root)
DEFINE_VEC_COMMON_UNARY_FUNCTION(tan,stdext,tangent)
DEFINE_VEC_COMMON_UNARY_FUNCTION(tanh,stdext,hyperbolic_tangent)
//@}

#define DEFINE_VEC_PLATFORM_UNARY_FUNCTION(FN,DESC)														\
																									\
template <typename T> struct FN##_function;																	\
																									\
template <typename T>																				\
	inline const typename FN##_function <typename macstl::impl::data_vec <T>::type>::result_type FN (const T& lhs)				\
	{																								\
		return FN##_function <typename macstl::impl::data_vec <T>::type> () (lhs);																	\
	}			

#define DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL(FN,DESC)											\
																									\
template <unsigned int i, typename T> struct FN##_function;													\
																									\
template <unsigned int i, typename T>																\
	inline const typename FN##_function <i, typename macstl::impl::data_vec <T>::type>::result_type FN (const T& lhs)				\
	{																								\
		return FN##_function <i, typename macstl::impl::data_vec <T>::type> () (lhs);																	\
	}			

#define DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4(FN,DESC)											\
																									\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l, typename T> struct FN##_function;													\
																									\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l, typename T>																\
	inline const typename FN##_function <i, j, k, l, typename macstl::impl::data_vec <T>::type>::result_type FN (const T& lhs)				\
	{																								\
		return FN##_function <i, j, k, l, typename macstl::impl::data_vec <T>::type> () (lhs);																	\
	}			

#define DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_RETURN_TYPE(FN,DESC)										\
																									\
template <typename R, typename T> struct FN##_function;												\
																									\
template <typename R, typename T> inline const R FN (const T& lhs)									\
	{																								\
		return FN##_function <R, typename macstl::impl::data_vec <T>::type> () (lhs);				\
	}			
	
#define DEFINE_VEC_PLATFORM_BINARY_FUNCTION(FN,DESC)														\
																									\
template <typename T1, typename T2 = T1> struct FN##_function;												\
																									\
template <typename T1, typename T2>																	\
	inline const typename FN##_function <typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type>::result_type FN (const T1& lhs, const T2& rhs)						\
	{																								\
		return FN##_function <typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type> () (lhs, rhs);															\
	}

#define DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL(FN,DESC)										\
																									\
template <unsigned int i, typename T1, typename T2 = T1> struct FN##_function;								\
																									\
template <unsigned int i, typename T1, typename T2>													\
	inline const typename FN##_function <i, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type>::result_type FN (const T1& lhs, const T2& rhs)					\
	{																								\
		return FN##_function <i, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type> () (lhs, rhs);														\
	}

#define DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL2(FN,DESC)										\
																									\
template <unsigned int i, unsigned int j, typename T1, typename T2 = T1> struct FN##_function;								\
																									\
template <unsigned int i, unsigned int j, typename T1, typename T2>													\
	inline const typename FN##_function <i, j, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type>::result_type FN (const T1& lhs, const T2& rhs)					\
	{																								\
		return FN##_function <i, j, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type> () (lhs, rhs);														\
	}

#define DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL4(FN,DESC)										\
																									\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l, typename T1, typename T2 = T1> struct FN##_function;								\
																									\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l, typename T1, typename T2>													\
	inline const typename FN##_function <i, j, k, l, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type>::result_type FN (const T1& lhs, const T2& rhs)					\
	{																								\
		return FN##_function <i, j, k, l, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type> () (lhs, rhs);														\
	}

#define DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_RETURN_TYPE(FN,DESC)									\
																									\
template <typename R, typename T1, typename T2 = T1> struct FN##_function;							\
																									\
template <typename R, typename T1, typename T2> inline const R FN (const T1& lhs, const T2& rhs)					\
	{																								\
		return FN##_function <R, typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type> () (lhs, rhs);			\
	}			

#define DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(FN,DESC)													\
																									\
template <typename T1, typename T2 = T1, typename T3 = T1> struct FN##_function;								\
																									\
template <typename T1, typename T2, typename T3>													\
	inline const typename FN##_function <typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type, typename macstl::impl::data_vec <T3>::type>::result_type FN (const T1& lhs, const T2& mhs, const T3& rhs)	\
	{																								\
		return FN##_function <typename macstl::impl::data_vec <T1>::type, typename macstl::impl::data_vec <T2>::type, typename macstl::impl::data_vec <T3>::type> () (lhs, mhs, rhs);													\
	}



#ifdef __VEC__
#include "impl/vec_altivec.h"
#else
#if defined(__MMX__) || defined(__SSE__) || defined(__SSE2__)
#include "impl/vec_mmx.h"
#endif
#endif

#endif



