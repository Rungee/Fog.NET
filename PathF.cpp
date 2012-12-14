/******************************************************************************
*
* Name:     PathF.cpp
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
#include "clix.h"
#include "PathF.h"
#include "Utility.h"

#include "Fog/G2d/Geometry/Path.h"
#include "Fog/G2d/Text/TextLayout.h"

namespace FogNET
{
	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace clix;

	PathF::PathF(void)
	{
		m_path = new Fog::PathF();
	}

	PathF::~PathF() 
	{
	    delete m_path;
	}

	void* PathF::GetNativePointer()
	{
		return m_path;
	}

	void PathF::Clear()
	{
		m_path->clear();
	}

	void PathF::Reset()
	{
		m_path->reset();
	}

	void PathF::Close()
	{ 
		m_path->close();
	}

	void PathF::Transform(Matrix ^matrix)
	{
		array<float> ^elements = matrix->Elements;
		Fog::TransformF trans(elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8]);
		m_path->transform(trans);
	}

	void PathF::Translate(float dx, float dy)
	{
		m_path->translate(Fog::PointF(dx, dy));
	}

    void PathF::Scale (float sx, float sy)
	{
		m_path->scale(Fog::PointF(sx, sy));
	}

	void PathF::Arc(float x, float y, float width, float height, float startAngle, float sweepAngle)
	{
		Fog::ArcF arc = Fog::ArcF(Fog::RectF(x, y, width, height), startAngle, sweepAngle);
		m_path->arc(arc);
	}

	void PathF::Ellipse(float x, float y, float width, float height)
	{
		m_path->ellipse(x, y, width, height);
	}

	void PathF::Rect(System::Drawing::Rectangle rect)
	{
		m_path->rect(rect.X, rect.Y, rect.Width, rect.Height);
	}

	void PathF::Rect(float x, float y, float width, float height)
	{
		m_path->rect(x, y, width, height);
	}

	void PathF::MoveTo(float x, float y)
	{
		m_path->moveTo(x, y);
	}

	void PathF::LineTo(float x, float y)
	{
		m_path->lineTo(x, y);
	}

	void PathF::Line(float x0, float y0, float x1, float y1)
	{
		m_path->line(x0, y0, x1, y1);
	}

	void PathF::Polygon(array<PointF> ^points)
	{
		int nLength = points->Length;
		if (nLength <= 0)
			return;
		
    	IntPtr ptr = Utility::ConvertPointToMemory(points);

		try
		{
			Fog::PointF* p = (Fog::PointF*)ptr.ToPointer();
			m_path->polygon(p, nLength, 1U);
		}
		finally
		{
			Marshal::FreeHGlobal(ptr);
		}
	}

	void PathF::Polygon(PointF* points, int length)
	{
		Fog::PointF* ptr = (Fog::PointF*)points;
		m_path->polygon(ptr, length, 1U);
	}

	void PathF::AddString(String ^text, Font ^font, PointF ^point)
	{
		std::string str2 = marshalString<E_UTF8>(text);
		Fog::StringW strW = Fog::StringW::fromUtf8(str2.c_str(), str2.length());

  	    Fog::GlyphShaper shaper;
		Fog::Font* fnt = (Fog::Font*)font->GetNativePointer();
	    shaper.addText(*fnt, strW);

		Fog::PathF np;
		fnt->getOutlineFromGlyphRun(np, Fog::CONTAINER_OP_REPLACE, Fog::PointF(point->X, point->Y), shaper._glyphRun); 
	
		m_path->append(np);
	}

	void PathF::AddString(String ^text, String ^familyName, FontStyle style, float size, PointF ^point, StringAlignment alignment)
	{
		AddString(text, familyName, style, FontWeight::FONT_WEIGHT_NORMAL, size, point, alignment);
	}

	void PathF::AddString(String ^text, String ^familyName, FontStyle style, FontWeight weight, float size, PointF ^point, StringAlignment alignment)
	{
		std::string str = marshalString<E_UTF8>(text);
		Fog::StringW strW = Fog::StringW::fromUtf8(str.c_str(), str.length());

		Font ^font = gcnew Font(familyName, size, style, weight);

		Fog::GlyphShaper shaper;
		Fog::Font* fnt = (Fog::Font*)font->GetNativePointer();
	    shaper.addText(*fnt, strW);

		Fog::PathF np;
		fnt->getOutlineFromGlyphRun(np, Fog::CONTAINER_OP_REPLACE, Fog::PointF(point->X, point->Y), shaper._glyphRun); 

		if (alignment == StringAlignment::Near)
			np.translate(Fog::PointF(0.0F, size));

		m_path->append(np);

		delete font;
	}

	RectangleF PathF::GetBounds()
	{
		Fog::RectF rect;
		m_path->getBoundingRect(rect);

		return RectangleF(rect.x, rect.y, rect.getWidth(), rect.getHeight());
	}
}