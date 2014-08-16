/*
 *  com_client.h
 *  macstl
 *
 *  Copyright (c) 2003, Pixelglow Software.
 *  http://www.pixelglow.com/macstl/
 *  macstl@pixelglow.com
 *
 *  You may copy, modify, distribute and sell this source code and its
 *  documentation without fee, provided that the above copyright notice
 *  appear in all copies and that both the copyright notice and these
 *  permission notices appear in supporting documentation. You may modify
 *  this source code without further permission from the copyright holders,
 *  but all such modified files must carry prominent notices stating
 *  that you changed the files and the date of any change.
 *
 *  If you register this source code with the copyright holders, you may
 *  compile any part of it from source code to object code. If you
 *  do not register, you may only compile it within 30 days of the first
 *  compilation, and must ensure that all the compiled code and its copies,
 *  modifications, distributions and sales are deleted within the 30 days.
 *
 *  The copyright holders make no representations about the suitability
 *  of this software for any purpose.  It is provided "as is" without
 *  express or implied warranty.
 */

#ifndef MACSTL_COM_CLIENT_H
#define MACSTL_COM_CLIENT_H

#include <internal/com_traits.h>

namespace macstl
	{
		/**
		 * @brief COM HRESULT exception.
		 * 
		 * The com_exception encapsulates a COM HRESULT error.
		 */
		class com_exception
			{
				public:
					/** Constructs from a COM HRESULT @a hr. */
					com_exception (HRESULT hr): _hr (hr)
						{
						}
					
					/** Returns the raw HRESULT. */
					HRESULT result () const
						{
							return _hr;
						}
						
				private:
					HRESULT _hr;
			};
			
		/**
		 * @relates com_exception
		 *
		 * Throws if @a hr is a COM failure.
		 */
		inline void throw_if_com_error (HRESULT hr)
			{
				if (FAILED (hr))
					throw com_exception (hr);
			}
			
		/**
		 * @brief COM interface smart pointer.
		 * @param Type The COM interface type.
		 * @par Models:
		 * Default Constructible, Copy Constructible, Assignable, Equality Comparable, Less Than Comparable
		 *
		 * The com_ptr encapsulates the COM interface pointer as a "smart pointer". It is conceptually similar to
		 * boost::counted_ptr, but based on COM reference counting. While it looks like Microsoft ATL's _com_ptr_t,
		 * it is far simpler with fewer loopholes and gotchas.
		 *
		 * AddRef is always only done at construction and Release at destruction, thus typical C++ usage takes care
		 * of reference-counting issues. Swaps, resets and assignment operators all create internal temporaries to
		 * preserve these invariants, ensuring the object does not leak references.
		 *
		 * The rule of thumb is: you only have to take care of your own raw interface pointers e.g.
		 * @code
		 * IFoo* bar = GetFoo();
		 * macstl::com_ptr <IFoo> barro = bar;
		 * bar->Release();
		 * @endcode
		 * You only have to Release <code>bar</code> because it is a raw interface pointer. On the other hand, the
		 * object <code>barro</code> can now be copied, passed by value, stored into a container or returned from a
		 * function and it will keep on counting references perfectly.
		 *
		 * Comparisons use COM equality rules: the interface pointers are converted to IUnknown pointers for
		 * comparison.
		 *
		 * On Mac OS X, you can use this to access a CFPlugIn.
		 */
		template <class Type> class com_ptr
			{
				public:
					typedef Type element_type;		/**< The COM interface type. */
					
					/** Constructs from a raw COM interface @a ptr. */
					explicit com_ptr (element_type* ptr = 0): ptr_ (ptr)
						{
							if (ptr_) ptr_->AddRef ();
						}
			
					/** Constructs a copy of @a other. */
					com_ptr (com_ptr& other): ptr_ (other.ptr_)
						{
							if (ptr_) ptr_->AddRef ();
						}
		
					/** Constructs from a different interface pointer @a other. */
					template <class ReType> com_ptr (const com_ptr <ReType>& other): ptr_ (0)
						{
							ReType* ptr = other.get ();
							if (ptr)
								throw_if_com_error (ptr->QueryInterface (com_traits <Type>::uuid, (void **) &ptr_));
						}
		
					/** Assigns from @a other. */
					com_ptr& operator= (const com_ptr& other)
						{
							if (&other != this)
								{
									com_ptr temp (other);
									swap (temp);
								}
							return *this;
						}
		
					/** Assigns from a different interface pointer @a other. */
					template <class ReType> com_ptr& operator= (const com_ptr <ReType>& other)
						{
							if (other.get () != get ())
								{
									com_ptr temp (other);
									swap (other);
								}
							return *this;
						}
						
					/** Destructs. */
					~com_ptr ()
						{
							if (ptr_) ptr_->Release ();
						}
						
					/** Swaps interface pointer with @a other. */
					void swap (com_ptr &other)
						{
							std::swap (ptr_, other.ptr_);
						}
						
					/** Returns a reference to the COM type. */
					element_type& operator* () const
						{
							return *ptr_;
						}
						
					/** Returns a pointer to the COM type. */
					element_type* operator-> () const
						{
							return ptr_;
						}
						
					/** Returns the raw interface pointer. */
					element_type* get () const
						{
							return ptr_;
						}
						
					/** Resets the pointer to point to @a ptr. */
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
			
		/**
		 * @relates com_ptr
		 *
		 * Checks whether the IUnknown pointer of @a left is equal to the IUnknown pointer of @a right.
		 */
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
		
		/**
		 * @relates com_ptr
		 *
		 * Checks whether the IUnknown pointer of @a left is less than the IUnknown pointer of @a right.
		 */
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
		
		/**
		 * @relates com_ptr
		 *
		 * Swaps the interface pointers of @a left and @a right.
		 */
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
	}
	
#endif
