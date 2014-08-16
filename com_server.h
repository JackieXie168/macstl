/*
 *  com_server.h
 *  macstl
 *
 *  Created by Glen Low on Fri Dec 27 2002.
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

#include <map>

#include "internal/com_traits.h"

namespace macstl
	{
		// com_type
		
			// Provides a basic COM implementation, a la Microsoft's ATL. Instead of using macros to record interface pointers,
			// we use an STL map of IIDs to interface pointers, which derived classes can register via add_interface. The
			// map allows fast retrieval of pointers through QueryInterface so that derived classes need not override those IUnknown
			// members. Typically, you don't need to explicitly subclass or construct com_type, since subclassing com_interface
			// implicitly subclasses com_type as a virtual base, and com_type has an appropriate default constructor
				
		class com_type
			{
				private:
					struct compare_interface
						{
							bool operator() (const REFIID& left, const REFIID& right) const
								{
									return memcmp (&left, &right, 16) < 0;
								}
						};
					typedef std::map <REFIID, IUnknown*, compare_interface> interfaces;
						
					interfaces intf_;			// stores our interface pointers, keyed by UUID
					ULONG ref_;									// reference count
					
				protected:
					com_type (): intf_ (), ref_ (1)
						{
						}
						
					void add_interface (REFIID iid, IUnknown* intf)
						{
							// register an interface pointer
							assert (intf != NULL);
							intf_ [iid] = intf;
						}
						
					void remove_interface (REFIID iid)
						{
							// unregister an interface pointer
							intf_.erase (iid);
						}
						
					HRESULT do_queryinterface (REFIID iid, LPVOID* ppv)
						{
							interfaces::iterator found = intf_.find (iid);
							if (found == intf_.end ())
								{
									// no such interface found
									*ppv = NULL;
									return E_NOINTERFACE;
								}
							else
								{
									// interface was found in our interfaces, add ref
									*ppv = found->second;
									++ref_;
									return S_OK;
								}
			
						}
					
					ULONG do_addref ()
						{
							return ++ref_;
						}
						
					ULONG do_release ()
						{
							if (--ref_)
								return ref_;
							else
								{
									// reference count fell to zero: free object
									delete this;
									return 0;
								}
						}
						
				public:
					virtual ~com_type ()
						{
						}
						
					IUnknown* unknown () const
						{
							// BUG: gcc seems to think that if a class inherits a COM interface through the com_interface template
							// it can be statically cast to that interface, even though we specified private inheritance on com_interface!!
							// ... so if we tried to do a cast to IUnknown*, it thinks that IUnknown is an ambiguous superclass
							// ... thus this workaround to get the identity IUnknown interface e.g. after creating the object							
							interfaces::const_iterator found = intf_.find (com_traits <IUnknown>::uuid);
							return found == intf_.end () ? NULL : found->second;
						}
			};
			
		// com_interface <Intf>
		
			// Implementation of the given COM interface. It automatically registers its interface pointer upon construction
			// in the virtual base com_type. The implementation of the interface delegates IUnknown calls to the virtual base's
			// methods. Typically, a COM type subclasses com_interface for each COM interface it implements.
			// It then defines the non-IUnknown member functions. At the minimum, the (non-aggregatable) COM type
			// must at least subclass IUnknown e.g. if class C implements interface I1 and I2, declare:
			//   class C: public com_interface <IUnknown>, public com_interface <I1>, public com_interface <I2> { ... };
			
			// NOTE: if you really want to step into the murky waters of COM aggregation, that is doable too. Just don't inherit
			// directly from com_interface <IUnknown>, and in your constructor call add_interface with the outer IUnknown.
				
		template <typename Intf> class com_interface: public virtual com_type, private Intf
			{
				public:
					virtual ~com_interface ()
						{
							// remove that interface
							remove_interface (com_traits <Intf>::uuid);
						}
						
					virtual HRESULT STDMETHODCALLTYPE QueryInterface (REFIID iid, LPVOID* ppv)
						{
							return do_queryinterface (iid, ppv);
						}
					
					virtual ULONG STDMETHODCALLTYPE AddRef ()
						{
							return do_addref ();
						}
						
					virtual ULONG STDMETHODCALLTYPE Release ()
						{
							return do_release ();
						}
						
				protected:
					com_interface (): com_type ()
						{
							// add our IUnknown interface
							add_interface (com_traits <Intf>::uuid, this);
						}
			};
			
		// specialization for IUnknown: the intent is that static casting to IUnknown* would return this interface, rather than
		// any other COM interface. However a bug with gcc prevents this from working: see unknown () in com_type.
		
		template <> class com_interface <IUnknown>: public virtual com_type, public IUnknown
			{
				public:
					virtual ~com_interface ()
						{
							// remove that interface
							remove_interface (com_traits <IUnknown>::uuid);
						}
						
					virtual HRESULT STDMETHODCALLTYPE QueryInterface (REFIID iid, LPVOID* ppv)
						{
							return do_queryinterface (iid, ppv);
						}
					
					virtual ULONG STDMETHODCALLTYPE AddRef ()
						{
							return do_addref ();
						}
						
					virtual ULONG STDMETHODCALLTYPE Release ()
						{
							return do_release ();
						}
						
				protected:
					com_interface (): com_type ()
						{
							// add our IUnknown interface
							add_interface (com_traits <IUnknown>::uuid, this);
						}
			};
	
	
	};

