/******************************************************************************
*
* Name:     PathF.h
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

#include "Font.h"

#include "Fog/G2d/Geometry/Path.h"

namespace FogNET
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class PathF
	{
	public:
		PathF(void);
		~PathF();

		void* GetNativePointer();
		void Clear();
		void Reset();
		void Close();

		void Transform(Matrix ^matrix);
		void Translate(float dx, float dy);
		void Scale (float sx, float sy);

		void Arc(float x, float y, float width, float height, float startAngle, float sweepAngle);
		void Ellipse(float x, float y, float width, float height);
		void Rect(System::Drawing::Rectangle rect);
		void Rect(float x, float y, float width, float height);

		void MoveTo(float x, float y);
		void LineTo(float x, float y);
		void Line(float x0, float y0, float x1, float y1);
		void Polygon(array<PointF> ^points);
		void Polygon(PointF* pointsPtr, int length);
		void AddString(String ^text, Font ^font, PointF ^point);
		void AddString(String ^text, String ^familyName, FontStyle style, float size, PointF ^point, StringAlignment alignment);
		void AddString(String ^text, String ^familyName, FontStyle style, FontWeight weight, float size, PointF ^point, StringAlignment alignment);
		RectangleF GetBounds();
	private:
		Fog::PathF* m_path;
	};
}

