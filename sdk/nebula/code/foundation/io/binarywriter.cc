//------------------------------------------------------------------------------
//  binarywriter.cc
//  (C) 2006 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "io/binarywriter.h"

namespace IO
{
__ImplementClass(IO::BinaryWriter, 'BINW', IO::StreamWriter);

using namespace Util;
using namespace System;
using namespace Math;

//------------------------------------------------------------------------------
/**
*/
BinaryWriter::BinaryWriter() :
    enableMapping(false),
    isMapped(false),
    mapCursor(0),
    mapEnd(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
BinaryWriter::~BinaryWriter()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
BinaryWriter::Open()
{
    if (StreamWriter::Open())
    {
        if (this->enableMapping && this->stream->CanBeMapped())
        {
            this->isMapped = true;
            this->mapCursor = (unsigned char*) this->stream->Map();
            this->mapEnd = this->mapCursor + this->stream->GetSize();
        }
        else
        {
            this->isMapped = false;
            this->mapCursor = 0;
            this->mapEnd = 0;
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::Close()
{
    StreamWriter::Close();
    this->isMapped = false;
    this->mapCursor = 0;
    this->mapEnd = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteChar(char c)
{
    if (this->isMapped)
    {
        n_assert(this->mapCursor < this->mapEnd);
        *this->mapCursor++ = c;
    }
    else
    {
        this->stream->Write(&c, sizeof(c));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteUChar(unsigned char c)
{
    if (this->isMapped)
    {
        n_assert(this->mapCursor < this->mapEnd);
        *this->mapCursor++ = c;
    }
    else
    {
        this->stream->Write(&c, sizeof(c));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteShort(short s)
{
    this->byteOrder.Convert<short>(s);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(s)) <= this->mapEnd);
        Memory::Copy(&s, this->mapCursor, sizeof(s));
        this->mapCursor += sizeof(s);
    }
    else
    {
        this->stream->Write(&s, sizeof(s));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteUShort(unsigned short s)
{
    this->byteOrder.Convert<ushort>(s);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(s)) <= this->mapEnd);
        Memory::Copy(&s, this->mapCursor, sizeof(s));
        this->mapCursor += sizeof(s);
    }
    else
    {
        this->stream->Write(&s, sizeof(s));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteInt(int i)
{
    this->byteOrder.Convert<int>(i);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(i)) <= this->mapEnd);
        Memory::Copy(&i, this->mapCursor, sizeof(i));
        this->mapCursor += sizeof(i);
    }
    else
    {
        this->stream->Write(&i, sizeof(i));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteUInt(unsigned int i)
{
    this->byteOrder.Convert<uint>(i);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(i)) <= this->mapEnd);
        Memory::Copy(&i, this->mapCursor, sizeof(i));
        this->mapCursor += sizeof(i);
    }
    else
    {
        this->stream->Write(&i, sizeof(i));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteFloat(float f)
{
    this->byteOrder.Convert<float>(f);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(f)) <= this->mapEnd);
        Memory::Copy(&f, this->mapCursor, sizeof(f));
        this->mapCursor += sizeof(f);
    }
    else
    {
        this->stream->Write(&f, sizeof(f));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteDouble(double d)
{
    this->byteOrder.Convert<double>(d);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(d)) <= this->mapEnd);
        Memory::Copy(&d, this->mapCursor, sizeof(d));
        this->mapCursor += sizeof(d);
    }
    else
    {
        this->stream->Write(&d, sizeof(d));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteBool(bool b)
{
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(b)) <= this->mapEnd);
        Memory::Copy(&b, this->mapCursor, sizeof(b));
        this->mapCursor += sizeof(b);
    }
    else
    {
        this->stream->Write(&b, sizeof(b));
    }
}

//------------------------------------------------------------------------------
/**
    NOTE: for strings, first the length will be written into a
    32-bit int, then the string contents without the 0-terminator.
*/
void
BinaryWriter::WriteString(const Util::String& s)
{
    n_assert(s.Length() < (1<<16));
    this->WriteUShort(ushort(s.Length()));
    if (s.Length() > 0)
    {
        if (this->isMapped)
        {
            n_assert((this->mapCursor + s.Length()) <= this->mapEnd);
            Memory::Copy(s.AsCharPtr(), this->mapCursor, s.Length());
            this->mapCursor += s.Length();
        }
        else
        {
            this->stream->Write((void*)s.AsCharPtr(), s.Length());
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteBlob(const Util::Blob& blob)
{
    this->WriteUInt(blob.Size());
    if (this->isMapped)
    {
        n_assert((this->mapCursor + blob.Size()) <= this->mapEnd);
        Memory::Copy(blob.GetPtr(), this->mapCursor, blob.Size());
        this->mapCursor += blob.Size();
    }
    else
    {
        this->stream->Write(blob.GetPtr(), blob.Size());
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteGuid(const Util::Guid& guid)
{
    const unsigned char* ptr;
    SizeT size = guid.AsBinary(ptr);
    Util::Blob blob(ptr, size);
    this->WriteBlob(blob);
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteFloat4(const float4& v)
{
    float4 val = v;
    this->byteOrder.Convert<float4>(val);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(v)) <= this->mapEnd);
        Memory::Copy(&val, this->mapCursor, sizeof(val));
        this->mapCursor += sizeof(val);
    }
    else
    {
        this->stream->Write(&val, sizeof(val));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteMatrix44(const matrix44& m)
{
    matrix44 val = m;
    this->byteOrder.Convert<matrix44>(val);
    if (this->isMapped)
    {
        // note: the memory copy is necessary to circumvent alignment problem on some CPUs
        n_assert((this->mapCursor + sizeof(val)) <= this->mapEnd);
        Memory::Copy(&val, this->mapCursor, sizeof(val));
        this->mapCursor += sizeof(val);
    }
    else
    {
        this->stream->Write(&val, sizeof(val));
    }
}

//------------------------------------------------------------------------------
/**
*/
void
BinaryWriter::WriteRawData(const void* ptr, SizeT numBytes)
{
    n_assert((ptr != 0) && (numBytes > 0));
    if (this->isMapped)
    {
        n_assert((this->mapCursor + numBytes) <= this->mapEnd);
        Memory::Copy(ptr, this->mapCursor, numBytes);
        this->mapCursor += numBytes;
    }
    else
    {
        this->stream->Write(ptr, numBytes);
    }
}

} // namespace IO
