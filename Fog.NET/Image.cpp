/******************************************************************************
*
* Name:     Image.cpp
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

#include "stdafx.h"
#include "Image.h"
#include "Enums.h"
#include "clix.h"
#include "ManagedStreamDevice.h"

#include "Fog/G2d/Imaging/Image.h"
#include "Fog/G2d/Imaging/ImageBits.h"

namespace FogNET
{
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace clix;

	Image::Image(int width, int height, ImageFormat format)
	{
		Fog::SizeI size = Fog::SizeI(width, height);
		Fog::IMAGE_FORMAT frmt = static_cast<Fog::IMAGE_FORMAT>(format);
		m_image = new Fog::Image(size, frmt);
		m_owner = true;
	}

	Image::Image(Bitmap ^bitmap)
	{
		Fog::SizeI size = Fog::SizeI(bitmap->Width, bitmap->Height);
		Fog::IMAGE_FORMAT frmt = Fog::IMAGE_FORMAT::IMAGE_FORMAT_PRGB32;

		System::Drawing::Imaging::PixelFormat pf = bitmap->PixelFormat;
		if (pf == PixelFormat::Format32bppPArgb)
			frmt = Fog::IMAGE_FORMAT::IMAGE_FORMAT_PRGB32;
		else if (pf == PixelFormat::Format32bppArgb)
			frmt = Fog::IMAGE_FORMAT::IMAGE_FORMAT_XRGB32;
		else if (pf == PixelFormat::Format24bppRgb)
			frmt = Fog::IMAGE_FORMAT::IMAGE_FORMAT_RGB24;
		else if (pf == PixelFormat::Format8bppIndexed)
			frmt = Fog::IMAGE_FORMAT::IMAGE_FORMAT_I8;

		m_image = new Fog::Image(size, frmt);
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0,0, bitmap->Width, bitmap->Height);
		BitmapData ^bd = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bitmap->PixelFormat);

		Fog::ImageBits imgBits = Fog::ImageBits(size, frmt, (uint32_t)bd->Stride, (uint8_t*)bd->Scan0.ToPointer());

		bitmap->UnlockBits(bd);
		m_image->adopt(imgBits, 0U);

		m_owner = false;
	}

	Image::Image(Size size, ImageFormat format, int stride, IntPtr scan0)
	{
		Fog::SizeI sizeI = Fog::SizeI(size.Width, size.Height);
		Fog::ImageBits imgBits = Fog::ImageBits(sizeI, (Fog::IMAGE_FORMAT)format, stride, (uint8_t*)scan0.ToPointer());

		m_image->adopt(imgBits, 0U);
		m_owner = false;
	}

	Image::~Image() 
    {
		if (!m_owner)
			m_image->detach();

		delete m_image;
		m_image = NULL;
    }

	void* Image::GetNativePointer()
	{
		return m_image;
	}

	void Image::Clear(Color color)
	{
		m_image->clear(Fog::Argb32(color.ToArgb()));
	}

	void Image::Save(String ^fileName)
	{
        std::string str = marshalString<E_UTF8>(fileName);
		Fog::StringW fileNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());
		err_t e = m_image->writeToFile(fileNameW);
	}

	Image^ Image::FromFile(String ^fileName)
	{
		std::string str = marshalString<E_UTF8>(fileName);
		Fog::StringW fileNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());

		Image ^image = gcnew Image(1, 1, ImageFormat::PRGB32);
		Fog::Image* nimg = (Fog::Image*)image->GetNativePointer();
		nimg->readFromFile(fileNameW);

		return image;
	}

	Image^ Image::FromStream(Stream ^stream)
	{
		if (!stream->CanRead)
			throw gcnew IOException("stream is closed");

		Image ^image = gcnew Image(1, 1, ImageFormat::PRGB32);

		Fog::Image* nimg = (Fog::Image*)image->GetNativePointer();

		ManagedStreamDevice* msd = new ManagedStreamDevice(stream);
		Fog::Stream* fStream = new Fog::Stream((Fog::StreamDevice*)msd);

		nimg->readFromStream(*fStream);

		return image;
	}

	void Image::BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect)
	{
		m_image->blitImage(Fog::PointI(point->X, point->Y), *(Fog::Image*)image->GetNativePointer(), Fog::RectI(rect.X, rect.Y, rect.Width, rect.Height));
	}

	void Image::BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect, CompositeOperation op, float opacity)
	{
		m_image->blitImage(Fog::PointI(point->X, point->Y), *(Fog::Image*)image->GetNativePointer(), Fog::RectI(rect.X, rect.Y, rect.Width, rect.Height), (uint32_t)op, opacity);
	}

    void Image::BlitImage(Point ^point, Image ^image, System::Drawing::Rectangle rect, CompositeOperation op)
	{
		m_image->blitImage(Fog::PointI(point->X, point->Y), *(Fog::Image*)image->GetNativePointer(), Fog::RectI(rect.X, rect.Y, rect.Width, rect.Height), (uint32_t)op);
	}
}