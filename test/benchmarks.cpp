#include <iostream>
#include <cmath>
#include <macvalarray.h>

#include <time.h>

const int size = 1000;

float f (float x)	{ return x + 1.0f; }

template <typename Fn> void benchmark (Fn fn, long long loops, const char* name)
	{
		// prime the caches first
		for (int i = 0; i != 10; ++i)
			fn ();
			
		clock_t start = clock ();
		for (long long i = 0; i != loops; ++i)
			fn ();
		clock_t finish = clock ();
		std::cout << "Benching " << name << " = " << loops / (finish - start) << " per tick.\n";
	}

class inline_arithmetic
	{
		public:
			inline_arithmetic ():
				v1 (std::valarray <float> (size)), v2 (std::valarray <float> (size)), vr (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ vr = v1 + v2; }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> v2;
			std::valarray <float> vr;
	
	};

class inline_transcendental
	{
		public:
			inline_transcendental ():
				v1 (std::valarray <float> (size)),
				vr (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ vr = sqrt (v1); }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> vr;
	
	};

class outline_transcendental
	{
		public:
			outline_transcendental ():
				v1 (std::valarray <float> (size)), v2 (std::valarray <float> (size)),
				vr (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ vr = pow (v1, v2); }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> v2;
			std::valarray <float> vr;
	
	};


class inline_scalarization
	{
		public:
			inline_scalarization ():
				v1 (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ r = v1.sum (); }
		
		private:
			std::valarray <float> v1;
			float r;
	
	};
	
class inline_predication
	{
		public:
			inline_predication ():
				v1 (std::valarray <float> (size)),
				v2 (std::valarray <float> (size))
				{
				}
				
		void operator() ()		{ r = (v1 == v2).min (); }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> v2;
			bool r;
	
	};

class unchunked_application
	{
		public:
			unchunked_application ():
				v1 (std::valarray <float> (size)),
				vr (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ vr = v1.apply (f); }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> vr;
	};

class unchunked_shift
	{
		public:
			unchunked_shift ():
				v1 (std::valarray <float> (size)),
				vr (std::valarray <float> (size))
				{
				}
				
			void operator() ()		{ vr = v1.cshift (100); }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> vr;
	};
	
class inline_slice
	{
		public:
			inline_slice ():
				v1 (std::valarray <float> (size)),
				vr (std::valarray <float> (size / 2)),
				slice (0, size / 2, 2)
				{
				}
				
			void operator() ()		{ vr = v1 [slice]; }
		
		private:
			std::valarray <float> v1;
			std::valarray <float> vr;
			std::slice slice;
	};
	
class unchunked_mask
	{
		public:
			unchunked_mask ():
				v1 (std::valarray <long> (size)),
				v2 (std::valarray <long> (size)),
				v3 (std::valarray <float> (size)),
				vr (std::valarray <float> (size / 2))
				{
					for (int i = 0; i != size; i += 2)
						v2 [i] = 1;
				}
				
			void operator() ()		{ vr = v3 [v1 == v2]; }
				
				
		private:
			std::valarray <long> v1;
			std::valarray <long> v2;
			std::valarray <float> v3;
			std::valarray <float> vr;
	
	};

class unchunked_indirect
	{
		public:
			unchunked_indirect ():
				v1 (std::valarray <size_t> (size)),
				v2 (std::valarray <size_t> (size)),
				v3 (std::valarray <float> (size)),
				vr (std::valarray <float> (size))
				{
					for (int i = 0; i != size / 2; ++i)
						v1 [i] = v2 [i] = i;
						
					for (int i = size / 2; i != size; ++i)
						{
							v1 [i] = 0;
							v2 [i] = i;
						}
				}
				
			void operator() ()		{ vr = v3 [v1 + v2]; }
				
				
		private:
			std::valarray <size_t> v1;
			std::valarray <size_t> v2;
			std::valarray <float> v3;
			std::valarray <float> vr;	
	};

void benchmarks ()
	{
		std::cout << "BENCHMARKS\n===\n\n";
		
		benchmark (inline_arithmetic (), 1000000, "inline arithmetic");
		benchmark (inline_transcendental (), 100000, "inline transcendental");
		benchmark (outline_transcendental (), 10000, "outline transcendental");
		benchmark (inline_scalarization (), 1000000, "inline scalarization");
		benchmark (inline_predication (), 100000, "inline predication");
		benchmark (inline_slice (), 1000000, "inline slice");
		benchmark (unchunked_application (), 100000, "unchunked application");
		benchmark (unchunked_shift (), 100000, "unchunked shift");
		benchmark (unchunked_mask (), 100000, "unchunked mask");
		benchmark (unchunked_indirect (), 100000, "unchunked indirect");
		
		std::cout << "\n";
	}
	

	
