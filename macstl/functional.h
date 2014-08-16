/*
 *  functional.h
 *  macstl
 *
 *  Created by Glen Low on Nov 13 2002.
 *
 *  Copyright (c) 2003-2005 Pixelglow Software, all rights reserved.
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
 
#ifndef MACSTL_FUNCTIONAL_H
#define MACSTL_FUNCTIONAL_H

#include <cmath>
#include <functional>
#include <limits>

#if defined(__PPC__) || defined(__PPC64__)
#include <ppc_intrinsics.h>
#endif

#include "impl/meta.h"

namespace stdext
	{
	
		namespace impl
			{
				template <typename T> struct smaller_than_half_int
					{
						enum { value = sizeof (T) > sizeof (int) / 2 };
					};
			}

		template <typename T> inline typename impl::enable_if <impl::smaller_than_half_int <T>::value, T>::type mulhi (const T& lhs, const T& rhs)
			{
				// if lhs * rhs will fit into an int, just do the multiply and grab the high word
				return (lhs * rhs) >> (sizeof (T) * CHAR_BIT);
			}
			
		template <typename T> inline typename impl::enable_if <impl::smaller_than_half_int <T>::value == 0, T>::type mulhi (const T& lhs, const T& rhs)
			{
				// if lhs * rhs won't fit into an int, split into high and low words and do it the schoolyard way...
				
				static const int half_size = sizeof (T) * CHAR_BIT / 2;
				static const T lo_mask = (1 << half_size) - 1;
				
				T lhs_hi = lhs >> half_size;
				T lhs_lo = lhs & lo_mask;
				T rhs_hi = rhs >> half_size;
				T rhs_lo = rhs & lo_mask;
				
				T mid = ((lhs_lo * rhs_lo) >> half_size) + (lhs_lo * rhs_hi);
				T mid_hi = mid >> half_size;
				T mid_lo = mid & lo_mask;
				
				return lhs_hi * rhs_hi + mid_hi + ((mid_lo + lhs_hi * rhs_lo) >> half_size);
			}
			
		#if defined(__PPC__) || defined(__PPC64__)

		inline int mulhi (int lhs, int rhs)
			{
				return __mulhw (lhs, rhs);
			}

		inline unsigned int mulhi (unsigned int lhs, unsigned int rhs)
			{
				return __mulhwu (lhs, rhs);
			}


		#endif

		template <typename T> struct identity: public std::unary_function <T, T>
			{
				T operator() (const T& x) const	
					{
						return x;
					}
			};
		
		template <typename T> struct bitwise_not: public std::unary_function <T, T>
			{
				T operator() (const T& x) const	
					{
						return ~x;
					}
			};
			
		template <typename T> struct bitwise_and: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return x & y;
					}
			};
		
		template <typename T> struct bitwise_or: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return x | y;
					}
			};
			
		template <typename T> struct bitwise_xor: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return x ^ y;
					}
			};
		
		template <typename T> struct multiplies_high: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return mulhi (x, y);
					}
			};

		template <typename T> struct multiplies_plus;

		template <typename T> struct shift_left: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return x << y;
					}
			};
		
		template <typename T> struct shift_right: public std::binary_function <T, T, T>
			{
				T operator() (const T& x, const T& y) const
					{
						return x >> y;
					}
			};

				
		template <typename T> struct absolute: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::abs;
						return abs (lhs);
					}
			};

		template <typename T> struct arc_cosine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::acos;
						return acos (lhs);
					}
			};

		template <typename T> struct arc_sine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::asin;
						return asin (lhs);
					}
			};

		template <typename T> struct arc_tangent: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::atan;
						return atan (lhs);
					}
			};
			
		template <typename T> struct arc_tangent2: public std::binary_function <T, T, T>
			{
				T operator() (const T& lhs, const T& rhs) const
					{
						using std::atan2;
						return atan2 (lhs, rhs);
					}
			};
			
		template <typename T> struct cosine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::cos;
						return cos (lhs);
					}
			};
			
		template <typename T> struct exponent: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::exp;
						return exp (lhs);
					}
			};

		template <typename T> struct exponent2: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						return exp2 (lhs);
					}
			};
			
		template <typename T> struct hyperbolic_cosine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::cosh;
						return cosh (lhs);
					}
			};

		template <typename T> struct hyperbolic_sine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::sinh;
						return sinh (lhs);
					}
			};

		template <typename T> struct hyperbolic_tangent: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::tanh;
						return tanh (lhs);
					}
			};

		template <typename T> struct logarithm: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::log;
						return log (lhs);
					}
			};

		template <typename T> struct logarithm2: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						return log2 (lhs);
					}
			};

		template <typename T> struct logarithm10: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::log10;
						return log10 (lhs);
					}
			};

		template <typename T> struct maximum: public std::binary_function <T, T, T>
			{
				T operator() (const T& lhs, const T& rhs) const
					{
						return rhs < lhs ? lhs : rhs;
					}
			};

		#if !__FINITE_MATH_ONLY__
		
		template <> struct maximum <float>: public std::binary_function <float, float, float>
			{
				float operator() (float lhs, float rhs) const
					{
						return rhs < lhs || rhs != rhs ? lhs : rhs;	// in case lhs is NAN
					}
			};

		template <> struct maximum <double>: public std::binary_function <double, double, double>
			{
				double operator() (double lhs, double rhs) const
					{
						return rhs < lhs || rhs != rhs ? lhs : rhs;	// in case lhs is NAN
					}
			};
			
		#endif
			
		template <typename T> struct minimum: public std::binary_function <T, T, T>
			{
				T operator() (const T& lhs, const T& rhs) const
					{
						return lhs < rhs ? lhs : rhs;
					}
			};
		
		#if !__FINITE_MATH_ONLY__

		template <> struct minimum <float>: public std::binary_function <float, float, float>
			{
				float operator() (float lhs, float rhs) const
					{
						return lhs < rhs || rhs != rhs ? lhs : rhs;	// in case lhs is NAN
					}
			};

		template <> struct minimum <double>: public std::binary_function <double, double, double>
			{
				double operator() (double lhs, double rhs) const
					{
						return lhs < rhs || rhs != rhs ? lhs : rhs;	// in case lhs is NAN
					}
			};
			
		#endif
			
		template <typename T> struct power: public std::binary_function <T, T, T>
			{
				T operator() (const T& lhs, const T& rhs) const
					{
						using std::pow;
						return pow (lhs, rhs);
					}
			};
			
		template <typename T> struct sine: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::sin;
						return sin (lhs);
					}
			};

		template <typename T> struct square_root: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::sqrt;
						return sqrt (lhs);
					}
			};

		template <typename T> struct tangent: public std::unary_function <T, T>
			{
				T operator() (const T& lhs) const
					{
						using std::tan;
						return tan (lhs);
					}
			};
						
		template <typename Type> struct parameter
			{
				typedef const Type& type;
			};
			
		template <typename Type> struct parameter <Type&>
			{
				typedef Type& type;
			};
				
		template <typename Operation> class binder1st: protected Operation
			{
				public:
					typedef typename Operation::second_argument_type argument_type;
					typedef typename Operation::result_type result_type;
					
					binder1st (const Operation& op,
						typename parameter <typename Operation::first_argument_type>::type bound):
						Operation (op), bound_ (bound)
						{
						}
						
					typename Operation::result_type operator()
						(typename parameter <typename Operation::second_argument_type>::type x) const
						{
							return (*this) (bound_, x); 
						}

					typename Operation::first_argument_type bound () const
						{
							return bound_;
						}

				private:
					const typename Operation::first_argument_type bound_;
					
					using Operation::operator();
			};
		
		template <typename Operation, typename Type> inline binder1st <Operation> 
			bind1st (const Operation& fn, const Type& x) 
			{
				typedef typename parameter <typename Operation::first_argument_type>::type first_argument_type;
				return binder1st <Operation> (fn, first_argument_type (x));
			}
	
		template <typename Operation, typename Type> inline binder1st <Operation> 
			bind1st (const Operation& fn, Type& x) 
			{
				typedef typename parameter <typename Operation::first_argument_type>::type first_argument_type;
				return binder1st<Operation> (fn, first_argument_type (x));
			}
	
		template <typename Operation> class binder2nd: protected Operation
			{
				public:
					typedef typename Operation::first_argument_type argument_type;
					typedef typename Operation::result_type result_type;
					
					binder2nd (const Operation& op,
						typename parameter <typename Operation::second_argument_type>::type bound):
						Operation (op), bound_ (bound)
						{
						}
						
					typename Operation::result_type operator()
						(typename parameter <typename Operation::first_argument_type>::type x) const
						{
							return (*this) (x, bound_); 
						}
						
					typename Operation::second_argument_type bound () const
						{
							return bound_;
						}
						
				private:
					const typename Operation::second_argument_type bound_;
					
					using Operation::operator();
			};
		
		template <typename Operation, typename Type> inline binder2nd <Operation> 
			bind2nd (const Operation& fn, const Type& x) 
			{
				typedef typename parameter <typename Operation::second_argument_type>::type second_argument_type;
				return binder2nd <Operation> (fn, second_argument_type (x));
			}
	
		template <typename Operation, typename Type> inline binder2nd <Operation> 
			bind2nd (const Operation& fn, Type& x) 
			{
				typedef typename parameter <typename Operation::second_argument_type>::type second_argument_type;
				return binder2nd <Operation> (fn, second_argument_type (x));
			}
	}
	
#endif
	


