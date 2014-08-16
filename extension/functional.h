/*
 *  functional.h
 *  macstl
 *
 *  Created by Glen Low on Wed Nov 13 2002.
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

namespace stdext
	{
		template <typename Type> struct minimize: public std::binary_function <Type, Type, Type>
			{
				const Type& operator() (const Type& x, const Type& y) const
					{
						return y < x ? x : y;
					}
			};
			
		template <typename Type> struct maximize: public std::binary_function <Type, Type, Type>
			{
				const Type& operator() (const Type& x, const Type& y) const
					{
						return x < y ? x : y;
					}
			};
		
		template <typename Type> struct bitwise_not: public std::unary_function <Type, Type>
			{
				Type operator() (const Type& x) const	
					{
						return ~x;
					}
			};
			
		template <typename Type> struct bitwise_and: public std::binary_function <Type, Type, Type>
			{
				Type operator() (const Type& x, const Type& y) const
					{
						return x & y;
					}
			};
		
		template <typename Type> struct bitwise_or: public std::binary_function <Type, Type, Type>
			{
				Type operator() (const Type& x, const Type& y) const
					{
						return x | y;
					}
			};
			
		template <typename Type> struct bitwise_xor: public std::binary_function <Type, Type, Type>
			{
				Type operator() (const Type& x, const Type& y) const
					{
						return x ^ y;
					}
			};
		
		template <typename Type> struct left_shift: public std::binary_function <Type, Type, Type>
			{
				Type operator() (const Type& x, const Type& y) const
					{
						return x << y;
					}
			};
		
		template <typename Type> struct right_shift: public std::binary_function <Type, Type, Type>
			{
				Type operator() (const Type& x, const Type& y) const
					{
						return x >> y;
					}
			};
			
		template <typename Type> struct assign: public std::binary_function <Type&, Type, Type&>
			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x = y;
					}
			};

		template <typename Type> struct plus_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x += y;
					}
			};
			
		template <typename Type> struct minus_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x -= y;
					}
			};
			
		template <typename Type> struct multiplies_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x *= y;
					}
			};

		template <typename Type> struct divides_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x /= y;
					}
			};

		template <typename Type> struct modulus_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x %= y;
					}
			};

		template <typename Type> struct bitwise_and_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x &= y;
					}
			};

		template <typename Type> struct bitwise_or_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x |= y;
					}
			};

		template <typename Type> struct bitwise_xor_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x ^= y;
					}
			};

		template <typename Type> struct left_shift_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x <<= y;
					}
			};

		template <typename Type> struct right_shift_assign: public std::binary_function <Type&, Type, Type&>			{
				Type& operator () (Type& x, const Type& y) const
					{
						return x >>= y;
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
					typedef typename Operation::first_argument_type argument_type;
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
	
				protected:
					typename Operation::first_argument_type bound_;
					
				private:
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
					typedef typename Operation::second_argument_type argument_type;
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
						
				protected:
					typename Operation::second_argument_type bound_;
					
				private:
					using Operation::operator();
			};
		
		template <typename Operation, typename Type> inline binder2nd <Operation> 
			bind2nd (const Operation& fn, const Type& x) 
			{
				typedef typename parameter <typename Operation::second_argument_type>::type second_argument_type;
				return binder2nd<Operation> (fn, second_argument_type (x));
			}
	
		template <typename Operation, typename Type> inline binder2nd <Operation> 
			bind2nd (const Operation& fn, Type& x) 
			{
				typedef typename parameter <typename Operation::second_argument_type>::type second_argument_type;
				return binder2nd<Operation> (fn, second_argument_type (x));
			}
	};
	
	
	
	


