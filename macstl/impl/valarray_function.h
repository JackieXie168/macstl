/*
 *  valarray_function.h
 *  macstl
 *
 *  Created by Glen Low on Jun 23 2003.
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
 *  While it is an open-source license, the RPL you from keeping your
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

#ifndef MACSTL_IMPL_VALARRAY_FUNCTION_H
#define MACSTL_IMPL_VALARRAY_FUNCTION_H

namespace stdext
	{
		namespace impl
			{
				template <typename T, typename Enable = void> class literal_iterator
					{
						public:
							typedef typename std::random_access_iterator_tag iterator_category;
							typedef T value_type; 
							typedef std::ptrdiff_t difference_type;
							typedef const value_type* pointer;
							typedef value_type reference;
							
							literal_iterator (const value_type& literal, difference_type index): constant_ (literal), index_ (index)
								{
								}
								
							value_type operator* () const				{ return constant_; }
							value_type operator[] (std::ptrdiff_t) const	{ return constant_; }

							literal_iterator& operator++ ()					{ ++index_; return *this; }
							literal_iterator operator++ (int)					{ return literal_iterator (constant_, index_++); }
							literal_iterator& operator+= (difference_type n)	{ index_ += n; return *this; }
		
							literal_iterator& operator-- ()					{ --index_; return *this; }
							literal_iterator operator-- (int)					{ return literal_iterator (constant_, index_--); }
							literal_iterator& operator-= (difference_type n)	{ index_ -= n; return *this; }
								
							friend literal_iterator operator+ (const literal_iterator& left, difference_type right)
								{
									return literal_iterator (left.constant_, right);
								}
		
							friend literal_iterator operator+ (difference_type left, const literal_iterator& right)
								{
									return literal_iterator (right.constant_, left + right.index_);
								}
		
							friend literal_iterator operator- (const literal_iterator& left, difference_type right)
								{
									return literal_iterator (left.constant_, left.index_ - right);
								}
							
							friend difference_type operator- (const literal_iterator& left, const literal_iterator& right)
								{
									return left.index_ - right.index_;
								}
								
							friend bool operator== (const literal_iterator& left, const literal_iterator& right)
								{
									return left.index_ == right.index_;
								}
								
							friend bool operator!= (const literal_iterator& left, const literal_iterator& right)
								{
									return left.index_ != right.index_;
								}
		
							friend bool operator< (const literal_iterator& left, const literal_iterator& right)
								{
									return left.index_ < right.index_;
								}
								
						protected:
							const value_type constant_;
							std::ptrdiff_t index_;
					};


				template <typename T, typename Enable = void> class chunked_scalar_iterator
					{
						public:
							typedef typename std::random_access_iterator_tag iterator_category;
							typedef T value_type; 
							typedef std::ptrdiff_t difference_type;
							typedef const value_type* pointer;
							typedef value_type reference;
							
							chunked_scalar_iterator (const value_type* literal, difference_type index): constant_ (literal), index_ (index)
								{
								}
								
							value_type operator* () const				{ return *constant_; }
							value_type operator[] (std::ptrdiff_t) const		{ return *constant_; }

							chunked_scalar_iterator& operator++ ()					{ ++index_; return *this; }
							chunked_scalar_iterator operator++ (int)					{ return chunked_scalar_iterator (constant_, index_++); }
							chunked_scalar_iterator& operator+= (difference_type n)	{ index_ += n; return *this; }
		
							chunked_scalar_iterator& operator-- ()					{ --index_; return *this; }
							chunked_scalar_iterator operator-- (int)					{ return chunked_scalar_iterator (constant_, index_--); }
							chunked_scalar_iterator& operator-= (difference_type n)	{ index_ -= n; return *this; }
								
							friend chunked_scalar_iterator operator+ (const chunked_scalar_iterator& left, difference_type right)
								{
									return chunked_scalar_iterator (left.constant_, right);
								}
		
							friend chunked_scalar_iterator operator+ (difference_type left, const chunked_scalar_iterator& right)
								{
									return chunked_scalar_iterator (right.constant_, left + right.index_);
								}
		
							friend chunked_scalar_iterator operator- (const chunked_scalar_iterator& left, difference_type right)
								{
									return chunked_scalar_iterator (left.constant_, left.index_ - right);
								}
							
							friend difference_type operator- (const chunked_scalar_iterator& left, const chunked_scalar_iterator& right)
								{
									return left.index_ - right.index_;
								}
								
							friend bool operator== (const chunked_scalar_iterator& left, const chunked_scalar_iterator& right)
								{
									return left.index_ == right.index_;
								}
								
							friend bool operator!= (const chunked_scalar_iterator& left, const chunked_scalar_iterator& right)
								{
									return left.index_ != right.index_;
								}
		
							friend bool operator< (const chunked_scalar_iterator& left, const chunked_scalar_iterator& right)
								{
									return left.index_ < right.index_;
								}
								
						protected:
							const value_type* const constant_;
							std::ptrdiff_t index_;
					};

				/// Base for literal term.
				
				/// @internal
				/// This base defines all common types and functions for both chunked and unchunked literal terms.
				///
				/// @param	Term	The subterm type.
				///
				/// @note	This term does not actually store its subterm, but uses the subterm type to figure out how to chunk the single value.

				template <typename Term> class literal_term_base
					{
						public:
							/// Element value type.
							typedef typename Term::value_type value_type;
							
							/// Iterator to access elements.
							typedef literal_iterator <value_type> const_iterator;
							typedef literal_iterator <value_type> iterator;
							
							typedef value_type reference;

							/// Gets the element at the index. Since this is a literal, all elements are the same.
							value_type operator[] (std::size_t) const	{ return constant_; }
							
							/// Gets the number of elements. Same as the subterm size.
							std::size_t size () const					{ return size_; }
								
							/// Gets an iterator to the first element.
							const_iterator begin () const
								{
									return const_iterator (constant_, 0);
								}

						protected:
							const value_type constant_;
							const std::size_t size_;

							literal_term_base (const value_type& literal, const Term& term):
								constant_ (literal), size_ (term.size ())
								{
								}
					};

				/// Expression template literal term.
				
				/// @internal
				/// This leaf term stores a single value. A literal term is const chunkable if the subterm is const chunkable. Such terms are declared as
				/// partial specializations with additional members.
				///
				/// @param	Term	The subterm type.
				/// @param	Enable	If void, enables a particular template specialization.
				///
				/// @note	This term does not actually store its subterm, but uses the subterm type to figure out how to chunk the single value.

				template <typename Term, typename Enable> class literal_term:
					public literal_term_base <Term>,
					public term <typename Term::value_type, literal_term <Term> >
					{
						public:
							/// The base type.
							typedef literal_term_base <Term> base;
							
							/// Constructs from a single value and a subterm.
							literal_term (const typename Term::value_type& literal, Term& term):
								base (literal, term)
								{
								}
	
							using base::operator[];
							using term <typename Term::value_type, literal_term <Term> >::operator[];
					};

				template <typename Term> class literal_term <Term, typename enable_if <exists <typename Term::const_chunk_iterator>::value>::type>:
					public literal_term_base <Term>,
					public term <typename Term::value_type, literal_term <Term> >					
					{
						public:
							typedef literal_term_base <Term> base;

							typedef typename std::iterator_traits <typename Term::const_chunk_iterator>::value_type chunk_type;
							
							typedef chunked_scalar_iterator <chunk_type> const_chunk_iterator;
							
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (&chunked_, 0);
								}
								
							literal_term (const typename Term::value_type& literal, const Term& term):
								base (literal, term),
								chunked_ (chunk_type::fill (literal))
								{
								}
	
							using base::operator[];
							using term <typename Term::value_type, literal_term <Term> >::operator[];
								
						private:
							const chunk_type chunked_;
					};

				template <typename TermIt, template <typename> class UOp, typename Enable = void>
					class unary_iterator_base
					{
						public:
							typedef UOp <typename std::iterator_traits <TermIt>::value_type> operation;
							typedef typename operation::result_type value_type; 
							
							unary_iterator_base (const TermIt& subterm_iter): subterm_iter_ (subterm_iter)
								{
								}
								
							value_type operator* () const
								{
									return operation () (*subterm_iter_);
								}
								
							value_type operator[] (typename std::iterator_traits <TermIt>::difference_type n) const
								{
									return operation () (subterm_iter_ [n]);
								}

						protected:
							TermIt subterm_iter_;
					};

				template <typename TermIt, template <typename> class UOp> class unary_iterator:
					public unary_iterator_base <TermIt, UOp>
					{
						public:
							typedef unary_iterator_base <TermIt, UOp> base;
							
							typedef typename std::iterator_traits <TermIt>::iterator_category iterator_category;
							typedef typename std::iterator_traits <TermIt>::difference_type difference_type;
							typedef const typename base::value_type* pointer;
							typedef typename base::value_type reference;
							
							unary_iterator (const TermIt& subterm_iter): base (subterm_iter)
								{
								}
								
							const TermIt& subterm_iter () const				{ return base::subterm_iter_; }
								
							unary_iterator& operator++ ()					{ ++base::subterm_iter_; return *this; }
							unary_iterator operator++ (int)					{ return unary_iterator (base::subterm_iter_++); }
							unary_iterator& operator+= (difference_type n)	{ base::subterm_iter_ += n; return *this; }
		
							unary_iterator& operator-- ()					{ --base::subterm_iter_; return *this; }
							unary_iterator operator-- (int)					{ return unary_iterator (base::subterm_iter_--); }
							unary_iterator& operator-= (difference_type n)	{ base::subterm_iter_ -= n; return *this; }
								
							friend unary_iterator operator+ (const unary_iterator& left, difference_type right)
								{
									return unary_iterator (left.subterm_iter_ + right);
								}
		
							friend unary_iterator operator+ (difference_type left, const unary_iterator& right)
								{
									return unary_iterator (left + right.subterm_iter_);
								}
		
							friend unary_iterator operator- (const unary_iterator& left, difference_type right)
								{
									return unary_iterator (left.subterm_iter_ - right);
								}
							
							friend difference_type operator- (const unary_iterator& left, const unary_iterator& right)
								{
									return left.subterm_iter_ - right.subterm_iter_;
								}
								
							friend bool operator== (const unary_iterator& left, const unary_iterator& right)
								{
									return left.subterm_iter_ == right.subterm_iter_;
								}
								
							friend bool operator!= (const unary_iterator& left, const unary_iterator& right)
								{
									return left.subterm_iter_ != right.subterm_iter_;
								}
		
							friend bool operator< (const unary_iterator& left, const unary_iterator& right)
								{
									return left.subterm_iter_ < right.subterm_iter_;
								}
					};
									
				/// Base for unary term.
				
				/// @internal
				/// This base defines all common types and functions for both chunked and unchunked unary terms.
				///
				/// @param	Term	The subterm type.
				/// @param	UOp		The unary functor.

				template <typename Term, template <typename> class UOp> class unary_term_base
					{
						public:
							typedef UOp <typename Term::value_type> operation;
							typedef typename operation::result_type value_type;
							
							/// Iterator to access elements.
							typedef unary_iterator <typename Term::const_iterator, UOp> const_iterator;
							typedef unary_iterator <typename Term::const_iterator, UOp> iterator;
							
							typedef value_type reference;
							
							/// Gets the element at index n.
							value_type operator[] (std::size_t n) const	{ return operation () (subterm_ [n]); }
							
							/// Gets the number of elements.
							std::size_t size () const					{ return subterm_.size (); }
							
							/// Gets an iterator to the first element.
							const_iterator begin () const
								{
									return const_iterator (subterm_.begin ());
								}
								
						protected:
							const Term subterm_;

							unary_term_base (const Term& subterm): subterm_ (subterm)
								{
								}								
					};

				/// Expression template unary term.
				
				/// @internal
				/// This branch term applies a unary functor to its subterm. A unary term is const chunkable if the subterm is const chunkable and there is
				/// an appropriate unary functor on the chunk type. Such terms are declared as partial specializations with additional members.
				///
				/// @param	Term	The subterm type.
				/// @param	UOp		The unary functor.
				/// @param	Enable	If void, enables a particular template specialization.

				template <typename Term, template <typename> class UOp, typename Enable> class unary_term:
					public unary_term_base <Term, UOp>,
					public term <typename UOp <typename Term::value_type>::result_type, unary_term <Term, UOp> >
					{
						public:
							/// The base type.
							typedef unary_term_base <Term, UOp> base;
							
							unary_term (const Term& subterm): base (subterm)
								{
								}

							using base::operator[];
							using term <typename UOp <typename Term::value_type>::result_type, unary_term <Term, UOp> >::operator[];
					};
					
				template <typename Term, template <typename> class UOp>
					class unary_term <Term, UOp, typename enable_if <
						exists <typename Term::const_chunk_iterator>::value != 0
						&& exists <typename UOp <typename std::iterator_traits <typename Term::const_chunk_iterator>::value_type>::result_type>::value != 0>::type>:
					public unary_term_base <Term, UOp>,
					public term <typename UOp <typename Term::value_type>::result_type, unary_term <Term, UOp> >
					{
						public:
							typedef unary_term_base <Term, UOp> base;
							
							typedef unary_iterator <typename Term::const_chunk_iterator, UOp> const_chunk_iterator;
								
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (base::subterm_.chunk_begin ());
								}
								
							unary_term (const Term& subterm): base (subterm)
								{
								}

							using base::operator[];
							using term <typename UOp <typename Term::value_type>::result_type, unary_term <Term, UOp> >::operator[];
					};


				template <typename TermIt, typename Fn, typename Enable = void>
					class apply_iterator
					{
						public:
							typedef typename std::iterator_traits <TermIt>::iterator_category iterator_category;
							typedef typename std::iterator_traits <TermIt>::value_type value_type; 
							typedef typename std::iterator_traits <TermIt>::difference_type difference_type;
							typedef const value_type* pointer;
							typedef value_type reference;
							
							apply_iterator (const TermIt& subterm_iter, Fn func): subterm_iter_ (subterm_iter), func_ (func)
								{
								}
								
							value_type operator* () const
								{
									return func_ (*subterm_iter_);
								}
								
							value_type operator[] (difference_type n) const
								{
									return func_ (subterm_iter_ [n]);
								}

							apply_iterator& operator++ ()					{ ++subterm_iter_; return *this; }
							apply_iterator operator++ (int)					{ return apply_iterator (subterm_iter_++, func_); }
							apply_iterator& operator+= (difference_type n)	{ subterm_iter_ += n; return *this; }
		
							apply_iterator& operator-- ()					{ --subterm_iter_; return *this; }
							apply_iterator operator-- (int)					{ return apply_iterator (subterm_iter_--, func_); }
							apply_iterator& operator-= (difference_type n)	{ subterm_iter_ -= n; return *this; }
								
							friend apply_iterator operator+ (const apply_iterator& left, difference_type right)
								{
									return apply_iterator (left.subterm_iter_ + right, left.func_);
								}
		
							friend apply_iterator operator+ (difference_type left, const apply_iterator& right)
								{
									return apply_iterator (left + right.subterm_iter_, right.func_);
								}
		
							friend apply_iterator operator- (const apply_iterator& left, difference_type right)
								{
									return apply_iterator (left.subterm_iter_ - right, left.func_);
								}
							
							friend difference_type operator- (const apply_iterator& left, const apply_iterator& right)
								{
									return left.subterm_iter_ - right.subterm_iter_;
								}
								
							friend bool operator== (const apply_iterator& left, const apply_iterator& right)
								{
									return left.subterm_iter_ == right.subterm_iter_ && left.func_ == right.func_;
								}
								
							friend bool operator!= (const apply_iterator& left, const apply_iterator& right)
								{
									return left.subterm_iter_ != right.subterm_iter_ || left.func_ != right.func_;
								}
		
							friend bool operator< (const apply_iterator& left, const apply_iterator& right)
								{
									return left.subterm_iter_ < right.subterm_iter_;
								}

						protected:
							TermIt subterm_iter_;
							Fn const func_;
					};

				/// Expression template apply term.
				
				/// @internal
				/// This branch term applies an arbitrary unary function to its subterm. A apply term is not const chunkable.
				///
				/// @param	Term	The subterm type.
				/// @param	Fn		The unary function.
				/// @param	Enable	If void, enables a particular template specialization.

				template <typename Term, typename Fn, typename Enable>
					class apply_term:
					public term <typename Term::value_type, apply_term <Term, Fn> >
					{
						public:
							typedef typename Term::value_type value_type;
							
							/// Iterator to access elements.
							typedef apply_iterator <typename Term::const_iterator, Fn> const_iterator;
							typedef apply_iterator <typename Term::iterator, Fn> iterator;
							
							typedef value_type reference;
							
							/// Gets the element at index n.
							value_type operator[] (std::size_t n) const	{ return func_ (subterm_ [n]); }
							
							/// Gets the number of elements.
							std::size_t size () const					{ return subterm_.size (); }
							
							/// Gets an iterator to the first element.
							const_iterator begin () const
								{
									return const_iterator (subterm_.begin (), func_);
								}
								
							apply_term (const Term& subterm, Fn func): subterm_ (subterm), func_ (func)
								{
								}
								
							using term <typename Term::value_type, apply_term <Term, Fn> >::operator[];
								
						protected:
							const Term subterm_;
							Fn const func_;
					};

				// ranking iterator categories: given 2 iterator categories we want to know which is least refined
				
				template <typename Cat> struct iterator_category_rank;
				
				template <> struct iterator_category_rank <std::input_iterator_tag>			{ static const int value = 1; };
				template <> struct iterator_category_rank <std::forward_iterator_tag>		{ static const int value = 2; };
				template <> struct iterator_category_rank <std::bidirectional_iterator_tag>	{ static const int value = 3; };
				template <> struct iterator_category_rank <std::random_access_iterator_tag> { static const int value = 4; };
					
				template <int Rank> struct iterator_rank_category;
				
				template <> struct iterator_rank_category <1>	{ typedef std::input_iterator_tag type; };
				template <> struct iterator_rank_category <2>	{ typedef std::forward_iterator_tag type; };
				template <> struct iterator_rank_category <3>	{ typedef std::bidirectional_iterator_tag type; };
				template <> struct iterator_rank_category <4>	{ typedef std::random_access_iterator_tag type; };
		
				template <typename Cat1, typename Cat2> struct iterator_ranker
					{
						static const int first_category_rank = iterator_category_rank <Cat1>::value;
						static const int second_category_rank = iterator_category_rank <Cat2>::value;
						
						typedef typename iterator_rank_category
							<first_category_rank < second_category_rank ? first_category_rank : second_category_rank>::type	type;
					};
				
				template <typename LTermIt, typename RTermIt, template <typename> class BOp, typename Enable = void>
					class binary_iterator_base
					{
						public:
							typedef BOp <typename std::iterator_traits <LTermIt>::value_type> operation;
							typedef typename operation::result_type value_type;
							
							binary_iterator_base (const LTermIt& left_subterm_iter, const RTermIt& right_subterm_iter):
								left_subterm_iter_ (left_subterm_iter), right_subterm_iter_ (right_subterm_iter)
								{
								}
								
							value_type operator* () const
								{
									return operation () (*left_subterm_iter_, *right_subterm_iter_);
								}
								
							value_type operator[] (typename std::iterator_traits <LTermIt>::difference_type n) const
								{
									return operation () (left_subterm_iter_ [n], right_subterm_iter_ [n]);
								}

						protected:
							LTermIt left_subterm_iter_;
							RTermIt right_subterm_iter_;
					};
					
				template <typename LTermIt, typename RTermIt, template <typename> class BOp> class binary_iterator:
					public binary_iterator_base <LTermIt, RTermIt, BOp>
					{
						public:
							typedef binary_iterator_base <LTermIt, RTermIt, BOp> base;
							
							// iterator category is the category with the least rank of the two expression's categories
							typedef typename iterator_ranker
								<typename std::iterator_traits <LTermIt>::iterator_category,
								typename std::iterator_traits <RTermIt>::iterator_category>::type iterator_category;
							
							typedef typename std::iterator_traits <LTermIt>::difference_type difference_type;
							typedef const typename base::value_type* pointer;
							typedef typename base::value_type reference;
							
							binary_iterator (const LTermIt& left_subterm_iter, const RTermIt& right_subterm_iter):
								base (left_subterm_iter, right_subterm_iter)
								{
								}
								
							const LTermIt& left_subterm_iter () const	{ return base::left_subterm_iter_; }
							const RTermIt& right_subterm_iter () const	{ return base::right_subterm_iter_; }
								
							binary_iterator& operator++ ()					{ ++base::left_subterm_iter_; ++base::right_subterm_iter_; return *this; }
							binary_iterator operator++ (int)				{ return binary_iterator (base::left_subterm_iter_++, base::right_subterm_iter_++); }
							binary_iterator& operator+= (difference_type n)	{ base::left_subterm_iter_ += n; base::right_subterm_iter_ += n; return *this; }
		
							binary_iterator& operator-- ()					{ --base::left_subterm_iter_; --base::right_subterm_iter_; return *this; }
							binary_iterator operator-- (int)				{ return binary_iterator (base::left_subterm_iter_--, base::right_subterm_iter_--); }
							binary_iterator& operator-= (difference_type n)	{ base::left_subterm_iter_ -= n; base::right_subterm_iter_ -= n; return *this; }
								
							friend binary_iterator operator+ (const binary_iterator& left, difference_type right)
								{
									return binary_iterator (left.left_subterm_iter_ + right, left.right_subterm_iter_ + right);
								}

							friend binary_iterator operator+ (difference_type left, const binary_iterator& right)
								{
									return binary_iterator (left + right.left_subterm_iter_, left + right.right_subterm_iter_);
								}

							friend binary_iterator operator- (const binary_iterator& left, difference_type right)
								{
									return binary_iterator (left.left_subterm_iter_ - right, left.right_subterm_iter_ - right);
								}
							
							friend difference_type operator- (const binary_iterator& left, const binary_iterator& right)
								{
									return left.left_subterm_iter_ - right.left_subterm_iter_;
								}
								
							friend bool operator== (const binary_iterator& left, const binary_iterator& right)
								{
									return left.left_subterm_iter_ == right.left_subterm_iter_;
								}
								
							friend bool operator!= (const binary_iterator& left, const binary_iterator& right)
								{
									return left.left_subterm_iter_ != right.left_subterm_iter_;
								}

							friend bool operator< (const binary_iterator& left, const binary_iterator& right)
								{
									return left.left_subterm_iter_ < right.left_subterm_iter_;
								}								
					};
		
				/// Base for binary term.
				
				/// @internal
				/// This base defines all common types and functions for both chunked and unchunked binary terms.
				///
				/// @param	LTerm	The left subterm type.
				/// @param	RTerm	The right subterm type.
				/// @param	BOp		The binary functor.
				
				template <typename LTerm, typename RTerm, template <typename> class BOp> class binary_term_base
					{
						public:
							typedef BOp <typename LTerm::value_type> operation;
							
							/// The element value type.
							typedef typename operation::result_type value_type;
							
							typedef binary_iterator <typename LTerm::const_iterator, typename RTerm::const_iterator, BOp> const_iterator;
							typedef binary_iterator <typename LTerm::const_iterator, typename RTerm::const_iterator, BOp> iterator;
							
							typedef value_type reference;
							
							// Gets the element at index @a n.
							value_type operator[] (std::size_t index) const	{ return operation () (left_subterm_ [index], right_subterm_ [index]); }
							
							/// Gets the number of elements.
							std::size_t size () const						{ return left_subterm_.size (); }
							
							/// Gets an iterator to the first element.
							const_iterator begin () const
								{
									return const_iterator (left_subterm_.begin (), right_subterm_.begin ());
								}

						protected:
							const LTerm left_subterm_;
							const RTerm right_subterm_;

							binary_term_base (const LTerm& left_subterm, const RTerm& right_subterm):
								left_subterm_ (left_subterm), right_subterm_ (right_subterm)
								{
								}								
					};


				/// Expression template binary term.
				
				/// @internal
				/// This branch term applies a binary functor to its subterms. A binary term is const chunkable if each subterm's chunked types
				/// are the same and there is an appropriate binary functor on the chunked type. Such terms are declared as partial specializations
				/// with additional members.
				///
				/// @param	LTerm	The left subterm type.
				/// @param	RTerm	The right subterm type.
				/// @param	BOp		The binary functor.
				/// @param	Enable	If void, enables a particular template specialization.
				
				template <typename LTerm, typename RTerm, template <typename> class BOp, typename Enable> class binary_term:
					public binary_term_base <LTerm, RTerm, BOp>,
					public term <typename BOp <typename LTerm::value_type>::result_type, binary_term <LTerm, RTerm, BOp> >
					{
						public:
							typedef binary_term_base <LTerm, RTerm, BOp> base;
							
							binary_term (const LTerm& left_subterm, const RTerm& right_subterm):
								base (left_subterm, right_subterm)
								{
								}

							using base::operator[];
							using term <typename BOp <typename LTerm::value_type>::result_type, binary_term <LTerm, RTerm, BOp> >::operator[];
							
					};

				template <typename LTerm, typename RTerm, template <typename> class BOp>
					class binary_term <LTerm, RTerm, BOp, typename enable_if <
						const_rechunkable <LTerm, RTerm>::value != 0
						&& exists <typename BOp <typename std::iterator_traits <typename LTerm::const_chunk_iterator>::value_type>::result_type>::value != 0>::type>:
					public binary_term_base <LTerm, RTerm, BOp>,
					public term <typename BOp <typename LTerm::value_type>::result_type, binary_term <LTerm, RTerm, BOp> >
					{
						public:
							typedef binary_term_base <LTerm, RTerm, BOp> base;
							
							typedef binary_iterator <typename LTerm::const_chunk_iterator, typename RTerm::const_chunk_iterator,
								BOp> const_chunk_iterator;
							
							const_chunk_iterator chunk_begin () const
								{
									return const_chunk_iterator (base::left_subterm_.chunk_begin (), base::right_subterm_.chunk_begin ());
								}
								
							binary_term (const LTerm& left_subterm, const RTerm& right_subterm):
								base (left_subterm, right_subterm)
								{
								}

							using base::operator[];
							using term <typename BOp <typename LTerm::value_type>::result_type, binary_term <LTerm, RTerm, BOp> >::operator[];							
					};


				template <typename LTermIt, typename RTermIt, template <typename, typename> class BOp, typename Enable = void>
					class binary_iterator_base2
					{
						public:
							typedef BOp <typename std::iterator_traits <LTermIt>::value_type, typename std::iterator_traits <RTermIt>::value_type> operation;
							typedef typename operation::result_type value_type;
							
							binary_iterator_base2 (const LTermIt& left_subterm_iter, const RTermIt& right_subterm_iter):
								left_subterm_iter_ (left_subterm_iter), right_subterm_iter_ (right_subterm_iter)
								{
								}
								
							value_type operator* () const
								{
									return operation () (*left_subterm_iter_, *right_subterm_iter_);
								}
								
							value_type operator[] (typename std::iterator_traits <LTermIt>::difference_type n) const
								{
									return operation () (left_subterm_iter_ [n], right_subterm_iter_ [n]);
								}

						protected:
							LTermIt left_subterm_iter_;
							RTermIt right_subterm_iter_;
					};
					
				template <typename LTermIt, typename RTermIt, template <typename, typename> class BOp> class binary_iterator2:
					public binary_iterator_base2 <LTermIt, RTermIt, BOp>
					{
						public:
							typedef binary_iterator_base2 <LTermIt, RTermIt, BOp> base;
							
							// iterator category is the category with the least rank of the two expression's categories
							typedef typename iterator_ranker
								<typename std::iterator_traits <LTermIt>::iterator_category,
								typename std::iterator_traits <RTermIt>::iterator_category>::type iterator_category;
							
							typedef typename std::iterator_traits <LTermIt>::difference_type difference_type;
							typedef const typename base::value_type* pointer;
							typedef typename base::value_type reference;
							
							binary_iterator2 (const LTermIt& left_subterm_iter, const RTermIt& right_subterm_iter):
								base (left_subterm_iter, right_subterm_iter)
								{
								}
								
							const LTermIt& left_subterm_iter () const	{ return base::left_subterm_iter_; }
							const RTermIt& right_subterm_iter () const	{ return base::right_subterm_iter_; }
								
							binary_iterator2& operator++ ()					{ ++base::left_subterm_iter_; ++base::right_subterm_iter_; return *this; }
							binary_iterator2 operator++ (int)				{ return binary_iterator2 (base::left_subterm_iter_++, base::right_subterm_iter_++); }
							binary_iterator2& operator+= (difference_type n)	{ base::left_subterm_iter_ += n; base::right_subterm_iter_ += n; return *this; }
		
							binary_iterator2& operator-- ()					{ --base::left_subterm_iter_; --base::right_subterm_iter_; return *this; }
							binary_iterator2 operator-- (int)				{ return binary_iterator2 (base::left_subterm_iter_--, base::right_subterm_iter_--); }
							binary_iterator2& operator-= (difference_type n)	{ base::left_subterm_iter_ -= n; base::right_subterm_iter_ -= n; return *this; }
								
							friend binary_iterator2 operator+ (const binary_iterator2& left, difference_type right)
								{
									return binary_iterator2 (left.left_subterm_iter_ + right, left.right_subterm_iter_ + right);
								}

							friend binary_iterator2 operator+ (difference_type left, const binary_iterator2& right)
								{
									return binary_iterator2 (left + right.left_subterm_iter_, left + right.right_subterm_iter_);
								}

							friend binary_iterator2 operator- (const binary_iterator2& left, difference_type right)
								{
									return binary_iterator2 (left.left_subterm_iter_ - right, left.right_subterm_iter_ - right);
								}
							
							friend difference_type operator- (const binary_iterator2& left, const binary_iterator2& right)
								{
									return left.left_subterm_iter_ - right.left_subterm_iter_;
								}
								
							friend bool operator== (const binary_iterator2& left, const binary_iterator2& right)
								{
									return left.left_subterm_iter_ == right.left_subterm_iter_;
								}
								
							friend bool operator!= (const binary_iterator2& left, const binary_iterator2& right)
								{
									return left.left_subterm_iter_ != right.left_subterm_iter_;
								}

							friend bool operator< (const binary_iterator2& left, const binary_iterator2& right)
								{
									return left.left_subterm_iter_ < right.left_subterm_iter_;
								}								
					};
				
			}
	}

#endif