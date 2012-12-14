/******************************************************************************
*
* Name:     Font.cpp
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
#include "Font.h"
#include "clix.h"
#include "Enums.h"

#include "Fog/G2d/Text/Font.h"
#include <Fog/G2d/Text/OpenType/OTCMap.h>
#include <Fog/G2d/Text/OpenType/OTEnum.h>
#include <Fog/G2d/Text/OpenType/OTFace.h>
#include <Fog/G2d/Text/OpenType/OTHmtx.h>
#include "Fog/G2d/Text/TextLayout.h"

namespace FogNET
{
	using namespace System;
	using namespace clix;

	Font::Font(String ^familyName, float size)
	{
		m_font = new Fog::Font();

		std::string str = marshalString<E_UTF8>(familyName);
		Fog::StringW familyNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());
		
		m_font->create(familyNameW, size);
		m_familyName = familyName;
	}

	Font::Font(String ^familyName, float size, FontStyle style)
    {
		m_font = new Fog::Font();

		std::string str = marshalString<E_UTF8>(familyName);
		Fog::StringW familyNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());
		Fog::FontFeatures ff;
		ff.setStyle((uint32_t)style);
		m_font->create(familyNameW, size, ff);
		m_familyName = familyName;
 	}

	Font::Font(String ^familyName, float size, FontStyle style, FontWeight weight)
    {
		m_font = new Fog::Font();

		std::string str = marshalString<E_UTF8>(familyName);
		Fog::StringW familyNameW = Fog::StringW::fromUtf8(str.c_str(), str.length());
		Fog::FontFeatures ff;
		ff.setStyle((uint32_t)style);
		ff.setWeight((uint32_t)weight);

		m_font->create(familyNameW, size, ff);
		m_familyName = familyName;
 	}
	
	Font::~Font()
	{
		delete m_font;
		m_font = NULL;
	}
	
	void* Font::GetNativePointer()
	{
		return m_font;
	}

	String^ Font::GetFamilyName()
	{
		return m_familyName;
	}

	float Font::GetSize()
	{
		return m_font->getSize();
	}

	FontMetrics^ Font::GetFontMetrics()
	{
		FontMetrics^ fm = gcnew FontMetrics();

		throw gcnew NotImplementedException();

		return fm;
	}

	float Font::GetCharAdvanceWidth(Char ^ch)
	{
		return GetGlyphMetrics(ch)->AdvanceWidth;
	}

	uint Font::GetCharIndex(Char ^ch)
	{
		return GetGlyphMetrics(ch)->Index;
	}

	GlyphMetrics^ Font::GetGlyphMetrics(Char ^ch)
	{
		GlyphMetrics^ gm = gcnew GlyphMetrics();

		Fog::OTFace* ot = m_font->getFace()->getOTFace();

    	if (FOG_IS_NULL(ot))
			return gm;

		Fog::OTCMap* cmap = ot->getCMap();
		if (FOG_IS_NULL(cmap))
			return gm;

	    Fog::OTHmtx* hmtx = ot->getHmtx();

		uint32_t _encoding = Fog::OT_ENCODING_ID_UNICODE;
		Fog::OTCMapContext cctx;
		cctx.init(cmap, _encoding);

		std::string str = marshalString<E_UTF8>(ch->ToString());
		Fog::StringW strW = Fog::StringW::fromUtf8(str.c_str(), str.length());
		Fog::StubW strWW = Fog::StubW(strW.getData(), strW.getLength());
		const Fog::CharW* sData = strWW.getData();
		size_t sLength = strWW.getComputedLength();
		Fog::GlyphShaper shaper;
		Fog::GlyphRun _glyphRun = shaper._glyphRun; 
	    Fog::GlyphItem* glyphs = _glyphRun._itemList._prepare(Fog::CONTAINER_OP_APPEND, sLength);
		cctx.getGlyphPlacement(&glyphs->_glyphIndex, sizeof(Fog::GlyphItem), reinterpret_cast<const uint16_t*>(sData), sLength);
		
		if (hmtx)
		{
            uint32_t glyphID = glyphs[0].getGlyphIndex();
			uint32_t hMetricsCount = hmtx->getNumberOfHMetrics();
			const Fog::OTHmtxMetric* hMetricsData = hmtx->getHMetrics();
		    float scale = m_font->_d->scale;
 	        int32_t advanceWidth = hMetricsData[glyphID].advanceWidth.getValueU();
			int32_t leftSideBearing = hMetricsData[glyphID].leftSideBearing.getValueU();
			//int32_t rightSideBearing = hMetricsData[glyphID].rightSideBearing.getValueU();

		    gm->Index = glyphID;
			gm->AdvanceWidth = float(advanceWidth) * scale;
			gm->LeftSideBearing = float(leftSideBearing ) * scale;
 	    }

		return gm;
	}
}