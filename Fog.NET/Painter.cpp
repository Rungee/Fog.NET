/******************************************************************************
*
* Name:     Painter.cpp
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
#include "Painter.h"
#include "PathF.h"
#include "Utility.h"
#include "clix.h"

#include "Fog/Core.h"
#include "Fog/Core/Global/EnumCore.h"
#include "Fog/G2d/Painting/Painter.h"
#include "Fog/G2d/Text/TextLayout.h"

namespace FogNET
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace clix;

    Painter::Painter(void)
    {
	    m_painter = new Fog::Painter();
    }

	Painter::Painter(Image ^image)
	{
		m_painter = new Fog::Painter(*(Fog::Image*)image->GetNativePointer());
	}

    Painter::~Painter() 
    {
    	delete m_painter;
    }

	void* Painter::GetNativePointer()
	{
		return m_painter;
	}

	void Painter::Begin(Image ^image)
	{
		m_painter->begin(*(Fog::Image*)image->GetNativePointer());
	}

	void Painter::End()
	{
		m_painter->end();
	}

	void Painter::Flush()
	{
		m_painter->flush(Fog::PAINTER_FLUSH::PAINTER_FLUSH_SYNC);
	}

	void Painter::Save()
	{
		m_painter->save();
	}

	void Painter::Restore()
	{
		m_painter->restore();
	}

	void Painter::BlitImage(Point p, Image ^image)
	{
		m_painter->blitImage(Fog::PointI(p.X, p.Y), *(Fog::Image*)image->GetNativePointer());
	}

	void Painter::BlitImage(PointF p, Image ^image)
	{
		m_painter->blitImage(Fog::PointF(p.X, p.Y), *(Fog::Image*)image->GetNativePointer());
	}

	void Painter::BlitImage(float x, float y, Image ^image)
	{
		m_painter->blitImage(Fog::PointF(x, y), *(Fog::Image*)image->GetNativePointer());
	}

	void Painter::BlitImage(RectangleF rect, Image ^image)
	{
		Fog::RectF rc(rect.X, rect.Y, rect.Width, rect.Height);
		m_painter->blitImage(rc, *(Fog::Image*)image->GetNativePointer());
	}

	void Painter::BlitImage(double x, double y, double width, double height, Image ^image)
	{
		Fog::RectD rc(x, y, width, height);
		m_painter->blitImage(rc, *(Fog::Image*)image->GetNativePointer());
	}

	void Painter::DrawEllipse(float x, float y, float width, float height)
	{
		Fog::EllipseF ellipse(x, y, width, height);
		m_painter->drawEllipse(ellipse);
	}

	void Painter::DrawEllipse(RectangleF rect)
	{
		Fog::EllipseF ellipse(rect.X, rect.Y, rect.Width, rect.Height);
		m_painter->drawEllipse(ellipse);
	}

	void Painter::FillEllipse(RectangleF rect)
	{
		Fog::EllipseF ellipse(rect.X, rect.Y, rect.Width, rect.Height);
		m_painter->fillEllipse(ellipse);
	}

	void Painter::FillEllipse(float x, float y, float width, float height)
	{
		Fog::EllipseF ellipse(x, y, width, height);
		m_painter->fillEllipse(ellipse);
	}

	void Painter::DrawLine(double x1, double y1, double x2, double y2)
	{
		m_painter->drawLine(x1, y1, x2, y2);
	}

    void Painter::FillRect(RectangleF rect)
    {
		m_painter->fillRect(rect.X, rect.Y, rect.Width, rect.Height);
	}

	void Painter::FillRect(double x, double y, double width, double height)
	{
		m_painter->fillRect(x, y, width, height);
	}

	void Painter::DrawRect(RectangleF rect)
    {
		m_painter->drawRect(rect.X, rect.Y, rect.Width, rect.Height);
	}

	void Painter::DrawRect(double x, double y, double width, double height)
	{
		m_painter->drawRect(x, y, width, height);
	}

	void Painter::DrawPath(PathF ^path)
    {
		Fog::PathF* pathf = (Fog::PathF*)path->GetNativePointer();
		m_painter->drawPath(*pathf);
	}

	void Painter::FillPath(PathF ^path)
    {
		Fog::PathF* pathf = (Fog::PathF*)path->GetNativePointer();
		m_painter->fillPath(*pathf);
	}

	void Painter::FillAll()
	{
		m_painter->fillAll();
	}

	void Painter::DrawPolyline(array<PointF> ^points) 
	{
		int nLength = points->Length;
		if (nLength <= 0)
			return;
		
    	IntPtr ptr = Utility::ConvertPointToMemory(points);

		try
		{
			Fog::PointF* p = (Fog::PointF*)ptr.ToPointer();
			m_painter->drawPolyline(p, nLength);
		}
		finally
		{
			Marshal::FreeHGlobal(ptr);
		}
	}

	void Painter::ClipRect(ClipOperation clipOp, RectangleF rect)
	{
		Fog::RectF rc(rect.X, rect.Y, rect.Width, rect.Height);
		m_painter->clipRect((uint32_t)clipOp, rc);
	}

	void Painter::ClipPath(ClipOperation clipOp, PathF ^path)
	{
		Fog::PathF* pathf = (Fog::PathF*)path->GetNativePointer();
		m_painter->clipPath((uint32_t)clipOp, *pathf);
	}

	void Painter::ResetClip()
	{
		m_painter->resetClip();
	}

	FillRule Painter::GetFillRule()
	{
		uint32_t fr;
		m_painter->getFillRule(fr);
		return static_cast<FillRule>(fr);
	}

	void Painter::SetFillRule(FillRule fillRule)
	{
		Fog::FILL_RULE fr = static_cast<Fog::FILL_RULE>(fillRule);
		m_painter->setFillRule(fr);
	}

	ImageQuality Painter::GetImageQuality()
	{
		uint32_t iq;
		m_painter->getImageQuality(iq);
		return static_cast<ImageQuality>(iq);
	}

	void Painter::SetImageQuality(ImageQuality quality)
	{
		m_painter->setImageQuality((uint32_t)quality);
	}

	RenderQuality Painter::GetRenderQuality()
	{
		uint32_t rq;
		m_painter->getRenderQuality(rq);
		return (RenderQuality)rq;
	}

	void Painter::SetRenderQuality(RenderQuality quality)
	{
		m_painter->setRenderQuality((uint32_t)quality);
	}

	SizeF Painter::MeasureString(String ^str, Font ^font)
	{
		if (str->Length == 0)
			return SizeF::Empty;

		SizeF size;
		PathF ^path = gcnew PathF();
		path->AddString(str, font, PointF(0,0));
		size = path->GetBounds().Size;
		delete path;

		return size;
	}

	void Painter::SetSource(Color color)
	{
		m_painter->setSource(Fog::Argb32(color.ToArgb()));
	}

	void Painter::SetOpacity(double value)
	{
		m_painter->setOpacity(value);
	}

	void Painter::SetStrokeParams(PathStrokerParamsF parameters)
	{
		Fog::PathStrokerParamsF paramsF;
		m_painter->setStrokeParams(paramsF);
	}

	PathStrokerParamsF^ Painter::GetStrokeParams()
	{
		Fog::PathStrokerParamsF paramsF;
		m_painter->getStrokeParams(paramsF);
		PathStrokerParamsF ^psp = gcnew PathStrokerParamsF();

		return psp;
	}

	void Painter::SetCompositeOperation(CompositeOperation cop)
	{
		Fog::COMPOSITE_OP op = static_cast<Fog::COMPOSITE_OP>(cop);
		m_painter->setCompositingOperator(op);
	}

	void Painter::SetLineWidth(double width)
	{
		m_painter->setLineWidth(width);
	}

	void Painter::SetLineJoin(LineJoin lineJoin)
	{
		m_painter->setLineJoin((uint32_t)lineJoin);
	}

	void Painter::SetMiterLimit(double value)
	{
		m_painter->setMiterLimit(value);
	}

	void Painter::SetDashOffset(double value)
	{
		m_painter->setDashOffset(value);
	}

	void Painter::SetDashList(array<double> ^values)
	{
		if (values == nullptr)
		{
			m_painter->resetDashList();
			return;
		}

		Fog::List<double> list;
		for (int i = 0;i< values->Length;i++)
		{
			double v = values[i];
			list.append(v);
		}

		m_painter->setDashList(list);
	}

	void Painter::SetDashList(array<float> ^values)
	{
		if (values == nullptr)
		{
			m_painter->resetDashList();
			return;
		}

		Fog::List<float> list;
		for (int i = 0;i< values->Length;i++)
		{
			float v = values[i];
			list.append(v);
		}

		m_painter->setDashList(list);
	}

	void Painter::SetLineCaps(LineCap lineCap)
	{
		m_painter->setLineCaps((uint32_t)lineCap);
	}

	void Painter::Transform(Matrix ^matrix)
	{
		array<float> ^elements = matrix->Elements;
		Fog::TransformF trans(elements[0], elements[1], elements[2], elements[3], elements[4], elements[5]);

		m_painter->setTransform(trans);
	}

	void Painter::Transform(float m00, float m01, float m02,
                            float m10, float m11, float m12,
                            float m20, float m21, float m22)
	{
		Fog::TransformF trans(m00, m01, m02, m10, m11, m12, m20, m21, m22);

		m_painter->setTransform(trans);
	}

	void Painter::ResetTransform()
	{
		m_painter->resetTransform();
	}

	void Painter::Rotate(double angle)
	{
		m_painter->rotate(angle);
	}

	void Painter::Rotate(double angle, double cx, double cy)
	{
		m_painter->rotate(angle, Fog::PointD(cx, cy));
	}

	void Painter::Scale(double sx, double sy)
	{
		m_painter->scale(Fog::PointD(sx, sy));
	}

	void Painter::Translate(double dx, double dy)
	{
		m_painter->translate(Fog::PointD(dx, dy));
	}
}