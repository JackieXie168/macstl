/*
 *  vec_mmx.h
 *  macstl
 *
 *  Created by Glen Low on Oct 29 2004.
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

#ifndef MACSTL_IMPL_VEC_MMX_H
#define MACSTL_IMPL_VEC_MMX_H

#ifdef __MMX__
#include <mmintrin.h>
#endif

#ifdef __SSE__
#include <xmmintrin.h>
#endif

#ifdef __SSE2__
#include <emmintrin.h>
#endif

namespace macstl
	{
		namespace impl
			{
				#ifdef __MMX__
				
				template <> struct data_vec <__m64>		{ typedef vec <int, 2> type; };
				
				template <unsigned int v0, unsigned int v1> struct generator_m64
					{
						__m64 operator() () const
							{
								union union_type
									{
										unsigned int val [2];
										__m64 vec;
									};
									
								static const union_type un = {v0, v1};
								return un.vec;
							}
					};

				template <> struct generator_m64 <0, 0>
					{
						__m64 operator() () const
							{
								return _mm_setzero_si64 ();
							}
					};
					
				#endif

				#ifdef __SSE__

				template <> struct data_vec <__m128>	{ typedef vec <float, 4> type; };
				
				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128
					{
						__m128 operator() () const
							{
								union union_type
									{
										unsigned int val [4];
										__m128 vec;
									};
									
								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};
					
				template <> struct generator_m128 <0, 0, 0, 0>
					{
						__m128 operator() () const
							{
								return _mm_setzero_ps ();
							}
					};
					
				#endif
				
				#ifdef __SSE2__

				template <> struct data_vec <__m128d>	{ typedef vec <double, 2> type; };
				template <> struct data_vec <__m128i>	{ typedef vec <int, 4> type; };

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128d
					{
						__m128d operator() () const
							{
								union union_type
									{
										unsigned int val [4];
										__m128d vec;
									};
									
								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};

				template <> struct generator_m128d <0, 0, 0, 0>
					{
						__m128d operator() () const
							{
								return _mm_setzero_pd ();
							}
					};

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128i
					{
						__m128i operator() () const
							{
								union union_type
									{
										unsigned int val [4];
										__m128i vec;
									};
									
								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};

				template <> struct generator_m128i <0, 0, 0, 0>
					{
						__m128i operator() () const
							{
								return _mm_setzero_si128 ();
							}
					};

				
				#endif
				
			}
			
		#ifndef DOXYGEN
		
		#ifdef __MMX__
		
		template <> class vec <unsigned char, 8>: public impl::vec_base <__m64, unsigned char, boolean <char> >
			{
				public:
					typedef unsigned char value_type;
					typedef unsigned char init_type;
					
					union union_type
						{
							unsigned char val [8];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <unsigned char, 8> set ()
						{
							return impl::generator_m64 <
								(v3 << 24) | (v2 << 16) | (v1 << 8) | v0,
								(v7 << 24) | (v6 << 16) | (v5 << 8) | v4> () ();
						}
					
					template <init_type v0>
						static vec <unsigned char, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, unsigned char, boolean <char> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <signed char, 8>: public impl::vec_base <__m64, signed char, boolean <char> >
			{
				public:
					typedef signed char value_type;
					typedef signed char init_type;
					
					union union_type
						{
							signed char val [8];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <signed char, 8> set ()
						{
							return impl::generator_m64 <
								(((unsigned char) v3) << 24) | (((unsigned char) v2) << 16) | (((unsigned char) v1) << 8) | ((unsigned char) v0),
								(((unsigned char) v7) << 24) | (((unsigned char) v6) << 16) | (((unsigned char) v5) << 8) | ((unsigned char) v4)> () ();
						}
					
					template <init_type v0>
						static vec <signed char, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, signed char, boolean <char> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <boolean <char>, 8>: public impl::vec_base <__m64, boolean <char>, boolean <char> >
			{
				public:
					typedef boolean <char> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned char val [8];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <boolean <char>, 8> set ()
						{
							return impl::generator_m64 <
								(v3 ? 0xFF000000U : 0) | (v2 ? 0x00FF0000U : 0) | (v1 ? 0x0000FF00U : 0) | (v0 ? 0x000000FFU : 0),
								(v7 ? 0xFF000000U : 0) | (v6 ? 0x00FF0000U : 0) | (v5 ? 0x0000FF00U : 0) | (v4 ? 0x000000FFU : 0)> () ();
						}
					
					template <init_type v0>
						static vec <boolean <char>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, boolean <char>, boolean <char> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <unsigned short, 4>: public impl::vec_base <__m64, unsigned short, boolean <short> >
			{
				public:
					typedef unsigned short value_type;
					typedef unsigned short init_type;
					
					union union_type
						{
							unsigned short val [4];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (v0, v1, v2, v3);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <unsigned short, 4> set ()
						{
							return impl::generator_m64 <
								(v1 << 16) | v0, (v3 << 16) | v2> () ();
						}
					
					template <init_type v0>
						static vec <unsigned short, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, unsigned short, boolean <short> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <short, 4>: public impl::vec_base <__m64, short, boolean <short> >
			{
				public:
					typedef short value_type;
					typedef short init_type;
					
					union union_type
						{
							short val [4];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (v0, v1, v2, v3);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <short, 4> set ()
						{
							return impl::generator_m64 <
								(((unsigned short) v1) << 16) | ((unsigned short) v0), (((unsigned short) v3) << 16) | ((unsigned short) v2)> () ();
						}
					
					template <init_type v0>
						static vec <short, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, short, boolean <short> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <boolean <short>, 4>: public impl::vec_base <__m64, boolean <short>, boolean <short> >
			{
				public:
					typedef boolean <short> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned short val [4];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <boolean <short>, 4> set ()
						{
							return impl::generator_m64 <
								(v1 ? 0xFFFF0000U : 0) | (v0 ? 0x0000FFFFU : 0), (v3 ? 0xFFFF0000U : 0) | (v2 ? 0x0000FFFFU : 0)> () ();
						}
					
					template <init_type v0>
						static vec <boolean <short>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, boolean <short>, boolean <short> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <unsigned int, 2>: public impl::vec_base <__m64, unsigned int, boolean <int> >
			{
				public:
					typedef unsigned int value_type;
					typedef unsigned int init_type;
					
					union union_type
						{
							unsigned int val [2];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (v0, v1);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <unsigned int, 2> set ()
						{
							return impl::generator_m64 <v0, v1> () ();
						}
					
					template <init_type v0>
						static vec <unsigned int, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, unsigned int, boolean <int> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <int, 2>: public impl::vec_base <__m64, int, boolean <int> >
			{
				public:
					typedef int value_type;
					typedef int init_type;
					
					union union_type
						{
							int val [2];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (v0, v1);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <int, 2> set ()
						{
							return impl::generator_m64 <(int) v0, (int) v1> () ();
						}
					
					template <init_type v0>
						static vec <int, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, int, boolean <int> >;
					
				private:
					__m64 data_;
			};

		template <> class vec <boolean <int>, 2>: public impl::vec_base <__m64, boolean <int>, boolean <int> >
			{
				public:
					typedef boolean <int> value_type;
					typedef bool init_type;
					
					union union_type
						{
							int val [2];
							__m64 vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (
								v0.data (), v1.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1>
						static vec <boolean <int>, 2> set ()
						{
							return impl::generator_m64 <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0> () ();
						}
					
					template <init_type v0>
						static vec <boolean <int>, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m64 <0, 0> () ())
						{
						}
						
					vec (__m64 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m64, boolean <int>, boolean <int> >;
					
				private:
					__m64 data_;
			};
									
		#endif

		#ifdef __SSE__

		template <> class vec <float, 4>: public impl::vec_base <__m128, float, boolean <float> >
			{
				public:
					typedef float value_type;
					typedef unsigned int init_type;
					
					union union_type
						{
							float val [4];
							__m128 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_ps (v0, v1, v2, v3);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_ps (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <float, 4> set ()
						{
							return impl::generator_m128 <v0, v1, v2, v3> () ();
						}
					
					template <init_type v0>
						static vec <float, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128 <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128 data): data_ (data)	{ }
					
					friend class impl::vec_base <__m128, float, boolean <float> >;
					
				private:
					__m128 data_;
			};

		template <> class vec <boolean <float>, 4>: public impl::vec_base <__m128, boolean <float>, boolean <float> >
			{
				public:
					typedef boolean <float> value_type;
					typedef bool init_type;
					
					union union_type
						{
							float val [4];
							__m128 vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_ps (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_ps (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <boolean <float>, 4> set ()
						{
							return impl::generator_m128 <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0> () ();
						}
					
					template <init_type v0>
						static vec <boolean <float>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128 <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128 data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128, boolean <float>, boolean <float> >;
					
				private:
					__m128 data_;
			};
		
		#endif
		
		#ifdef __SSE2__
		
		template <> class vec <double, 2>: public impl::vec_base <__m128d, double, boolean <double> >
			{
				public:
					typedef double value_type;
					typedef unsigned long long init_type;
					
					union union_type
						{
							double val [2];
							__m128d vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pd (v0, v1);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pd (v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <double, 2> set ()
						{
							return impl::generator_m128d <
								v0 & 0x00000000FFFFFFFFULL, (v0 & 0xFFFFFFFF00000000ULL) >> 32, 
								v1 & 0x00000000FFFFFFFFULL, (v1 & 0xFFFFFFFF00000000ULL) >> 32> () ();
						}
					
					template <init_type v0>
						static vec <double, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128d <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128d data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128d, double, boolean <double> >;
					
				private:
					__m128d data_;
			};

		template <> class vec <boolean <double>, 2>: public impl::vec_base <__m128d, boolean <double>, boolean <double> >
			{
				public:
					typedef boolean <double> value_type;
					typedef bool init_type;
					
					union union_type
						{
							double val [2];
							__m128d vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pd (
								v0.data (), v1.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_pd (v0.data ());
						}
						
					template <
						init_type v0, init_type v1>
						static vec <boolean <double>, 2> set ()
						{
							return impl::generator_m128d <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U> () ();
						}
					
					template <init_type v0>
						static vec <boolean <double>, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128d <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128d data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128d, boolean <double>, boolean <double> >;
					
				private:
					__m128d data_;
			};

		template <> class vec <unsigned char, 16>: public impl::vec_base <__m128i, unsigned char, boolean <char> >
			{
				public:
					typedef unsigned char value_type;
					typedef unsigned char init_type;
					
					union union_type
						{
							unsigned char val [16];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (v0, v1, v2, v3, v4, v5, v6, v7,
								v8, v9, v10, v11, v12, v13, v14, v15);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec <unsigned char, 16> set ()
						{
							return impl::generator_m128i <
								(v3 << 24) | (v2 << 16) | (v1 << 8) | v0,
								(v7 << 24) | (v6 << 16) | (v5 << 8) | v4,
								(v11 << 24) | (v10 << 16) | (v9 << 8) | v8,
								(v15 << 24) | (v14 << 16) | (v13 << 8) | v12> () ();
						}
					
					template <init_type v0>
						static vec <unsigned char, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, unsigned char, boolean <char> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <signed char, 16>: public impl::vec_base <__m128i, signed char, boolean <char> >
			{
				public:
					typedef signed char value_type;
					typedef signed char init_type;
					
					union union_type
						{
							signed char val [16];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec <signed char, 16> set ()
						{
							return impl::generator_m128i <
								(((unsigned char) v3) << 24) | (((unsigned char) v2) << 16) | (((unsigned char) v1) << 8) | ((unsigned char) v0),
								(((unsigned char) v7) << 24) | (((unsigned char) v6) << 16) | (((unsigned char) v5) << 8) | ((unsigned char) v4),
								(((unsigned char) v11) << 24) | (((unsigned char) v10) << 16) | (((unsigned char) v9) << 8) | ((unsigned char) v8),
								(((unsigned char) v15) << 24) | (((unsigned char) v14)<< 16) | (((unsigned char) v13) << 8) | ((unsigned char) v12)> () ();
						}
					
					template <init_type v0>
						static vec <signed char, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, signed char, boolean <char> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <boolean <char>, 16>: public impl::vec_base <__m128i, boolean <char>, boolean <char> >
			{
				public:
					typedef boolean <char> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned char val [16];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data (),
								v8.data (), v9.data (), v10.data (), v11.data (),
								v12.data (), v13.data (), v14.data (), v15.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec <boolean <char>, 16> set ()
						{
							return impl::generator_m128i <
								(v3 ? 0xFF000000U : 0) | (v2 ? 0x00FF0000U : 0) | (v1 ? 0x0000FF00U : 0) | (v0 ? 0x000000FFU : 0),
								(v7 ? 0xFF000000U : 0) | (v6 ? 0x00FF0000U : 0) | (v5 ? 0x0000FF00U : 0) | (v4 ? 0x000000FFU : 0),
								(v11 ? 0xFF000000U : 0) | (v10 ? 0x00FF0000U : 0) | (v9 ? 0x0000FF00U : 0) | (v8 ? 0x000000FFU : 0),
								(v15 ? 0xFF000000U : 0) | (v14 ? 0x00FF0000U : 0) | (v13 ? 0x0000FF00U : 0) | (v12 ? 0x000000FFU : 0)> () ();
						}
					
					template <init_type v0>
						static vec <boolean <char>, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, boolean <char>, boolean <char> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <unsigned short, 8>: public impl::vec_base <__m128i, unsigned short, boolean <short> >
			{
				public:
					typedef unsigned short value_type;
					typedef unsigned short init_type;
					
					union union_type
						{
							unsigned short val [8];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <unsigned short, 8> set ()
						{
							return impl::generator_m128i <
								(v1 << 16) | v0, (v3 << 16) | v2,
								(v5 << 16) | v4, (v7 << 16) | v6> () ();
						}
					
					template <init_type v0>
						static vec <unsigned short, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, unsigned short, boolean <short> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <short, 8>: public impl::vec_base <__m128i, short, boolean <short> >
			{
				public:
					typedef short value_type;
					typedef short init_type;
					
					union union_type
						{
							short val [8];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <short, 8> set ()
						{
							return impl::generator_m128i <
								(((unsigned short) v1) << 16) | ((unsigned short) v0), (((unsigned short) v3) << 16) | ((unsigned short) v2),
								(((unsigned short) v5) << 16) | ((unsigned short) v4), (((unsigned short) v7) << 16) | ((unsigned short) v6)> () ();
						}
					
					template <init_type v0>
						static vec <short, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, short, boolean <short> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <boolean <short>, 8>: public impl::vec_base <__m128i, boolean <short>, boolean <short> >
			{
				public:
					typedef boolean <short> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned short val [8];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec <boolean <short>, 8> set ()
						{
							return impl::generator_m128i <
								(v1 ? 0xFFFF0000U : 0) | (v0 ? 0x0000FFFFU : 0), (v3 ? 0xFFFF0000U : 0) | (v2 ? 0x0000FFFFU : 0),
								(v5 ? 0xFFFF0000U : 0) | (v4 ? 0x0000FFFFU : 0), (v7 ? 0xFFFF0000U : 0) | (v6 ? 0x0000FFFFU : 0)> () ();
						}
					
					template <init_type v0>
						static vec <boolean <short>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, boolean <short>, boolean <short> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <unsigned int, 4>: public impl::vec_base <__m128i, unsigned int, boolean <int> >
			{
				public:
					typedef unsigned int value_type;
					typedef unsigned int init_type;
					
					union union_type
						{
							unsigned int val [4];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (v0, v1, v2, v3);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <unsigned int, 4> set ()
						{
							return impl::generator_m128i <v0, v1, v2, v3> () ();
						}
					
					template <init_type v0>
						static vec <unsigned int, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, unsigned int, boolean <int> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <int, 4>: public impl::vec_base <__m128i, int, boolean <int> >
			{
				public:
					typedef int value_type;
					typedef int init_type;
					
					union union_type
						{
							int val [4];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (v0, v1, v2, v3);
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <int, 4> set ()
						{
							return impl::generator_m128i <(int) v0, (int) v1, (int) v2, (int) v3> () ();
						}
					
					template <init_type v0>
						static vec <int, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, int, boolean <int> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <boolean <int>, 4>: public impl::vec_base <__m128i, boolean <int>, boolean <int> >
			{
				public:
					typedef boolean <int> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned int val [4];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0.data ());
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec <boolean <int>, 4> set ()
						{
							return impl::generator_m128i <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0> () ();
						}
					
					template <init_type v0>
						static vec <boolean <int>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, boolean <int>, boolean <int> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <unsigned long long, 2>: public impl::vec_base <__m128i, unsigned long long, boolean <long long> >
			{
				public:
					typedef unsigned long long value_type;
					typedef unsigned long long init_type;
					
					union union_type
						{
							unsigned long long val [2];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0, v1};
							return un.vec;
						}

					static vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <unsigned long long, 2> set ()
						{
							return impl::generator_m128i <
								v0 & 0x00000000FFFFFFFFULL, (v0 & 0xFFFFFFFF00000000ULL) >> 32,
								v1 & 0x00000000FFFFFFFFULL, (v1 & 0xFFFFFFFF00000000ULL) >> 32> () ();
						}
					
					template <init_type v0>
						static vec <unsigned long long, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, unsigned long long, boolean <long long> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <long long, 2>: public impl::vec_base <__m128i, long long, boolean <long long> >
			{
				public:
					typedef long long value_type;
					typedef long long init_type;
					
					union union_type
						{
							long long val [2];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0, v1};
							return un.vec;
						}

					static vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <long long, 2> set ()
						{
							return impl::generator_m128i <
								((unsigned long long) v0) & 0x00000000FFFFFFFFULL, (((unsigned long long) v0) & 0xFFFFFFFF00000000ULL) >> 32,
								((unsigned long long) v1) & 0x00000000FFFFFFFFULL, (((unsigned long long) v1) & 0xFFFFFFFF00000000ULL) >> 32> () ();
						}
					
					template <init_type v0>
						static vec <long long, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, long long, boolean <long long> >;
					
				private:
					__m128i data_;
			};

		template <> class vec <boolean <long long>, 2>: public impl::vec_base <__m128i, boolean <long long>, boolean <long long> >
			{
				public:
					typedef boolean <long long> value_type;
					typedef bool init_type;
					
					union union_type
						{
							unsigned long long val [2];
							__m128i vec;
						};
					
					static vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0.data (), v1.data ()};
							return un.vec;
						}

					static vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}
						
					template <
						init_type v0, init_type v1>
						static vec <boolean <long long>, 2> set ()
						{
							return impl::generator_m128i <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U> () ();
						}
					
					template <init_type v0>
						static vec <boolean <long long>, 2> fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (impl::generator_m128i <0, 0, 0, 0> () ())
						{
						}
						
					vec (__m128i data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__m128i, boolean <long long>, boolean <long long> >;
					
				private:
					__m128i data_;
			};
		
		#endif
		
		#endif
		
#define DEFINE_MMX_UNARY_CONVERSION(FN,INTR,ARG,RESULT)								\
template <> struct FN##_function <RESULT, ARG >										\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data ());											\
			}																		\
	};

#define DEFINE_MMX_UNARY_SHUFFLE4(FN,INTR,ARG,RESULT)								\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l> struct FN##_function <i, j, k, l, ARG >										\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data (), (i << 6) | (j << 4) | (k << 2) | l);		\
			}																		\
	};

#define DEFINE_MMX_BINARY_SHUFFLE4(FN,INTR,ARG1,ARG2,RESULT)								\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l> struct FN##_function <i, j, k, l, ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;													\
		typedef ARG2 second_argument_type;													\
		typedef RESULT result_type;													\
																					\
		result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data (), (i << 6) | (j << 4) | (k << 2) | l);		\
			}																		\
	};

#define DEFINE_MMX_BINARY_SHUFFLE2(FN,INTR,ARG1,ARG2,RESULT)								\
template <unsigned int i, unsigned int j> struct FN##_function <i, j, ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;													\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data (), (i << 1) | j);		\
			}																		\
	};


#define DEFINE_MMX_UNARY_FUNCTION(FN,INTR,ARG,RESULT)								\
template <> struct FN##_function <ARG >												\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data ());											\
			}																		\
	};

#define DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL(FN,INTR,ARG,RESULT)					\
template <unsigned int i> struct FN##_function <i, ARG >								\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data (), i);										\
			}																		\
	};

#define DEFINE_MMX_BINARY_CONVERSION(FN,INTR,ARG1,ARG2,RESULT)						\
template <> struct FN##_function <ARG1, ARG2, RESULT >								\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data ());								\
			}																		\
	};

#define DEFINE_MMX_BINARY_FUNCTION(FN,INTR,ARG1,ARG2,RESULT)						\
template <> struct FN##_function <ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data ());								\
			}																		\
	};
	
#define DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL(FN,INTR,ARG1,ARG2,RESULT)			\
template <unsigned int i> struct FN##_function <i, ARG1, ARG2 >						\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data (), i);							\
			}																		\
	};

		/// MMX/SSE/SSE2/SSE3 intrinsics.
		
		/// Sequesters the MMX/SSE/SSE2/SSE3 intrinsics from similarly named common or platform SIMD functions.
		/// Each MMX intrinsic of the form _mm_xxx_yyy is wrapped in a function xxx as well as a functor xxx_function.
		/// Any literal parameters are expressed as template non-type parameters, e.g. slli <0> (x) wraps _mm_slli_yyy (x, 0).
		///
		/// @note	You can use either the raw vector type or macstl::vec for any of the type parameters, except that the raw
		///			types convert to the object type with a 32-bit element size e.g. __m128i converts to macstl::vec <unsigned int, 4>.
	
		namespace mmx
			{
				/// @name Arithmetic
				
				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (add,add) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (adds,add saturated) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (addsub,add odd and subtract even) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (avg,rounded average) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (div,divide) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (hadd,add adjacent) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (hsub,subtract adjacent) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (madd,multiply and add adjacent) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (max,maximum) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (min,minimum) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mul,multiply) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mulhi,multiply high) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mullo,multiply low)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (rcp,reciprocal) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (rsqrt,reciprocal square root) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sad,sum of absolute differences) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sqrt,square root) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sub,subtract) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (subs,subtract saturated) 
				//@}
				
				/// @name Logic
				
				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vand,bitwise AND) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (andnot,bitwise AND-NOT) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vor,bitwise OR) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vxor,bitwise XOR) 
				//@}
	
				/// @name Shifters
				
				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sll,shift left logical) 
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (slli,shift left logical immediate) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sra,shift right algebraic) 
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (srai, shift right algebraic immediate) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (srl,shift right logical) 
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (srli,shift right logical immediate) 
				//@}

				/// @name Conversions
				
				//@{
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_RETURN_TYPE (cvt,convert)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_RETURN_TYPE (cvtt,convert truncate)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_RETURN_TYPE (cvt2,convert)
				//@}
			
				/// @name Compares
				
				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpeq,compare equal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpge,compare greater-than-orequal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpgt,compare greater-than) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmple,compare less-than-or-equal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmplt,compare less-than) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpneq,compare not equal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnge,compare not greater-than-or-equal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpngt,compare not greater-than) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnle,compare not less-than-or-equal-to) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnlt,compare not less-than) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpord,compare ordered) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpunord,compare unordered)
				//@}
				
				/// @name Miscellaneous
				
				//@{				
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (extract,extract element)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL (insert,insert element)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movedup,duplicate low to high) 
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movehdup,duplicate odd to even) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (movehl,move high to low)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (moveldup,duplicate even to odd) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (movelh,move low to high) 
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movemask,mask creation) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (packs,pack signed saturated) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (packus,pack unsigned saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL4 (shuffles,shuffle 4 float)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL2 (shuffled,shuffle 2 double)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shuffle,shuffle 4)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shufflehi,shuffle 4 high)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shufflelo,shuffle 4 low)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (unpackhi,unpack high) 
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (unpacklo,unpack low) 				
				//@}
				
				#define M64_U8 vec <unsigned char, 8>
				#define M64_I8 vec <signed char, 8>
				#define M64_B8 vec <boolean <char>, 8>
				#define M64_U16 vec <unsigned short, 4>
				#define M64_I16 vec <short, 4>
				#define M64_B16 vec <boolean <short>, 4>
				#define M64_U32 vec <unsigned int, 2>
				#define M64_I32 vec <int, 2>
				#define M64_B32 vec <boolean <int>, 2>
				#define M128_F32 vec <float, 4>
				#define M128_B32 vec <boolean <float>, 4>
				#define M128D_F64 vec <double, 2>
				#define M128D_B64 vec <boolean <double>, 2>
				#define M128I_U8 vec <unsigned char, 16>
				#define M128I_I8 vec <signed char, 16>
				#define M128I_B8 vec <boolean <char>, 16>
				#define M128I_U16 vec <unsigned short, 8>
				#define M128I_I16 vec <short, 8>
				#define M128I_B16 vec <boolean <short>, 8>
				#define M128I_U32 vec <unsigned int, 4>
				#define M128I_I32 vec <int, 4>
				#define M128I_B32 vec <boolean <int>, 4>
				#define M128I_U64 vec <unsigned long long, 2>
				#define M128I_I64 vec <long long, 2>
				#define M128I_B64 vec <boolean <long long>, 2>

				// MMX General Support Intrinsics

				#ifdef __MMX__
				
				inline void empty ()	{ _mm_empty (); }
				
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pi16, M64_I16, M64_I16, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pi32, M64_I32, M64_I32, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pu16, M64_U16, M64_U16, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_B32, M64_B32, M64_B32)

				// MMX Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_pi16, M64_I16, M64_I16, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_pi16, M64_U16, M64_U16, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_pi16, M64_I16, M64_I16, M64_I16)

				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_pi16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pu16, M64_U16, M64_U16, M64_U16)

				// MMX Shift Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi16, M64_B16, M64_U16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi32, M64_I32, M64_U32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi32, M64_B32, M64_U32, M64_B32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi16, M64_U16, M64_U16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi16, M64_B16, M64_B16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi32, M64_I32, M64_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi32, M64_U32, M64_U32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_pi32, M64_I32, M64_U32, M64_I32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_pi32, M64_I32, M64_I32)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi16, M64_B16, M64_U16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi32, M64_I32, M64_U32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi32, M64_B32, M64_U32, M64_B32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi16, M64_U16, M64_U16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi16, M64_B16, M64_B16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi32, M64_I32, M64_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi32, M64_U32, M64_U32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi32, M64_B32, M64_B32)

				// MMX Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_B32, M64_B32)

				// MMX Compare Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_I8, M64_I8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_U8, M64_U8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_I16, M64_I16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_U16, M64_U16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_I32, M64_I32, M64_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_U32, M64_U32, M64_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi8, M64_I8, M64_I8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi16, M64_I16, M64_I16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi32, M64_I32, M64_I32, M64_B32)

				#endif
				
				#ifdef __SSE__
				
				// SSE Floating-Point Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (div, _mm_div_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_UNARY_FUNCTION (rcp, _mm_rcp_ps, M128_F32, M128_F32)

				DEFINE_MMX_UNARY_FUNCTION (rsqrt, _mm_rsqrt_ps, M128_F32, M128_F32)

				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm_sqrt_ps, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_ps, M128_F32, M128_F32, M128_F32)

				// SSE Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_B32, M128_B32, M128_B32)

				// SSE Comparison Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmple, _mm_cmple_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpge, _mm_cmpge_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpneq, _mm_cmpneq_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpnlt, _mm_cmpnlt_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpnle, _mm_cmpnle_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpngt, _mm_cmpngt_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpnge, _mm_cmpnge_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpord, _mm_cmpord_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpunord, _mm_cmpunord_ps, M128_F32, M128_F32, M128_B32)
				
				// SSE Conversion Operations
				
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi32, M128_F32, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttps_pi32, M128_F32, M64_I32)
				DEFINE_MMX_BINARY_CONVERSION (cvt2, _mm_cvtpi32_ps, M128_F32, M64_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi16_ps, M64_I16, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpu16_ps, M64_U16, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi8_ps, M64_I8, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpu8_ps, M64_U8, M128_F32)
				DEFINE_MMX_BINARY_CONVERSION (cvt2, _mm_cvtpi32x2_ps, M64_I32, M64_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi16, M128_F32, M64_I16)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi8, M128_F32, M64_I8)
	
				// SSE Miscellaneous Intrinsics
				
				DEFINE_MMX_BINARY_FUNCTION (movehl, _mm_movehl_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (movehl, _mm_movehl_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (movelh, _mm_movelh_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (movelh, _mm_movelh_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_ps, M128_F32, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_ps, M128_B32, unsigned int)

				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm_shuffle_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm_shuffle_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_ps, M128_B32, M128_B32, M128_B32)

				// SSE Integer Intrinsics

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_I16, short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_U16, unsigned short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_B16, boolean <short>)
				
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_I16, short, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_U16, unsigned short, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_B16, boolean <short>, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pu8, M64_U8, M64_U8, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pu8, M64_U8, M64_U8, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_I8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_U8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_B8, unsigned int)

				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sad, _mm_sad_pu8, M64_U8, M64_U8, M64_U16)

				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_U16, M64_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_B16, M64_B16)
				
				#endif
				
				#ifdef __SSE2__
				
				// SSE2 Floating-Point Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (div, _mm_div_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm_sqrt_pd, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pd, M128D_F64, M128D_F64, M128D_F64)

				// SSE2 Floating-Point Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_B64, M128D_B64, M128D_B64)

				// SSE2 Floating-Point Comparison Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmple, _mm_cmple_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpge, _mm_cmpge_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpneq, _mm_cmpneq_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpnlt, _mm_cmpnlt_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpnle, _mm_cmpnle_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpngt, _mm_cmpngt_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpnge, _mm_cmpnge_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpord, _mm_cmpord_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpunord, _mm_cmpunord_pd, M128D_F64, M128D_F64, M128D_B64)

				// SSE2 Floating-Point Conversion

				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_ps, M128D_F64, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pd, M128_F32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtepi32_pd, M128I_I32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_epi32, M128D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttpd_epi32, M128D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvtepi32_pd, M128I_I32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtepi32_ps, M128I_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_epi32, M128_F32, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttps_epi32, M128_F32, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_pi32, M128D_F64, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttpd_pi32, M128D_F64, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi32_pd, M64_I32, M128D_F64)

				// SSE2 Floating-Point Miscellaneous Operations

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pd, M128D_F64, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pd, M128D_B64, unsigned int)
				
				DEFINE_MMX_BINARY_SHUFFLE2 (shuffled, _mm_shuffle_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_SHUFFLE2 (shuffled, _mm_shuffle_pd, M128D_B64, M128D_B64, M128D_B64)

				// SSE2 Integer Arithmetic

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi64, M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_epi16, M128I_I16, M128I_I16, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_epi16, M128I_U16, M128I_U16, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_epu8, M128I_U8, M128I_U8, M128I_U8)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_epu8, M128I_U8, M128I_U8, M128I_U8)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_epi16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_epu32, M128I_I32, M128I_I32, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_epu32, M128I_U32, M128I_U32, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (sad, _mm_sad_epu8, M128I_U8, M128I_U8, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi64, M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epu16, M128I_U16, M128I_U16, M128I_U16)

				// SSE2 Integer Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_B64, M128I_B64)

				// SSE2 Integer Compare Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_U8, M128I_U8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_U16, M128I_U16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_I32, M128I_I32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_U32, M128I_U32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi32, M128I_I32, M128I_I32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi32, M128I_I32, M128I_I32, M128I_B32)

				// SSE2 Integer Miscellaneous Operations

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_I16, short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_U16, unsigned short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_B16, boolean <short>)
				
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_I16, short, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_U16, unsigned short, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_B16, boolean <short>, M128I_B16)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_I8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_U8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_B8, unsigned int)

				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_epi16, M128I_I16, M128I_I16, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_epi32, M128I_I32, M128I_I32, M128I_I16)

				DEFINE_MMX_BINARY_FUNCTION (packus, _mm_packus_epi16, M128I_I16, M128I_I16, M128I_U8)

				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_I32, M128I_I32)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_U32, M128I_U32)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_B32, M128I_B32)

				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_U16, M128I_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_B16, M128I_B16)

				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_U16, M128I_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_B64, M128I_B64, M128I_B64)
				
				#endif
				
				#ifdef __SSE3__
				
				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm_addsub_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm_hadd_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm_hsub_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (movehdup, _mm_movehdup_ps, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (moveldup, _mm_moveldup_ps, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm_addsub_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm_hadd_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm_hsub_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_UNARY_FUNCTION (movedup, _mm_movedup_pd, M128D_F64, M128D_F64)
				
				#endif
				
				/// MMX/SSE/SSE2/SSE3 intrinsics implementation.
				namespace impl
					{
						// sin (x) -- where x is in [-Pi/2, Pi/2]
						inline vec <float, 4> sine_reduced (const vec <float, 4>& x)
							{
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <float, 4> xx = mmx::mul (x, x);
								return
									mmx::mul (
										mmx::add (mmx::mul (
											mmx::add (mmx::mul (
												mmx::add (mmx::mul (
													mmx::add (mmx::mul (
														xx, vec <float, 4>::fill <0x362E9C5BU> ()),	// 2.60190306765133772461701600763e-6 x^9
														vec <float, 4>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx), vec <float, 4>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx), vec <float, 4>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx), vec <float, 4>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x);
							}
					}
			}
	}
	
namespace std
	{
		// negate
		
		template <typename T, std::size_t n> struct negate <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef macstl::vec <T, n> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return mmx::sub (argument_type::template fill <0> (), lhs);
					}
			};

		template <typename T, std::size_t n> struct negate <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						return lhs;
					}
			};

		// logical_not
		
		template <typename T, std::size_t n> struct logical_not <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return lhs == argument_type::template fill <0> ();
					}
			};

		template <typename T, std::size_t n> struct logical_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, argument_type::template fill <true> ());
					}
			};
			
		// multiplies

		template <typename T, std::size_t n> struct multiplies <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vand (lhs, rhs);
					}
			};

		#ifdef __MMX__
		
		template <> struct multiplies <macstl::vec <unsigned short, 4> >:
			public macstl::mmx::mullo_function <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >
			{
			};

		template <> struct multiplies <macstl::vec <short, 4> >:
			public macstl::mmx::mullo_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};
			
		#endif

		#ifdef __SSE__
		
		template <> struct multiplies <macstl::vec <float, 4> >:
			public macstl::mmx::mul_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		#endif
		
		#ifdef __SSE2__
		
		template <> struct multiplies <macstl::vec <double, 2> >:
			public macstl::mmx::mul_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct multiplies <macstl::vec <unsigned short, 8> >:
			public macstl::mmx::mullo_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};

		template <> struct multiplies <macstl::vec <short, 8> >:
			public macstl::mmx::mullo_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		#endif

		// divides

		#ifdef __SSE__
		
		template <> struct divides <macstl::vec <float, 4> >:
			public macstl::mmx::div_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
		
		#endif

		#ifdef __SSE2__
		
		template <> struct divides <macstl::vec <double, 2> >:
			public macstl::mmx::div_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};
		
		#endif
		
		// plus
		
		template <typename T, std::size_t n> struct plus <macstl::vec <T, n> >:
			public macstl::mmx::add_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};
	
		template <typename T, std::size_t n> struct plus <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vor (lhs, rhs);
					}
			};	

		// minus
		
		template <typename T, std::size_t n> struct minus <macstl::vec <T, n> >:
			public macstl::mmx::sub_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};
	
		template <typename T, std::size_t n> struct minus <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (lhs, rhs);
					}
			};
			
		// equal_to

		template <typename T, std::size_t n> struct equal_to <macstl::vec <T, n> >:
			public macstl::mmx::cmpeq_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

#ifdef __SSE__
		template <> struct equal_to <macstl::vec <macstl::boolean <float>, 4> >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::template fill <true> ());
					}
			};
#endif

#ifdef __SSE2__
		template <> struct equal_to <macstl::vec <macstl::boolean <double>, 2> >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::template fill <true> ());
					}
			};
		
		template <> struct equal_to <macstl::vec <long long, 2> >
			{
				typedef macstl::vec <long long, 2> first_argument_type;
				typedef macstl::vec <long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <int, 4> > (lhs), data_cast <vec <int, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

		template <> struct equal_to <macstl::vec <unsigned long long, 2> >
			{
				typedef macstl::vec <unsigned long long, 2> first_argument_type;
				typedef macstl::vec <unsigned long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

#endif
		// not_equal_to

		template <typename T, std::size_t n> struct not_equal_to <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (mmx::cmpeq (lhs, rhs), result_type::fill <true> ());
					}
			};

#ifdef __SSE__

		template <> struct not_equal_to <macstl::vec <float, 4> >:
			public macstl::mmx::cmpneq_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
		
		template <> struct not_equal_to <macstl::vec <macstl::boolean <float>, 4> >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (lhs, rhs);
					}
			};
#endif

#ifdef __SSE2__
		
		template <> struct not_equal_to <macstl::vec <double, 2> >:
			public macstl::mmx::cmpneq_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <double>, 2> >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (lhs, rhs);
					}
			};
		
		template <> struct not_equal_to <macstl::vec <long long, 2> >
			{
				typedef macstl::vec <long long, 2> first_argument_type;
				typedef macstl::vec <long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <int, 4> > (lhs), data_cast <vec <int, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

		template <> struct not_equal_to <macstl::vec <unsigned long long, 2> >
			{
				typedef macstl::vec <unsigned long long, 2> first_argument_type;
				typedef macstl::vec <unsigned long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

#endif
		// greater

		template <typename T, std::size_t n> struct greater <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::andnot (rhs, lhs);
					}
			};

#ifdef __MMX__
		template <> struct greater <macstl::vec <unsigned char, 8> >
			{
				typedef macstl::vec <unsigned char, 8> first_argument_type;
				typedef macstl::vec <unsigned char, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <char>, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned char, 8> offset = vec <unsigned char, 8>::fill <0x80U> ();
						return mmx::cmpgt (
							data_cast <vec <signed char, 8> > (mmx::sub (lhs, offset)),
							data_cast <vec <signed char, 8> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <signed char, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <signed char, 8>, macstl::vec <signed char, 8> >
			{
			};

		template <> struct greater <macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <short>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned short, 4> offset = vec <unsigned short, 4>::fill <0x8000U> ();
						return mmx::cmpgt (
							data_cast <vec <short, 4> > (mmx::sub (lhs, offset)),
							data_cast <vec <short, 4> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <short, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		template <> struct greater <macstl::vec <unsigned int, 2> >
			{
				typedef macstl::vec <unsigned int, 2> first_argument_type;
				typedef macstl::vec <unsigned int, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <int>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned int, 2> offset = vec <unsigned int, 2>::fill <0x80000000U> ();
						return mmx::cmpgt (
							data_cast <vec <int, 2> > (mmx::sub (lhs, offset)),
							data_cast <vec <int, 2> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <int, 2> >:
			public macstl::mmx::cmpgt_function <macstl::vec <int, 2>, macstl::vec <int, 2> >
			{
			};

#endif

	#ifdef __SSE__
		
		template <> struct greater <macstl::vec <float, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

	#endif

	#ifdef __SSE2__

		template <> struct greater <macstl::vec <double, 2> >:
			public macstl::mmx::cmpgt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct greater <macstl::vec <unsigned char, 16> >
			{
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <macstl::boolean <char>, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned char, 16> offset = vec <unsigned char, 16>::fill <0x80U> ();
						return mmx::cmpgt (
							data_cast <vec <signed char, 16> > (mmx::sub (lhs, offset)),
							data_cast <vec <signed char, 16> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <signed char, 16> >:
			public macstl::mmx::cmpgt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >
			{
			};

		template <> struct greater <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <short>, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned short, 8> offset = vec <unsigned short, 8>::fill <0x8000U> ();
						return mmx::cmpgt (
							data_cast <vec <short, 8> > (mmx::sub (lhs, offset)),
							data_cast <vec <short, 8> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <short, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		template <> struct greater <macstl::vec <unsigned int, 4> >
			{
				typedef macstl::vec <unsigned int, 4> first_argument_type;
				typedef macstl::vec <unsigned int, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <int>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned int, 4> offset = vec <unsigned int, 4>::fill <0x80000000U> ();
						return mmx::cmpgt (
							data_cast <vec <int, 4> > (mmx::sub (lhs, offset)),
							data_cast <vec <int, 4> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <int, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >
			{
			};


#endif
		// less
		
		template <typename T, std::size_t n> struct less <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return rhs > lhs;
					}
			};

#ifdef __SSE2__

		template <> struct less <macstl::vec <unsigned long long, 2> >;
		template <> struct less <macstl::vec <long long, 2> >;

#endif

		// less_equal

		template <typename T, std::size_t n> struct less_equal <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return !(lhs > rhs);
					}
			};

	#ifdef __SSE__

		template <> struct less_equal <macstl::vec <float, 4> >:
			public macstl::mmx::cmple_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
			
	#endif

	#ifdef __SSE2__

		template <> struct less_equal <macstl::vec <double, 2> >:
			public macstl::mmx::cmple_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};
			
		template <> struct less_equal <macstl::vec <unsigned long long, 2> >;
		template <> struct less_equal <macstl::vec <long long, 2> >;

	#endif	

		// greater_equal

		template <typename T, std::size_t n> struct greater_equal <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return !(rhs > lhs);
					}
			};
		
	#ifdef __SSE__

		template <> struct greater_equal <macstl::vec <float, 4> >:
			public macstl::mmx::cmpge_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
			
	#endif

	#ifdef __SSE2__

		template <> struct greater_equal <macstl::vec <double, 2> >:
			public macstl::mmx::cmpge_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct greater_equal <macstl::vec <unsigned long long, 2> >;
		template <> struct greater_equal <macstl::vec <long long, 2> >;
			
	#endif
		
		// logical_and

		template <typename T, std::size_t n> struct logical_and <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::andnot (
							mmx::cmpeq (lhs, first_argument_type::template fill <0> ()),
							mmx::vxor (mmx::cmpeq (rhs, second_argument_type::template fill <0> ()), result_type::fill <true> ()));
					}
			};
					
		template <typename T, std::size_t n> struct logical_and <macstl::vec <macstl::boolean <T>, n> >:
			public macstl::mmx::vand_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};
			
		#ifdef __SSE__
		
		template <> struct logical_and <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;
							
							vec <float, 4> zero = vec <float, 4>::fill <0> ();
							return mmx::vand (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};
		
		#endif

		#ifdef __SSE2__
		
		template <> struct logical_and <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> first_argument_type;
				typedef macstl::vec <double, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;
							
							vec <double, 2> zero = vec <double, 2>::fill <0> ();
							return mmx::vand (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};

		template <> struct logical_and <macstl::vec <unsigned long long, 2> >;
		template <> struct logical_and <macstl::vec <long long, 2> >;

		#endif

		// logical_or

		template <typename T, std::size_t n> struct logical_or <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return mmx::vxor (mmx::vand (
							mmx::cmpeq (lhs, first_argument_type::template fill <0> ()),
							mmx::cmpeq (rhs, second_argument_type::template fill <0> ())),
							result_type::fill <true> ());
					}
			};
		
		template <typename T, std::size_t n> struct logical_or <macstl::vec <macstl::boolean <T>, n> >:
			public macstl::mmx::vor_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};

		#ifdef __SSE__
		
		template <> struct logical_or <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;
							
							vec <float, 4> zero = vec <float, 4>::fill <0> ();
							return mmx::vor (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};
		
		#endif

		#ifdef __SSE2__
		
		template <> struct logical_or <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> first_argument_type;
				typedef macstl::vec <double, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;
							
							vec <double, 2> zero = vec <double, 2>::fill <0> ();
							return mmx::vor (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};

		template <> struct logical_or <macstl::vec <unsigned long long, 2> >;
		template <> struct logical_or <macstl::vec <long long, 2> >;

		#endif
	}
	
namespace stdext
	{
		// accumulator <maximum>
		
		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <char>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 8> argument_type;
				typedef macstl::boolean <char> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) != 0;
					}
			};

		template <> struct accumulator <maximum <macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <short, 4> offset = vec <short, 4>::fill <0x8000U> ();
						const vec <short, 4> lhs_offset = mmx::sub (data_cast <vec <short, 4> > (lhs), offset);
						
						const vec <short, 4> result = mmx::max (lhs_offset, mmx::shuffle <0, 3, 2, 1> (lhs_offset));
						return mmx::extract <0> (
							mmx::add (mmx::max (result, mmx::shuffle <1, 0, 3, 2> (result)), offset));
					}
			};

		template <> struct accumulator <maximum <macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <short, 4> result = mmx::max (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::extract <0> (mmx::max (result, mmx::shuffle <1, 0, 3, 2> (result)));
					}
			};
			
		#endif
		
		#ifdef __SSE__
		
		template <> struct accumulator <maximum <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> result = mmx::max (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
						return mmx::max (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <float>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> argument_type;
				typedef macstl::boolean <float> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) != 0;
					}
			};

		#endif

		#ifdef __SSE2__
		
		template <> struct accumulator <maximum <macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return mmx::max (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <double>, 2> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> argument_type;
				typedef macstl::boolean <double> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) != 0;
					}
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <char>, 16> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 16> argument_type;
				typedef macstl::boolean <char> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) != 0;
					}
			};

		#endif

		// accumulator <minimum>

		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <char>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 8> argument_type;
				typedef macstl::boolean <char> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) == 255;
					}
			};
			
		template <> struct accumulator <minimum <macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <short, 4> offset = vec <short, 4>::fill <0x8000U> ();
						const vec <short, 4> lhs_offset = mmx::sub (data_cast <vec <short, 4> > (lhs), offset);
						
						const vec <short, 4> result = mmx::min (lhs_offset, mmx::shuffle <0, 3, 2, 1> (lhs_offset));
						return mmx::extract <0> (
							mmx::add (mmx::min (result, mmx::shuffle <1, 0, 3, 2> (result)), offset));
					}
			};

		template <> struct accumulator <minimum <macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <short, 4> result = mmx::min (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::extract <0> (mmx::min (result, mmx::shuffle <1, 0, 3, 2> (result)));
					}
			};
			
		#endif
		
		#ifdef __SSE__
		
		template <> struct accumulator <minimum <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> result = mmx::min (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
						return mmx::min (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <float>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> argument_type;
				typedef macstl::boolean <float> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) == 15;
					}
			};

		#endif

		#ifdef __SSE2__
		
		template <> struct accumulator <minimum <macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return mmx::min (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <double>, 2> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> argument_type;
				typedef macstl::boolean <double> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) == 3;
					}
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <char>, 16> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 16> argument_type;
				typedef macstl::boolean <char> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::movemask (lhs) == 65535;
					}
			};

		#endif

		// accumulator <plus>
		
		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <std::plus <macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <unsigned short, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::extract <0> (mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)));
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <short, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::extract <0> (mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)));
					}
			};
			
		#endif
			
		#ifdef __SSE__
		
		template <> struct accumulator <std::plus <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> result = mmx::add (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
						return mmx::add (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
					}
			};
		
		#endif

		#ifdef __SSE2__
		
		template <> struct accumulator <std::plus <macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return mmx::add (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <unsigned int, 4> > >
			{
				typedef macstl::vec <unsigned int, 4> argument_type;
				typedef unsigned int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <unsigned int, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)) [0];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <int, 4> > >
			{
				typedef macstl::vec <int, 4> argument_type;
				typedef int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <int, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
						return mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)) [0];
					}
			};
		
		#endif

		// absolute
		
		template <typename T, std::size_t n> struct absolute <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						return lhs;
					}
			};

		#ifdef __SSE__
		
		template <> struct absolute <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vand (argument_type::fill <0x7FFFFFFFU> (), lhs);
					}
			};

		
		#endif

		#ifdef __SSE2__
		
		template <> struct absolute <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::andnot (argument_type::fill <0x7FFFFFFFFFFFFFFFULL> (), lhs);
					}
			};

		
		#endif
		
		// bitwise_not

		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef macstl::vec <T, n> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, argument_type::fill <-1> ());
					}
			};

		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const argument_type&) const
					{
						return argument_type::fill <true> ();
					}
			};

		template <std::size_t n> struct bitwise_not <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_not <macstl::vec <double, n> >;

		// bitwise_xor
		
		template <typename T, std::size_t n> struct bitwise_xor <macstl::vec <T, n> >:
			public macstl::mmx::vxor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_xor <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_xor <macstl::vec <double, n> >;
	
		// bitwise_and
		
		template <typename T, std::size_t n> struct bitwise_and <macstl::vec <T, n> >:
			public macstl::mmx::vand_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_and <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_and <macstl::vec <double, n> >;

		// bitwise_or
		
		template <typename T, std::size_t n> struct bitwise_or <macstl::vec <T, n> >:
			public macstl::mmx::vor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_or <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_or <macstl::vec <double, n> >;

		// cosine
		
		#if defined(__SSE__) && defined(__SSE2__)

		template <> struct cosine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <double, 2> pi = vec <double, 2>::fill <0x400921FB54442D18ULL> ();	// pi
						const vec <double, 2> half_pi = vec <double, 2>::fill <0x3FF921FB54442D18ULL> ();	// pi/2
						
						const vec <int, 4> lhs_n = mmx::cvt <vec <int, 4> > (
							mmx::mul (lhs, vec <float, 4>::fill <0x3EA2F983U> ()));	// 1/pi
						const vec <float, 4> lhs_reduced =
							mmx::movelh (
								// low two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::sub (mmx::cvt <vec <double, 2> > (lhs), half_pi),
									mmx::mul (mmx::cvt <vec <double, 2> > (lhs_n), pi))),
								// high two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::sub (mmx::cvt <vec <double, 2> > (mmx::movehl (lhs, lhs)), half_pi),
									mmx::mul (mmx::cvt <vec <double, 2> > (mmx::shuffle <1, 0, 3, 2> (lhs_n)), pi))));
					
						return
							mmx::vxor (
								mmx::impl::sine_reduced (lhs_reduced),
								mmx::vand (
									 vec <float, 4>::fill <0x80000000U> (),	// -0.0
									reinterpret_cast <const vec <float, 4>&> (mmx::cmpeq (
										mmx::vand (lhs_n, vec <int, 4>::fill <1> ()),
										vec <int, 4>::fill <0> ()).data ())));
						

							
					}	
			};
		
		#endif
	
		// maximum

		template <typename T, std::size_t n> struct maximum <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vor (lhs, rhs);
					}
			};

	#if defined(__MMX__) && defined(__SSE__)

		template <> struct maximum <macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <unsigned short, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 4> offset = vec <short, 4>::fill <0x8000U> ();
						return data_cast <vec <unsigned short, 4> > (mmx::add (mmx::max (
							mmx::sub (data_cast <vec <short, 4> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 4> > (rhs), offset)),
							offset));
					}
			};

		template <> struct maximum <macstl::vec <short, 4> >:
			public macstl::mmx::max_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};
			
		template <> struct maximum <macstl::vec <unsigned char, 8> >:
			public macstl::mmx::max_function <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >
			{
			};


	#endif

	#ifdef __SSE__

		template <> struct maximum <macstl::vec <float, 4> >:
			public macstl::mmx::max_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
			
			
	#endif
	
	#ifdef __SSE2__
	
		template <> struct maximum <macstl::vec <double, 2> >:
			public macstl::mmx::max_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct maximum <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> offset = vec <short, 8>::fill <0x8000U> ();
						return data_cast <vec <unsigned short, 8> > (mmx::add (mmx::max (
							mmx::sub (data_cast <vec <short, 8> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 8> > (rhs), offset)),
							offset));
					}
			};
			
		template <> struct maximum <macstl::vec <short, 8> >:
			public macstl::mmx::max_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};
			
		template <> struct maximum <macstl::vec <unsigned char, 16> >:
			public macstl::mmx::max_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
			};


	#endif

		// minimum

		template <typename T, std::size_t n> struct minimum <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vand (lhs, rhs);
					}
			};

	#if defined(__MMX__) && defined(__SSE__)

		template <> struct minimum <macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <unsigned short, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 4> offset = vec <short, 4>::fill <0x8000U> ();
						return data_cast <vec <unsigned short, 4> > (mmx::add (mmx::min (
							mmx::sub (data_cast <vec <short, 4> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 4> > (rhs), offset)),
							offset));
					}
			};

		template <> struct minimum <macstl::vec <short, 4> >:
			public macstl::mmx::min_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};
			
		template <> struct minimum <macstl::vec <unsigned char, 8> >:
			public macstl::mmx::min_function <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >
			{
			};
#endif
			
	#ifdef __SSE__

		template <> struct minimum <macstl::vec <float, 4> >:
			public macstl::mmx::min_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

	#endif
	#ifdef __SSE2__
	
		template <> struct minimum <macstl::vec <double, 2> >:
			public macstl::mmx::min_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct minimum <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> offset = vec <short, 8>::fill <0x8000U> ();
						return data_cast <vec <unsigned short, 8> > (mmx::add (mmx::min (
							mmx::sub (data_cast <vec <short, 8> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 8> > (rhs), offset)),
							offset));
					}
			};

		template <> struct minimum <macstl::vec <short, 8> >:
			public macstl::mmx::min_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};
			
		template <> struct minimum <macstl::vec <unsigned char, 16> >:
			public macstl::mmx::min_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
			};

	#endif
	
		// multiplies_high
		
		template <typename T, std::size_t n> struct multiplies_high <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type&, const second_argument_type&) const
					{
						return result_type::template fill <false> ();
					}
			};

		#ifdef __MMX__
		
		template <> struct multiplies_high <macstl::vec <short, 4> >:
			public macstl::mmx::mulhi_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};
			
		#endif

		#ifdef __SSE2__
		
		template <> struct multiplies_high <macstl::vec <unsigned short, 8> >:
			public macstl::mmx::mulhi_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};

		template <> struct multiplies_high <macstl::vec <short, 8> >:
			public macstl::mmx::mulhi_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		#endif

		// sine
		
		#if defined(__SSE__) && defined(__SSE2__)
		
		template <> struct sine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <double, 2> pi = vec <double, 2>::fill <0x400921FB54442D18ULL> ();	// pi
						
						// force lhs to [-pi/2, pi/2]
						const vec <int, 4> lhs_n = mmx::cvt <vec <int, 4> > (
							mmx::mul (lhs, vec <float, 4>::fill <0x3EA2F983U> ()));
						const vec <float, 4> lhs_reduced =
							mmx::movelh (
								// low two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::cvt <vec <double, 2> > (lhs),
									mmx::mul (mmx::cvt <vec <double, 2> > (lhs_n), pi))),
								// high two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::cvt <vec <double, 2> > (mmx::movehl (lhs, lhs)),
									mmx::mul (mmx::cvt <vec <double, 2> > (mmx::shuffle <1, 0, 3, 2> (lhs_n)), pi))));

						return
							mmx::vxor (
								mmx::impl::sine_reduced (lhs_reduced),
								mmx::andnot (
									// if lhs == -0.0 or lhs_n is odd, need to invert sign of result
									reinterpret_cast <const vec <float, 4>&> (mmx::andnot (
										mmx::cmpeq (reinterpret_cast <const vec <int, 4>&> (lhs), vec <int, 4>::fill <0x80000000U> ()),
										mmx::cmpeq (mmx::vand (lhs_n, vec <int, 4>::fill <1> ()), vec <int, 4>::fill <0> ()))),
									vec <float, 4>::fill <0x80000000U> ()));
						
					}	
					
			};

		#endif
		
		// square_root
		
		#ifdef __SSE__

		template <> struct square_root <macstl::vec <float, 4> >:
			public macstl::mmx::sqrt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
			
		#endif

		#ifdef __SSE2__

		template <> struct square_root <macstl::vec <double, 2> >:
			public macstl::mmx::sqrt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};
			
		#endif
	
	}
	
#endif