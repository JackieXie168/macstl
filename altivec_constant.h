/*
 *  altivec_constant.h
 *  macstl
 *
 *  Created by Glen Low on Mon Sep 22 2003.
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

/**
 * @file altivec_constant.h
 * @ingroup altivec_public
 * @brief Altivec constants
 *
 * Declares the macstl::altivec_constant function.
 */
 
#ifndef MACSTL_ALTIVEC_CONSTANT_H
#define MACSTL_ALTIVEC_CONSTANT_H

#include <altivec_type.h>

namespace macstl
	{
		namespace impl
			{
				// instead of repeating ugly casts in the generator code, we abstract them all into opcodes that take and return v
				
				typedef __vector unsigned short v;
				
				typedef __vector unsigned char vub;
				typedef __vector signed char vsb;
				typedef __vector unsigned short vuh;
				typedef __vector signed short vsh;
				typedef __vector unsigned int vuw;
				typedef __vector signed int vsw;
				
				inline v vaddsbs (v v0, v v1)		{ return static_cast <v> (vec_vaddsbs (static_cast <vsb> (v0), static_cast <vsb> (v1))); }
				inline v vaddubm (v v0, v v1)		{ return static_cast <v> (vec_vaddubm (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vaddubs (v v0, v v1)		{ return static_cast <v> (vec_vaddubs (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vadduhm (v v0, v v1)		{ return static_cast <v> (vec_vadduhm (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vand (v v0, v v1)			{ return vec_vand (v0, v1); }
				inline v vandc (v v0, v v1)			{ return vec_vandc (v0, v1); }
				inline v vavgsb (v v0, v v1)		{ return static_cast <v> (vec_vavgsb (static_cast <vsb> (v0), static_cast <vsb> (v1))); }
				inline v vavgsh (v v0, v v1)		{ return static_cast <v> (vec_vavgsh (static_cast <vsh> (v0), static_cast <vsh> (v1))); }
				inline v vavgub (v v0, v v1)		{ return static_cast <v> (vec_vavgub (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vavguh (v v0, v v1)		{ return static_cast <v> (vec_vavguh (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vnor (v v0, v v1)			{ return vec_vnor (v0, v1); }
				inline v vor (v v0, v v1)			{ return vec_vor (v0, v1); }
				inline v vmaxub (v v0, v v1)		{ return static_cast <v> (vec_vmaxub (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vmaxsb (v v0, v v1)		{ return static_cast <v> (vec_vmaxsb (static_cast <vsb> (v0), static_cast <vsb> (v1))); }
				inline v vminsb (v v0, v v1)		{ return static_cast <v> (vec_vminsb (static_cast <vsb> (v0), static_cast <vsb> (v1))); }
				inline v vminub (v v0, v v1)		{ return static_cast <v> (vec_vminub (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vmrghb (v v0, v v1)		{ return static_cast <v> (vec_vmrghb (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vperm (v v0, v v1, v v2)	{ return static_cast <v> (vec_vperm (v0, v1, static_cast <vub> (v2))); }
				inline v vpkpx (v v0, v v1)			{ return static_cast <v> (vec_vpkpx (static_cast <vuw> (v0), static_cast <vuw> (v1))); }
				inline v vpkshss (v v0, v v1)		{ return static_cast <v> (vec_vpkshss (static_cast <vsh> (v0), static_cast <vsh> (v1))); }
				inline v vrlb (v v0, v v1)			{ return static_cast <v> (vec_vrlb (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vrlh (v v0, v v1)			{ return static_cast <v> (vec_vrlh (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vsel (v v0, v v1, v v2)	{ return static_cast <v> (vec_vsel (v0, v1, v2)); }
				inline v vslb (v v0, v v1)			{ return static_cast <v> (vec_vslb (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vslh (v v0, v v1)			{ return static_cast <v> (vec_vslh (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vsrab (v v0, v v1)			{ return static_cast <v> (vec_vsrab (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vsrah (v v0, v v1)			{ return static_cast <v> (vec_vsrah (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vsrb (v v0, v v1)			{ return static_cast <v> (vec_vsrb (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vsrh (v v0, v v1)			{ return static_cast <v> (vec_vsrh (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vsubsbs (v v0, v v1)		{ return static_cast <v> (vec_vsubsbs (static_cast <vsb> (v0), static_cast <vsb> (v1))); }
				inline v vsububs (v v0, v v1)		{ return static_cast <v> (vec_vsububs (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vsububm (v v0, v v1)		{ return static_cast <v> (vec_vsububm (static_cast <vub> (v0), static_cast <vub> (v1))); }
				inline v vsubuhm (v v0, v v1)		{ return static_cast <v> (vec_vsubuhm (static_cast <vuh> (v0), static_cast <vuh> (v1))); }
				inline v vupkhsb (v v0)				{ return static_cast <v> (vec_vupkhsb (static_cast <vsb> (v0))); }
				inline v vxor (v v0, v v1)			{ return vec_vxor (v0, v1); }
	
				template <int i> inline v vspltib ()			{ return static_cast <v> (vec_splat_u8 (i)); }
				template <int i> inline v vspltih ()			{ return static_cast <v> (vec_splat_u16 (i)); }
				template <int i> inline v vsldoi (v v0, v v1)	{ return vec_sld (v0, v1, i); }
			
				// for short constants, specializations will use Holger Bettag's algorithmically
				// derived list of optimal Altivec short constants, given the C++ treatment...

				template <unsigned char hi, unsigned char lo> struct generator
					{
						static v call ()
							{
								return altivec_traits <unsigned short>::splat (hi * 0x100 + lo);
							}
					};
							
				#ifdef NDEBUG
				#include <internal/generator.h>
				#endif
				
				// for long constants, dispatch repeated shorts to the generator, else try to map to vec_splat
				
				template <unsigned short hi, unsigned short lo> struct long_generator;
				
				template <unsigned short value> struct long_generator <value, value>
					{
						static v call ()	{ return generator <value / 0x100, value % 0x100>::call (); }
					};
					
				template <> struct long_generator <0xFFFF, 0xFFF0> { static vuw call () { return vec_splat_u32 (-16); } };
				template <> struct long_generator <0xFFFF, 0xFFF1> { static vuw call () { return vec_splat_u32 (-15); } };
				template <> struct long_generator <0xFFFF, 0xFFF2> { static vuw call () { return vec_splat_u32 (-14); } };
				template <> struct long_generator <0xFFFF, 0xFFF3> { static vuw call () { return vec_splat_u32 (-13); } };
				template <> struct long_generator <0xFFFF, 0xFFF4> { static vuw call () { return vec_splat_u32 (-12); } };
				template <> struct long_generator <0xFFFF, 0xFFF5> { static vuw call () { return vec_splat_u32 (-11); } };
				template <> struct long_generator <0xFFFF, 0xFFF6> { static vuw call () { return vec_splat_u32 (-10); } };
				template <> struct long_generator <0xFFFF, 0xFFF7> { static vuw call () { return vec_splat_u32 (-9); } };
				template <> struct long_generator <0xFFFF, 0xFFF8> { static vuw call () { return vec_splat_u32 (-8); } };
				template <> struct long_generator <0xFFFF, 0xFFF9> { static vuw call () { return vec_splat_u32 (-7); } };
				template <> struct long_generator <0xFFFF, 0xFFFA> { static vuw call () { return vec_splat_u32 (-6); } };
				template <> struct long_generator <0xFFFF, 0xFFFB> { static vuw call () { return vec_splat_u32 (-5); } };
				template <> struct long_generator <0xFFFF, 0xFFFC> { static vuw call () { return vec_splat_u32 (-4); } };
				template <> struct long_generator <0xFFFF, 0xFFFD> { static vuw call () { return vec_splat_u32 (-3); } };
				template <> struct long_generator <0xFFFF, 0xFFFE> { static vuw call () { return vec_splat_u32 (-2); } };
				template <> struct long_generator <0xFFFF, 0xFFFF> { static vuw call () { return vec_splat_u32 (-1); } };
				template <> struct long_generator <0x0000, 0x0000> { static vuw call () { return vec_splat_u32 (0); } };
				template <> struct long_generator <0x0000, 0x0001> { static vuw call () { return vec_splat_u32 (1); } };
				template <> struct long_generator <0x0000, 0x0002> { static vuw call () { return vec_splat_u32 (2); } };
				template <> struct long_generator <0x0000, 0x0003> { static vuw call () { return vec_splat_u32 (3); } };
				template <> struct long_generator <0x0000, 0x0004> { static vuw call () { return vec_splat_u32 (4); } };
				template <> struct long_generator <0x0000, 0x0005> { static vuw call () { return vec_splat_u32 (5); } };
				template <> struct long_generator <0x0000, 0x0006> { static vuw call () { return vec_splat_u32 (6); } };
				template <> struct long_generator <0x0000, 0x0007> { static vuw call () { return vec_splat_u32 (7); } };
				template <> struct long_generator <0x0000, 0x0008> { static vuw call () { return vec_splat_u32 (8); } };
				template <> struct long_generator <0x0000, 0x0009> { static vuw call () { return vec_splat_u32 (9); } };
				template <> struct long_generator <0x0000, 0x000A> { static vuw call () { return vec_splat_u32 (10); } };
				template <> struct long_generator <0x0000, 0x000B> { static vuw call () { return vec_splat_u32 (11); } };
				template <> struct long_generator <0x0000, 0x000C> { static vuw call () { return vec_splat_u32 (12); } };
				template <> struct long_generator <0x0000, 0x000D> { static vuw call () { return vec_splat_u32 (13); } };
				template <> struct long_generator <0x0000, 0x000E> { static vuw call () { return vec_splat_u32 (14); } };
				template <> struct long_generator <0x0000, 0x000F> { static vuw call () { return vec_splat_u32 (15); } };
					
				template <typename Type, Type value> struct altivec_constant_dispatch;
				
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec unsigned constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for unsigned chars to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <unsigned char value> struct altivec_constant_dispatch <unsigned char, value>
					{
						/** Calls the appropriate generator. */
						static altivec <unsigned char> call ()
							{
								return static_cast <__vector unsigned char> (generator <value, value>::call ());
							}
					};
					
				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec char constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for chars to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <char value> struct altivec_constant_dispatch <char, value>
					{
						/** Calls the appropriate generator. */
						static altivec <char> call ()
							{
								return static_cast <__vector signed char>
									(generator <static_cast <unsigned char> (value), static_cast <unsigned char> (value)>::call ());
							}
					};

				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec unsigned short constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for unsigned shorts to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <unsigned short value> struct altivec_constant_dispatch <unsigned short, value>
					{
						/** Calls the appropriate generator. */
						static altivec <unsigned short> call ()
							{
								return generator <value / 0x100, value % 0x100>::call ();
							}
					};

				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec short constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for shorts to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <short value> struct altivec_constant_dispatch <short, value>
					{
						/** Calls the appropriate generator. */
						static altivec <short> call ()
							{
								return static_cast <__vector signed short>
									(generator <static_cast <unsigned short> (value) / 0x100, static_cast <unsigned short> (value) % 0x100>::call ());
							}
					};

				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec unsigned long constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for unsigned longs to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <unsigned long value> struct altivec_constant_dispatch <unsigned long, value>
					{
						/** Calls the appropriate generator. */
						static altivec <unsigned long> call ()
							{
								return static_cast <__vector unsigned int> (long_generator <value / 0x10000, value % 0x10000>::call ());
							}
					};

				/**
				 * @internal
				 * @ingroup altivec_internal
				 * @brief Dispatcher for Altivec long constants.
				 * @param value The value to repeat.
				 *
				 * Dispatches altivec_constant calls for longs to the appropriate generator, since we can't partially specialize the
				 * altivec_constant function template.
				 */
				template <long value> struct altivec_constant_dispatch <long, value>
					{
						/** Calls the appropriate generator. */
						static altivec <long> call ()
							{
								return static_cast <__vector signed short>
									(long_generator <static_cast <unsigned long> (value) / 0x10000, static_cast <unsigned long> (value) % 0x10000>::call ());
							}
					};										
			}
			
		/**
		 * @ingroup altivec_public
		 * @brief Generated Altivec constant.
		 *
		 * Generates an altivec object with the given value repeated. When you code <code>(vector short) (1234)</code>, most compilers will translate
		 * that into a slow memory load. The equivalent call <code>altivec_constant \<short, 1234\> ()</code> generates the required constant
		 * entirely in the CPU, using an optimal series of Altivec instructions.
		 */		 
		template <typename Type, Type value> inline altivec <Type> altivec_constant ()
			{
				return impl::altivec_constant_dispatch <Type, value>::call ();
			}
	}

#endif
