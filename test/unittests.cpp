#include <iostream>
#include <macvalarray.h>
#include <extension/functional.h>
#include <math.h>

#ifdef __GNUC__
#define      isinf( x )         ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isinfd ( x ) :                                 \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isinff ( x ) :                                 \
                              __isinf  ( x ) )
#define      isnan( x )         ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isnand ( x ) :                                 \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isnanf ( x ) :                                 \
                              __isnan  ( x ) )
#define      signbit( x )       ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __signbitd ( x ) :                               \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __signbitf ( x ) :                               \
                              __signbitl  ( x ) )
#endif

static const double tolerance = 0.000001;
static const double double_tolerance = 0.00000000001;

template <typename Type> bool should_be (const Type& left, const Type& right)
	{
		return left == right;
	}

template <> bool should_be <float> (const float& left, const float& right)
	{
		if ((isnan (left) && isnan (right)) ||
			(signbit (left) == signbit (right) && isinf (left) && isinf (right)))
			return true;
		else
			{
				// Knuthean algorithm
				double diff = fabs (left - right);
				return diff <= tolerance * fabs (left) && diff <= tolerance * fabs (right);
			}
	}

template <> bool should_be <double> (const double& left, const double& right)
	{
		if ((isnan (left) && isnan (right)) ||
			(signbit (left) == signbit (right) && isinf (left) && isinf (right)))
			return true;
		else
			{
				// Knuthean algorithm
				double diff = fabs (left - right);
				return diff <= double_tolerance * fabs (left) && diff <= double_tolerance * fabs (right);
			}
	}

template <typename Type> Type filter_scalarization (const Type& x)
	{
		return x;
	}

template <> float filter_scalarization (const float& x)
	{
		return isnan (x) ? 0.0 : x;
	}

template <> double filter_scalarization (const double& x)
	{
		return isnan (x) ? 0.0 : x;
	}
	
void random_fill (void* area, size_t len)
	{
		// fill area with a random pattern, using chars for aliasing safety
		for (size_t i = 0; i != len; ++i)
			static_cast <char*> (area) [i] = random ();
	}

template <typename Type> struct square_root
	{
		Type operator() (Type x) { return sqrt (x); }
	};
	
template <typename Type, int size> void copy_construct_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		random_fill (a1, size * sizeof (Type));
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			if (!should_be (v1 [i], a1 [i]))
				{
					passed = false;
					std::cout << "\nfailed with " << v1 [i] << " != " << a1 [i] << ")";
				}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}
	

template <typename Type, int size> void assign_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		random_fill (a1, size * sizeof (Type));
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		std::valarray <Type> vr (size);
		vr = v1;
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			if (!should_be (vr [i], a1 [i]))
				{
					passed = false;
					std::cout << "\nfailed with " << vr [i] << " != " << a1 [i] << ")";
				}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}

template <typename Type, int size> void scalarization_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		random_fill (a1, size * sizeof (Type));
		for (int i = 0; i != size; ++i)
			a1 [i] = filter_scalarization (a1 [i]);
			
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		
		// find min, max, sum
		Type minx = a1 [0];
		Type maxx = a1 [0];
		Type sumx = a1 [0];
		for (int i = 1; i != size; ++i)
			{
				if (a1 [i] < minx)
					minx = a1 [i];
					
				if (maxx < a1 [i])
					maxx = a1 [i];
			
				sumx += a1 [i];
			}
		
		// compare each result valarray element to each array element
		bool passed = true;
		if (!should_be (minx, v1.min ()))
			{
				std::cout << "\nfailed min with " << minx << " != " << v1.min ();
				passed = false;
			}
		if (!should_be (maxx, v1.max ()))
			{
				std::cout << "\nfailed max with " << maxx << " != " << v1.max ();
				passed = false;
			}
		if (!should_be (sumx, v1.sum ()))
			{
				std::cout << "\nfailed sum with " << sumx << " != " << v1.sum () << " diff is " << sumx - v1.sum ();
				passed = false;
			}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}
	

template <template <typename> class Test, typename Type, int size> void unary_function_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		random_fill (a1, size * sizeof (Type));
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		
		// make result valarray from performing operation on each valarray
		std::valarray <Type> vr = Test <std::valarray <Type> > () (v1);
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			{
				Type result = Test <Type> () (a1 [i]);
				if (!should_be (vr [i], result))
					{
						passed = false;
						std::cout << "\nfailed with " << vr [i] << " != " << result << " == op (" << a1 [i] << ")";
					}
			}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}


template <template <typename> class Test, typename Type, int size> void binary_function_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		Type a2 [size];
		random_fill (a1, size * sizeof (Type));
		random_fill (a2, size * sizeof (Type));
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		std::valarray <Type> v2 (a2, size);
		
		// make result valarray from performing operation on each valarray
		std::valarray <Type> vr = Test <std::valarray <Type> > () (v1, v2);
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			{
				Type result = Test <Type> () (a1 [i], a2 [i]);
				if (!should_be (vr [i], result))
					{
						passed = false;
						std::cout << "\nfailed with " << vr [i] << " != " << result << " == op (" << a1 [i] << ", " << a2 [i] << ")";
					}
			}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}


template <template <typename> class Test, typename Type, int size> void shift_function_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		Type a2 [size];
		random_fill (a1, size * sizeof (Type));
		random_fill (a2, size * sizeof (Type));
		
		// ensure shift amount is within range
		for (int i = 0; i != size; ++i)
			a2 [i] %= sizeof (Type);
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		std::valarray <Type> v2 (a2, size);
		
		// make result valarray from performing operation on each valarray
		std::valarray <Type> vr = Test <std::valarray <Type> > () (v1, v2);
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			{
				Type result = Test <Type> () (a1 [i], a2 [i]);
				if (!should_be (vr [i], result))
					{
						passed = false;
						std::cout << "\nfailed with " << vr [i] << " != " << result << " == op (" << a1 [i] << ", " << a2 [i] << ")";
					}
			}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}

template <template <typename> class Test, typename Type, int size> void division_function_test (const char* title)
	{
		std::cout << "Testing " << title << ":";
		
		Type a1 [size];
		Type a2 [size];
		random_fill (a1, size * sizeof (Type));
		random_fill (a2, size * sizeof (Type));
		
		// ensure denominator is non-zero
		for (int i = 0; i != size; ++i)
			if (should_be (a2 [i], (Type) 0)) a2 [i] = 1;
		
		// copy each array into each valarray
		std::valarray <Type> v1 (a1, size);
		std::valarray <Type> v2 (a2, size);
		
		// make result valarray from performing operation on each valarray
		std::valarray <Type> vr = Test <std::valarray <Type> > () (v1, v2);
		
		// compare each result valarray element to each array element
		bool passed = true;
		for (int i = 0; i != size; ++i)
			{
				Type result = Test <Type> () (a1 [i], a2 [i]);
				if (!should_be (vr [i], result))
					{
						passed = false;
						std::cout << "\nfailed with " << vr [i] << " != " << result << " == op (" << a1 [i] << ", " << a2 [i] << ")";
					}
			}
		if (passed)
			std::cout << " passed\n";
		else
			std::cout << "\n";
	}

	
template <typename Type, int size> void integer_test_suite (const char* title)
	{
		std::cout << title << "\n---\n";
		copy_construct_test <Type, size> ("copy construction");
		assign_test <Type, size> ("assignment");
		scalarization_test <Type, size> ("scalarization");
		unary_function_test <stdext::identity, Type, size> ("identity");
		unary_function_test <std::negate, Type, size> ("negation");
		unary_function_test <stdext::bitwise_not, Type, size> ("bitwise not");
		binary_function_test <std::multiplies, Type, size> ("multiplication");
	//	binary_function_test <std::divides, Type, size> ("division");		// not defined yet
	//	binary_function_test <std::modulus, Type, size> ("modulus");		// not defined yet
		binary_function_test <std::plus, Type, size> ("addition");
		binary_function_test <std::minus, Type, size> ("subtraction");
		binary_function_test <stdext::bitwise_xor, Type, size> ("bitwise xor");
		binary_function_test <stdext::bitwise_and, Type, size> ("bitwise and");
		binary_function_test <stdext::bitwise_or, Type, size> ("bitwise or");
		shift_function_test <stdext::left_shift, Type, size> ("left shift");
		shift_function_test <stdext::right_shift, Type, size> ("right shift");
		std::cout << "\n";

	}


template <typename Type, int size> void floating_test_suite (const char* title)
	{
		std::cout << title << "\n---\n";
		copy_construct_test <Type, size> ("copy construction");
		assign_test <Type, size> ("assignment");
		scalarization_test <Type, size> ("scalarization");
		unary_function_test <stdext::identity, Type, size> ("identity");
		unary_function_test <std::negate, Type, size> ("negation");
		binary_function_test <std::multiplies, Type, size> ("multiplication");
		binary_function_test <std::divides, Type, size> ("division");
		binary_function_test <std::plus, Type, size> ("addition");
		binary_function_test <std::minus, Type, size> ("subtraction");
		unary_function_test <square_root, Type, size> ("square root");
		std::cout << "\n";
	}

		
void tests ()
	{
		std::cout << "UNIT TESTS\n===\n\n";
		
		integer_test_suite <long, 99> ("long");
		integer_test_suite <unsigned long, 99> ("unsigned long");
		integer_test_suite <short, 99> ("short");
		integer_test_suite <unsigned short, 99> ("unsigned short");
		integer_test_suite <char, 99> ("char");
		integer_test_suite <unsigned char, 99> ("unsigned char");
		
		vec_mtvscr ((vector unsigned char) (0));
		floating_test_suite <float, 99> ("float");
		floating_test_suite <double, 99> ("double (unoptimized)");
		
	}

