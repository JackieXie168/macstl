/*
 *  valarray_vec.h
 *  macstl
 *
 *  Created by Glen Low on Jan 05 2005.
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

#ifndef MACSTL_IMPL_VALARRAY_VEC_H
#define MACSTL_IMPL_VALARRAY_VEC_H

namespace stdext
	{
		namespace impl
			{
				/// Chunking type.
				
				/// @internal
				/// Template typedef to declare the chunking type corresponding to a scalar type.
				///
				/// @param	T	The scalar type.
				
				template <typename T> struct chunk
					{
						/// The chunking type. The default is the same type, but specializations may change this.
						typedef T type;
					};

				template <typename V> class dechunk_iterator
					{
						public:
							typedef V chunk_type;
							
							typedef typename std::random_access_iterator_tag iterator_category;
							typedef typename chunk_type::value_type value_type; 
							typedef std::ptrdiff_t difference_type;
							typedef const value_type* pointer;
							typedef typename chunk_type::reference reference;
							
							dechunk_iterator (chunk_type* it, std::size_t index): it_ (it), index_ (index)
								{
								}

							dechunk_iterator (const dechunk_iterator <const V>& other): it_ (other.it_), index_ (other.index_)
								{
								}
								
							reference operator* () const
								{
									std::size_t index = index_;
									return it_ [index / chunk_type::length] [index % chunk_type::length];
								}
							
							typename chunk_type::reference operator[] (difference_type n) const
								{
									std::size_t index = n + index_;
									return it_ [index / chunk_type::length] [index % chunk_type::length];
								}
							
							dechunk_iterator& operator++ ()
								{
									++index_;
									return *this;
								}
								
							dechunk_iterator operator++ (int)
								{
									return dechunk_iterator (it_, index_ + 1);
								}
								
							dechunk_iterator& operator+= (difference_type n)
								{
									index_ += n;
									return *this;
								}
		
							dechunk_iterator& operator-- ()
								{
									--index_;
									return *this;
								}
								
							dechunk_iterator operator-- (int)
								{
									return dechunk_iterator (it_, index_ - 1);
								}
								
							dechunk_iterator& operator-= (difference_type n)
								{
									index_ -= n;
									return *this;
								}
								
							friend dechunk_iterator operator+ (const dechunk_iterator& left, difference_type right)
								{
									return dechunk_iterator (left.it_, left.index_ + right);
								}
		
							friend dechunk_iterator operator+ (difference_type left, const dechunk_iterator& right)
								{
									return dechunk_iterator (right.it_, left + right.index_);
								}
		
							friend dechunk_iterator operator- (const dechunk_iterator& left, difference_type right)
								{
									return dechunk_iterator (left.it_, left.index_ - right);
								}

							friend difference_type operator- (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.index_ - right.index_;
								}
								
							friend bool operator== (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.it_ == right.it_ && left.index_ == right.index_;
								}
								
							friend bool operator!= (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.it_ != right.it_ || left.index_ != right.index_;
								}
		
							friend bool operator< (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.index_ < right.index_;
								}
									
						private:
							chunk_type* it_;
							std::size_t index_;
					};

				template <typename V> class dechunk_iterator <const V>
					{
						public:
							typedef const V chunk_type;
							
							typedef typename std::random_access_iterator_tag iterator_category;
							typedef typename chunk_type::value_type value_type;
							typedef std::ptrdiff_t difference_type;
							typedef const value_type* pointer;
							typedef value_type reference;

							dechunk_iterator (const chunk_type* it, std::size_t index): it_ (it), index_ (index)
								{
								}
								
							value_type operator* () const
								{
									std::size_t index = index_;
									return it_ [index / chunk_type::length] [index % chunk_type::length];
								}
							
							value_type operator[] (difference_type n) const
								{
									std::size_t index = n + index_;
									return it_ [index / chunk_type::length] [index % chunk_type::length];
								}
							
							dechunk_iterator& operator++ ()
								{
									++index_;
									return *this;
								}
								
							dechunk_iterator operator++ (int)
								{
									return dechunk_iterator (it_, index_ + 1);
								}
								
							dechunk_iterator& operator+= (difference_type n)
								{
									index_ += n;
									return *this;
								}
		
							dechunk_iterator& operator-- ()
								{
									--index_;
									return *this;
								}
								
							dechunk_iterator operator-- (int)
								{
									return dechunk_iterator (it_, index_ - 1);
								}
								
							dechunk_iterator& operator-= (difference_type n)
								{
									index_ -= n;
									return *this;
								}
								
							friend dechunk_iterator operator+ (const dechunk_iterator& left, difference_type right)
								{
									return dechunk_iterator (left.it_, left.index_ + right);
								}
		
							friend dechunk_iterator operator+ (difference_type left, const dechunk_iterator& right)
								{
									return dechunk_iterator (right.it_, left + right.index_);
								}
		
							friend dechunk_iterator operator- (const dechunk_iterator& left, difference_type right)
								{
									return dechunk_iterator (left.it_, left.index_ - right);
								}
							
							friend difference_type operator- (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.index_ - right.index_;
								}
								
							friend bool operator== (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.it_ == right.it_ && left.index_ == right.index_;
								}
								
							friend bool operator!= (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.it_ != right.it_ || left.index_ != right.index_;
								}
		
							friend bool operator< (const dechunk_iterator& left, const dechunk_iterator& right)
								{
									return left.index_ < right.index_;
								}
								
							friend class dechunk_iterator <V>;
		
						private:
							const chunk_type* it_;
							std::size_t index_;
					};
					
				template <typename T> class array_term <T, typename enable_if <is_same <typename chunk <T>::type, T>::value == 0>::type>:
					public term <T, array_term <T> >
					{
						public:
							typedef T value_type;
							typedef typename chunk <T>::type chunk_type;
							
							using term <T, array_term <T> >::operator[];
														
							typedef dechunk_iterator <const chunk_type> const_iterator;
							typedef dechunk_iterator <chunk_type> iterator;
							typedef typename chunk_type::reference reference;
							
							value_type operator[] (std::size_t n) const
								{
									return static_cast <const chunk_type*> (data_) [n / chunk_type::length] [n % chunk_type::length];
								}
							
							reference operator[] (std::size_t n)
								{
									return data_ [n / chunk_type::length] [n % chunk_type::length];
								}							

							const_iterator begin () const	{ return const_iterator (data_, 0); }							
							iterator begin ()				{ return iterator (data_, 0); }

							typedef const chunk_type* const_chunk_iterator;
							typedef chunk_type* chunk_iterator;
							
							std::size_t size () const			{ return size_; }

							const_chunk_iterator chunk_begin () const	{ return data_; }
							chunk_iterator chunk_begin ()				{ return data_; }
							
						protected:
							chunk_type* data_;
							std::size_t size_;
							
							void init (chunk_type* data, std::size_t size)
								{
									data_ = data;
									size_ = size;
								}
		
							void swap (array_term& other)
								{
									std::swap (data_, other.data_);
									std::swap (size_, other.size_);
								}
					};
					
				#if 0

				template <std::size_t n> struct boolean_of;

				template <> struct boolean_of <1> { typedef macstl::vec <macstl::boolean <char> > type; };
				template <> struct boolean_of <2> { typedef macstl::vec <macstl::boolean <short> > type; };
				template <> struct boolean_of <4> { typedef macstl::vec <macstl::boolean <int> > type; };
				template <> struct boolean_of <8> { typedef macstl::vec <macstl::boolean <long long> > type; };
				
				// boolean specializations: (1) for C++ bool, it is chunkable but not const-chunkable
				template <> class array_term <bool, void>: public term <bool, array_term <bool> >
					{
						public:
							typedef bool value_type;					/**< The element type, see std::valarray. */
							typedef boolean_of <sizeof (bool)>::type chunk_type;
							
							using term <bool, array_term <bool> >::operator[];

							typedef dechunk_iterator <const chunk_type> const_iterator;		/**< Constant iterator into the array. */
							typedef dechunk_iterator <chunk_type> iterator;					/**< Mutable iterator into the array. */
							typedef chunk_type::reference reference;

							/** Returns the element at index @a n. */
							value_type operator[] (std::size_t n) const
								{
									return data_of (static_cast <const chunk_type*> (data_) [n / chunk_type::length] [n % chunk_type::length]);
								}
							
							/** Returns a reference to the element at index @a n. */
							chunk_type::reference operator[] (std::size_t n)
								{ 
									return data_ [n / chunk_type::length] [n % chunk_type::length];
								}
								
							const_iterator begin () const	{ return const_iterator (data_, 0); }
							iterator begin ()				{ return iterator (data_, 0); }
													
							typedef chunk_type* chunk_iterator;
							
							/** Returns the number of elements. */
							std::size_t size () const			{ return size_; }

							chunk_iterator chunk_begin ()				{ return data_; }
							
						protected:
							chunk_type* data_;
							std::size_t size_;
							
							void init (chunk_type* data, std::size_t size)
								{
									data_ = data;
									size_ = size;
								}
		
							void swap (array_term& other)
								{
									std::swap (data_, other.data_);
									std::swap (size_, other.size_);
								}
					};																															
				#endif
			}
	}
	
#if defined(__VEC__)
#include "valarray_altivec.h"
#else
#if defined(__MMX__) || defined(__SSE__) || defined(__SSE2__)
#include "valarray_mmx.h"
#endif
#endif

#endif

