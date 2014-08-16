/*
 *  vec_altivec.h
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
 
#ifndef MACSTL_IMPL_VEC_ALTIVEC_H
#define MACSTL_IMPL_VEC_ALTIVEC_H

namespace macstl
	{
		namespace impl
			{
				template <> struct data_vec <__vector unsigned char>	{ typedef vec <unsigned char, 16> type; };
				template <> struct data_vec <__vector signed char>		{ typedef vec <signed char, 16> type; };
				template <> struct data_vec <__vector bool char>		{ typedef vec <boolean <char>, 16> type; };
				template <> struct data_vec <__vector unsigned short>	{ typedef vec <unsigned short, 8> type; };
				template <> struct data_vec <__vector signed short>		{ typedef vec <short, 8> type; };
				template <> struct data_vec <__vector bool short>		{ typedef vec <boolean <short>, 8> type; };
				template <> struct data_vec <__vector unsigned int>		{ typedef vec <unsigned int, 4> type; };
				template <> struct data_vec <__vector signed int>		{ typedef vec <int, 4> type; };
				template <> struct data_vec <__vector bool int>			{ typedef vec <boolean <int>, 4> type; };
				template <> struct data_vec <__vector float>			{ typedef vec <float, 4> type; };
				template <> struct data_vec <__vector pixel>			{ typedef vec <pixel, 8> type; };

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator
					{
						__vector unsigned int operator() () const
							{
								#if defined(USE_C99_VEC_INIT_IN_TEMPL)
								
								return (__vector unsigned int) {v0, v1, v2, v3};
								
								#elif defined(USE_MOT_VEC_INIT_IN_TEMPL)
								
								// most compilers choke on this, not realizing v0 - v3 ARE constant expressions!!
								return (__vector unsigned int) (v0, v1, v2, v3);
								
								#else
						
								union union_type
									{
										unsigned int val [4];
										__vector unsigned int vec;
									};
									
								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
								
								#endif
								
							}
					};
					
				#ifdef NDEBUG
				#include "impl/generator.h"
				#endif
			}
			
		#ifndef DOXYGEN
		
		template <> class vec <unsigned char, 16>: public impl::vec_base <__vector unsigned char, unsigned char, boolean <char> >
			{
				public:
					typedef unsigned char value_type;
					typedef unsigned char init_type;
					
					union union_type
						{
							unsigned char val [16];
							__vector unsigned char vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							union_type un = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15};
							return un.vec;
						}

					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec set ()
						{
							return static_cast <__vector unsigned char> (impl::generator <
								(v0 << 24) | (v1 << 16) | (v2 << 8) | v3,
								(v4 << 24) | (v5 << 16) | (v6 << 8) | v7,
								(v8 << 24) | (v9 << 16) | (v10 << 8) | v11,
								(v12 << 24) | (v13<< 16) | (v14 << 8) | v15> () ());
						}
					
					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector unsigned char> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector unsigned char data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector unsigned char, unsigned char, boolean <char> >;
					
				private:
					__vector unsigned char data_;
			};

		template <> class vec <signed char, 16>: public impl::vec_base <__vector signed char, signed char, boolean <char> >
			{
				public:
					typedef signed char value_type;
					typedef signed char init_type;
					
					union union_type
						{
							signed char val [16];
							__vector signed char vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							union_type un = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec set ()
						{
							return static_cast <__vector signed char> (impl::generator <
								(((unsigned char) v0) << 24) | (((unsigned char) v1) << 16) | (((unsigned char) v2) << 8) | ((unsigned char) v3),
								(((unsigned char) v4) << 24) | (((unsigned char) v5) << 16) | (((unsigned char) v6) << 8) | ((unsigned char) v7),
								(((unsigned char) v8) << 24) | (((unsigned char) v9) << 16) | (((unsigned char) v10) << 8) | ((unsigned char) v11),
								(((unsigned char) v12) << 24) | (((unsigned char) v13)<< 16) | (((unsigned char) v14) << 8) | ((unsigned char) v15)> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector signed char> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector signed char data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector signed char, signed char, boolean <char> >;
					
				private:
					__vector signed char data_;
			};

		template <> class vec <boolean <char>, 16>: public impl::vec_base <__vector bool char, boolean <char>, boolean <char> >
			{
				public:
					typedef boolean <char> value_type;
					typedef bool init_type;
					
					union union_type
						{
							signed char val [16];
							__vector bool char vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							union_type un = {
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data (),
								v8.data (), v9.data (), v10.data (), v11.data (),
								v12.data (), v13.data (), v14.data (), v15.data ()};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0.data ()};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static vec set ()
						{
							return static_cast <__vector bool char> (impl::generator <
								(v0 ? 0xFF000000U : 0) | (v1 ? 0x00FF0000U : 0) | (v2 ? 0x0000FF00U : 0) | (v3 ? 0x000000FFU : 0),
								(v4 ? 0xFF000000U : 0) | (v5 ? 0x00FF0000U : 0) | (v6 ? 0x0000FF00U : 0) | (v7 ? 0x000000FFU : 0),
								(v8 ? 0xFF000000U : 0) | (v9 ? 0x00FF0000U : 0) | (v10 ? 0x0000FF00U : 0) | (v11 ? 0x000000FFU : 0),
								(v12 ? 0xFF000000U : 0) | (v13 ? 0x00FF0000U : 0) | (v14 ? 0x0000FF00U : 0) | (v15 ? 0x000000FFU : 0)> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector bool char> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector bool char data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector bool char, boolean <char>, boolean <char> >;
					
				private:
					__vector bool char data_;
			};
	
		template <> class vec <unsigned short, 8>: public impl::vec_base <__vector unsigned short, unsigned short, boolean <short> >
			{
				public:
					typedef unsigned short value_type;
					typedef unsigned short init_type;
					
					union union_type
						{
							unsigned short val [8];
							__vector unsigned short vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							union_type un = {v0, v1, v2, v3, v4, v5, v6, v7};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec set ()
						{
							return static_cast <__vector unsigned short> (impl::generator <
								(v0 << 16) | v1, (v2 << 16) | v3,
								(v4 << 16) | v5, (v6 << 16) | v7> () ());
						}
						
					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector unsigned short> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector unsigned short data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector unsigned short, unsigned short, boolean <short> >;
					
				private:
					__vector unsigned short data_;
			};

		template <> class vec <short, 8>: public impl::vec_base <__vector signed short, short, boolean <short> >
			{
				public:
					typedef short value_type;
					typedef short init_type;
					
					union union_type
						{
							short val [8];
							__vector signed short vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							union_type un = {v0, v1, v2, v3, v4, v5, v6, v7};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec set ()
						{
							return static_cast <__vector signed short> (impl::generator <
								(((unsigned short) v0) << 16) | ((unsigned short) v1), (((unsigned short) v2) << 16) | ((unsigned short) v3),
								(((unsigned short) v4) << 16) | ((unsigned short) v5), (((unsigned short) v6) << 16) | ((unsigned short) v7)> () ());
						}
						
					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector signed short> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector signed short data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector signed short, short, boolean <short> >;
					
				private:
					__vector signed short data_;
			};

		template <> class vec <boolean <short>, 8>: public impl::vec_base <__vector bool short, boolean <short>, boolean <short> >
			{
				public:
					typedef boolean <short> value_type;
					typedef bool init_type;
					
					union union_type
						{
							short val [8];
							__vector bool short vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							union_type un = {
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data ()};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0.data ()};
							return vec_splat (un.vec, 0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static vec set ()
						{
							return static_cast <__vector bool short> (impl::generator <
								(v0 ? 0xFFFF0000U : 0) | (v1 ? 0x0000FFFFU : 0), (v2 ? 0xFFFF0000U : 0) | (v3 ? 0x0000FFFFU : 0),
								(v4 ? 0xFFFF0000U : 0) | (v5 ? 0x0000FFFFU : 0), (v6 ? 0xFFFF0000U : 0) | (v7 ? 0x0000FFFFU : 0)> () ());
						}
						
					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector bool short> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector bool short data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector bool short, boolean <short>, boolean <short> >;
					
				private:
					__vector bool short data_;
			};

		template <> class vec <unsigned int, 4>: public impl::vec_base <__vector unsigned int, unsigned int, boolean <int> >
			{
				public:
					typedef unsigned int value_type;
					typedef unsigned int init_type;
					
					union union_type
						{
							unsigned int val [4];
							__vector unsigned int vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0, v1, v2, v3};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec set ()
						{
							return impl::generator <v0, v1, v2, v3> () ();
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector unsigned int> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector unsigned int data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector unsigned int, unsigned int, boolean <int> >;
					
				private:
					__vector unsigned int data_;
			};


		template <> class vec <int, 4>: public impl::vec_base <__vector signed int, int, boolean <int> >
			{
				public:
					typedef int value_type;
					typedef int init_type;
					
					union union_type
						{
							int val [4];
							__vector signed int vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0, v1, v2, v3};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec set ()
						{
							return static_cast <__vector signed int> (impl::generator <(int) v0, (int) v1, (int) v2, (int) v3> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector signed int> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector signed int data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector signed int, int, boolean <int> >;
					
				private:
					__vector signed int data_;
			};

		template <> class vec <float, 4>: public impl::vec_base <__vector float, float, boolean <int> >
			{
				public:
					typedef float value_type;
					typedef unsigned int init_type;
					
					union union_type
						{
							float val [4];
							__vector float vec;
						};
					
					static vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0, v1, v2, v3};
							return un.vec;
						}
						
					static vec fill (
						value_type v0)
						{
							union_type un = {v0};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec set ()
						{
							return static_cast <__vector float> (impl::generator <v0, v1, v2, v3> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector float> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector float data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector float, float, boolean <int> >;
					
				private:
					__vector float data_;
			};

		template <> class vec <boolean <int>, 4>: public impl::vec_base <__vector bool int, boolean <int>, boolean <int> >
			{
				public:
					typedef boolean <int> value_type;
					typedef bool init_type;
					
					union union_type
						{
							int val [4];
							__vector bool int vec;
						};
					
					static vec set (
						boolean <int> v0, boolean <int> v1, boolean <int> v2, boolean <int> v3)
						{
							union_type un = {
								v0.data (), v1.data (), v2.data (), v3.data ()};
							return un.vec;
						}
						
					static vec fill (
						boolean <int> v0)
						{
							union_type un = {v0.data ()};
							return vec_splat (un.vec, 0);
						}
						
					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static vec set ()
						{
							return static_cast <__vector bool int> (impl::generator <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0, v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector bool int> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector bool int data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector bool int, boolean <int>, boolean <int> >;
					
				private:
					__vector bool int data_;
			};

		template <> class vec <stdext::complex <float>, 2>: public impl::vec_base <__vector float, stdext::complex <float>, boolean <long long> >
			{
				public:
					typedef stdext::complex <float> value_type;
					typedef unsigned long long init_type;
					
					union union_type
						{
							stdext::complex <float>::data_type val [2];
							__vector float vec;
						};
					
					static vec set (
						stdext::complex <float> v0, stdext::complex <float> v1)
						{
							#ifdef HAS_C99_COMPLEX
							union_type un = {v0.data (), v1.data ()};
							#else
							union_type un = {v0.real (), v0.imag (), v1.real (), v1.imag ()};
							#endif
							return un.vec;
						}
						
					static vec fill (
						stdext::complex <float> v0)
						{
							return set (v0, v0);
						}
						
					template <
						unsigned long long v0, unsigned long long v1>
						static vec set ()
						{
							return static_cast <__vector float> (impl::generator <
								(v0 & 0xFFFFFFFF00000000ULL) >> 32, v0 & 0x00000000FFFFFFFFULL,
								(v1 & 0xFFFFFFFF00000000ULL) >> 32, v1 & 0x00000000FFFFFFFFULL> () ());
						}

					template <unsigned long long v0>
						static vec fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector float> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector float data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector float, stdext::complex <float>, boolean <long long> >;
					
				private:
					__vector float data_;
			};

		template <> class vec <boolean <long long>, 2>: public impl::vec_base <__vector bool int, boolean <long long>, boolean <long long> >
			{
				public:
					typedef boolean <long long> value_type;
					typedef bool init_type;
					
					union union_type
						{
							long long val [2];
							__vector bool int vec;
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
							union_type un = {v0.data (), v0.data ()};
							return un.vec;
						}
						
					template <
						init_type v0, init_type v1>
						static vec set ()
						{
							return static_cast <__vector bool int> (impl::generator <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U> () ());
						}

					template <init_type v0>
						static vec fill ()
						{
							return set <v0, v0> ();
						}
						
					vec (): data_ (static_cast <__vector bool int> (impl::generator <0, 0, 0, 0> () ()))
						{
						}
						
					vec (__vector bool int data): data_ (data)
						{
						}
					
					friend class impl::vec_base <__vector bool int, boolean <long long>, boolean <long long> >;
					
				private:
					__vector bool int data_;
			};
			
		#endif

#define DEFINE_ALTIVEC_LOAD(FN,INTR,DESC)																\
																										\
DEFINE_VEC_PLATFORM_BINARY_FUNCTION(FN,DESC)																\
																										\
template <typename T1, typename T2> struct FN##_function <T1, const T2*>											\
	{																									\
		typedef T1 first_argument_type;																	\
		typedef const T2* second_argument_type;															\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (0, (const T2*) NULL))) };						\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator() (first_argument_type x, second_argument_type y) const					\
			{																							\
				return INTR (x, y);																		\
			}																							\
	};																									\
																										\
template <typename T1, typename T2> struct FN##_function <T1, T2*>												\
	{																									\
		typedef T1 first_argument_type;																	\
		typedef T2* second_argument_type;																\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (0, (T2*) NULL))) };							\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator() (first_argument_type x, second_argument_type y) const					\
			{																							\
				return INTR (x, y);																		\
			}																							\
	};																									\
					
#define DEFINE_ALTIVEC_STORE(FN,INTR,DESC)																\
																										\
DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(FN,DESC)															\
																										\
template <typename T1, std::size_t n1, typename T2, typename T3> struct FN##_function <vec <T1, n1>, T2, T3*>			\
	{																									\
		typedef vec <T1, n1> first_argument_type;														\
		typedef T2 second_argument_type;																\
		typedef T3* third_argument_type;																\
																										\
		typedef void result_type;																		\
																										\
		result_type operator() (const first_argument_type& x,											\
			second_argument_type y, third_argument_type z) const										\
			{																							\
				INTR (x.data (), y, z);																	\
			}																							\
	};

#define DEFINE_ALTIVEC_UNARY_FUNCTION(FN,INTR,DESC)															\
																										\
DEFINE_VEC_PLATFORM_UNARY_FUNCTION(FN,DESC)																	\
																										\
template <typename T, std::size_t n> struct FN##_function <vec <T, n> >									\
	{																									\
		typedef vec <T, n> argument_type;																\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (												\
			*(typename argument_type::data_type*) NULL))) };											\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator () (const argument_type& lhs) const										\
			{																							\
				return INTR (lhs.data ());																\
			}																							\
	};

#define DEFINE_ALTIVEC_UNARY_FUNCTION_WITH_LITERAL(FN,INTR,DESC)												\
																										\
DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL(FN,DESC)														\
																										\
template <unsigned int i, typename T> struct FN##_function												\
	{																									\
		typedef T argument_type;																		\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (												\
			*(typename argument_type::data_type*) NULL,													\
			0))) };																						\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator () (const argument_type& lhs) const										\
			{																							\
				return INTR (lhs.data (), i);															\
			}																							\
	};
	
	
#define DEFINE_ALTIVEC_BINARY_FUNCTION(FN,INTR,DESC)														\
																										\
DEFINE_VEC_PLATFORM_BINARY_FUNCTION(FN,DESC)																\
																										\
template <typename T1, std::size_t n1, typename T2, std::size_t n2> struct FN##_function <vec <T1, n1>, vec <T2, n2> >		\
	{																									\
		typedef vec <T1, n1> first_argument_type;														\
		typedef vec <T2, n2> second_argument_type;														\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (												\
			*(typename first_argument_type::data_type*) NULL,											\
			*(typename second_argument_type::data_type*) NULL))) };									\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator () (const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																							\
				return INTR (lhs.data (), rhs.data ());													\
			}																							\
	};

#define DEFINE_ALTIVEC_BINARY_FUNCTION_WITH_LITERAL(FN,INTR,DESC)										\
																										\
DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL(FN,DESC)												\
																										\
template <unsigned int i, typename T1, std::size_t n1, typename T2, std::size_t n2>								\
	struct FN##_function <i, vec <T1, n1>, vec <T2, n2> >															\
	{																									\
		typedef vec <T1, n1> first_argument_type;														\
		typedef vec <T2, n2> second_argument_type;														\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (												\
			*(typename first_argument_type::data_type*) NULL,											\
			*(typename second_argument_type::data_type*) NULL,										\
			0))) };																						\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator () (const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																							\
				return INTR (lhs.data (), rhs.data (), i);												\
			}																							\
	};


#define DEFINE_ALTIVEC_TERNARY_FUNCTION(FN,INTR,DESC)													\
																										\
DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(FN,DESC)															\
																										\
template <typename T1, std::size_t n1, typename T2, std::size_t n2, typename T3, std::size_t n3>						\
	struct FN##_function <vec <T1, n1>, vec <T2, n2>, vec <T3, n3> >												\
	{																									\
		typedef vec <T1, n1> first_argument_type;														\
		typedef vec <T2, n2> second_argument_type;														\
		typedef vec <T3, n3> third_argument_type;														\
																										\
		enum { kind = sizeof (*impl::type_to_kind (INTR (												\
			*(typename first_argument_type::data_type*) NULL,											\
			*(typename second_argument_type::data_type*) NULL,											\
			*(typename third_argument_type::data_type*) NULL))) };										\
		typedef typename impl::kind_to_type <kind>::type result_type;									\
																										\
		result_type operator () (const first_argument_type& lhs, const second_argument_type& mhs,		\
			const third_argument_type& rhs) const														\
			{																							\
				return INTR (lhs.data (), mhs.data (), rhs.data ());									\
			}																							\
	};

#define DEFINE_ALTIVEC_UNARY_PREDICATE_FUNCTION(FN,INTR,DESC)											\
																										\
DEFINE_VEC_PLATFORM_UNARY_FUNCTION(FN,DESC)																\
																										\
template <typename T, std::size_t n> struct FN##_function <vec <T, n> >												\
	{																									\
		typedef vec <T, n> argument_type;																\
		typedef bool result_type;																		\
																										\
		result_type operator() (const argument_type& lhs) const											\
			{																							\
				return INTR (lhs.data ());																\
			}																							\
	};

#define DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(FN,INTR,DESC)											\
																										\
DEFINE_VEC_PLATFORM_BINARY_FUNCTION(FN,DESC)																\
																										\
template <typename T1, std::size_t n1, typename T2, std::size_t n2> struct FN##_function <vec <T1, n1>, vec <T2, n2> >		\
	{																									\
		typedef vec <T1, n1> first_argument_type;														\
		typedef vec <T2, n2> second_argument_type;														\
		typedef bool result_type;																		\
																										\
		result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																							\
				return INTR (lhs.data (), rhs.data ());													\
			}																							\
	};

		/// Altivec intrinsics.
		
		/// Sequesters the Altivec intrinsics from similarly named common or platform SIMD functions.
		/// Each Altivec intrinsic of the form vec_xxx is wrapped in a function xxx as well as a functor xxx_function.
		/// Any literal parameters are expressed as template non-type parameters, e.g. ctu <0> (x) wraps vec_ctu (x, 0).
		/// See http://developer.apple.com/hardware/ve/instruction_crossref.html for a comprehensive list of intrinsics and their explanations.
		///
		/// @note	You can use either the raw vector type or macstl::vec for any of the type parameters.
		
		namespace altivec
			{
				/// Altivec intrinsics implementation.
				namespace impl
					{
						// more Dewhurstian SFINAE concepts: a partial typeof implementation, to help
						// keep in sync the object interface and the underlying Altivec operators

						enum typekind
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
							
						char (*type_to_kind (__vector unsigned char)) [vector_unsigned_char];
						char (*type_to_kind (__vector signed char)) [vector_signed_char];
						char (*type_to_kind (__vector bool char)) [vector_bool_char];
						char (*type_to_kind (__vector unsigned short)) [vector_unsigned_short];
						char (*type_to_kind (__vector signed short)) [vector_signed_short];
						char (*type_to_kind (__vector bool short)) [vector_bool_short];
						char (*type_to_kind (__vector unsigned int)) [vector_unsigned_int];
						char (*type_to_kind (__vector signed int)) [vector_signed_int];
						char (*type_to_kind (__vector bool int)) [vector_bool_int];
						char (*type_to_kind (__vector float)) [vector_float];
						char (*type_to_kind (__vector __pixel)) [vector_pixel];
					
						template <std::size_t k> struct kind_to_type;
						
						template <> struct kind_to_type <vector_unsigned_char> { typedef vec <unsigned char, 16> type; };
						template <> struct kind_to_type <vector_signed_char> { typedef vec <signed char, 16> type; };
						template <> struct kind_to_type <vector_bool_char> { typedef vec <boolean <char>, 16> type; };
						template <> struct kind_to_type <vector_unsigned_short> { typedef vec <unsigned short, 8> type; };
						template <> struct kind_to_type <vector_signed_short> { typedef vec <short, 8> type; };
						template <> struct kind_to_type <vector_bool_short> { typedef vec <boolean <short>, 8> type; };
						template <> struct kind_to_type <vector_unsigned_int> { typedef vec <unsigned int, 4> type; };
						template <> struct kind_to_type <vector_signed_int> { typedef vec <int, 4> type; };
						template <> struct kind_to_type <vector_bool_int> { typedef vec <boolean <int>, 4> type; };
						template <> struct kind_to_type <vector_float> { typedef vec <float, 4> type; };
						template <> struct kind_to_type <vector_pixel> { typedef vec <pixel, 8> type; };
					}

				/// @name Load and Store
				/// See <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html#load_and_store">instruction cross-reference</a>.
				
				//@{
				DEFINE_ALTIVEC_LOAD(ld,vec_ld,load indexed)
				DEFINE_ALTIVEC_LOAD(ldl,vec_ldl,load indexed LRU)
				DEFINE_ALTIVEC_LOAD(lde,vec_lde,load element indexed)
				DEFINE_ALTIVEC_LOAD(lvsl,vec_lvsl,load for shift left)
				DEFINE_ALTIVEC_LOAD(lvsr,vec_lvsr,load for shift right)
				DEFINE_ALTIVEC_STORE(st,vec_st,store indexed)
				DEFINE_ALTIVEC_STORE(stl,vec_stl,store indexed LRU)
				DEFINE_ALTIVEC_STORE(ste,vec_ste,store element indexed)
				//@}
							
				/// @name Data Manipulation
				/// See <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html#data_manipulation">instruction cross-reference</a>.
				
				//@{
				DEFINE_ALTIVEC_TERNARY_FUNCTION(perm,vec_perm,permute)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(sel,vec_sel,conditional select)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sr,vec_sr,shift right)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sra,vec_sra,shift right algebraic)
				DEFINE_ALTIVEC_BINARY_FUNCTION(srl,vec_srl,shift right logical)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sro,vec_sro,shift right by octet)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sl,vec_sl,shift left)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sll,vec_sll,shift left logical)
				DEFINE_ALTIVEC_BINARY_FUNCTION(slo,vec_slo,shift left by octet)
				DEFINE_ALTIVEC_BINARY_FUNCTION_WITH_LITERAL(sld,vec_sld,shift left double by octet immediate)
				DEFINE_ALTIVEC_BINARY_FUNCTION(rl,vec_rl,rotate left integer)
				DEFINE_ALTIVEC_BINARY_FUNCTION(mergeh,vec_mergeh,merge high)
				DEFINE_ALTIVEC_BINARY_FUNCTION(mergel,vec_mergel,merge low)
				DEFINE_ALTIVEC_UNARY_FUNCTION_WITH_LITERAL(splat,vec_splat,splat)
			//	DEFINE_ALTIVEC_NULLARY_FUNCTION(mfvscr,mfvscr_function,vec_mfvscr)
				DEFINE_ALTIVEC_UNARY_FUNCTION(mtvscr,vec_mtvscr,move to status and control register)
				DEFINE_ALTIVEC_BINARY_FUNCTION(pack,vec_pack,pack modulo)
				DEFINE_ALTIVEC_BINARY_FUNCTION(packpx,vec_packpx,pack pixel)
				DEFINE_ALTIVEC_BINARY_FUNCTION(packs,vec_packs,pack saturate)
				DEFINE_ALTIVEC_BINARY_FUNCTION(packsu,vec_packsu,pack unsigned saturate)
				DEFINE_ALTIVEC_UNARY_FUNCTION(unpackh,vec_unpackh,unpack high)
				DEFINE_ALTIVEC_UNARY_FUNCTION(unpackl,vec_unpackl,unpack low)		
				//@}
				
				/// @name Arithmetic
				/// See <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html#arithmetic">instruction cross-reference</a>.
				
				//@{
				DEFINE_ALTIVEC_UNARY_FUNCTION(abs,vec_abs,absolute value)
				DEFINE_ALTIVEC_UNARY_FUNCTION(abss,vec_abss,absolute value saturated)
				DEFINE_ALTIVEC_BINARY_FUNCTION(add,vec_add,add modulo)
				DEFINE_ALTIVEC_BINARY_FUNCTION(addc,vec_addc,add and write carry-out)
				DEFINE_ALTIVEC_BINARY_FUNCTION(adds,vec_adds,add saturated)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sub,vec_sub,subtract modulo)
				DEFINE_ALTIVEC_BINARY_FUNCTION(subc,vec_subc,subtract and write carry-out)
				DEFINE_ALTIVEC_BINARY_FUNCTION(subs,vec_subs,subtract saturated)
				DEFINE_ALTIVEC_BINARY_FUNCTION(mule,vec_mule,multiply even integer)
				DEFINE_ALTIVEC_BINARY_FUNCTION(mulo,vec_mulo,multiply odd integer)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(madd,vec_madd,multiply-add float)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(madds,vec_madds,multiply-high and add saturate)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(mladd,vec_mladd,multiply-low and add modulo)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(mradds,vec_mradds,multiply-high round and add saturate)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(msum,vec_msum,multiply-sum modulo)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(msums,vec_msums,multiply-sum saturate)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sum4s,vec_sum4s,sum across 1/4 integer)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sum2s,vec_sum2s,sum across 1/2 signed integer)
				DEFINE_ALTIVEC_BINARY_FUNCTION(sums,vec_sums,sum across signed integer)
				DEFINE_ALTIVEC_TERNARY_FUNCTION(nmsub,vec_nmsub,negative multiply-subtract)
				DEFINE_ALTIVEC_BINARY_FUNCTION(avg,vec_avg,average integer)
				DEFINE_ALTIVEC_BINARY_FUNCTION(max,vec_max,maximum)
				DEFINE_ALTIVEC_BINARY_FUNCTION(min,vec_min,minimum)
				DEFINE_ALTIVEC_UNARY_FUNCTION(round,vec_round,round to nearest)
				DEFINE_ALTIVEC_UNARY_FUNCTION(ceil,vec_ceil,round to ceiling)
				DEFINE_ALTIVEC_UNARY_FUNCTION(floor,vec_floor,round to floor)		
				DEFINE_ALTIVEC_UNARY_FUNCTION(trunc,vec_trunc,truncate)
				DEFINE_ALTIVEC_UNARY_FUNCTION(re,vec_re,reciprocal estimate)
				DEFINE_ALTIVEC_UNARY_FUNCTION(rsqrte,vec_rsqrte,reciprocal square root estimate)
				DEFINE_ALTIVEC_UNARY_FUNCTION(loge,vec_loge,logarithm estimate)
				DEFINE_ALTIVEC_UNARY_FUNCTION(expte,vec_expte,raise to exponent estimate)
				DEFINE_ALTIVEC_UNARY_FUNCTION_WITH_LITERAL(ctf,vec_ctf,convert from fixed-point word)
				DEFINE_ALTIVEC_UNARY_FUNCTION_WITH_LITERAL(cts,vec_cts,convert to signed fixed-point word saturate)
				DEFINE_ALTIVEC_UNARY_FUNCTION_WITH_LITERAL(ctu,vec_ctu,convert to unsigned fixed-point word saturate)
				//@}

				/// @name Logic
				/// See <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html#logical">instruction cross-reference</a>.
				
				//@{
				DEFINE_ALTIVEC_BINARY_FUNCTION(vand,vec_and,bitwise AND)
				DEFINE_ALTIVEC_BINARY_FUNCTION(andc,vec_andc,bitwise AND-NOT)
				DEFINE_ALTIVEC_BINARY_FUNCTION(vor,vec_or,bitwise OR)
				DEFINE_ALTIVEC_BINARY_FUNCTION(nor,vec_nor,bitwise NOR)
				DEFINE_ALTIVEC_BINARY_FUNCTION(vxor,vec_xor,bitwise XOR)
				//@}
				
				/// @name Compares and Predicates
				/// See <a href="http://developer.apple.com/hardware/ve/instruction_crossref.html#compare">instruction cross-reference</a>.
				
				//@{
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmpeq,vec_cmpeq,compare equal-to)
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmpge,vec_cmpge,compare greater-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmpgt,vec_cmpgt,compare greater-than)
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmple,vec_cmple,compare less-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmplt,vec_cmplt,compare less-than)
				DEFINE_ALTIVEC_BINARY_FUNCTION(cmpb,vec_cmpb,compare bounds float)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_eq,vec_all_eq,compare all equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_ne,vec_all_ne,compare all not-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_eq,vec_any_eq,compare any equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_ne,vec_any_ne,compare any not-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_ge,vec_all_ge,compare all greater-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_le,vec_all_le,compare all less-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_ge,vec_any_ge,compare any greater-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_le,vec_any_le,compare any less-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_gt,vec_all_gt,compare all greater-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_lt,vec_all_lt,compare all less-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_gt,vec_any_gt,compare any greater-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_lt,vec_any_lt,compare any less-than)
				DEFINE_ALTIVEC_UNARY_PREDICATE_FUNCTION(all_nan,vec_all_nan,compare all nan)
				DEFINE_ALTIVEC_UNARY_PREDICATE_FUNCTION(all_numeric,vec_all_numeric,compare all numeric)
				DEFINE_ALTIVEC_UNARY_PREDICATE_FUNCTION(any_nan,vec_any_nan,compare any nan)
				DEFINE_ALTIVEC_UNARY_PREDICATE_FUNCTION(any_numeric,vec_any_numeric,compare any numeric)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_nge,vec_all_nge,compare all not greater-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_nle,vec_all_nle,compare all not less-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_nge,vec_any_nge,compare any not greater-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_nle,vec_any_nle,compare any not less-than-or-equal-to)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_ngt,vec_all_ngt,compare all not greater-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_nlt,vec_all_nlt,compare all not less-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_ngt,vec_any_ngt,compare any not greater-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_nlt,vec_any_nlt,compare any not less-than)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(all_in,vec_all_in,compare bounds float in)
				DEFINE_ALTIVEC_BINARY_PREDICATE_FUNCTION(any_out,vec_any_out,compare bounds flout out)
				//@}
				
				namespace impl
					{
						inline vec <float, 4> reciprocal (const vec <float, 4>& lhs)
							{
								// estimate reciprocal then do one pass of Newton-Raphson
								vec <float, 4> estimate = altivec::re (lhs);
								return altivec::madd (
									altivec::nmsub (estimate, lhs, vec <float, 4>::fill <0x3F800000U> ()), // 1.0f
									estimate,
									estimate);
							}

						inline vec <unsigned int, 4> multiply_high
							(const vec <unsigned int, 4>& lhs, const vec <unsigned int, 4>& rhs)
							{
								// the high long of multiplying lhs and rhs, but ignoring any carry from the low long
								
								vec <unsigned int, 4> sixteen = vec <unsigned int, 4>::fill <0xFFFFFFF0U> ();
								vec <unsigned short, 8> rhs_shift = data_cast <vec <unsigned short, 8> > (altivec::rl (rhs, sixteen));

								vec <unsigned int, 4> lhs_low_rhs_high = altivec::mulo (data_cast <vec <unsigned short, 8> > (lhs), rhs_shift);
								vec <unsigned int, 4> lhs_high_rhs_low = altivec::mule (data_cast <vec <unsigned short, 8> > (lhs), rhs_shift);
								vec <unsigned int, 4> lhs_high_rhs_high = altivec::mule (data_cast <vec <unsigned short, 8> > (lhs), data_cast <vec <unsigned short, 8> > (rhs));

								vec <unsigned int, 4> lhs_rhs_middle = altivec::add (lhs_low_rhs_high, lhs_high_rhs_low);
								
								return altivec::add (
									altivec::add (lhs_high_rhs_high, altivec::sr (lhs_rhs_middle, sixteen)),
									altivec::sl (altivec::addc (lhs_low_rhs_high, lhs_high_rhs_low), sixteen));
							}
							
						inline vec <unsigned int, 4> multiply
							(const vec <unsigned int, 4>& lhs, const vec <unsigned int, 4>& rhs)
							{
								vec <unsigned int, 4> sixteen = vec <unsigned int, 4>::fill <0xFFFFFFF0U> ();
								
								// low order of result = low order of lhs * low order of rhs
								vec <unsigned int, 4> low = altivec::mulo (
									data_cast <vec <unsigned short, 8> > (lhs),
									data_cast <vec <unsigned short, 8> > (rhs));
										
								// high order of result = low order of lhs * high order of rhs + low order of rhs * high order of lhs
								vec <unsigned int, 4> high = altivec::msum (
									data_cast <vec <unsigned short, 8> > (lhs),
									data_cast <vec <unsigned short, 8> > (altivec::rl (rhs, sixteen)),
									vec <unsigned int, 4>::fill <0> ());
										
								return altivec::add (altivec::sl (high, sixteen), low);
							}


						inline vec <unsigned int, 4> estimate_divide (const vec <unsigned int, 4>& dividend, const vec <unsigned int, 4>& divisor)
							{
								// we conduct two Newton-Raphson iterations to get a fairly accurate 32-bit result: the first is conducted in floating point,
								// and the second in (!) 64-bit fixed point
								
								// compute reciprocal (0.32) of divisor
								// NOTE: this is a floating point N-R of the intrinsic, approximately 23 bits accuracy
								const vec <unsigned int, 4> divisor_reciprocal = altivec::ctu <0> (data_cast <vec <float, 4> > (
									altivec::add (data_cast <vec <unsigned int, 4> > (reciprocal (altivec::ctf <0> (divisor))), (vector unsigned int) (1 << 28))));
								
								// compute 2 (0.32) - divisor (int) * reciprocal (0.32)
								// NOTE: divisor * reciprocal is either 0x1U 0000 xxxx OR 0x0U FFFF xxxx, so to calculate high word it is sufficient to check whether low word is "negative" 
								vec <unsigned int, 4> divisor_reciprocal_low = multiply (divisor, divisor_reciprocal);
								vec <unsigned int, 4> two_minus_divisor_reciprocal_low = altivec::sub ((vector unsigned int) (0), divisor_reciprocal_low);
								vec <boolean <int>, 4> two_minus_divisor_reciprocal_high =
									altivec::cmplt (data_cast <vec <int, 4> > (divisor_reciprocal_low), (vector signed int) (1));

								// compute dividend (int) * reciprocal (0.32)
								// NOTE: we ignore the low word
								vec <unsigned int, 4> dividend_reciprocal_high = multiply_high (dividend, divisor_reciprocal);
								
								// compute the dividend * fixed point N-R of the reciprocal (0.64)
								// NOTE: estimated error is 0 - 3
								return altivec::add (multiply_high (dividend_reciprocal_high, two_minus_divisor_reciprocal_low),
									altivec::vand (dividend_reciprocal_high, two_minus_divisor_reciprocal_high));
							}
							
						inline vec <unsigned char, 16> select_high_half ()
							{
								vector unsigned int zero = (vector unsigned int) (0);
								vector unsigned int sixteen = vec_splat_u32 (-16);
								
								return data_cast <vec <unsigned char, 16> > (altivec::mergeh (
									altivec::pack (altivec::rl (data_cast <vec <unsigned int, 4> > (altivec::lvsl (0, (int*) NULL)), sixteen), zero),
									altivec::pack (altivec::rl (data_cast <vec <unsigned int, 4> > (altivec::lvsr (0, (int*) NULL)), sixteen), zero)));
							}

						inline vec <unsigned short, 8> estimate_divide
							(const vec <unsigned short, 8>& dividend, const vec <unsigned short, 8>& divisor)
							{
								// we conduct one Newton-Raphson iteration in floating point to get a fairly accurate 16-bit result
								
								vec <unsigned char, 16> high_half = select_high_half ();
															
								vector unsigned short zero = (vector unsigned short) (0);
								vec <unsigned short, 8> divisor_reciprocal = altivec::packs (
									altivec::ctu <16> (reciprocal (altivec::ctf <0> (data_cast <vec <unsigned int, 4> > (altivec::mergeh (zero, divisor))))),
									altivec::ctu <16> (reciprocal (altivec::ctf <0> (data_cast <vec <unsigned int, 4> > (altivec::mergel (zero, divisor))))));
									
								return data_cast <vec <unsigned short, 8> > (altivec::perm (
									altivec::mule (dividend, divisor_reciprocal),
									altivec::mulo (dividend, divisor_reciprocal),
									high_half));
							}
					
						inline vec <unsigned char, 16> estimate_divide
							(const vec <unsigned char, 16>& dividend, const vec <unsigned char, 16>& divisor)
							{
								// we use the reciprocal estimate directly to get a fairly accurate 8-bit result

								vector unsigned char zero = (vector unsigned char) (0);
								vec <unsigned char, 16> high_half = select_high_half ();

								vec <unsigned short, 8> dividend_high = data_cast <vec <unsigned short, 8> > (altivec::mergeh (zero, dividend));
								vec <unsigned short, 8> dividend_low = data_cast <vec <unsigned short, 8> > (altivec::mergel (zero, dividend));
								
								vec <unsigned short, 8> divisor_high = data_cast <vec <unsigned short, 8> > (altivec::mergeh (zero, divisor));
								vec <unsigned short, 8> divisor_low = data_cast <vec <unsigned short, 8> > (altivec::mergel (zero, divisor));
								
								vec <unsigned short, 8> divisor_reciprocal_high = altivec::packs (
									altivec::ctu <16> (altivec::re (altivec::ctf <0> (altivec::unpackh (data_cast <vec <short, 8> > (divisor_high))))),
									altivec::ctu <16> (altivec::re (altivec::ctf <0> (altivec::unpackl (data_cast <vec <short, 8> > (divisor_high))))));

								vec <unsigned short, 8> divisor_reciprocal_low = altivec::packs (
									altivec::ctu <16> (altivec::re (altivec::ctf <0> (altivec::unpackh (data_cast <vec <short, 8> > (divisor_low))))),
									altivec::ctu <16> (altivec::re (altivec::ctf <0> (altivec::unpackl (data_cast <vec <short, 8> > (divisor_low))))));
						
								return altivec::pack (
									data_cast <vec <unsigned short, 8> > (altivec::perm (
										altivec::mule (dividend_high, divisor_reciprocal_high),
										altivec::mulo (dividend_high, divisor_reciprocal_high),
										high_half)),
									data_cast <vec <unsigned short, 8> > (altivec::perm (
										altivec::mule (dividend_low, divisor_reciprocal_low),
										altivec::mulo (dividend_low, divisor_reciprocal_low),
										high_half)));
									
							}
						template <std::size_t n> vec <unsigned char, 16> swap_real_imag ();
						
						template <> inline vec <unsigned char, 16> swap_real_imag <4> ()	// for words
							{
								return altivec::vxor (vec_splat_u8 (4), altivec::lvsl (0, (int*) NULL));
							}
						
						template <> inline vec <unsigned char, 16> swap_real_imag <8> ()	// for shorts
							{
								return altivec::vxor (vec_splat_u8 (2), altivec::lvsl (0, (int*) NULL));
							}

						template <> inline vec <unsigned char, 16> swap_real_imag <16> ()	// for bytes
							{
								return altivec::vxor (vec_splat_u8 (1), altivec::lvsl (0, (int*) NULL));
							}
														
						inline vec <stdext::complex <float>, 2> complex_fma
							(const vec <stdext::complex <float>, 2>& lhs, const vec <stdext::complex <float>, 2>& mhs, const vec <stdext::complex <float>, 2> &rhs)
							{
								const vec <unsigned char, 16> inc = altivec::lvsl (0, (int*) NULL);
								const vec <unsigned char, 16> four = vec_splat_u8 (4);
									
								const vec <float, 4> lhs2 = lhs.data ();					// a b c d
								const vec <float, 4> mhs2 = mhs.data ();					// e f g h
								const vec <float, 4> rhs2 = rhs.data ();					// i j k l
								
								return altivec::madd (
									altivec::perm (lhs2, lhs2, altivec::vxor (inc, four)),			// b a d c
									
									altivec::vxor (
										altivec::perm (mhs2, mhs2, altivec::vor (inc, four)),	// f f h h
										vec <float, 4>::set <0x80000000U, 0, 0x80000000U, 0> ()),	// -f f -h h
									
									altivec::madd (
										lhs2,
										altivec::perm (mhs2, mhs2, altivec::andc (inc, four)),	// e e g g
										rhs2)														// ae+i be+j cg+k dg+l
									).data ();															// ae-bf+i be+af+j cg-dh+k dg+ch+l
								
							}
					
						// perform floating point divide assuming y is not denormal
						inline vec <float, 4> divide_normal (const vec <float, 4>& x, const vec <float, 4>& y)
							{
								const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0f
								
								const vec <float, 4> estimate = altivec::re (y);
								const vec <float, 4> two_minus_estimate_y = altivec::nmsub (estimate, y, vec <float, 4>::fill <0x40000000U> ()); // 2.0f
								const vec <float, 4> two_minus_estimate_y_no_nan =
									altivec::sel (
										vec <float, 4>::fill <0x3F800000U> (),		// when result is nan, y is either +/-0 or +/-inf, therefore est is accurate and we may substitute 1.0f for this term
										two_minus_estimate_y,	// not a nan, so keep the value
										altivec::cmpeq (two_minus_estimate_y, two_minus_estimate_y));
										
								const vec <float, 4> estimate_x = altivec::madd (estimate, x, zero);
								const vec <boolean <int>, 4> estimate_x_not_overflow = // check if estimate * scale_x didn't overflow
									altivec::cmpeq (
										altivec::cmpb (estimate_x, vec <float, 4>::fill <0x7F7FFFFFU> ()),
										vec <int, 4>::fill <0> ());
								
								return
									altivec::madd (
										altivec::sel (
											estimate,
											estimate_x,
											estimate_x_not_overflow),
										altivec::sel (
											altivec::madd (x, two_minus_estimate_y_no_nan, zero),
											two_minus_estimate_y_no_nan,
											estimate_x_not_overflow),
										zero);
							}
														
						// sin (x - n * Pi) -- where x - n * Pi is in [-Pi/2, Pi/2]
						inline vec <float, 4> sine_n (const vec <float, 4>& x, const vec <float, 4>& n)
							{
								const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
								const vec <float, 4> x_reduced = altivec::madd (
									n, vec <float, 4>::fill <0xA84234C4U> (), // minus third 24 bits of Pi
									altivec::madd (
										n, vec <float, 4>::fill <0xB4222168U> (),	// minus second 24 bits of Pi
										altivec::madd (
											n, vec <float, 4>::fill <0xC0490FDAU> (), // minus first 24 bits of Pi
											x)));
								
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <float, 4> xx = altivec::madd (x_reduced, x_reduced, zero);
								return
									altivec::madd (
										altivec::madd (
											altivec::madd (
												altivec::madd (
													altivec::madd (
														xx, vec <float, 4>::fill <0x362E9C5BU> (),	// 2.60190306765133772461701600763e-6 x^9
														vec <float, 4>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx, vec <float, 4>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx, vec <float, 4>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx, vec <float, 4>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x_reduced, zero);
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
						
						return altivec::sub (argument_type::template fill <0> (), lhs);
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

		template <> struct negate <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::vxor (lhs,
							vec <float, 4>::fill <0x80000000U> ());
					}
			};

		template <> struct negate <macstl::vec <stdext::complex <float>, 2> >
			{
				typedef macstl::vec <stdext::complex <float>, 2> argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <stdext::complex <float>, 2> > (altivec::vxor (
							data_cast <vec <float, 4> > (lhs),
							vec <float, 4>::fill <0x80000000U> ()));
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
						
						return altivec::cmpeq (lhs, argument_type::template fill <0> ());
					}
			};

		template <typename T, std::size_t n> struct logical_not <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> argument_type;
				typedef typename macstl::vec <stdext::complex <T>, n>::vec_boolean result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						typename vec <T, n * 2>::vec_boolean eq = altivec::cmpeq (
							data_cast <vec <T, n * 2> > (lhs),
							vec <T, n * 2>::template fill <0> ());
							
						return data_cast <result_type> (altivec::vand (eq,
							altivec::perm (eq, eq, altivec::impl::swap_real_imag <n * 2> ())));
					}
			};

		template <typename T, std::size_t n> struct logical_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::nor (lhs, lhs);
					}
			};

		template <> struct logical_not <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> lhs2 = data_cast <vec <boolean <int>, 4> > (lhs);
						return data_cast <vec <boolean <long long>, 2> > (altivec::nor (lhs2, lhs2));
					}
			};

					
		// multiplies
		
		template <> struct multiplies <macstl::vec <unsigned char, 16> >
			{
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <unsigned char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned short, 8> p1 = altivec::mule (lhs, rhs);
						vec <unsigned short, 8> p2 = altivec::mulo (lhs, rhs);
						return data_cast <result_type> (altivec::mergel (altivec::pack (p1, p1), altivec::pack (p2, p2)));
					}
			};

		template <> struct multiplies <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <short, 8> p1 = altivec::mule (lhs, rhs);
						vec <short, 8> p2 = altivec::mulo (lhs, rhs);
						return data_cast <result_type> (altivec::mergel (altivec::pack (p1, p1), altivec::pack (p2, p2)));
					}
			};

		template <> struct multiplies <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::mladd (lhs, rhs, vec <unsigned short, 8>::fill <0> ());
					}
			};
			
		template <> struct multiplies <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::mladd (lhs, rhs, vec <short, 8>::fill <0> ());
					}
			};

		template <> struct multiplies <macstl::vec <unsigned int, 4> >
			{
				typedef macstl::vec <unsigned int, 4> first_argument_type;
				typedef macstl::vec <unsigned int, 4> second_argument_type;
				typedef macstl::vec <unsigned int, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::impl::multiply (lhs, rhs);
					}
			};

		template <> struct multiplies <macstl::vec <int, 4> >
			{
				typedef macstl::vec <int, 4> first_argument_type;
				typedef macstl::vec <int, 4> second_argument_type;
				typedef macstl::vec <int, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <int, 4> zero = vec <int, 4>::fill <0> ();
						
						// unsigned multiply
						vec <int, 4> result = data_cast <vec <int, 4> > (
							data_cast <vec <unsigned int, 4> > (altivec::abs (lhs)) *
							data_cast <vec <unsigned int, 4> > (altivec::abs (rhs)));
							
						// if both signs negative or positive, select the unsigned result
						// if one sign negative and the other positive, select the negative of the unsigned result
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, altivec::vxor (lhs, rhs)));
					}
			};

		template <> struct multiplies <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <float, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::madd (lhs, rhs, vec <float, 4>::fill <0x80000000U> ()); // -0.0f
					}
			};

		template <typename T, std::size_t n> struct multiplies <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vand (lhs, rhs);
					}
			};

		template <> struct multiplies <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vand (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <> struct multiplies <macstl::vec <stdext::complex <float>, 2> >
			{
				typedef macstl::vec <stdext::complex <float>, 2> first_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> second_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::impl::complex_fma (lhs, rhs,
							vec <stdext::complex <float>, 2>::fill <0x8000000080000000ULL> ());	// (-0.0f, -0.0f)
					}
			};
	
		// divides

		template <> struct divides <macstl::vec <unsigned char, 16> >
			{
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <unsigned char, 16> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned char, 16> quotient = altivec::impl::estimate_divide (lhs, rhs);
						vec <unsigned char, 16> difference = altivec::sub (lhs, quotient * rhs);
						return altivec::add (quotient,
							altivec::andc (vec <unsigned char, 16>::fill <1> (), altivec::cmplt (difference, rhs)));
					}
			};

		template <> struct divides <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <signed char, 16> zero = vec <signed char, 16>::fill <0> ();
						
						// unsigned divide
						vec <signed char, 16> result = data_cast <vec <signed char, 16> > (
							data_cast <vec <unsigned char, 16> > (altivec::abs (lhs)) /
							data_cast <vec <unsigned char, 16> > (altivec::abs (rhs)));
							
						// if both signs negative or positive, select the unsigned result
						// if one sign negative and the other positive, select the negative of the unsigned result
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, altivec::vxor (lhs, rhs)));
					}
			};

		template <> struct divides <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned short, 8> quotient = altivec::impl::estimate_divide (lhs, rhs);
						vec <unsigned short, 8> difference = altivec::mladd (quotient,
							altivec::sub (vec <unsigned short, 8>::fill <0> (), rhs), lhs);
						
						return altivec::add (quotient,
							altivec::andc (vec <unsigned short, 8>::fill <1> (), altivec::cmplt (difference, rhs)));
					}
			};

		template <> struct divides <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> zero = vec <short, 8>::fill <0> ();
						
						// unsigned divide
						vec <short, 8> result = data_cast <vec <short, 8> > (
							data_cast <vec <unsigned short, 8> > (altivec::abs (lhs)) /
							data_cast <vec <unsigned short, 8> > (altivec::abs (rhs)));
							
						// if both signs negative or positive, select the unsigned result
						// if one sign negative and the other positive, select the negative of the unsigned result
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, altivec::vxor (lhs, rhs)));
					}
			};
		
		template <> struct divides <macstl::vec <unsigned int, 4> >
			{
				typedef macstl::vec <unsigned int, 4> first_argument_type;
				typedef macstl::vec <unsigned int, 4> second_argument_type;
				typedef macstl::vec <unsigned int, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						const vec <unsigned int, 4> rhs2 = altivec::adds (rhs, rhs);
						const vec <unsigned int, 4> quotient = altivec::impl::estimate_divide (lhs, rhs);

						// compute lhs - quotient * rhs, then perform 3 bit division on it
						vec <unsigned int, 4> difference = altivec::sub (lhs, quotient * rhs);
						vec <boolean <int>, 4> unbounded2 = altivec::cmplt (difference, rhs2);
						difference = altivec::sel (altivec::sub (difference, rhs2), difference, unbounded2);
						vec <boolean <int>, 4> unbounded1 = altivec::cmplt (difference, rhs);
							
						return altivec::add (quotient, altivec::vor (
							altivec::andc (vec <unsigned int, 4>::fill <2> (), unbounded2),
							altivec::andc (vec <unsigned int, 4>::fill <1> (), unbounded1)));
					}
			};

		template <> struct divides <macstl::vec <int, 4> >
			{
				typedef macstl::vec <int, 4> first_argument_type;
				typedef macstl::vec <int, 4> second_argument_type;
				typedef macstl::vec <int, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <int, 4> zero = vec <int, 4>::fill <0> ();
						
						// unsigned divide
						vec <int, 4> result = data_cast <vec <int, 4> > (
							data_cast <vec <unsigned int, 4> > (altivec::abs (lhs)) /
							data_cast <vec <unsigned int, 4> > (altivec::abs (rhs)));
							
						// if both signs negative or positive, select the unsigned result
						// if one sign negative and the other positive, select the negative of the unsigned result
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, altivec::vxor (lhs, rhs)));
					}
			};
	
		template <> struct divides <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const first_argument_type& x, const second_argument_type& y) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0f
						const vec <float, 4> scale = vec <float, 4>::fill <0x4B000000U> ();	// scale by 2^23, converts smallest denorm into smallest norm
						
						const vec <boolean <int>, 4> denormal =	// check if y is a denormalized number
							altivec::cmpeq (
								altivec::cmpb (y, vec <float, 4>::fill <0x007FFFFFU> ()),
								vec <int, 4>::fill <0> ());
								
						// do the division on the renormalized numbers
						// NOTE: the scale is in both divisor and dividend so it will cancel out
						return altivec::impl::divide_normal (
							altivec::sel (x, altivec::madd (x, scale, zero), denormal),
							altivec::sel (y, altivec::madd (y, scale, zero), denormal));
					}
			};

		template <> struct divides <macstl::vec <stdext::complex <float>, 2> >
			{
				typedef macstl::vec <stdext::complex <float>, 2> first_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> second_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						const vec <unsigned char, 16> inc = altivec::lvsl (0, (int*) NULL);
						const vec <unsigned char, 16> four = vec_splat_u8 (4);
						const vec <unsigned char, 16> swap = altivec::vxor (inc, four);
						
						const vec <float, 4> zero = vec <float, 4>::fill <0> ();

						const vec <float, 4> lhs2 = lhs.data ();					// a b c d
						const vec <float, 4> rhs2 = rhs.data ();					// e f g h
						
						const vec <float, 4> rhs2_square = altivec::madd (rhs2, rhs2, zero);	// e2 f2 g2 h2
						
						const vec <float, 4> divisor = altivec::add (
							rhs2_square,
							altivec::perm (rhs2_square, rhs2_square, swap)						// f2 e2 h2 g2
							);																		// e2+f2 e2+f2 g2+h2 g2+h2
						
						const vec <float, 4> dividend = altivec::madd (
							altivec::perm (lhs2, lhs2, swap),			// b a d c
							
							altivec::vxor (
								altivec::perm (rhs2, rhs2, altivec::vor (inc, four)),	// f f h h
								vec <float, 4>::set <0, 0x80000000U, 0, 0x80000000U> ()),		// f -f h -h
							
							altivec::madd (
								lhs2,
								altivec::perm (rhs2, rhs2, altivec::andc (inc, four)),	// e e g g
								zero)														// ae be cg dg
							);																		// ae+bf be-af cg+dh dg-ch
							
						return (dividend / divisor).data ();										// (ae+bf)/(e2+f2) (be-af)/(e2+f2) (cg+dh)/(g2+h2) (dg-ch)/(g2+h2)
					}
			};

		template <typename T, size_t n> struct divides <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vor (lhs, altivec::nor (rhs, rhs));
					}
			};

		template <> struct divides <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> rhs2 = data_cast <vec <boolean <int>, 4> > (rhs);
						return data_cast <result_type> (altivec::vor (lhs, altivec::nor (rhs2, rhs2)));
					}
			};

		// modulus

		template <> struct modulus <macstl::vec <unsigned char, 16> >
			{			
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <unsigned char, 16> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned char, 16> quotient = altivec::impl::estimate_divide (lhs, rhs);

						vec <unsigned char, 16> difference = altivec::sub (lhs, quotient * rhs);
						return altivec::sel (altivec::sub (difference, rhs), difference, altivec::cmplt (difference, rhs));
					}
			};
			
		template <> struct modulus <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <signed char, 16> zero = vec <signed char, 16>::fill <0> ();
						
						// unsigned modulus
						vec <signed char, 16> result = data_cast <vec <signed char, 16> > (
							data_cast <vec <unsigned char, 16> > (altivec::abs (lhs)) %
							data_cast <vec <unsigned char, 16> > (altivec::abs (rhs)));
							
						// if lhs is negative, result is negative
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, lhs));
					}
			};
			
		template <> struct modulus <macstl::vec <unsigned short, 8> >
			{			
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned short, 8> quotient = altivec::impl::estimate_divide (lhs, rhs);

						vec <unsigned short, 8> difference = altivec::mladd (quotient,
							altivec::sub (vec <unsigned short, 8>::fill <0> (), rhs), lhs);
						return altivec::sel (altivec::sub (difference, rhs), difference, altivec::cmplt (difference, rhs));
					}
			};
			
		template <> struct modulus <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> zero = vec <short, 8>::fill <0> ();
						
						// unsigned divide
						vec <short, 8> result = data_cast <vec <short, 8> > (
							data_cast <vec <unsigned short, 8> > (altivec::abs (lhs)) %
							data_cast <vec <unsigned short, 8> > (altivec::abs (rhs)));
							
						// if lhs is negative, result is negative
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, lhs));
					}
			};

		template <> struct modulus <macstl::vec <unsigned int, 4> >
			{			
				typedef macstl::vec <unsigned int, 4> first_argument_type;
				typedef macstl::vec <unsigned int, 4> second_argument_type;
				typedef macstl::vec <unsigned int, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <unsigned int, 4> rhs2 = altivec::adds (rhs, rhs);
						vec <unsigned int, 4> quotient = altivec::impl::estimate_divide (lhs, rhs);

						// compute lhs - quotient * rhs, then perform 3 bit division on it
						vec <unsigned int, 4> difference = altivec::sub (lhs, quotient * rhs);
						difference = altivec::sel (altivec::sub (difference, rhs2), difference, altivec::cmplt (difference, rhs2));
						return altivec::sel (altivec::sub (difference, rhs), difference, altivec::cmplt (difference, rhs));
					}
			};

		template <> struct modulus <macstl::vec <int, 4> >
			{
				typedef macstl::vec <int, 4> first_argument_type;
				typedef macstl::vec <int, 4> second_argument_type;
				typedef macstl::vec <int, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <int, 4> zero = vec <int, 4>::fill <0> ();
						
						// unsigned modulus
						vec <int, 4> result = data_cast <vec <int, 4> > (
							data_cast <vec <unsigned int, 4> > (altivec::abs (lhs)) %
							data_cast <vec <unsigned int, 4> > (altivec::abs (rhs)));
							
						// if lhs is negative, result is negative
						return altivec::sel (result, altivec::sub (zero, result), altivec::cmpgt (zero, lhs));
					}
			};

		template <typename T, size_t n> struct modulus <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::andc (lhs, rhs);
					}
			};

		template <> struct modulus <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (
							altivec::andc (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		// plus
		
		template <typename T, std::size_t n> struct plus <macstl::vec <T, n> >:
			public macstl::altivec::add_function <macstl::vec <T, n>, macstl::vec <T, n> >
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
						
						return altivec::vor (lhs, rhs);
					}
			};

		template <> struct plus <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::vor (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <typename T, std::size_t n> struct plus <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::add (
							data_cast <macstl::vec <T, n * 2> > (lhs),
							data_cast <macstl::vec <T, n * 2> > (rhs)));
					}
			};


		// minus
		
		template <typename T, std::size_t n> struct minus <macstl::vec <T, n> >:
			public macstl::altivec::sub_function <macstl::vec <T, n>, macstl::vec <T, n> >
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
						
						return altivec::vxor (lhs, rhs);
					}
			};

		template <> struct minus <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::vxor (
							data_cast <vec <macstl::boolean <int>, 4> > (lhs),
							data_cast <vec <macstl::boolean <int>, 4> > (rhs)));
					}
			};

		template <typename T, std::size_t n> struct minus <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::sub (
							data_cast <vec <T, n * 2> > (lhs),
							data_cast <vec <T, n * 2> > (rhs)));
					}
			};
			
		// equal_to

		template <typename T, std::size_t n> struct equal_to <macstl::vec <T, n> >:
			public macstl::altivec::cmpeq_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <typename T, std::size_t n> struct equal_to <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						result_type neq = altivec::vxor (lhs, rhs);
						return altivec::nor (neq, neq);
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
						
						vec <boolean <int>, 4> neq = altivec::vxor (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs));
						return data_cast <vec <boolean <long long>, 2> > (altivec::nor (neq, neq));
					}
			};

		template <typename T, std::size_t n> struct equal_to <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef typename macstl::vec <stdext::complex <T>, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						typename vec <T, n * 2>::vec_boolean eq = altivec::cmpeq (
							data_cast <vec <T, n * 2> > (lhs),
							data_cast <vec <T, n * 2> > (rhs));
							
						return data_cast <result_type> (altivec::vand (eq,
							altivec::perm (eq, eq, altivec::impl::swap_real_imag <n * 2> ())));
					}
			};
			
		// not_equal_to
		
		template <typename T, std::size_t n> struct not_equal_to <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						result_type eq = altivec::cmpeq (lhs, rhs);
						return altivec::nor (eq, eq);
					}
			};

		template <typename T, std::size_t n> struct not_equal_to <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vxor (lhs, rhs);
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
						
						return data_cast <vec <boolean <long long>, 2> > (
							altivec::vxor (data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <typename T, std::size_t n> struct not_equal_to <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef typename macstl::vec <stdext::complex <T>, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						typename vec <T, n * 2>::vec_boolean eq = altivec::cmpeq (
							data_cast <vec <T, n * 2> > (lhs),
							data_cast <vec <T, n * 2> > (rhs));
							
						return data_cast <result_type> (altivec::andc (altivec::nor (eq, eq),
							altivec::perm (eq, eq, altivec::impl::swap_real_imag <n * 2> ())));
					}
			};

		// less

		template <typename T, std::size_t n> struct less <macstl::vec <T, n> >:
			public macstl::altivec::cmplt_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <typename T, std::size_t n> struct less <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::andc (rhs, lhs);
					}
			};

		template <> struct less <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::andc (
							data_cast <vec <boolean <int>, 4> > (rhs),
							data_cast <vec <boolean <int>, 4> > (lhs)));
					}
			};

		template <typename T, std::size_t n> struct less <macstl::vec <stdext::complex <T>, n> >;
			
		// greater
		
		template <typename T, std::size_t n> struct greater <macstl::vec <T, n> >:
			public macstl::altivec::cmpgt_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <typename T, std::size_t n> struct greater <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::andc (lhs, rhs);
					}
			};

		template <> struct greater <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::andc (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <typename T, std::size_t n> struct greater <macstl::vec <stdext::complex <T>, n> >;
			
		// less_equal

		template <typename T, std::size_t n> struct less_equal <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
						
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						result_type gt = altivec::cmpgt (lhs, rhs);
						return altivec::nor (gt, gt);
					}
			};

		template <> struct less_equal <macstl::vec <float, 4> >:
			public macstl::altivec::cmple_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <typename T, std::size_t n> struct less_equal <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vor (altivec::nor (lhs, lhs), rhs);
					}
			};

		template <> struct less_equal <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> lhs2 = data_cast <vec <boolean <int>, 4> > (lhs);
						return data_cast <vec <boolean <long long>, 2> > (altivec::vor (
							altivec::nor (lhs, lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <typename T, std::size_t n> struct less_equal <macstl::vec <stdext::complex <T>, n> >;

		// greater_equal

		template <typename T, std::size_t n> struct greater_equal <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						result_type lt = altivec::cmplt (lhs, rhs);
						return altivec::nor (lt, lt);
					}
			};

		template <> struct greater_equal <macstl::vec <float, 4> >:
			public macstl::altivec::cmpge_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <typename T, std::size_t n> struct greater_equal <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vor (lhs, altivec::nor (rhs, rhs));
					}
			};

		template <> struct greater_equal <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						vec <boolean <int>, 4> rhs2 = data_cast <vec <boolean <int>, 4> > (rhs);
						return data_cast <vec <boolean <long long>, 2> > (altivec::vor (
							data_cast <vec <boolean <int>, 4> > (lhs),
							altivec::nor (rhs2, rhs2)));
					}
			};

		template <typename T, std::size_t n> struct greater_equal <macstl::vec <stdext::complex <T>, n> >;
	
		// logical_and
		
		template <typename T, std::size_t n> struct logical_and <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::nor (
							altivec::cmpeq (lhs, first_argument_type::template fill <0> ()),
							altivec::cmpeq (rhs, second_argument_type::template fill <0> ()));
					}
			};

		template <typename T, std::size_t n> struct logical_and <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef typename macstl::vec <stdext::complex <T>, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						typename vec <T, n * 2>::vec_boolean lhs_rhs = altivec::nor (
							altivec::cmpeq (data_cast <vec <T, n * 2> > (lhs), vec <T, n * 2>::template fill <0> ()),
							altivec::cmpeq (data_cast <vec <T, n * 2> > (rhs), vec <T, n * 2>::template fill <0> ()));
						
						return data_cast <result_type> (altivec::vand (lhs_rhs,
							altivec::perm (lhs_rhs, lhs_rhs, altivec::impl::swap_real_imag <n * 2> ())));
					}
			};

		template <typename T, std::size_t n> struct logical_and <macstl::vec <macstl::boolean <T>, n> >:
			public macstl::altivec::vand_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};

		template <> struct logical_and <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vand (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		// logical_or
		
		template <typename T, std::size_t n> struct logical_or <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						result_type lhs_rhs = altivec::vand (
							altivec::cmpeq (lhs, first_argument_type::template fill <0> ()),
							altivec::cmpeq (rhs, second_argument_type::template fill <0> ()));
						return altivec::nor (lhs_rhs, lhs_rhs);
					}
			};

		template <typename T, std::size_t n> struct logical_or <macstl::vec <stdext::complex <T>, n> >
			{
				typedef macstl::vec <stdext::complex <T>, n> first_argument_type;
				typedef macstl::vec <stdext::complex <T>, n> second_argument_type;
				typedef typename macstl::vec <stdext::complex <T>, n>::vec_boolean result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						typename vec <T, n * 2>::vec_boolean lhs_rhs = altivec::vand (
							altivec::cmpeq (data_cast <vec <T, n * 2> > (lhs), vec <T, n * 2>::template fill <0> ()),
							altivec::cmpeq (data_cast <vec <T, n * 2> > (rhs), vec <T, n * 2>::template fill <0> ()));
						typename vec <T, n * 2>::vec_boolean lhs_rhs2 = altivec::nor (lhs_rhs, lhs_rhs);
						
						return data_cast <result_type> (altivec::vor (lhs_rhs,
							altivec::perm (lhs_rhs2, lhs_rhs2, altivec::impl::swap_real_imag <n * 2> ())));
					}
			};

		template <typename T, std::size_t n> struct logical_or <macstl::vec <macstl::boolean <T>, n> >:
			public macstl::altivec::vor_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};

		template <> struct logical_or <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vor (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

	}
	
namespace stdext
	{
		// maximum

		template <typename T, std::size_t n> struct maximum <macstl::vec <T, n> >:
			public macstl::altivec::max_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <> struct maximum <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						#if __FINITE_MATH_ONLY__
						return altivec::max (lhs, rhs);
						#else
						return altivec::sel (
							rhs, lhs,
							altivec::andc (altivec::cmpeq (lhs, lhs), altivec::cmplt (lhs, rhs)));
						#endif
					}
			};
			
		template <typename T, std::size_t n> struct maximum <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vor (lhs, rhs);
					}
			};

		template <> struct maximum <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> >
							(altivec::vor (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		template <std::size_t n> struct maximum <macstl::vec <stdext::complex <float>, n> >;
			
		// minimum

		template <typename T, std::size_t n> struct minimum <macstl::vec <T, n> >:
			public macstl::altivec::min_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <> struct minimum <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						#if __FINITE_MATH_ONLY__
						return altivec::min (lhs, rhs);
						#else
						return altivec::sel (
							lhs, rhs,
							altivec::andc (altivec::cmpeq (rhs, rhs), altivec::cmplt (lhs, rhs)));
						#endif
					}
			};
			
		template <typename T, std::size_t n> struct minimum <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::vand (lhs, rhs);
					}
			};

		template <> struct minimum <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> >
							(altivec::vand (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};
			
		template <std::size_t n> struct minimum <macstl::vec <stdext::complex <float>, n> >;


		// accumulator <maximum>

		template <> struct accumulator <maximum <macstl::vec <unsigned char, 16> > >
			{
				typedef macstl::vec <unsigned char, 16> argument_type;
				typedef unsigned char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned char, 16> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <8> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <signed char, 16> > >
			{
				typedef macstl::vec <signed char, 16> argument_type;
				typedef char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <signed char, 16> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <8> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <unsigned short, 8> > >
			{
				typedef macstl::vec <unsigned short, 8> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned short, 8> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <short, 8> > >
			{
				typedef macstl::vec <short, 8> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <short, 8> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <unsigned int, 4> > >
			{
				typedef macstl::vec <unsigned int, 4> argument_type;
				typedef unsigned int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned int, 4> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <int, 4> > >
			{
				typedef macstl::vec <int, 4> argument_type;
				typedef int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <int, 4> result = altivec::max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <maximum <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> result = max (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return max (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <typename T, std::size_t n> struct accumulator <maximum <macstl::vec <macstl::boolean <T>, n> > >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::boolean <T> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::any_ne (lhs, argument_type::template fill <false> ());
					}
			};
		
		// accumulator <minimum>

		template <> struct accumulator <minimum <macstl::vec <unsigned char, 16> > >
			{
				typedef macstl::vec <unsigned char, 16> argument_type;
				typedef unsigned char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned char, 16> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <8> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <signed char, 16> > >
			{
				typedef macstl::vec <signed char, 16> argument_type;
				typedef char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <signed char, 16> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <8> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <unsigned short, 8> > >
			{
				typedef macstl::vec <unsigned short, 8> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned short, 8> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <short, 8> > >
			{
				typedef macstl::vec <short, 8> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <short, 8> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <16> ()));
						result = altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <unsigned int, 4> > >
			{
				typedef macstl::vec <unsigned int, 4> argument_type;
				typedef unsigned int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						macstl::vec <unsigned int, 4> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <int, 4> > >
			{
				typedef macstl::vec <int, 4> argument_type;
				typedef int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						macstl::vec <int, 4> result = altivec::min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <minimum <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						macstl::vec <float, 4> result = min (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return min (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <typename T, std::size_t n> struct accumulator <minimum <macstl::vec <macstl::boolean <T>, n> > >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::boolean <T> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::all_eq (lhs, argument_type::template fill <true> ());
					}
			};
		
		// accumulator <std::plus>

		template <> struct accumulator <std::plus <macstl::vec <signed char, 16> > >
			{
				typedef macstl::vec <signed char, 16> argument_type;
				typedef char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <int, 4> zero = vec <int, 4>::fill <0> ();
						return data_cast <vec <signed char, 16> > (altivec::sums (
							altivec::sum4s (lhs, zero), zero)) [15];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <unsigned char, 16> > >
			{
				typedef macstl::vec <unsigned char, 16> argument_type;
				typedef unsigned char result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <signed char, 16> > (altivec::sums (
							data_cast <vec <int, 4> > (altivec::sum4s (lhs, vec <unsigned int, 4>::fill <0> ())), vec <int, 4>::fill <0> ())) [15];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <short, 8> > >
			{
				typedef macstl::vec <short, 8> argument_type;
				typedef short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <int, 4> zero = vec <int, 4>::fill <0> ();
						return altivec::sums (
							altivec::sum4s (lhs, zero), zero) [3];
					}
			};
			
		template <> struct accumulator <std::plus <macstl::vec <unsigned short, 8> > >
			{
				typedef macstl::vec <unsigned short, 8> argument_type;
				typedef unsigned short result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::sums (altivec::sum4s (
							altivec::sub (data_cast <vec <short, 8> > (lhs), vec <short, 8>::fill <-0x8000> ()),
							vec <int, 4>::fill <0> ()), 
							vec <int, 4>::fill <0x40000U> ()) [3];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <int, 4> > >
			{
				typedef macstl::vec <int, 4> argument_type;
				typedef int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <int, 4> result = altivec::add (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::add (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};
			
		template <> struct accumulator <std::plus <macstl::vec <unsigned int, 4> > >
			{
				typedef macstl::vec <unsigned int, 4> argument_type;
				typedef unsigned int result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <unsigned int, 4> result = altivec::add (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::add (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						vec <float, 4> result = altivec::add (lhs, altivec::slo (lhs, vec <unsigned char, 16>::fill <32> ()));
						return altivec::add (result, altivec::slo (result, vec <unsigned char, 16>::fill <64> ())) [0];
					}
			};

		template <typename T, std::size_t n> struct accumulator <std::plus <macstl::vec <macstl::boolean <T>, n> > >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::boolean <T> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return result_type (altivec::any_ne (lhs, argument_type::template fill <false> ()));
					}
			};

		template <> struct accumulator <std::plus <macstl::vec <stdext::complex <float>, 2> > >
			{
				typedef macstl::vec <stdext::complex <float>, 2> argument_type;
				typedef stdext::complex <float> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const argument_type result = data_cast <argument_type> (altivec::add (lhs,
							altivec::slo (data_cast <vec <float, 4> > (lhs), vec <unsigned char, 16>::fill <64> ())));
						return result [0];
					}
			};
			
		// cshifter

		template <typename T, std::size_t n> struct cshifter <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef int second_argument_type;
				typedef macstl::vec <T, n> result_type;

				result_type operator() (const first_argument_type& lhs, second_argument_type rhs) const
					{
						using namespace macstl;
						
						return altivec::perm (lhs, lhs, altivec::lvsl (rhs * sizeof (typename result_type::value_type), (int*) NULL));
					}
			};

		// shifter

		template <typename T, std::size_t n> struct shifter <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef int second_argument_type;
				typedef macstl::vec <T, n> result_type;

				result_type operator() (const first_argument_type& lhs, second_argument_type rhs) const
					{
						using namespace macstl;
						
						result_type zero = result_type::template fill <0> ();
						if (rhs >= (int) result_type::length || -rhs >= (int) result_type::length)
							return zero;
						else if (rhs >= 0)
							return altivec::perm (lhs, zero, altivec::lvsl (rhs * sizeof (typename result_type::value_type), (int*) NULL));
						else
							return altivec::perm (zero, lhs, altivec::lvsr (-rhs * sizeof (typename result_type::value_type), (int*) NULL));
					}
			};
		
		// bitwise_not
		
		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef macstl::vec <T, n> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						return altivec::nor (lhs, lhs);
					}
			};

		template <std::size_t n> struct bitwise_not <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_not <macstl::vec <stdext::complex <float>, n> >;

		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const argument_type&) const
					{
						return result_type::template fill <true> ();
					}
			};


		// bitwise_xor
		
		template <typename T, std::size_t n> struct bitwise_xor <macstl::vec <T, n> >:
			public macstl::altivec::vxor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_xor <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_xor <macstl::vec <stdext::complex <float>, n> >;
		
		template <> struct bitwise_xor <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vxor (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		// bitwise_and
		
		template <typename T, std::size_t n> struct bitwise_and <macstl::vec <T, n> >:
			public macstl::altivec::vand_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_and <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_and <macstl::vec <stdext::complex <float>, n> >;
		
		template <> struct bitwise_and <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vand (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};
			
		// bitwise_or
		
		template <typename T, std::size_t n> struct bitwise_or <macstl::vec <T, n> >:
			public macstl::altivec::vor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_or <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_or <macstl::vec <stdext::complex <float>, n> >;
		
		template <> struct bitwise_or <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> > (altivec::vor (
							data_cast <vec <boolean <int>, 4> > (lhs),
							data_cast <vec <boolean <int>, 4> > (rhs)));
					}
			};

		// shift_left
		
		template <typename T, std::size_t n> struct shift_left <macstl::vec <T, n> >:
			public macstl::altivec::sl_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <> struct shift_left <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sl (lhs, data_cast <vec <unsigned char, 16> > (rhs)); 
					}
			};

		template <> struct shift_left <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sl (lhs, data_cast <vec <unsigned short, 8> > (rhs)); 
					}
			};

		template <> struct shift_left <macstl::vec <int, 4> >
			{
				typedef macstl::vec <int, 4> first_argument_type;
				typedef macstl::vec <int, 4> second_argument_type;
				typedef macstl::vec <int, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sl (lhs, data_cast <vec <unsigned int, 4> > (rhs)); 
					}
			};

		template <typename T, std::size_t n> struct shift_left <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type&) const
					{
						return lhs; 
					}
			};

		template <std::size_t n> struct shift_left <macstl::vec <float, n> >;

		template <typename T, std::size_t n> struct shift_left <macstl::vec <stdext::complex <T>, n> >;
		
		// shift_right

		template <> struct shift_right <macstl::vec <unsigned char, 16> >:
			public macstl::altivec::sr_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
			};
		
		template <> struct shift_right <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sra (lhs, data_cast <vec <unsigned char, 16> > (rhs)); 
					}
			};

		template <> struct shift_right <macstl::vec <unsigned short, 8> >:
			public macstl::altivec::sr_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};
		
		template <> struct shift_right <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sra (lhs, data_cast <vec <unsigned short, 8> > (rhs)); 
					}
			};

		template <> struct shift_right <macstl::vec <unsigned int, 4> >:
			public macstl::altivec::sr_function <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> >
			{
			};
		
		template <> struct shift_right <macstl::vec <int, 4> >
			{
				typedef macstl::vec <int, 4> first_argument_type;
				typedef macstl::vec <int, 4> second_argument_type;
				typedef macstl::vec <int, 4> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::sra (lhs, data_cast <vec <unsigned int, 4> > (rhs)); 
					}
			};
			
		template <typename T, std::size_t n> struct shift_right <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::andc (lhs, rhs); 
					}
			};

		template <> struct shift_right <macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <vec <boolean <long long>, 2> >
							(altivec::andc (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs))); 
					}
			};

		template <typename T, std::size_t n> struct shift_right <macstl::vec <stdext::complex <T>, n> >;
		

		// absolute

		template <typename T, std::size_t n> struct absolute <macstl::vec <T, n> >:
			public macstl::altivec::abs_function <macstl::vec <T, n> >
			{
			};
			
		template <> struct absolute <macstl::vec <unsigned char, 16> >;
		template <> struct absolute <macstl::vec <unsigned short, 8> >;
		template <> struct absolute <macstl::vec <unsigned int, 4> >;
		template <typename T, std::size_t n> struct absolute <macstl::vec <stdext::complex <T>, n> >;	// need to define later
		
		template <typename T, std::size_t n> struct absolute <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						return lhs;
					}
			};
			
		// cosine

		template <> struct cosine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;
				
				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
						
						const vec <float, 4> lhs_n = altivec::floor (
							altivec::madd (lhs,
								vec <float, 4>::fill <0x3EA2F983U> (),	// 1/pi
								zero));
						const vec <float, 4> lhs_n1 = altivec::add (lhs_n, vec <float, 4>::fill <0x3F000000U> ());
						const vec <float, 4> lhs_sin = altivec::impl::sine_n (lhs, lhs_n1);

						return
							altivec::sel (
								lhs_sin,
								altivec::vxor (lhs_sin, zero),	// if lhs_n is even, then flip the sign
								altivec::cmpeq (
									altivec::vand (altivec::cts <0> (lhs_n), vec <int, 4>::fill <1> ()),
									vec <int, 4>::fill <0> ()));
								
					}	
			};
			
		// exponent
		template <> struct exponent <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
													
						// split lhs into integer and fractional parts [0, +ln2]
						const vec <float, 4> lhs_by_ln2 = altivec::madd (lhs, vec <float, 4>::fill <0x3FB8AA3BU> (), zero);		// 1/ln(2)
						const vec <float, 4> lhs_int = altivec::floor (lhs_by_ln2);
						const vec <float, 4> lhs_frac = 
							altivec::madd (
								lhs_int, vec <float, 4>::fill <0xB377D1CFU> (),	// minus second 24 bits of ln(2)
								altivec::madd (
									lhs_int, vec <float, 4>::fill <0xBF317217U> (), lhs));	// minus first 24 bits of ln(2)
							
						// use Horner's rule on a degree-6 minimax polynomial of the fractional part
						const vec <float, 4> lhs_frac_exp =
							altivec::madd (
								altivec::madd (
									altivec::madd (
										altivec::madd (
											altivec::madd (
												altivec::madd (
													lhs_frac, vec <float, 4>::fill <0x3B003E16U> (), // 0.00195682552652430140353293184891 x^6
													vec <float, 4>::fill <0x3BFEC2B1U> ()),			// 0.00777467380338161389689207265976 x^5
												lhs_frac, vec <float, 4>::fill <0x3D2BBE74U> ()),	// 0.0419296764466847981348619399182 x^4
											lhs_frac, vec <float, 4>::fill <0x3E2A9A52U> ()),		// 0.166604308879848761318886951003 x^3
										lhs_frac, vec <float, 4>::fill <0x3F000074U> ()),			// 0.500006929532678917196283309815 x^2
									lhs_frac, vec <float, 4>::fill <0x3F7FFFFBU> ()),				// 0.999999716194003701324519731142 x
								lhs_frac, vec <float, 4>::fill <0x3F800000U> ());					// 1.00000000185580021465272157828
						
						// use exponent estimate on the integer part, which should be accurate according to Altivec spec
						const vec <float, 4> lhs_int_exp = altivec::expte (lhs_int);
						
						return altivec::sel (
							altivec::madd (lhs_int_exp, lhs_frac_exp, zero),
							lhs_int_exp,
							// if exp would be +0 or +inf, use that directly instead of multiplying since a nan might otherwise result
							altivec::vor (
								altivec::cmple (lhs, vec <float, 4>::fill <0xC2CFF1B5U> ()),		// smallest x such that exp(x) = 0
								altivec::cmpeq (lhs, vec <float, 4>::fill <0x7F800000U> ())));	// +inf
					}
			};

		template <> struct exponent2 <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
													
						// split lhs into integer and fractional parts [0, 1]
						const vec <float, 4> lhs_int = altivec::floor (lhs);
						const vec <float, 4> lhs_frac = altivec::sub (lhs, lhs_int);
												
						// use Horner's rule on a degree-6 minimax polynomial of the fractional part
						const vec <float, 4> lhs_frac_exp =
							altivec::madd (
								altivec::madd (
									altivec::madd (
										altivec::madd (
											altivec::madd (
												altivec::madd (
													lhs_frac, vec <float, 4>::fill <0x3963908CU> (), // 0.000217022554601006748641498598969 x^6
													vec <float, 4>::fill <0x3AA30CAAU> ()),			// 0.00124396878272283273818119486344 x^5
												lhs_frac, vec <float, 4>::fill <0x3C1E9400U> ()),	// 0.00967884099612727763162995487637 x^4
											lhs_frac, vec <float, 4>::fill <0x3D634280U> ()),		// 0.0554833419845677471704726400130 x^3
										lhs_frac, vec <float, 4>::fill <0x3E75FECFU> ()),			// 0.240229836273961342768861150779 x^2
									lhs_frac, vec <float, 4>::fill <0x3F317215U> ()),				// 0.693146983840619148984048826026 x
								lhs_frac, vec <float, 4>::fill <0x3F800000U> ());					// 1.00000000185580021465272157828
						
						// use exponent estimate on the integer part, which should be accurate according to Altivec spec
						const vec <float, 4> lhs_int_exp = altivec::expte (lhs_int);
						
						return altivec::sel (
							altivec::madd (lhs_int_exp, lhs_frac_exp, zero),
							lhs_int_exp,
							// if exp would be +0 or +inf, use that directly instead of multiplying since a nan might otherwise result
							altivec::vor (
								altivec::cmple (lhs, vec <float, 4>::fill <0xC315FFFFU> ()),		// smallest x such that exp2(x) = 0
								altivec::cmpeq (lhs, vec <float, 4>::fill <0x7F800000U> ())));	// +inf
					}
			};

		// logarithm

		template <> struct logarithm <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0f
						const vec <float, 4> one = vec <float, 4>::fill <0x3F800000U> ();	// 1.0f
						const vec <float, 4> inf = vec <float, 4>::fill <0x7F800000U> ();	// +inf
						
						const vec <unsigned int, 4> exponent_mask = vec <unsigned int, 4>::fill <0x7F800000U> ();	// bit mask for IEEE 754 exponent

						// if denormal, scale the lhs by 2^23 which converts the smallest denormal into the smallest normal
						const vec <boolean <int>, 4> denormal =
							altivec::cmpeq (
								altivec::cmpb (lhs, vec <float, 4>::fill <0x007FFFFFU> ()),
								vec <int, 4>::fill <0> ());
						const vec <float, 4> scaled_lhs = altivec::sel (lhs, altivec::madd (lhs, vec <float, 4>::fill <0x4B000000U> (), zero), denormal);

						// mantissa is [1.0, 1.5), exponent base is 0; mantissa is [1.5, 2.0), exponent base is -1 (remaps mantissa to [.75, 1.0))
						const vec <int, 4> exponent_base =
							altivec::sub (
								data_cast <vec <int, 4> > (one),
								altivec::sl (
									altivec::vand (data_cast <vec <int, 4> > (scaled_lhs), vec <int, 4>::fill <0x00400000U> ()),
									vec <unsigned int, 4>::fill <1> ()));
						
						// convert the masked out exponent back to a float, correcting for lhs == -ve, NAN or +/-0
						// this results in a base-2 logarithm of the exponent value
						// NOTE: all calculations occur outside of VFP, so can be interleaved with mantissa log calculation
						const vec <int, 4> exponent = altivec::sub (
							data_cast <vec <int, 4> > (altivec::vand (scaled_lhs, data_cast <vec <float, 4> > (exponent_mask))),
							exponent_base);
						const vec <float, 4> exponent_log_no_inf =
							altivec::sel (
								vec <float, 4>::fill <0x7FC00000U> (),			
								altivec::sel (
									altivec::ctf <23> (
										altivec::sel (						// exponent scaled if denormal
											exponent,
											altivec::sub (exponent, vec <int, 4>::fill <0x0B800000U> ()),
											denormal)),
									vec <float, 4>::fill <0xFF800000U> (),		// -inf
									altivec::cmpeq (lhs, zero)),				// log (0) or log (-0) == -inf
								altivec::cmpge (lhs, zero));					// log (-ve) or log (NAN) == NAN
						
						const vec <float, 4> exponent_log =
						#if __FINITE_MATH_ONLY__
							exponent_log_no_inf;
						#else
							altivec::sel (
								exponent_log_no_inf,
								inf,									
								altivec::cmpeq (lhs, inf));				// log (+inf) == +inf
						#endif
						
						// Horner's rule on a minimax polynomial of degree 2,3 for ln(x)/(x-1) on x in [.75, 1.5)
						// NOTE: numerator and denominator are independent, so a good scheduler should be able to interleave their calculations for pipelining
						// NOTE: we use divide_normal since we can be sure the denominator is always normal
						const vec <float, 4> mantissa = altivec::sel (scaled_lhs, data_cast <vec <float, 4> > (exponent_base), exponent_mask);
						const vec <float, 4> mantissa_log =
							altivec::impl::divide_normal (
								altivec::madd (													// numerator polynomial * (x-1)
									altivec::madd (	
										altivec::madd (
											mantissa, vec <float, 4>::fill <0x404D3311U> (),		// 3.20624188116494258282979643094 x^2
											vec <float, 4>::fill <0x413DCC4AU> ()),				// 11.8623754244055151556763131910 x
										mantissa, vec <float, 4>::fill <0x40684317U> ()),		// 3.62909478362961322327103772332
									altivec::sub (mantissa, one),								// x-1
									zero),
								altivec::madd (													// denominator polynomial
									altivec::madd (
										altivec::madd (
											mantissa, vec <float, 4>::fill <0x3F5C0BD7U> (),		// 0.859555683739559800917799543335 x^3
											vec <float, 4>::fill <0x41034F68U> ()),				// 8.20688632350085657541581455421 x^2
										mantissa, vec <float, 4>::fill <0x410A19AEU> ()),		// 8.63126989781522129158072963582 x
									mantissa, one));												// 1

						// recompose the result, since log (mantissa * exponent) = log (mantissa) + log (exponent)
						return 
							altivec::madd (
								exponent_log,
								vec <float, 4>::fill <0x3F317218U> (),	// ln(2)
								mantissa_log);
					}
			};

		template <> struct logarithm2 <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0f
						const vec <float, 4> one = vec <float, 4>::fill <0x3F800000U> ();	// 1.0f
						const vec <float, 4> inf = vec <float, 4>::fill <0x7F800000U> ();	// +inf
						
						const vec <unsigned int, 4> exponent_mask = vec <unsigned int, 4>::fill <0x7F800000U> ();	// bit mask for IEEE 754 exponent

						// if denormal, scale the lhs by 2^23 which converts the smallest denormal into the smallest normal
						const vec <boolean <int>, 4> denormal =
							altivec::cmpeq (
								altivec::cmpb (lhs, vec <float, 4>::fill <0x007FFFFFU> ()),
								vec <int, 4>::fill <0> ());
						const vec <float, 4> scaled_lhs = altivec::sel (lhs, altivec::madd (lhs, vec <float, 4>::fill <0x4B000000U> (), zero), denormal);

						// mantissa is [1.0, 1.5), exponent base is 0; mantissa is [1.5, 2.0), exponent base is -1 (remaps mantissa to [.75, 1.0))
						const vec <int, 4> exponent_base =
							altivec::sub (
								data_cast <vec <int, 4> > (one),
								altivec::sl (
									altivec::vand (data_cast <vec <int, 4> > (scaled_lhs), vec <int, 4>::fill <0x00400000U> ()),
									vec <unsigned int, 4>::fill <1> ()));
						
						// convert the masked out exponent back to a float, correcting for lhs == -ve, NAN or +/-0
						// this results in a base-2 logarithm of the exponent value
						// NOTE: all calculations occur outside of VFP, so can be interleaved with mantissa log calculation
						const vec <int, 4> exponent = altivec::sub (
							data_cast <vec <int, 4> > (altivec::vand (scaled_lhs, data_cast <vec <float, 4> > (exponent_mask))),
							exponent_base);
						const vec <float, 4> exponent_log_no_inf =
							altivec::sel (
								vec <float, 4>::fill <0x7FC00000U> (),			
								altivec::sel (
									altivec::ctf <23> (
										altivec::sel (						// exponent scaled if denormal
											exponent,
											altivec::sub (exponent, vec <int, 4>::fill <0x0B800000U> ()),
											denormal)),
									vec <float, 4>::fill <0xFF800000U> (),		
									altivec::cmpeq (lhs, zero)),				// log (0) or log (-0) == -inf
								altivec::cmpge (lhs, zero));					// log (-ve) or log (NAN) == NAN

						
						const vec <float, 4> exponent_log =
						#if __FINITE_MATH_ONLY__
							exponent_log_no_inf;
						#else
							altivec::sel (
								exponent_log_no_inf,
								inf,									
								altivec::cmpeq (lhs, inf));				// log (+inf) == +inf
						#endif
						
						// Horner's rule on a minimax polynomial of degree 2,3 for ln(x)/(x-1) on x in [.75, 1.5)
						// NOTE: numerator and denominator are independent, so a good scheduler should be able to interleave their calculations for pipelining
						// NOTE: we use divide_normal since we can be sure the denominator is always normal
						const vec <float, 4> mantissa = altivec::sel (scaled_lhs, data_cast <vec <float, 4> > (exponent_base), exponent_mask);
						const vec <float, 4> mantissa_log =
							altivec::impl::divide_normal (
								altivec::madd (													// numerator polynomial * (x-1)
									altivec::madd (	
										altivec::madd (
											mantissa, vec <float, 4>::fill <0x40940528U> (),		// 5.23567704725844865881904827716 x^2
											vec <float, 4>::fill <0x4188E90BU> ()),				// 17.1137901979529493404012042551 x
										mantissa, vec <float, 4>::fill <0x40A78AABU> ()),		// 5.23567704725844865881904827716
									altivec::sub (mantissa, one),								// x-1
									zero),
								altivec::madd (													// denominator polynomial
									altivec::madd (
										altivec::madd (
											mantissa, vec <float, 4>::fill <0x3F5C0BD7U> (),		// 0.859555683739559800917799540876 x^3
											vec <float, 4>::fill <0x41034F68U> ()),				// 8.20688632350085657541581453883 x^2
										mantissa, vec <float, 4>::fill <0x410A19AEU> ()),		// 8.63126989781522129158072962789 x
									mantissa, one));												// 1
									
						// recompose the result, since log (mantissa * exponent) = log (mantissa) + log (exponent)
						return 
							altivec::add (exponent_log, mantissa_log);
					}
			};
			
		// multiplies_high
				
		template <> struct multiplies_high <macstl::vec <unsigned char, 16> >
			{
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <unsigned char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::perm (
							altivec::mule (lhs, rhs),
							altivec::mulo (lhs, rhs),
							vec <unsigned char, 16>::set <0x00U, 0x10U, 0x02U, 0x12U, 0x04U, 0x14U, 0x06U, 0x16U, 0x08U, 0x18U, 0x0AU, 0x1AU, 0x0CU, 0x1CU, 0x0EU, 0x1EU> ())); 
					}
			};

		template <> struct multiplies_high <macstl::vec <signed char, 16> >
			{
				typedef macstl::vec <signed char, 16> first_argument_type;
				typedef macstl::vec <signed char, 16> second_argument_type;
				typedef macstl::vec <signed char, 16> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::perm (
							altivec::mule (lhs, rhs),
							altivec::mulo (lhs, rhs),
							vec <unsigned char, 16>::set <0x00U, 0x10U, 0x02U, 0x12U, 0x04U, 0x14U, 0x06U, 0x16U, 0x08U, 0x18U, 0x0AU, 0x1AU, 0x0CU, 0x1CU, 0x0EU, 0x1EU> ())); 
					}
			};

		template <> struct multiplies_high <macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						return data_cast <result_type> (altivec::perm (
							altivec::mule (lhs, rhs),
							altivec::mulo (lhs, rhs),
							vec <unsigned char, 16>::set <0x00U, 0x01U, 0x10U, 0x11U, 0x04U, 0x05U, 0x14U, 0x15U, 0x08U, 0x09U, 0x18U, 0x19U, 0x0CU, 0x0DU, 0x1CU, 0x1DU> ())); 
					}
			};
			
		template <> struct multiplies_high <macstl::vec <short, 8> >
			{
				typedef macstl::vec <short, 8> first_argument_type;
				typedef macstl::vec <short, 8> second_argument_type;
				typedef macstl::vec <short, 8> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						using namespace macstl;
						
						return data_cast <result_type> (altivec::perm (
							altivec::mule (lhs, rhs),
							altivec::mulo (lhs, rhs),
							vec <unsigned char, 16>::set <0x00U, 0x01U, 0x10U, 0x11U, 0x04U, 0x05U, 0x14U, 0x15U, 0x08U, 0x09U, 0x18U, 0x19U, 0x0CU, 0x0DU, 0x1CU, 0x1DU> ())); 
 					}
			};
			
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
						
		// multiplies_plus

		template <> struct multiplies_plus <macstl::vec <unsigned short, 8> >:
			public macstl::altivec::mladd_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};

		template <> struct multiplies_plus <macstl::vec <short, 8> >:
			public macstl::altivec::mladd_function <macstl::vec <short, 8>, macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		template <> struct multiplies_plus <macstl::vec <float, 4> >:
			public macstl::altivec::madd_function <macstl::vec <float, 4>, macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct multiplies_plus <macstl::vec <stdext::complex <float>, 2> >
			{
				typedef macstl::vec <stdext::complex <float>, 2> first_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> second_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> third_argument_type;
				typedef macstl::vec <stdext::complex <float>, 2> result_type;
				
				result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs) const
					{
						using namespace macstl;
						
						return altivec::impl::complex_fma (lhs, mhs, rhs);
					}
			};


		// power
		
		template <> struct power <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();
						
						const vec <float, 4> rhs_int = altivec::trunc (rhs);
						const vec <float, 4> rhs_half = altivec::madd (rhs_int, vec <float, 4>::fill <0x3F000000U> (), zero);
						
						const vec <float, 4> lhs_power_rhs = exp2 (altivec::madd (log2 (altivec::andc (lhs, zero)), rhs, zero));
						return altivec::sel (
							altivec::sel (
								altivec::vxor (lhs_power_rhs, zero),
								lhs_power_rhs,
								altivec::cmpeq (rhs_half, altivec::trunc (rhs_half))),
							vec <float, 4>::fill <0x7FFFFFFFU> (),	// nan
							altivec::andc (altivec::cmple (lhs, zero), altivec::cmpeq (rhs, rhs_int)));
							
						/*
						std::cout << "lhs = " << lhs << "; log2 = " << log2 (lhs) << "\n";
						std::cout << "x = " << altivec::madd (log2 (lhs), rhs, vec <float, 4>::fill <0x80000000U> ()) << "\n";
						std::cout << "exp2 = " << exp2 (vec <float, 4> ((__vector float) (1.0/0.0))) << "\n";
						return exp2 (altivec::madd (log2 (lhs), rhs, vec <float, 4>::fill <0x80000000U> ()));
						*/
					}
			};
			
		// sine

		template <> struct sine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
						
						// force lhs to [-pi/2, pi/2]
						const vec <float, 4> lhs_n = altivec::round (
							altivec::madd (lhs,
								vec <float, 4>::fill <0x3EA2F983U> (),	// 1/pi
								zero));
								
						const vec <float, 4> lhs_sin = altivec::impl::sine_n (lhs, lhs_n);
								
						return
							altivec::sel (
								altivec::vxor (lhs_sin, zero),	// if lhs_n is odd, then flip the sign
								lhs_sin,
								altivec::andc (
									altivec::cmpeq (
										altivec::vand (altivec::cts <0> (lhs_n), vec <int, 4>::fill <1> ()),
										vec <int, 4>::fill <0> ()),
									altivec::cmpeq (
										data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (zero))));
					}	
					
			};

		// square_root
		
		template <> struct square_root <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0f
						
						const vec <float, 4> estimate = altivec::rsqrte (lhs);
						const vec <float, 4> x_estimate = altivec::madd (lhs, estimate, zero);
						
						return altivec::sel (
							altivec::madd (
								altivec::nmsub (x_estimate, estimate, vec <float, 4>::fill <0x3F800000U> ()),	// 1.0f
								altivec::madd (x_estimate, vec <float, 4>::fill <0x3F000000U> (), zero),	// 0.5f
								x_estimate),
							lhs,
							// if +/-0 or +inf, just use lhs directly as result
							#if __FINITE_MATH_ONLY__
							altivec::cmpeq (
								lhs, vec <float, 4>::fill <0> ())
							#else
							altivec::vor (
								altivec::cmpeq (
									lhs, vec <float, 4>::fill <0> ()),
								altivec::cmpeq (
									lhs, vec <float, 4>::fill <0x7F800000U> ()))
							#endif
							);	// +inf
					}
			};

		template <> struct tangent <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						
						const vec <float, 4> zero = vec <float, 4>::fill <0x80000000U> ();	// -0.0
						const vec <float, 4> one = vec <float, 4>::fill <0x3F800000U> ();	// 1.0
												
						// force lhs to [-pi/4, pi/4]
						const vec <float, 4> lhs_n = altivec::round (
							altivec::madd (lhs,
								vec <float, 4>::fill <0x3F22F983U> (),	// 2/Pi
								zero));
						const vec <float, 4> lhs_reduced =
							altivec::madd (
								lhs_n, vec <float, 4>::fill <0xA7C234C4U> (), // minus third 24 bits of Pi/2
								altivec::madd (
									lhs_n, vec <float, 4>::fill <0xB3A22168U> (),	// minus second 24 bits of Pi/2
									altivec::madd (
										lhs_n, vec <float, 4>::fill <0xBFC90FDAU> (), // minus first 24 bits of Pi/2
										lhs)));

						// minimax polynomial of degree 3,4 for tan(x) on [0,Pi/4] -- this also works on [-Pi/4,0]
						// NOTE: we used a minimax polynomial of degree 1,2 for tan(sqrt(x))/sqrt(x) on [0, (Pi^2)/16] and expanded
						const vec <float, 4> lhs_square = altivec::madd (lhs_reduced, lhs_reduced, zero);						
						const vec <float, 4> lhs_top =
							altivec::madd (
								altivec::madd (
									lhs_square, vec <float, 4>::fill <0xBDC433B8U> (),	// -0.0958017695746054481568783178326 x^3
									one),												// 0.999999985836114771076206239598 x
								lhs_reduced, zero);
						const vec <float, 4> lhs_bottom =
							altivec::madd (
								altivec::madd (
									lhs_square, vec <float, 4>::fill <0x3C1F3374U> (),	// 0.00971685740156122723678148091232 x^4
									vec <float, 4>::fill <0xBEDBB7AFU> ()),				// -0.429135774643039347827850693821 x^2
								lhs_square, one);										// 1
							
						// if even n, need to use -1/p(x) as result
						const vec <boolean <int>, 4> even =
							altivec::cmpeq (
								altivec::vand (altivec::cts <0> (lhs_n), vec <int, 4>::fill <1> ()),
								vec <int, 4>::fill <0> ());
						return
							altivec::sel (
								altivec::sel (altivec::vxor (lhs_bottom, zero), lhs_top, even)
								/
								altivec::sel (lhs_top, lhs_bottom, even),
								zero,
								altivec::cmpeq (data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (zero)));
					}	
					
			};
	
	}
	
#endif
