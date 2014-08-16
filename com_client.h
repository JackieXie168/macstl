/*
 *  com_client.h
 *  macstl
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

#include "internal/com_traits.h"

namespace macstl
	{
		// com_exception
		
		class com_exception
			{
				private:
					HRESULT _hr;
					
				public:
					com_error (HRESULT hr): _hr (hr)
						{
						}
					
					HRESULT result () const
						{
							return _hr;
						}
			};
			
		inline void throw_if_com_error (HRESULT hr)
			{
				if (FAILED (hr))
					throw com_exception (hr);
			}
			
		// com_ptr <Type>
		
			// Encapsulates the COM interface pointer as a "smart pointer". This is conceptually similar to boost::counted_ptr,
			// but based on COM references, and while it looks like Microsoft ATL's _com_ptr_t, it is much simpler
			// and thus has fewer loopholes. To use COM terminology, QueryInterface can only be done via constructing a new
			// com_ptr (and thus Release-ing the interface pointer at end of scope), AddRef's only done at construction and Release's
			// only done at destruction. Swaps, resets and assignment operators all create internal temporaries to preserve these
			// invariants. Two COM pointers compare equal when their IUnknown pointers compare equal, according to COM rules.
			
		template <class Type> class com_ptr
			{
				public:
					typedef Type element_type;
					
					explicit com_ptr (element_type* ptr = 0): ptr_ (ptr)
						{
							if (ptr_) ptr_->AddRef ();
						}
			
					com_ptr (com_ptr& other): ptr_ (other.ptr_)
						{
							if (ptr_) ptr_->AddRef ();
						}
		
					template <class ReType> com_ptr (const com_ptr <ReType>& other): ptr_ (0)
						{
							ReType* ptr = other.get ();
							if (ptr)
								throw_if_com_error (ptr->QueryInterface (com_traits <Type>::uuid, (void **) &ptr_));
						}
		
					com_ptr& operator= (const com_ptr& other)
						{
							if (&other != this)
								{
									com_ptr temp (other);
									swap (temp);
								}
							return *this;
						}
		
					template <class ReType> com_ptr& operator= (const com_ptr <ReType>& other)
						{
							if (other.get () != get ())
								{
									com_ptr temp (other);
									swap (other);
								}
							return *this;
						}
						
					~com_ptr ()
						{
							if (ptr_) ptr_->Release ();
						}
						
					void swap (com_ptr &other)
						{
							std::swap (ptr_, other.ptr_);
						}
						
					element_type& operator* () const
						{
							return *ptr_;
						}
						
					element_type* operator-> () const
						{
							return ptr_;
						}
						
					element_type* get () const
						{
							return ptr_;
						}
						
					void reset (element_type* ptr = 0) const
						{
							if (ptr != ptr_)
								{
									com_ptr temp (ptr);
									swap (temp);
								}
						}
		
				private:
					Type* ptr_;
			};
			
			
		template <class Type1, class Type2> inline bool operator== (const com_ptr <Type1> &left, const com_ptr <Type2> &right)
			{
				Type1* leftptr = left.get ();
				Type2* rightptr = right.get ();
				if (leftptr == rightptr)
					// if they have the same underlying COM object, or both are null, they are equal
					return true;
				else if (leftptr && rightptr)
					// if they are non-null and have the same underlying IUnknown interface, they are equal
					return (com_ptr <IUnknown> (left)).get () == (com_ptr <IUnknown> (right)).get ();
				else
					// either one is null and other is non-null, so they are not equal
					return false;
			}
		
		template <class Type1, class Type2> inline bool operator< (const com_ptr <Type1> &left, const com_ptr <Type2> &right)
			{
				Type1* leftptr = left.get ();
				Type2* rightptr = right.get ();
				if (leftptr && rightptr)
					// if they are non-null, compare underlying IUnknown interface
					return (com_ptr <IUnknown> (left)).get () < (com_ptr <IUnknown> (right)).get ();
				else
					return !leftptr && rightptr;
			}
		
		template <class Type> inline void swap (com_ptr <Type> &left, com_ptr <Type> &right)
			{
				left.swap (right);
			}
			
		inline com_ptr <IUnknown> create (CFUUIDRef factory, CFUUIDRef type, CFAllocatorRef allocator = NULL)
			{
				com_ptr <IUnknown> instance (static_cast <IUnknown*> (CFPlugInInstanceCreate (allocator, factory, type)));
				instance->Release ();	// since CFPlugInInstanceCreate implicitly addref's
				return instance;
			}
	};
