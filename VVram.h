#pragma once
#include <string.h>
#include "cate.h"

constexpr byte VVramWidth = 24;
constexpr byte VVramHeight = 16;

extern byte VVramBack[], VVramFront[];

inline void VVramBackToFront()
{
    memcpy(VVramFront, VVramBack, VVramWidth * VVramHeight);
}
inline ptr<byte> VPut(ptr<byte> pVVram, byte c)
{
    *pVVram++ = c;
    return pVVram;
}

extern void DrawAll();
extern word VVramOffset(byte x, byte y);
extern ptr<byte> VPut2C(ptr<byte> pVVram, byte c);
extern ptr<byte> VErase2(ptr<byte> pVVram);
