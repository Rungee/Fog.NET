/******************************************************************************
*
* Name:     Painter.h
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
#include "Image.h"
#include "PathF.h"
#include "PathStrokerParams.h"

#include "Fog/Core.h"
#include "Fog/G2d/Painting/Painter.h"

namespace FogNET
{
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

    public ref class Painter
    {
    public:
    	Painter(void);
    	Painter(Image ^image);
		~Painter();

		void Begin(Image ^image);
		void End();
		void Flush();

		void BlitImage(Point p, Image ^image);
		void BlitImage(PointF p, Image ^image);
		void BlitImage(float x, float y, Image ^image);
		void BlitImage(RectangleF rect, Image ^image);
		void BlitImage(double x, double y, double width, double height, Image ^image);
		void DrawEllipse(float x, float y, float width, float height);
		void DrawEllipse(RectangleF rect);
		void FillEllipse(RectangleF rect);
		void FillEllipse(float x, float y, float width, float height);
		void DrawLine(double x1, double y1, double x2, double y2);
		void DrawRect(RectangleF rect);
		void DrawRect(double x, double y, double width, double height);
		void FillRect(RectangleF rect);
		void FillRect(double x, double y, double width, double height);
		void DrawPath(PathF ^path);
		void FillPath(PathF ^path);
		void FillAll();
		void DrawPolyline(array<PointF> ^points); 

		SizeF MeasureString(String ^str, Font ^font);

		void SetSource(Color color);
		void SetOpacity(double value);

		FillRule GetFillRule();
		void SetFillRule(FillRule fillRule);
		ImageQuality GetImageQuality();
		void SetImageQuality(ImageQuality quality);
		RenderQuality GetRenderQuality();
		void SetRenderQuality(RenderQuality quality);

		PathStrokerParamsF^ GetStrokeParams();
	    void SetStrokeParams(PathStrokerParamsF parameters);

		void SetCompositeOperation(CompositeOperation cop);

		void SetLineWidth(double width);
		void SetLineJoin(LineJoin lineJoin);
		void SetMiterLimit(double value);
		void SetLineCaps(LineCap lineCap);
		void SetDashOffset(double value);
		void SetDashList(array<double> ^values);
		void SetDashList(array<float> ^values);

		void Transform(Matrix ^matrix);
		void ResetTransform();
		void Rotate(double angle);
		void Rotate(double angle, double cx, double cy);
		void Scale(double sx, double sy);
		void Translate(double dx, double dy);
    private:
    	Fog::Painter* m_painter;
    };
}