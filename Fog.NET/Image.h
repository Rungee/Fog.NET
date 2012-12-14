/******************************************************************************
*
* Name:     Image.h
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

#include "Enums.h"

#include "Fog/G2d/Imaging/Image.h"

namespace FogNET
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::IO;

    public ref class Image
	{
	public:
		Image(Bitmap ^bitmap);
		Image(int width, int height, ImageFormat format);
		Image(Size size, ImageFormat format, int stride, IntPtr scan0);
		~Image();

		void* GetNativePointer();
		void Clear(Color color);
		void Save(String ^fileName);

		void BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect);
		void BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect, CompositeOperation op);
		void BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect, CompositeOperation op, float opacity);

		static Image^ FromFile(String ^fileName);
		static Image^ FromStream(Stream ^stream);
	private:
		Fog::Image* m_image;
		bool m_owner;
	};
}
