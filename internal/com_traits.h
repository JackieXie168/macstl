/*
 *  com_traits.h
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

#include <CoreFoundation/CFPlugInCOM.h>

namespace macstl
	{
		// com_traits <Type>
		
			// This associates a REFIID with a type, allowing QueryInterfaces to be done on the
			// static type of COM objects. Either specify the uuid as a static field in the type (if you control it yourself)
			// or define a specialization of com_traits on the type (if you don't control it yourself).
	
		template <class Type> struct com_traits
			{
				static const REFIID uuid;
			};
			
		template <class Type> const REFIID com_traits <Type>::uuid = Type::uuid;
		
		template <> const REFIID com_traits <IUnknown>::uuid =
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46};
	};
