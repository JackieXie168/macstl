/*
 *  valarray_mmx.h
 *  macstl
 *
 *  Created by Glen Low on Jan 5 2005.
 *
 *  Copyright (c) 2005 Pixelglow Software, all rights reserved.
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

#ifndef MACSTL_IMPL_VALARRAY_MMX_H
#define MACSTL_IMPL_VALARRAY_MMX_H

namespace stdext
	{
		namespace impl
			{
				#ifdef __SSE__
				template <> struct chunk <float>							{ typedef macstl::vec <float, 4> type; };
				#endif
				
				#ifdef __SSE2__
				template <> struct chunk <unsigned char>					{ typedef macstl::vec <unsigned char, 16> type; };
				template <> struct chunk <signed char>						{ typedef macstl::vec <signed char, 16> type; };
				template <> struct chunk <unsigned short>					{ typedef macstl::vec <unsigned short, 8> type; };
				template <> struct chunk <short>							{ typedef macstl::vec <short, 8> type; };
				template <> struct chunk <unsigned int>						{ typedef macstl::vec <unsigned int, 4> type; };
				template <> struct chunk <int>								{ typedef macstl::vec <int, 4> type; };
				template <> struct chunk <unsigned long long>				{ typedef macstl::vec <unsigned long long, 2> type; };
				template <> struct chunk <long long>						{ typedef macstl::vec <long long, 2> type; };
				template <> struct chunk <double>							{ typedef macstl::vec <double, 2> type; };
				#endif

				template <typename T> class valarray_base <T, typename enable_if <exists <typename array_term <T>::chunk_type>::value>::type>:
					public array_term <T>
					{
						public:
							typedef array_term <T> base;
							typedef typename array_term <T>::chunk_type chunk_type;
							
							/** Constructs with space for @a n elements. */
							valarray_base (std::size_t n)
								{
									// allocate enough bytes to put equivalent of n elements of T, but as aligned chunks
									base::init (
										reinterpret_cast <chunk_type*> (_mm_malloc (sizeof (chunk_type) * ((n + chunk_type::length - 1) / chunk_type::length),
											sizeof (typename chunk <T>::type))),
										n);
								}

							/** Destructs entire array. */
							~valarray_base ()
								{
									_mm_free (base::data_);
								}
					};
			}
	}
#endif