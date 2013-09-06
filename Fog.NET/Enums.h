/******************************************************************************
*
* Name:     Enums.h
* Project:  Fog-Framework (Copyright (c) 2006-2011, Petr Kobalicek <kobalicek.petr@gmail.com>) C++/CLI Interface
* Author:   Maxim Rylov
*
******************************************************************************
* The MIT License (MIT)
*
* Copyright (C) 2012, Maxim Rylov
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*****************************************************************************/

#pragma once

namespace FogNET
{
	public enum class ImageFormat
	{
		PRGB32 = 0,

	//! @brief 32-bit RGB (8 bits per component).
	//!
	//! Supported natively by these libraries:
	//!   - Cairo (CAIRO_FORMAT_RGB24)
	//!   - CGImageRef (8bpc, 32bpp, Default byte-order, skip alpha last).
	//!   - DIBSECTION (32bpp, RGB)
	//!   - Qt (QImage::Format_RGB32)
		XRGB32 = 1,

	//! @brief 24-bit RGB (8 bits per component).
	//!
	//! Supported natively by these libraries:
	//!   - DIBSECTION (24bpp, RGB)
		RGB24 = 2,

	//! @brief 8-bit ALPHA.
	//!
	//! Supported natively by these libraries:
	//!   - Cairo (CAIRO_FORMAT_A8)
	//!   - CGImageRef (8bpc, 8bpp, alpha only).
	//!   - DIBSECTION (8bpp, palette)
		A8 = 3,

	//! @brief 8-bit INDEXED (RGB32 palette, without alpha).
		I8 = 4,

	// --------------------------------------------------------------------------
	// [16-bit Per Component]
	// --------------------------------------------------------------------------

	//! @brief 64-bit ARGB (16 bits per component), premultiplied.
		PRGB64 = 5,
	//! @brief 48-bit RGB (16 bits per component).
		RGB48 = 6,
	//! @brief 16-bit ALPHA.
		A16 = 7
	};

	public enum class ImageQuality
    {
		Nearest = 0,
        Bilinear = 1,
        Bicubic = 2,

        BilinearHighQuality = 3,
        BicubicHighQuality = 4,

        Default = Bilinear,
	};

    public enum class RenderQuality
	{
		//! @brief Aliased (disabled antialiasing).
		Aliased = 0,

		//! @brief Use at least 4 shades of grey for antialiasing.
		//!
		//! This is only recommendation for paint-engine. It can use higher render
		//! quality if this option is not supported.
		Grey4 = 1,

		//! @brief Use at least 8 shades of grey for antialiasing.
		//!
		//! This is only recommendation for paint-engine. It can use higher or lower
		//! render quality if this option is not supported.
		Grey8 = 2,

		//! @brief Use at least 16 shades of grey for antialiasing.
		//!
		//! This is only recommendation for paint-engine. It can use higher or lower
		//! render quality if this option is not supported.
		Grey16 = 3,

		//! @brief Use at least 32 shades of grey for antialiasing.
		//!
		//! This is only recommendation for paint-engine. It can use higher or lower
		//! render quality if this option is not supported.
		Grey32 = 4,

		//! @brief Use at least 64 shades of grey for antialiasing.
		//!
		//! This is only recommendation for paint-engine. It can use higher or lower
		//! render quality if this option is not supported.
		Grey64 = 5,

		//! @brief Use at least 256 shades of grey for antialiasing when rendering
		//! for 8-bit target and 65536 shades of grey when rendering for 16-bit
		//! target.
		//!
		//! This is only recommendation for paint-engine. It can use higher or lower
		//! render quality if this option is not supported.
		GreyHighQuality = 6,

		//! @brief LCD subpixel antialiasing.
		//!
		//! This type of antialiasing is usually only implemented for font rendering.
		LCD = 7,

		Default = Grey16
	};

	public enum class FontStretch
	{
		ULTRA_CONDENSED = 10,
		EXTRA_CONDENSED = 20,
		CONDENSED = 30,
		SEMI_CONDENSED = 40,
		NORMAL = 50,
		SEMI_EXPANDED = 60,
		EXPANDED = 70,
		EXTRA_EXPANDED = 80,
		ULTRA_EXPANDED = 90,

		MAX = 100
	};

	public enum class FontStyle
	{
	    //! @brief Normal style.
	    Normal = 0,

		//! @brief Oblique (slanted, sloped) style.
		//!
		//! Form of type that slants slightly to the right, using shearing transform
		//! of original glyph-set.
        Oblique = 1,

		//! @brief Italic style.
		//!
		//! Form of type that slants slightly to the right, using different glyph-set.
		//! If glyph-set for italic is not available, the @c FONT_STYLE_OBLIQUE is
		//! used instead.
		Italic = 2,
	};

	public enum class FontWeight
	{
		FONT_WEIGHT_100 = 10,
		FONT_WEIGHT_200 = 20,
		FONT_WEIGHT_300 = 30,
		FONT_WEIGHT_400 = 40,
		FONT_WEIGHT_500 = 50,
		FONT_WEIGHT_600 = 60,
		FONT_WEIGHT_700 = 70,
		FONT_WEIGHT_800 = 80,
		FONT_WEIGHT_900 = 90,

		FONT_WEIGHT_THIN       = FONT_WEIGHT_100,
		FONT_WEIGHT_EXTRALIGHT = FONT_WEIGHT_200,
		FONT_WEIGHT_LIGHT      = FONT_WEIGHT_300,
		FONT_WEIGHT_NORMAL     = FONT_WEIGHT_400,
		FONT_WEIGHT_MEDIUM     = FONT_WEIGHT_500,
		FONT_WEIGHT_SEMIBOLD   = FONT_WEIGHT_600,
		FONT_WEIGHT_BOLD       = FONT_WEIGHT_700,
		FONT_WEIGHT_EXTRABOLD  = FONT_WEIGHT_800,
		FONT_WEIGHT_BLACK      = FONT_WEIGHT_900,
	};

	public enum class FillRule
	{
		//! @brief Fill using non-zero rule.
		NonZero = 0,
		//! @brief Fill using even-odd rule.
		EvenOdd = 1,

		//! @brief Default fill-rule.
		Default = NonZero,
		//! @brief Used to catch invalid arguments.
	};

	//! @brief Clip operation.
	public enum class ClipOperation
	{
	  //! @brief Replace the current clipping area.
	  Replace = 0,
      //! @brief Intersect the current clipping area.
      Intersect = 1,
    };

	public enum class CompositeOperation
	{
		Src = 0,
		SrcOver = 1,
  	    SrcIn = 2,
        SrcOut = 3,
		SrcAtop = 4,
		Dst = 5,
		DstOver = 6,
	    DstIn = 7,
		DstOut = 8,
	    DstAtop = 9,
		Xor = 10,
        Clear = 11,
        Plus = 12,
        Minus = 13,
        Multiply = 14,
        Screen = 15,
        Overlay = 16,
		Darken = 17,
	    Lighten = 18,
		ColorDodge = 19,
        ColorBurn = 20,
		HardLight = 21,
		SoftLight = 22,
		Difference = 23,
		Exclusion = 24,
	};

	public enum class LineJoin
	{
		Miter = 0,
        Round = 1,
		Bevel = 2,
        MiterRevert = 3,
        MiterRound = 4,
        Default = Miter
	};

	public enum class LineCap
	{
		//! @brief Butt line-cap (default).
		Butt = 0,
		//! @brief Square line-cap.
		Square = 1,
		//! @brief Round line-cap.
		Round = 2,
		//! @brief Reversed round line-cap.
		RoundReverse = 3,
		//! @brief Triangle line-cap.
		Triangle = 4,
		//! @brief Reversed triangle line-cap.
		TriangleReverse = 5,

		//! @brief Default line-cap type.
		Default = Butt,
	};
}
