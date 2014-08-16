/*
 *  generator.h
 *  macstl
 *
 *  Created by Glen Low on Nov 23 2004.
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

#ifndef MACSTL_IMPL_GENERATOR_H
#define MACSTL_IMPL_GENERATOR_H

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (0); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000F8>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-8); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000F9>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-7); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FA>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-6); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FB>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-5); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FC>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-4); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FD>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-3); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FE>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-2); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x000000FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-1); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F0F0>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-16); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F1F1>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-15); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F2F2>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-14); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F3F3>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-13); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F4F4>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-12); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F5F5>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-11); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F6F6>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-10); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000F7F7>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-9); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF0>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-16); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF1>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-15); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF2>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-14); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF3>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-13); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF4>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-12); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF5>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-11); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF6>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-10); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFF7>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-9); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000000, 0x00000000, 0x0000FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x00000001, 0x00000000, 0x00000001>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (1); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000002, 0x00000000, 0x00000002>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (2); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000003, 0x00000000, 0x00000003>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (3); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000004, 0x00000000, 0x00000004>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (4); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000005, 0x00000000, 0x00000005>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (5); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000006, 0x00000000, 0x00000006>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (6); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000007, 0x00000000, 0x00000007>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (7); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000008, 0x00000000, 0x00000008>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (8); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000009, 0x00000000, 0x00000009>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (9); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000A, 0x00000000, 0x0000000A>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (10); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000B, 0x00000000, 0x0000000B>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (11); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000C, 0x00000000, 0x0000000C>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (12); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000D, 0x00000000, 0x0000000D>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (13); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000E, 0x00000000, 0x0000000E>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (14); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x0000000F, 0x00000000, 0x0000000F>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (15); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0x00000000, 0x00000101, 0x00000000, 0x00000101>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (1); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000202, 0x00000000, 0x00000202>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (2); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000303, 0x00000000, 0x00000303>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (3); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000404, 0x00000000, 0x00000404>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (4); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000505, 0x00000000, 0x00000505>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (5); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000606, 0x00000000, 0x00000606>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (6); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000707, 0x00000000, 0x00000707>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (7); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000808, 0x00000000, 0x00000808>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (8); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000909, 0x00000000, 0x00000909>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (9); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000A0A, 0x00000000, 0x00000A0A>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (10); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000B0B, 0x00000000, 0x00000B0B>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (11); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000C0C, 0x00000000, 0x00000C0C>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (12); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000D0D, 0x00000000, 0x00000D0D>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (13); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000E0E, 0x00000000, 0x00000E0E>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (14); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00000F0F, 0x00000000, 0x00000F0F>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (15); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0x00000000, 0x00010001, 0x00000000, 0x00010001>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (1); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00020002, 0x00000000, 0x00020002>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (2); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00030003, 0x00000000, 0x00030003>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (3); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00040004, 0x00000000, 0x00040004>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (4); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00050005, 0x00000000, 0x00050005>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (5); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00060006, 0x00000000, 0x00060006>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (6); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00070007, 0x00000000, 0x00070007>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (7); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00080008, 0x00000000, 0x00080008>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (8); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x00090009, 0x00000000, 0x00090009>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (9); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000A000A, 0x00000000, 0x000A000A>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (10); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000B000B, 0x00000000, 0x000B000B>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (11); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000C000C, 0x00000000, 0x000C000C>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (12); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000D000D, 0x00000000, 0x000D000D>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (13); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000E000E, 0x00000000, 0x000E000E>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (14); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x000F000F, 0x00000000, 0x000F000F>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (15); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0x00000000, 0x08000000, 0x08000000, 0x08000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (8); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x09000000, 0x09000000, 0x09000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (9); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0A000000, 0x0A000000, 0x0A000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (10); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0B000000, 0x0B000000, 0x0B000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (11); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0C000000, 0x0C000000, 0x0C000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (12); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0D000000, 0x0D000000, 0x0D000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (13); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0E000000, 0x0E000000, 0x0E000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (14); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000000, 0x0F000000, 0x0F000000, 0x0F000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (15); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000001, 0x00000001, 0x00000001, 0x00000001>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (1); }
	};

template <> struct generator <0x00000002, 0x00000002, 0x00000002, 0x00000002>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (2); }
	};

template <> struct generator <0x00000003, 0x00000003, 0x00000003, 0x00000003>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (3); }
	};

template <> struct generator <0x00000004, 0x00000004, 0x00000004, 0x00000004>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (4); }
	};

template <> struct generator <0x00000005, 0x00000005, 0x00000005, 0x00000005>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (5); }
	};

template <> struct generator <0x00000006, 0x00000006, 0x00000006, 0x00000006>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (6); }
	};

template <> struct generator <0x00000007, 0x00000007, 0x00000007, 0x00000007>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (7); }
	};

template <> struct generator <0x00000008, 0x00000008, 0x00000008, 0x00000008>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (8); }
	};

template <> struct generator <0x00000009, 0x00000009, 0x00000009, 0x00000009>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (9); }
	};

template <> struct generator <0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (10); }
	};

template <> struct generator <0x0000000B, 0x0000000B, 0x0000000B, 0x0000000B>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (11); }
	};

template <> struct generator <0x0000000C, 0x0000000C, 0x0000000C, 0x0000000C>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (12); }
	};

template <> struct generator <0x0000000D, 0x0000000D, 0x0000000D, 0x0000000D>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (13); }
	};

template <> struct generator <0x0000000E, 0x0000000E, 0x0000000E, 0x0000000E>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (14); }
	};

template <> struct generator <0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (15); }
	};

template <> struct generator <0x00000100, 0x00000100, 0x00000100, 0x00000100>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (1); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000101, 0x00000101, 0x00000101, 0x00000101>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (1); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000200, 0x00000200, 0x00000200, 0x00000200>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (2); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000202, 0x00000202, 0x00000202, 0x00000202>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (2); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000300, 0x00000300, 0x00000300, 0x00000300>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (3); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000303, 0x00000303, 0x00000303, 0x00000303>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (3); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000400, 0x00000400, 0x00000400, 0x00000400>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (4); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000404, 0x00000404, 0x00000404, 0x00000404>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (4); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000500, 0x00000500, 0x00000500, 0x00000500>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (5); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000505, 0x00000505, 0x00000505, 0x00000505>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (5); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000600, 0x00000600, 0x00000600, 0x00000600>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (6); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000606, 0x00000606, 0x00000606, 0x00000606>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (6); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000700, 0x00000700, 0x00000700, 0x00000700>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (7); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000707, 0x00000707, 0x00000707, 0x00000707>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (7); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000800, 0x00000800, 0x00000800, 0x00000800>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (8); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000800, 0x08000800, 0x08000800, 0x08000800>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (8); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000801, 0x00000801, 0x00000801, 0x00000801>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (1); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00000808, 0x00000808, 0x00000808, 0x00000808>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (8); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000900, 0x00000900, 0x00000900, 0x00000900>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (9); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000900, 0x09000900, 0x09000900, 0x09000900>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (9); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000909, 0x00000909, 0x00000909, 0x00000909>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (9); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000A00, 0x00000A00, 0x00000A00, 0x00000A00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (10); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000A00, 0x0A000A00, 0x0A000A00, 0x0A000A00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (10); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000A0A, 0x00000A0A, 0x00000A0A, 0x00000A0A>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (10); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000B00, 0x00000B00, 0x00000B00, 0x00000B00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (11); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000B00, 0x0B000B00, 0x0B000B00, 0x0B000B00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (11); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000B0B, 0x00000B0B, 0x00000B0B, 0x00000B0B>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (11); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000C00, 0x00000C00, 0x00000C00, 0x00000C00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (12); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000C00, 0x0C000C00, 0x0C000C00, 0x0C000C00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (12); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000C0C, 0x00000C0C, 0x00000C0C, 0x00000C0C>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (12); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000D00, 0x00000D00, 0x00000D00, 0x00000D00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (13); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000D00, 0x0D000D00, 0x0D000D00, 0x0D000D00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (13); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000D0D, 0x00000D0D, 0x00000D0D, 0x00000D0D>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (13); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000E00, 0x00000E00, 0x00000E00, 0x00000E00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (14); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000E00, 0x0E000E00, 0x0E000E00, 0x0E000E00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (14); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000E0E, 0x00000E0E, 0x00000E0E, 0x00000E0E>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (14); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00000F00, 0x00000F00, 0x00000F00, 0x00000F00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (15); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x00000F00, 0x0F000F00, 0x0F000F00, 0x0F000F00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (15); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00000F0F, 0x00000F0F, 0x00000F0F, 0x00000F0F>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (15); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0x00001002, 0x00001002, 0x00001002, 0x00001002>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (2); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00001803, 0x00001803, 0x00001803, 0x00001803>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (3); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00010000, 0x00010000, 0x00010000, 0x00010000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (1); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00010001, 0x00010001, 0x00010001, 0x00010001>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (1); }
	};

template <> struct generator <0x00010004, 0x00010004, 0x00010004, 0x00010004>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (4); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00010805, 0x00010805, 0x00010805, 0x00010805>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (5); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00011006, 0x00011006, 0x00011006, 0x00011006>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (6); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00011807, 0x00011807, 0x00011807, 0x00011807>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (7); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00020000, 0x00020000, 0x00020000, 0x00020000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (2); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00020002, 0x00020002, 0x00020002, 0x00020002>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (2); }
	};

template <> struct generator <0x00020008, 0x00020008, 0x00020008, 0x00020008>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (8); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00020809, 0x00020809, 0x00020809, 0x00020809>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (9); return vec_vupkhpx (v); }
	};

template <> struct generator <0x0002100A, 0x0002100A, 0x0002100A, 0x0002100A>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (10); return vec_vupkhpx (v); }
	};

template <> struct generator <0x0002180B, 0x0002180B, 0x0002180B, 0x0002180B>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (11); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00030000, 0x00030000, 0x00030000, 0x00030000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (3); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00030003, 0x00030003, 0x00030003, 0x00030003>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (3); }
	};

template <> struct generator <0x0003000C, 0x0003000C, 0x0003000C, 0x0003000C>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (12); return vec_vupkhpx (v); }
	};

template <> struct generator <0x0003080D, 0x0003080D, 0x0003080D, 0x0003080D>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (13); return vec_vupkhpx (v); }
	};

template <> struct generator <0x0003100E, 0x0003100E, 0x0003100E, 0x0003100E>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (14); return vec_vupkhpx (v); }
	};

template <> struct generator <0x0003180F, 0x0003180F, 0x0003180F, 0x0003180F>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (15); return vec_vupkhpx (v); }
	};

template <> struct generator <0x00040000, 0x00040000, 0x00040000, 0x00040000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (4); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00040004, 0x00040004, 0x00040004, 0x00040004>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (4); }
	};

template <> struct generator <0x00050000, 0x00050000, 0x00050000, 0x00050000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (5); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00050005, 0x00050005, 0x00050005, 0x00050005>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (5); }
	};

template <> struct generator <0x00060000, 0x00060000, 0x00060000, 0x00060000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (6); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00060006, 0x00060006, 0x00060006, 0x00060006>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (6); }
	};

template <> struct generator <0x00070000, 0x00070000, 0x00070000, 0x00070000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (7); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00070007, 0x00070007, 0x00070007, 0x00070007>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (7); }
	};

template <> struct generator <0x00080000, 0x00080000, 0x00080000, 0x00080000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (8); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00080008, 0x00080008, 0x00080008, 0x00080008>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (8); }
	};

template <> struct generator <0x00080808, 0x08080808, 0x08080808, 0x08080808>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (8); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x00090000, 0x00090000, 0x00090000, 0x00090000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (9); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x00090009, 0x00090009, 0x00090009, 0x00090009>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (9); }
	};

template <> struct generator <0x00090909, 0x09090909, 0x09090909, 0x09090909>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (9); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000A0000, 0x000A0000, 0x000A0000, 0x000A0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (10); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000A000A, 0x000A000A, 0x000A000A, 0x000A000A>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (10); }
	};

template <> struct generator <0x000A0A0A, 0x0A0A0A0A, 0x0A0A0A0A, 0x0A0A0A0A>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (10); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000B0000, 0x000B0000, 0x000B0000, 0x000B0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (11); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000B000B, 0x000B000B, 0x000B000B, 0x000B000B>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (11); }
	};

template <> struct generator <0x000B0B0B, 0x0B0B0B0B, 0x0B0B0B0B, 0x0B0B0B0B>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (11); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000C0000, 0x000C0000, 0x000C0000, 0x000C0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (12); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000C000C, 0x000C000C, 0x000C000C, 0x000C000C>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (12); }
	};

template <> struct generator <0x000C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (12); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000D0000, 0x000D0000, 0x000D0000, 0x000D0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (13); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000D000D, 0x000D000D, 0x000D000D, 0x000D000D>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (13); }
	};

template <> struct generator <0x000D0D0D, 0x0D0D0D0D, 0x0D0D0D0D, 0x0D0D0D0D>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (13); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000E0000, 0x000E0000, 0x000E0000, 0x000E0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (14); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000E000E, 0x000E000E, 0x000E000E, 0x000E000E>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (14); }
	};

template <> struct generator <0x000E0E0E, 0x0E0E0E0E, 0x0E0E0E0E, 0x0E0E0E0E>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (14); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (15); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0x000F000F, 0x000F000F, 0x000F000F, 0x000F000F>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (15); }
	};

template <> struct generator <0x000F0F0F, 0x0F0F0F0F, 0x0F0F0F0F, 0x0F0F0F0F>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (15); return vec_vsro (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x01000000, 0x01000000, 0x01000000, 0x01000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (1); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x01000100, 0x01000100, 0x01000100, 0x01000100>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (1); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x01010101, 0x01010101, 0x01010101, 0x01010101>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (1); }
	};

template <> struct generator <0x02000000, 0x02000000, 0x02000000, 0x02000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (2); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x02000200, 0x02000200, 0x02000200, 0x02000200>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (2); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x02020202, 0x02020202, 0x02020202, 0x02020202>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (2); }
	};

template <> struct generator <0x03000000, 0x03000000, 0x03000000, 0x03000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (3); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x03000300, 0x03000300, 0x03000300, 0x03000300>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (3); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x03030303, 0x03030303, 0x03030303, 0x03030303>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (3); }
	};

template <> struct generator <0x04000000, 0x04000000, 0x04000000, 0x04000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (4); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x04000400, 0x04000400, 0x04000400, 0x04000400>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (4); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x04010401, 0x04010401, 0x04010401, 0x04010401>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (8); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0x04040404, 0x04040404, 0x04040404, 0x04040404>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (4); }
	};

template <> struct generator <0x04210421, 0x04210421, 0x04210421, 0x04210421>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (8); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0x05000000, 0x05000000, 0x05000000, 0x05000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (5); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x05000500, 0x05000500, 0x05000500, 0x05000500>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (5); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x05050505, 0x05050505, 0x05050505, 0x05050505>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (5); }
	};

template <> struct generator <0x06000000, 0x06000000, 0x06000000, 0x06000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (6); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x06000600, 0x06000600, 0x06000600, 0x06000600>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (6); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x06060606, 0x06060606, 0x06060606, 0x06060606>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (6); }
	};

template <> struct generator <0x07000000, 0x07000000, 0x07000000, 0x07000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (7); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x07000700, 0x07000700, 0x07000700, 0x07000700>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (7); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x07070707, 0x07070707, 0x07070707, 0x07070707>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (7); }
	};

template <> struct generator <0x08000000, 0x08000000, 0x08000000, 0x08000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (8); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x08000800, 0x08000800, 0x08000800, 0x08000800>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (8); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x08080808, 0x08080808, 0x08080808, 0x08080800>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (8); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x08080808, 0x08080808, 0x08080808, 0x08080808>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (8); }
	};

template <> struct generator <0x09000000, 0x09000000, 0x09000000, 0x09000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (9); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x09000900, 0x09000900, 0x09000900, 0x09000900>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (9); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x09090909, 0x09090909, 0x09090909, 0x09090900>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (9); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x09090909, 0x09090909, 0x09090909, 0x09090909>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (9); }
	};

template <> struct generator <0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (10); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0A000A00, 0x0A000A00, 0x0A000A00, 0x0A000A00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (10); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0A0A0A0A, 0x0A0A0A0A, 0x0A0A0A0A, 0x0A0A0A00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (10); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0A0A0A0A, 0x0A0A0A0A, 0x0A0A0A0A, 0x0A0A0A0A>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (10); }
	};

template <> struct generator <0x0B000000, 0x0B000000, 0x0B000000, 0x0B000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (11); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0B000B00, 0x0B000B00, 0x0B000B00, 0x0B000B00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (11); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0B0B0B0B, 0x0B0B0B0B, 0x0B0B0B0B, 0x0B0B0B00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (11); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0B0B0B0B, 0x0B0B0B0B, 0x0B0B0B0B, 0x0B0B0B0B>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (11); }
	};

template <> struct generator <0x0C000000, 0x0C000000, 0x0C000000, 0x0C000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (12); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0C000C00, 0x0C000C00, 0x0C000C00, 0x0C000C00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (12); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (12); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (12); }
	};

template <> struct generator <0x0D000000, 0x0D000000, 0x0D000000, 0x0D000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (13); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0D000D00, 0x0D000D00, 0x0D000D00, 0x0D000D00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (13); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0D0D0D0D, 0x0D0D0D0D, 0x0D0D0D0D, 0x0D0D0D00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (13); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0D0D0D0D, 0x0D0D0D0D, 0x0D0D0D0D, 0x0D0D0D0D>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (13); }
	};

template <> struct generator <0x0E000000, 0x0E000000, 0x0E000000, 0x0E000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (14); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0E000E00, 0x0E000E00, 0x0E000E00, 0x0E000E00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (14); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0E0E0E0E, 0x0E0E0E0E, 0x0E0E0E0E, 0x0E0E0E00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (14); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0E0E0E0E, 0x0E0E0E0E, 0x0E0E0E0E, 0x0E0E0E0E>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (14); }
	};

template <> struct generator <0x0F000000, 0x0F000000, 0x0F000000, 0x0F000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (15); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0x0F000F00, 0x0F000F00, 0x0F000F00, 0x0F000F00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (15); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0x0F0F0F0F, 0x0F0F0F0F, 0x0F0F0F0F, 0x0F0F0F00>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (15); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0x0F0F0F0F, 0x0F0F0F0F, 0x0F0F0F0F, 0x0F0F0F0F>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (15); }
	};

template <> struct generator <0x7BDE7BDE, 0x7BDE7BDE, 0x7BDE7BDE, 0x7BDE7BDE>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-16); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0x7F7F7F7F, 0x7F7F7F7F, 0x7F7F7F7F, 0x7F7F7F7F>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (1); return (__vector unsigned int) vec_vpkshss (v, v); }
	};

template <> struct generator <0x7FFF7FFF, 0x7FFF7FFF, 0x7FFF7FFF, 0x7FFF7FFF>
	{
		__vector unsigned int operator() () const { __vector signed int v = (__vector signed int) vec_vspltish (1); return (__vector unsigned int) vec_vpkswss (v, v); }
	};

template <> struct generator <0x80008000, 0x80008000, 0x80008000, 0x80008000>
	{
		__vector unsigned int operator() () const { __vector signed int v = (__vector signed int) vec_vspltish (-16); return (__vector unsigned int) vec_vpkswss (v, v); }
	};

template <> struct generator <0x80808080, 0x80808080, 0x80808080, 0x80808080>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-16); return (__vector unsigned int) vec_vpkshss (v, v); }
	};

template <> struct generator <0x84218421, 0x84218421, 0x84218421, 0x84218421>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (9); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0xF0F00000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-16); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-16); }
	};

template <> struct generator <0xF0F0F0FF, 0xF0F0F0FF, 0xF0F0F0FF, 0xF0F0F0FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF0FFF0FF, 0xF0FFF0FF, 0xF0FFF0FF, 0xF0FFF0FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-16); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF0FFFFFF, 0xF0FFFFFF, 0xF0FFFFFF, 0xF0FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF1F10000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-15); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF1F1F1F1, 0xF1F1F1F1, 0xF1F1F1F1, 0xF1F1F1F1>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-15); }
	};

template <> struct generator <0xF1F1F1FF, 0xF1F1F1FF, 0xF1F1F1FF, 0xF1F1F1FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-15); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF1FFF1FF, 0xF1FFF1FF, 0xF1FFF1FF, 0xF1FFF1FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-15); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xF1FFFFFF, 0xF1FFFFFF, 0xF1FFFFFF, 0xF1FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-15); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF2F20000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-14); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF2F2F2F2, 0xF2F2F2F2, 0xF2F2F2F2, 0xF2F2F2F2>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-14); }
	};

template <> struct generator <0xF2F2F2FF, 0xF2F2F2FF, 0xF2F2F2FF, 0xF2F2F2FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-14); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF2FFF2FF, 0xF2FFF2FF, 0xF2FFF2FF, 0xF2FFF2FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-14); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF2FFFFFF, 0xF2FFFFFF, 0xF2FFFFFF, 0xF2FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-14); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF3F30000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-13); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF3F3F3F3, 0xF3F3F3F3, 0xF3F3F3F3, 0xF3F3F3F3>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-13); }
	};

template <> struct generator <0xF3FFF3FF, 0xF3FFF3FF, 0xF3FFF3FF, 0xF3FFF3FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-13); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xF3FFFFFF, 0xF3FFFFFF, 0xF3FFFFFF, 0xF3FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-13); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF4F40000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-12); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF4F4F4F4, 0xF4F4F4F4, 0xF4F4F4F4, 0xF4F4F4F4>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-12); }
	};

template <> struct generator <0xF4F4F4FF, 0xF4F4F4FF, 0xF4F4F4FF, 0xF4F4F4FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-12); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF4FFF4FF, 0xF4FFF4FF, 0xF4FFF4FF, 0xF4FFF4FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-12); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF4FFFFFF, 0xF4FFFFFF, 0xF4FFFFFF, 0xF4FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-12); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF5F50000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-11); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF5F5F5F5, 0xF5F5F5F5, 0xF5F5F5F5, 0xF5F5F5F5>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-11); }
	};

template <> struct generator <0xF5F5F5FF, 0xF5F5F5FF, 0xF5F5F5FF, 0xF5F5F5FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-11); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF5FFF5FF, 0xF5FFF5FF, 0xF5FFF5FF, 0xF5FFF5FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-11); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xF5FFFFFF, 0xF5FFFFFF, 0xF5FFFFFF, 0xF5FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-11); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF6F60000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-10); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF6F6F6F6, 0xF6F6F6F6, 0xF6F6F6F6, 0xF6F6F6F6>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-10); }
	};

template <> struct generator <0xF6F6F6FF, 0xF6F6F6FF, 0xF6F6F6FF, 0xF6F6F6FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-10); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF6FFF6FF, 0xF6FFF6FF, 0xF6FFF6FF, 0xF6FFF6FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-10); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF6FFFFFF, 0xF6FFFFFF, 0xF6FFFFFF, 0xF6FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-10); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF7F70000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-9); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF7F7F7F7, 0xF7F7F7F7, 0xF7F7F7F7, 0xF7F7F7F7>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-9); }
	};

template <> struct generator <0xF7FFF7FF, 0xF7FFF7FF, 0xF7FFF7FF, 0xF7FFF7FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-9); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-9); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF8000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-8); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF8F8F8F8, 0xF8F8F8F8, 0xF8F8F8F8, 0xF8F8F8F8>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-8); }
	};

template <> struct generator <0xF8F8F8FF, 0xF8F8F8FF, 0xF8F8F8FF, 0xF8F8F8FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-8); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF8FFF8FF, 0xF8FFF8FF, 0xF8FFF8FF, 0xF8FFF8FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-8); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF8FFFFFF, 0xF8FFFFFF, 0xF8FFFFFF, 0xF8FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-8); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xF9000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-7); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF9F9F9F9, 0xF9F9F9F9, 0xF9F9F9F9, 0xF9F9F9F9>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-7); }
	};

template <> struct generator <0xF9F9F9FF, 0xF9F9F9FF, 0xF9F9F9FF, 0xF9F9F9FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-7); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xF9FFF9FF, 0xF9FFF9FF, 0xF9FFF9FF, 0xF9FFF9FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-7); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xF9FFFFFF, 0xF9FFFFFF, 0xF9FFFFFF, 0xF9FFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-7); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFA000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-6); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFAFAFAFA, 0xFAFAFAFA, 0xFAFAFAFA, 0xFAFAFAFA>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-6); }
	};

template <> struct generator <0xFAFAFAFF, 0xFAFAFAFF, 0xFAFAFAFF, 0xFAFAFAFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-6); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFAFFFAFF, 0xFAFFFAFF, 0xFAFFFAFF, 0xFAFFFAFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-6); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFAFFFFFF, 0xFAFFFFFF, 0xFAFFFFFF, 0xFAFFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-6); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFB000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-5); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFBDEFBDE, 0xFBDEFBDE, 0xFBDEFBDE, 0xFBDEFBDE>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisb (-15); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0xFBFBFBFB, 0xFBFBFBFB, 0xFBFBFBFB, 0xFBFBFBFB>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-5); }
	};

template <> struct generator <0xFBFEFBFE, 0xFBFEFBFE, 0xFBFEFBFE, 0xFBFEFBFE>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-16); return (__vector unsigned int) vec_vpkpx (v, v); }
	};

template <> struct generator <0xFBFFFBFF, 0xFBFFFBFF, 0xFBFFFBFF, 0xFBFFFBFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-5); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFBFFFFFF, 0xFBFFFFFF, 0xFBFFFFFF, 0xFBFFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-5); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFC000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-4); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFCFCFCFC, 0xFCFCFCFC, 0xFCFCFCFC, 0xFCFCFCFC>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-4); }
	};

template <> struct generator <0xFCFCFCFF, 0xFCFCFCFF, 0xFCFCFCFF, 0xFCFCFCFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-4); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFCFFFCFF, 0xFCFFFCFF, 0xFCFFFCFF, 0xFCFFFCFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-4); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFCFFFFFF, 0xFCFFFFFF, 0xFCFFFFFF, 0xFCFFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-4); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFD000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-3); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFDFDFDFD, 0xFDFDFDFD, 0xFDFDFDFD, 0xFDFDFDFD>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-3); }
	};

template <> struct generator <0xFDFDFDFF, 0xFDFDFDFF, 0xFDFDFDFF, 0xFDFDFDFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-3); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFDFFFDFF, 0xFDFFFDFF, 0xFDFFFDFF, 0xFDFFFDFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-3); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFDFFFFFF, 0xFDFFFFFF, 0xFDFFFFFF, 0xFDFFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-3); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFE000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-2); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFEFEFEFE, 0xFEFEFEFE, 0xFEFEFEFE, 0xFEFEFEFE>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisb (-2); }
	};

template <> struct generator <0xFEFEFEFF, 0xFEFEFEFF, 0xFEFEFEFF, 0xFEFEFEFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-2); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFEFFFEFF, 0xFEFFFEFF, 0xFEFFFEFF, 0xFEFFFEFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltish (-2); return vec_vperm (v, v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFEFFFFFF, 0xFEFFFFFF, 0xFEFFFFFF, 0xFEFFFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-2); return vec_vsldoi (v, v, 3); }
	};

template <> struct generator <0xFF000000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-1); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFF1C0710, 0xFF1C0710, 0xFF1C0710, 0xFF1C0710>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-16); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1C0F11, 0xFF1C0F11, 0xFF1C0F11, 0xFF1C0F11>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-15); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1C1712, 0xFF1C1712, 0xFF1C1712, 0xFF1C1712>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-14); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1C1F13, 0xFF1C1F13, 0xFF1C1F13, 0xFF1C1F13>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-13); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1D0714, 0xFF1D0714, 0xFF1D0714, 0xFF1D0714>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-12); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1D0F15, 0xFF1D0F15, 0xFF1D0F15, 0xFF1D0F15>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-11); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1D1716, 0xFF1D1716, 0xFF1D1716, 0xFF1D1716>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-10); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1D1F17, 0xFF1D1F17, 0xFF1D1F17, 0xFF1D1F17>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-9); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1E0718, 0xFF1E0718, 0xFF1E0718, 0xFF1E0718>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-8); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1E0F19, 0xFF1E0F19, 0xFF1E0F19, 0xFF1E0F19>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-7); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1E171A, 0xFF1E171A, 0xFF1E171A, 0xFF1E171A>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-6); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1E1F1B, 0xFF1E1F1B, 0xFF1E1F1B, 0xFF1E1F1B>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-5); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F071C, 0xFF1F071C, 0xFF1F071C, 0xFF1F071C>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-4); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F0F1D, 0xFF1F0F1D, 0xFF1F0F1D, 0xFF1F0F1D>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-3); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F171E, 0xFF1F171E, 0xFF1F171E, 0xFF1F171E>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisb (-2); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F10, 0xFF1F1F10, 0xFF1F1F10, 0xFF1F1F10>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-16); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F11, 0xFF1F1F11, 0xFF1F1F11, 0xFF1F1F11>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-15); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F12, 0xFF1F1F12, 0xFF1F1F12, 0xFF1F1F12>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-14); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F13, 0xFF1F1F13, 0xFF1F1F13, 0xFF1F1F13>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-13); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F14, 0xFF1F1F14, 0xFF1F1F14, 0xFF1F1F14>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-12); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F15, 0xFF1F1F15, 0xFF1F1F15, 0xFF1F1F15>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-11); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F16, 0xFF1F1F16, 0xFF1F1F16, 0xFF1F1F16>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-10); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F17, 0xFF1F1F17, 0xFF1F1F17, 0xFF1F1F17>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-9); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F18, 0xFF1F1F18, 0xFF1F1F18, 0xFF1F1F18>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-8); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F19, 0xFF1F1F19, 0xFF1F1F19, 0xFF1F1F19>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-7); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1A, 0xFF1F1F1A, 0xFF1F1F1A, 0xFF1F1F1A>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-6); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1B, 0xFF1F1F1B, 0xFF1F1F1B, 0xFF1F1F1B>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-5); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1C, 0xFF1F1F1C, 0xFF1F1F1C, 0xFF1F1F1C>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-4); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1D, 0xFF1F1F1D, 0xFF1F1F1D, 0xFF1F1F1D>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-3); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1E, 0xFF1F1F1E, 0xFF1F1F1E, 0xFF1F1F1E>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltish (-2); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F10, 0xFF1F1F1F, 0xFF1F1F10>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-16); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F11, 0xFF1F1F1F, 0xFF1F1F11>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-15); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F12, 0xFF1F1F1F, 0xFF1F1F12>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-14); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F13, 0xFF1F1F1F, 0xFF1F1F13>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-13); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F14, 0xFF1F1F1F, 0xFF1F1F14>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-12); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F15, 0xFF1F1F1F, 0xFF1F1F15>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-11); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F16, 0xFF1F1F1F, 0xFF1F1F16>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-10); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F17, 0xFF1F1F1F, 0xFF1F1F17>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-9); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F18, 0xFF1F1F1F, 0xFF1F1F18>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-8); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F19, 0xFF1F1F1F, 0xFF1F1F19>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-7); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1A, 0xFF1F1F1F, 0xFF1F1F1A>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-6); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1B, 0xFF1F1F1F, 0xFF1F1F1B>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-5); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1C, 0xFF1F1F1F, 0xFF1F1F1C>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-4); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1D, 0xFF1F1F1F, 0xFF1F1F1D>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-3); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1E, 0xFF1F1F1F, 0xFF1F1F1E>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-2); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFF1F1F1F, 0xFF1F1F1F, 0xFF1F1F1F, 0xFF1F1F1F>
	{
		__vector unsigned int operator() () const { __vector pixel v = (__vector pixel) vec_vspltisw (-1); return vec_vupkhpx (v); }
	};

template <> struct generator <0xFFF00000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF0FFF0, 0xFFF0FFF0, 0xFFF0FFF0, 0xFFF0FFF0>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-16); }
	};

template <> struct generator <0xFFF0FFFF, 0xFFF0FFFF, 0xFFF0FFFF, 0xFFF0FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF10000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-15); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF1FFF1, 0xFFF1FFF1, 0xFFF1FFF1, 0xFFF1FFF1>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-15); }
	};

template <> struct generator <0xFFF1FFFF, 0xFFF1FFFF, 0xFFF1FFFF, 0xFFF1FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-15); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF20000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-14); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF2FFF2, 0xFFF2FFF2, 0xFFF2FFF2, 0xFFF2FFF2>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-14); }
	};

template <> struct generator <0xFFF2FFFF, 0xFFF2FFFF, 0xFFF2FFFF, 0xFFF2FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-14); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF30000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-13); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF3FFF3, 0xFFF3FFF3, 0xFFF3FFF3, 0xFFF3FFF3>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-13); }
	};

template <> struct generator <0xFFF3FFFF, 0xFFF3FFFF, 0xFFF3FFFF, 0xFFF3FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-13); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF40000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-12); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF4FFF4, 0xFFF4FFF4, 0xFFF4FFF4, 0xFFF4FFF4>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-12); }
	};

template <> struct generator <0xFFF4FFFF, 0xFFF4FFFF, 0xFFF4FFFF, 0xFFF4FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-12); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF50000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-11); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF5FFF5, 0xFFF5FFF5, 0xFFF5FFF5, 0xFFF5FFF5>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-11); }
	};

template <> struct generator <0xFFF5FFFF, 0xFFF5FFFF, 0xFFF5FFFF, 0xFFF5FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-11); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF60000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-10); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF6FFF6, 0xFFF6FFF6, 0xFFF6FFF6, 0xFFF6FFF6>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-10); }
	};

template <> struct generator <0xFFF6FFFF, 0xFFF6FFFF, 0xFFF6FFFF, 0xFFF6FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-10); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF70000, 0x00000000, 0x00000000, 0x00000000>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-9); return vec_vslo (v, (__vector unsigned char) v); }
	};

template <> struct generator <0xFFF7FFF7, 0xFFF7FFF7, 0xFFF7FFF7, 0xFFF7FFF7>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-9); }
	};

template <> struct generator <0xFFF7FFFF, 0xFFF7FFFF, 0xFFF7FFFF, 0xFFF7FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-9); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF8FFF8, 0xFFF8FFF8, 0xFFF8FFF8, 0xFFF8FFF8>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-8); }
	};

template <> struct generator <0xFFF8FFFF, 0xFFF8FFFF, 0xFFF8FFFF, 0xFFF8FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-8); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFF9FFF9, 0xFFF9FFF9, 0xFFF9FFF9, 0xFFF9FFF9>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-7); }
	};

template <> struct generator <0xFFF9FFFF, 0xFFF9FFFF, 0xFFF9FFFF, 0xFFF9FFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-7); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFAFFFA, 0xFFFAFFFA, 0xFFFAFFFA, 0xFFFAFFFA>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-6); }
	};

template <> struct generator <0xFFFAFFFF, 0xFFFAFFFF, 0xFFFAFFFF, 0xFFFAFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-6); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFBFFFB, 0xFFFBFFFB, 0xFFFBFFFB, 0xFFFBFFFB>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-5); }
	};

template <> struct generator <0xFFFBFFFF, 0xFFFBFFFF, 0xFFFBFFFF, 0xFFFBFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-5); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFCFFFC, 0xFFFCFFFC, 0xFFFCFFFC, 0xFFFCFFFC>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-4); }
	};

template <> struct generator <0xFFFCFFFF, 0xFFFCFFFF, 0xFFFCFFFF, 0xFFFCFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-4); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFDFFFD, 0xFFFDFFFD, 0xFFFDFFFD, 0xFFFDFFFD>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-3); }
	};

template <> struct generator <0xFFFDFFFF, 0xFFFDFFFF, 0xFFFDFFFF, 0xFFFDFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-3); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFEFFFE, 0xFFFEFFFE, 0xFFFEFFFE, 0xFFFEFFFE>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltish (-2); }
	};

template <> struct generator <0xFFFEFFFF, 0xFFFEFFFF, 0xFFFEFFFF, 0xFFFEFFFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-2); return vec_vsldoi (v, v, 2); }
	};

template <> struct generator <0xFFFFF0F0, 0xFFFFF0F0, 0xFFFFF0F0, 0xFFFFF0F0>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-16); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF0FF, 0xFFFFF0FF, 0xFFFFF0FF, 0xFFFFF0FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-16); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF1F1, 0xFFFFF1F1, 0xFFFFF1F1, 0xFFFFF1F1>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-15); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF1FF, 0xFFFFF1FF, 0xFFFFF1FF, 0xFFFFF1FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-15); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF2F2, 0xFFFFF2F2, 0xFFFFF2F2, 0xFFFFF2F2>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-14); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF2FF, 0xFFFFF2FF, 0xFFFFF2FF, 0xFFFFF2FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-14); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF3F3, 0xFFFFF3F3, 0xFFFFF3F3, 0xFFFFF3F3>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-13); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF3FF, 0xFFFFF3FF, 0xFFFFF3FF, 0xFFFFF3FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-13); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF4F4, 0xFFFFF4F4, 0xFFFFF4F4, 0xFFFFF4F4>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-12); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF4FF, 0xFFFFF4FF, 0xFFFFF4FF, 0xFFFFF4FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-12); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF5F5, 0xFFFFF5F5, 0xFFFFF5F5, 0xFFFFF5F5>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-11); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF5FF, 0xFFFFF5FF, 0xFFFFF5FF, 0xFFFFF5FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-11); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF6F6, 0xFFFFF6F6, 0xFFFFF6F6, 0xFFFFF6F6>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-10); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF6FF, 0xFFFFF6FF, 0xFFFFF6FF, 0xFFFFF6FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-10); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF7F7, 0xFFFFF7F7, 0xFFFFF7F7, 0xFFFFF7F7>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-9); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF7FF, 0xFFFFF7FF, 0xFFFFF7FF, 0xFFFFF7FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-9); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF8F8, 0xFFFFF8F8, 0xFFFFF8F8, 0xFFFFF8F8>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-8); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF8FF, 0xFFFFF8FF, 0xFFFFF8FF, 0xFFFFF8FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-8); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFF9F9, 0xFFFFF9F9, 0xFFFFF9F9, 0xFFFFF9F9>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-7); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFF9FF, 0xFFFFF9FF, 0xFFFFF9FF, 0xFFFFF9FF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-7); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFAFA, 0xFFFFFAFA, 0xFFFFFAFA, 0xFFFFFAFA>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-6); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFFAFF, 0xFFFFFAFF, 0xFFFFFAFF, 0xFFFFFAFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-6); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFBFB, 0xFFFFFBFB, 0xFFFFFBFB, 0xFFFFFBFB>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-5); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFFBFF, 0xFFFFFBFF, 0xFFFFFBFF, 0xFFFFFBFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-5); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFCFC, 0xFFFFFCFC, 0xFFFFFCFC, 0xFFFFFCFC>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-4); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFFCFF, 0xFFFFFCFF, 0xFFFFFCFF, 0xFFFFFCFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-4); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFDFD, 0xFFFFFDFD, 0xFFFFFDFD, 0xFFFFFDFD>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-3); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFFDFF, 0xFFFFFDFF, 0xFFFFFDFF, 0xFFFFFDFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-3); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFEFE, 0xFFFFFEFE, 0xFFFFFEFE, 0xFFFFFEFE>
	{
		__vector unsigned int operator() () const { __vector signed short v = (__vector signed short) vec_vspltisb (-2); return (__vector unsigned int) vec_vupkhsh (v); }
	};

template <> struct generator <0xFFFFFEFF, 0xFFFFFEFF, 0xFFFFFEFF, 0xFFFFFEFF>
	{
		__vector unsigned int operator() () const { __vector unsigned int v = (__vector unsigned int) vec_vspltisw (-2); return vec_vsldoi (v, v, 1); }
	};

template <> struct generator <0xFFFFFFF0, 0xFFFFFFF0, 0xFFFFFFF0, 0xFFFFFFF0>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-16); }
	};

template <> struct generator <0xFFFFFFF1, 0xFFFFFFF1, 0xFFFFFFF1, 0xFFFFFFF1>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-15); }
	};

template <> struct generator <0xFFFFFFF2, 0xFFFFFFF2, 0xFFFFFFF2, 0xFFFFFFF2>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-14); }
	};

template <> struct generator <0xFFFFFFF3, 0xFFFFFFF3, 0xFFFFFFF3, 0xFFFFFFF3>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-13); }
	};

template <> struct generator <0xFFFFFFF4, 0xFFFFFFF4, 0xFFFFFFF4, 0xFFFFFFF4>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-12); }
	};

template <> struct generator <0xFFFFFFF5, 0xFFFFFFF5, 0xFFFFFFF5, 0xFFFFFFF5>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-11); }
	};

template <> struct generator <0xFFFFFFF6, 0xFFFFFFF6, 0xFFFFFFF6, 0xFFFFFFF6>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-10); }
	};

template <> struct generator <0xFFFFFFF7, 0xFFFFFFF7, 0xFFFFFFF7, 0xFFFFFFF7>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-9); }
	};

template <> struct generator <0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-8); }
	};

template <> struct generator <0xFFFFFFF9, 0xFFFFFFF9, 0xFFFFFFF9, 0xFFFFFFF9>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-7); }
	};

template <> struct generator <0xFFFFFFFA, 0xFFFFFFFA, 0xFFFFFFFA, 0xFFFFFFFA>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-6); }
	};

template <> struct generator <0xFFFFFFFB, 0xFFFFFFFB, 0xFFFFFFFB, 0xFFFFFFFB>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-5); }
	};

template <> struct generator <0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-4); }
	};

template <> struct generator <0xFFFFFFFD, 0xFFFFFFFD, 0xFFFFFFFD, 0xFFFFFFFD>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-3); }
	};

template <> struct generator <0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-2); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF0FFF0, 0xFFFFFFFF, 0xFFF0FFF0>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-16); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF1FFF1, 0xFFFFFFFF, 0xFFF1FFF1>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-15); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF2FFF2, 0xFFFFFFFF, 0xFFF2FFF2>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-14); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF3FFF3, 0xFFFFFFFF, 0xFFF3FFF3>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-13); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF4FFF4, 0xFFFFFFFF, 0xFFF4FFF4>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-12); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF5FFF5, 0xFFFFFFFF, 0xFFF5FFF5>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-11); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF6FFF6, 0xFFFFFFFF, 0xFFF6FFF6>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-10); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF7FFF7, 0xFFFFFFFF, 0xFFF7FFF7>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-9); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF8FFF8, 0xFFFFFFFF, 0xFFF8FFF8>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-8); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFF9FFF9, 0xFFFFFFFF, 0xFFF9FFF9>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-7); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFAFFFA, 0xFFFFFFFF, 0xFFFAFFFA>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-6); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFBFFFB, 0xFFFFFFFF, 0xFFFBFFFB>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-5); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFCFFFC, 0xFFFFFFFF, 0xFFFCFFFC>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-4); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFDFFFD, 0xFFFFFFFF, 0xFFFDFFFD>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-3); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFEFFFE, 0xFFFFFFFF, 0xFFFEFFFE>
	{
		__vector unsigned int operator() () const { __vector unsigned short v = (__vector unsigned short) vec_vspltisw (-2); return (__vector unsigned int) vec_vmrghh (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF0F0, 0xFFFFFFFF, 0xFFFFF0F0>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-16); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF1F1, 0xFFFFFFFF, 0xFFFFF1F1>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-15); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF2F2, 0xFFFFFFFF, 0xFFFFF2F2>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-14); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF3F3, 0xFFFFFFFF, 0xFFFFF3F3>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-13); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF4F4, 0xFFFFFFFF, 0xFFFFF4F4>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-12); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF5F5, 0xFFFFFFFF, 0xFFFFF5F5>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-11); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF6F6, 0xFFFFFFFF, 0xFFFFF6F6>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-10); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF7F7, 0xFFFFFFFF, 0xFFFFF7F7>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-9); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF8F8, 0xFFFFFFFF, 0xFFFFF8F8>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-8); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFF9F9, 0xFFFFFFFF, 0xFFFFF9F9>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-7); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFAFA, 0xFFFFFFFF, 0xFFFFFAFA>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-6); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFBFB, 0xFFFFFFFF, 0xFFFFFBFB>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-5); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFCFC, 0xFFFFFFFF, 0xFFFFFCFC>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-4); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFDFD, 0xFFFFFFFF, 0xFFFFFDFD>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-3); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFEFE, 0xFFFFFFFF, 0xFFFFFEFE>
	{
		__vector unsigned int operator() () const { __vector unsigned char v = (__vector unsigned char) vec_vspltisw (-2); return (__vector unsigned int) vec_vmrghb (v, v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFF0>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-16); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF1, 0xFFFFFFFF, 0xFFFFFFF1>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-15); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF2, 0xFFFFFFFF, 0xFFFFFFF2>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-14); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF3, 0xFFFFFFFF, 0xFFFFFFF3>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-13); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF4, 0xFFFFFFFF, 0xFFFFFFF4>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-12); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFF5>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-11); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFF6>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-10); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFF7>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-9); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFF8>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-8); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFF9, 0xFFFFFFFF, 0xFFFFFFF9>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-7); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFA>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-6); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFB>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-5); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFC>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-4); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFD>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-3); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE>
	{
		__vector unsigned int operator() () const { __vector signed char v = (__vector signed char) vec_vspltisw (-2); return (__vector unsigned int) vec_vupkhsb (v); }
	};

template <> struct generator <0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF>
	{
		__vector unsigned int operator() () const { return (__vector unsigned int) vec_vspltisw (-1); }
	};
	
#endif

