#include "VVram.h"
#include "Sprite.h"
#include "Vram.h"
#include "Chars.h"

byte VVramBack[VVramWidth * VVramHeight], VVramFront[VVramWidth * VVramHeight];

void DrawAll()
{
    VVramBackToFront();
    DrawSprites();
    VVramToVram();
}

word VVramOffset(byte x, byte y)
{
    return y * VVramWidth + x;
}

ptr<byte> VPut2C(ptr<byte> pVVram, byte c)
{
    repeat (2) {
        repeat (2) {
            pVVram = VPut(pVVram, c++);
        }
        pVVram += VVramWidth - 2;
    }
    return pVVram + 2 - VVramWidth * 2;
}

ptr<byte> VErase2(ptr<byte> pVVram)
{
    repeat (2) {
        repeat (2) {
            pVVram = VPut(pVVram, Char_Space);
        }
        pVVram += VVramWidth - 2;
    }
    return pVVram + 2 - VVramWidth * 2;
}
