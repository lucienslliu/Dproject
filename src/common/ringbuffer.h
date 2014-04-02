#pragma once

#include "base_type.h"
#include "std_head.h"
#include "message.h"

// ´æ´¢ÖÇÄÜÖ¸ÕëµÄRingBuffer

// #ifdef NULL
// #undef NULL
// #define NULL ((void *)0)
// #endif

template <class CPtr, int nMaxLen>
class PtrRingBuffer
{
	class 
	{
	public:
		template<typename CPtr>
		operator Ptr<CPtr>() { return Ptr<CPtr>(); }
	} nullPtr;


public:
	PtrRingBuffer()
	: m_vecDataBuf(nMaxLen) 
    {
        m_nWritePos = m_nReadPos = -1;
		m_nMaxLen = nMaxLen;
    }

	PtrRingBuffer(const PtrRingBuffer& rfs)
	{
		this->m_vecDataBuf = rfs.m_vecDataBuf;
		this->m_nWritePos = rfs.m_nWritePos;
		this->m_nMaxLen = rfs.m_nMaxLen;
		this->m_nReadPos = rfs.m_nReadPos;
	}

    virtual ~PtrRingBuffer()
    {
        Clear();
    }

    void Clear()
    {
		bool bLoop = true;
        do 
		{
            CPtr pData = Pop();
            if (pData == NULL) 
				break;

            pData = nullPtr;

        } while(bLoop);
    }

    int Push(CPtr pData)
    {
        if (pData == NULL)
        {
            return -1;
        }

        if (m_nWritePos < 0)
        {
            m_nWritePos = m_nReadPos = 0;
        }
        else
        {
			while(GetNextPos(m_nWritePos) == m_nReadPos)
            {
// #ifdef WIN32
// 				::Sleep(1);
// #else
//                 usleep(1000);
// #endif
            }

        }

        m_vecDataBuf[m_nWritePos] = pData;

		m_nWritePos = GetNextPos(m_nWritePos);
		
        return m_nWritePos;        
    }

    CPtr Pop()
    {
        if (m_nReadPos < 0 || m_nReadPos == m_nWritePos)
        {
            return nullPtr;
        }

        CPtr pData = m_vecDataBuf[m_nReadPos];
        m_vecDataBuf[m_nReadPos] = nullPtr;
        assert(pData != NULL);
		m_nReadPos = GetNextPos(m_nReadPos);

        return pData;
    }

	CPtr GetFront()
	{
		if (m_nReadPos<0 || m_nReadPos==m_nWritePos)
		{
			return CPtr(NULL);
		}

		CPtr pData = m_vecDataBuf[m_nReadPos];
		n_assert(pData != NULL);
		return pData;
	}

    __forceinline int Size()
    {
		if (m_nWritePos>=0)
		{
			int num = m_nWritePos - m_nReadPos;
			if (num >= 0)
			{
				return num;
			}
			else
			{
				return num + nMaxLen;
			}
		}
        return 0;
    }

    bool IsFull()
    {
        if (m_nWritePos<0)
        {
            return false;
        }

		if (GetNextPos(m_nWritePos) == m_nReadPos)
        {
            return true;
        }

        return false;
    }

private:

	const PtrRingBuffer& operator=(const PtrRingBuffer& rfs);

	int	GetNextPos(int nPos)
	{
		if (nPos + 1 >= m_nMaxLen)
		{
			return nPos + 1 - m_nMaxLen;
		}else
		{
			return nPos + 1;
		}
	}

    int m_nWritePos;
    int m_nReadPos;
    int m_nMaxLen;
	std::vector<CPtr> m_vecDataBuf;
};

#define RINGBUFF_MAX 1024
typedef PtrRingBuffer<Ptr<Message>, RINGBUFF_MAX> MsgRingBuffer;

