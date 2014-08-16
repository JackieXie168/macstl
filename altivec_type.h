/*
 *  altivec_type
 *  macstl
 *
 *  Created by Glen Low on Tue Sep 10 2002.
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

#include <functional>
#include <iosfwd>
#include <iomanip>

#include "boolean.h"
#include "internal/altivec_traits.h"

#define __DEFINE_ALTIVEC_MEMBER_FUNCTION(FUNC, OPER, RSLT)																			\
RSLT FUNC () const										{ return altivec_traits::OPER (data ()); }

#define __DEFINE_ALTIVEC_UNARY_FUNCTION(FUNC, OPER, RSLT)																			\
friend RSLT FUNC (const altivec& x)						{ return altivec_traits::OPER (x.data ()); }

#define __DEFINE_ALTIVEC_BINARY_FUNCTION(FUNC, OPER, RSLT)																			\
friend RSLT FUNC (const altivec& x, const altivec& y)	{ return altivec_traits::OPER (x.data (), y.data ()); }						\
friend RSLT FUNC (const altivec& x, vector_type y)		{ return altivec_traits::OPER (x.data (), y); }							\
friend RSLT FUNC (vector_type x, const altivec& y)		{ return altivec_traits::OPER (x, y.data ()); }							\
friend RSLT FUNC (const altivec& x, value_type y)		{ return altivec_traits::OPER (x.data (), altivec_traits::splat (y)); }	\
friend RSLT FUNC (value_type x, const altivec& y)		{ return altivec_traits::OPER (altivec_traits::splat (x), y.data ()); }

#define __DEFINE_ALTIVEC_CASSIGN_FUNCTION(FUNC, OPER)																				\
friend altivec& FUNC (altivec& x, const altivec& y)		{ return x = altivec_traits::OPER (x.data (), y.data ()); }				\
friend altivec& FUNC (altivec& x, vector_type y)		{ return x = altivec_traits::OPER (x.data (), y); }						\
friend altivec& FUNC (altivec& x, value_type y)			{ return x = altivec_traits::OPER (x.data (), altivec_traits::splat (y)); }

namespace macstl
	{
		template <typename Type> class altivec_access;
		
		template <typename Type> class altivec
			{
				public:
					typedef altivec_traits <Type> altivec_traits;
					
					typedef typename altivec_traits::vector_type vector_type;
					typedef typename altivec_traits::value_type value_type;
					typedef typename altivec_traits::union_type union_type;
					
					typedef altivec <typename altivec_traits::bool_value_type> altivec_bool;
					
					static const size_t length = altivec_traits::length;
					
							// constructors
					
					altivec (): data_ (altivec_traits::zero ())
						{
						}
					
					explicit altivec (value_type scalar): data_ (altivec_traits::splat (scalar))
						{
						}
						
					altivec (vector_type data): data_ (data)
						{
						}
						
					// trivial destructor
					// ~altivec ();
					
					// load from aligned address
					
					static altivec load (const value_type* address, size_t offset = 0)
						{
							return altivec_traits::load (address, offset);
						}
		
					// trivial copy constructor
					// altivec (const altivec&);
									
					// assignments
					
					altivec& operator= (value_type scalar)
						{
							data_ = altivec_traits::splat (scalar);
							return *this;
						}
						
					altivec& operator= (vector_type data)
						{
							data_ = data;
							return *this;
						}
						
					// trivial assignment operator
					// altivec& operator= (const altivec&);
						
					// store to aligned address
					void store (value_type* address, size_t offset = 0) const
						{
							altivec_traits::store (data_, address, offset);
						}
													
					static size_t size ()
						{
							return altivec_traits::length;
						}
						
						
					// DANGER WILL ROBINSON!! If this is to work under -fstrict-aliasing, an vector_type should be allowed
					// to alias its value_type e.g. vector float* can alias float*. We don't use a union since carrying that
					// baggage around in the type seems to spoil further alias analysis optimizations. In any case, this seems
					// to be true of gcc 3.1 but isn't explicitly sanctioned by the Standard...
					
					value_type operator[] (size_t index) const
						{
							return reinterpret_cast <const value_type*> (&data_) [index];
						}

					value_type& operator[] (size_t index)
						{
							return reinterpret_cast <value_type*> (&data_) [index];
						}
						
					vector_type data () const
						{
							return data_;
						}
						
					value_type sum () const
						{
							return altivec_traits::sum (data_);
						}
						
					value_type min () const
						{
							return altivec_traits::min (data_);
						}
						
					value_type max () const
						{
							return altivec_traits::max (data_);
						}

					altivec apply (value_type func (value_type)) const
						{
							union_type un;
							for (size_t index = 0; index != altivec_traits::length; ++index)
								un.val [index] = func ((*this) [index]);
							return un.vec;
						}
						
					altivec apply (value_type func (const value_type&)) const
						{
							union_type un;
							for (size_t index = 0; index != altivec_traits::length; ++index)
								un.val [index] = func ((*this) [index]);
							return un.vec;
						}
						
					// unary operators
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator-, negate, altivec)
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator~, bitwise_not, altivec)
					__DEFINE_ALTIVEC_MEMBER_FUNCTION (operator!, logical_not, altivec_bool)
					
					// binary operators
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator+, plus, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator-, minus, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator*, multiplies, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator/, divides, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator%, modulus, altivec)            
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator&, bitwise_and, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator|, bitwise_or, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator^, bitwise_xor, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<<, left_shift, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>>, right_shift, altivec)            
					
					// operator assigments
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
				
					// binary relations
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator==, equal_to, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator!=, not_equal_to, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>, greater, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator>=, greater_equal, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<, less, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator<=, less_equal, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator&&, logical_and, altivec_bool)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (operator||, logical_or, altivec_bool)
		
					// transcendental functions
					__DEFINE_ALTIVEC_UNARY_FUNCTION (abs, abs, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (cos, cos, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (acos, acos, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (cosh, cosh, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (sin, sin, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (asin, asin, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (sinh, sinh, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (tan, tan, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (tanh, tanh, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (atan, atan, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (exp, exp, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (log, log, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (log10, log10, altivec)
					__DEFINE_ALTIVEC_UNARY_FUNCTION (sqrt, sqrt, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (atan2, atan2, altivec)
					__DEFINE_ALTIVEC_BINARY_FUNCTION (pow, pow, altivec)
					
				private:
					vector_type data_;
			};
			
		// output stream extractor
		template <class Type, class _CharT, class _Traits> std::basic_ostream <_CharT, _Traits>&
			operator<< (std::basic_ostream <_CharT, _Traits>& os, const altivec <Type>& vec)
			{
				std::streamsize subwidth = os.width () / altivec <Type>::size ();
				if (subwidth)
					for (size_t i = 0; i < altivec <Type>::size (); ++i)
						os << std::setw (subwidth) << vec [i];
				else
					{
						os << vec [0];
						for (size_t i = 1; i < altivec <Type>::size (); ++i)
							os << os.fill () << vec [i];
					}
				return os;
			}
		
		// input stream inserter
		
		template <class Type, class _CharT, class _Traits> std::basic_istream <_CharT, _Traits>&
			operator>> (std::basic_istream <_CharT, _Traits>& is, altivec <Type>& vec)
			{
				for (size_t i = 0; i < altivec <Type>::size (); ++i)
					is >> vec [i];
				
				return is;
			}
			
	};
	
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
			
		// max and min from algorithm
		// NOTE: these functions have a different sense from the ones in algorithm since the result is a composition of the two
		// inputs, not one or the other. On the other hand, the ones in algorithm could not have worked anyway since operator< does
		// yield a bool, it yields an altivec boolean.
		
		template <typename Type> inline macstl::altivec <Type> max (const macstl::altivec <Type>& a, const macstl::altivec <Type>& b)
			{
				return macstl::altivec_traits <Type>::max (a.data (), b.data ());
			}

		template <typename Type> inline macstl::altivec <Type> min (const macstl::altivec <Type>& a, const macstl::altivec <Type>& b)
			{
				return macstl::altivec_traits <Type>::min (a.data (), b.data ());
			}

	};
