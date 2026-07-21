#pragma once
#include <string.h>

inline void CopyMemory(ptr<byte> pDestination, constptr<byte> pSource, word length)
{
    memcpy(pDestination, pSource, length);
}

inline void FillMemory(ptr<byte> pDestination, word length, byte b)
{
    memset(pDestination, b, length);
}
