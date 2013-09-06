/******************************************************************************
*
* Name:     SvgDocument.cpp
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
#include "SvgDocument.h"
#include "Enums.h"
#include "clix.h"
#include "ManagedStreamDevice.h"

#include "Fog/Core/Tools/Stream.h"
#include "Fog/G2d/Svg/SvgDom.h"

namespace FogNET
{
	using namespace clix;

	SvgDocument::SvgDocument(void) 
    {
		m_svgDocument = new Fog::SvgDocument();
    }

	SvgDocument::~SvgDocument() 
    {
		delete m_svgDocument;
		m_svgDocument = NULL;
    }

	SizeF SvgDocument::GetSize()
	{
		Fog::SizeF size = m_svgDocument->getDocumentSize();

		return SizeF(size.w, size.h);
	}

	SvgDocument^ SvgDocument::FromFile(String ^fileName)
	{
		std::string str = marshalString<E_UTF8>(fileName);
		Fog::StringW fileNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());

		SvgDocument ^doc = gcnew SvgDocument();
		doc->m_svgDocument->readFromFile(fileNameW);
		
		return doc;
	}

	SvgDocument^ SvgDocument::FromStream(Stream ^stream)
	{
		if (!stream->CanRead)
			throw gcnew IOException("stream is closed");

		ManagedStreamDevice* msd = new ManagedStreamDevice(stream);
		Fog::Stream* fStream = new Fog::Stream((Fog::StreamDevice*)msd);

		SvgDocument ^doc = gcnew SvgDocument();
		doc->m_svgDocument->readFromStream(*fStream);

		return doc;
	}

	void SvgDocument::Render(Painter ^painter)
	{
		m_svgDocument->render((Fog::Painter*)painter->GetNativePointer());
	}
}
