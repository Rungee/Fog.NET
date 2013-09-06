/******************************************************************************
*
* Name:     ManagedStreamDevice.cpp
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
#include "ManagedStreamDevice.h"

#include "Fog/Core/Global/EnumCore.h"
#include "Fog/Core/Memory/MemOps.h"

namespace FogNET
{
	using namespace clix;
	using namespace System::IO;

	ManagedStreamDevice::ManagedStreamDevice(Stream ^stream)
	{
		m_stream = stream;
		//m_buffer = gcnew array<byte>(4096);
	}

	ManagedStreamDevice::~ManagedStreamDevice(void)
	{
		
	}
	
	int64_t ManagedStreamDevice::seek(int64_t offset, int whence)
	{
		System::IO::SeekOrigin seekOrigin = System::IO::SeekOrigin::Begin; 

		switch (whence)
		{
			 case STREAM_SEEK_SET:
			   seekOrigin = System::IO::SeekOrigin::Begin;
			   break;
			 case STREAM_SEEK_CUR:
               seekOrigin = System::IO::SeekOrigin::Current;
               break;
             case STREAM_SEEK_END:
               seekOrigin = System::IO::SeekOrigin::End;
               break;
        }

		return m_stream->Seek(offset, seekOrigin);
	}

	int64_t ManagedStreamDevice::tell() const
	{
		int64_t result = m_stream->Position;

		if (result < FOG_INT64_C(0))
		  return -1;
		else
          return result;
	}

	size_t ManagedStreamDevice::read(void* buffer, size_t size)
	{
		//if (m_buffer->Length < size)
		//	m_buffer = gcnew array<byte>(size);

		size_t length = m_stream->Length;
		size_t pos = m_stream->Position;
		size_t remain = (size_t)(length - pos);
		if (size > remain) size = remain;

		array<Byte>^ buffer2 = gcnew array<byte>(size);

		m_stream->Read(buffer2, 0, size);

		pin_ptr<byte> buffer_start = &buffer2[0];
		Fog::MemOps::copy(buffer, const_cast<byte*>(buffer_start), size);

		return size;
	}

	size_t ManagedStreamDevice::write(const void* buffer, size_t size)
	{
		//m_stream->Write(
		return 0;
	}

	err_t ManagedStreamDevice::getSize(int64_t* size)
	{
		 *size = m_stream->Length;
		 return Fog::ERR_CODE::ERR_OK;
	}	

	err_t ManagedStreamDevice::setSize(int64_t size)
	{
		m_stream->SetLength(size);

		if (size == 0)
			 return Fog::ERR_CODE::ERR_OK;
		 else
			 return Fog::ERR_CODE::ERR_IO_CANT_RESIZE;
	}

	err_t ManagedStreamDevice::truncate(int64_t offset)
	{
		 return Fog::ERR_CODE::ERR_IO_CANT_TRUNCATE;
	}

	void ManagedStreamDevice::close()
	{
		m_stream->Close();
	}
}