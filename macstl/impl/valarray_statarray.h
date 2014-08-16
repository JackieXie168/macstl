/*
 *  valarray_statarray.h
 *  macstl
 *
 *  Created by Glen Low on Jan 08 2005.
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

#ifndef MACSTL_IMPL_VALARRAY_STATARRAY_H
#define MACSTL_IMPL_VALARRAY_STATARRAY_H

namespace stdext
	{
		namespace impl
			{
				 /// Base for statarray
				 
				 /// @internal
				 /// Partial specializations may
				 /// allocate memory differently e.g. with a different alignment or type, to fulfill chunking
				 /// requirements.
				 ///
				 /// @param	T		The element type.
				 /// @param	Enable	If void, enables a particular specialization

				template <typename T, std::size_t n, typename Enable = void> class statarray_base: public array_term <T>
					{
						protected:
							statarray_base ()
								{
									init (array_, n);
								}

						private:
							T array_ [n];
					};
	
				template <typename T, std::size_t n> class statarray_base <T, n, typename enable_if <exists <typename array_term <T>::chunk_type>::value>::type>:
					public array_term <T>
					{
						public:
							typedef typename array_term <T>::chunk_type chunk_type;
							
							statarray_base ()
								{
									// reserve enough bytes to put equivalent of n elements of T, but as aligned chunks
									init (array_, n);
								}
								
						private:
							chunk_type array_ [(n + chunk_type::length - 1) / chunk_type::length];

					};
				
			}
			
		/// Fixed-size numeric (n-at-a-time) array.
		
		/// This class is similar to stdext::valarray but has a fixed size through a template non-type parameter. This makes the class useful
		/// for auto variables, since it will not touch the heap and thus improve locality of reference and construction speed.
		///
		/// @param	T	The value type, which shall satisfy the following requirements:
		///				- not an abstract class, reference type or cv-qualified type
		///				- if a class, must publicly define: default constructor, copy constructor, destructor and assignment operator
		///				- Default construct + assign == copy construct
		///				- Destruct + copy construct == assign
		///				.
		///				For example, built-in arithmetic types like char, short, int, float, double.
		/// @param	n	The number of elements.
		///
		/// @header	#include <macstl/valarray.h>
		
		template <typename T, std::size_t n> class statarray: public impl::statarray_base <T, n>
			{
				public:
					using impl::array_term <T>::value_type;
					
					/// @name Constructors and Destructors
					
					//@{
					
					/// Constructs an array, each element zero.
					statarray (): impl::statarray_base <T, n> ()
						{
							impl::fill_array (*this, T ());
						}
						
					/// Constructs an array, each element a copy of x.
					statarray (const T& x): impl::statarray_base <T, n> ()
						{
							impl::fill_array (*this, x);
						}
		
					/// Constructs an array with copies of the first b elements from x.
					statarray (const T* x): impl::statarray_base <T, n> ()
						{
							impl::copy_array_ptr (*this, x);
						}
		
					/// Constructs a copy of other array.
					statarray (const statarray& other): impl::statarray_base <T, n> ()
						{
							impl::copy_array (*this, other);
						}
		
					/// Constructs a copy of other term.
					template <typename Term> statarray (const impl::term <T, Term>& other):
						impl::statarray_base <T, n> ()
						{
							impl::copy_array (*this, other.that ());
						}
														
					/// Destructs the array.
					~statarray ()
						{
							impl::destroy_array (*this);
						}
						
					//@}
					
					/// @name Assignments
					
					//@{
					
					/// Assigns the other array.
					statarray& operator= (const statarray& other)
						{
							if (this != &other)
								impl::copy_array (*this, other);
							return *this;
						}
					
					/// Assigns the other term.
					template <typename Expr> statarray& operator= (const impl::term <T, Expr>& other)
						{
							impl::copy_array (*this, other.that ());
							return *this;
						}					

					/// Assigns x to each element.
					statarray& operator= (const T& x)
						{
							impl::fill_array (*this, x);
							return *this;
						}
						
					//@}
			};
	}

#endif