/******************************************************************************
*
* Name:     Utility.cpp
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
#include "Utility.h"

namespace FogNET
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	IntPtr Utility::ConvertPointToMemory(array<PointF> ^points)
	{
		int nLength = points->Length;
		int num = Marshal::SizeOf(Fog::PointF::typeid);
    	IntPtr intPtr = Marshal::AllocHGlobal(nLength * num);
		Fog::PointF* ptr = (Fog::PointF*)intPtr.ToPointer();
		Fog::PointF* pp = ptr;
	
		for (int i = 0; i < nLength; i++)
		{
			PointF p = points[i];
			pp->x = p.X;
			pp->y = p.Y;
			pp++;
		}

		return intPtr;
	}
}
