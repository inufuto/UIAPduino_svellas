#include "Sprite.h"
#include "Chars.h"
#include "VVram.h"
#include "Vram.h"

constexpr byte InvalidPattern = 0xff;
struct Sprite {
    byte x, y;
    byte pattern;
};
Sprite Sprites[Sprite_End];

void HideAllSprites()
{
    for (auto pSprite = Sprites; pSprite < Sprites + Sprite_End; ++pSprite) {
        pSprite->pattern = InvalidPattern;
    }
}


void ShowSprite(ptr<Movable> pMovable, byte pattern)
{
    ptr<Sprite> pSprite = Sprites + pMovable->sprite;
    pSprite->x = pMovable->x;
    pSprite->y = pMovable->y;
    pSprite->pattern = pattern;
}


void HideSprite(byte index) 
{
    ptr<Sprite> pSprite = Sprites + index;
    pSprite->pattern = InvalidPattern;
}


void DrawSprites()
{
    for (auto pSprite = Sprites; pSprite < Sprites + Sprite_End; ++pSprite) {
        if (pSprite->pattern != InvalidPattern) {
            ptr<byte> pVVram = VVramFront + VVramOffset(pSprite->x, pSprite->y);
            byte c = pSprite->pattern;
            if (c < Char_Man) {
                *pVVram = c;
            }
            else {
                repeat (2) {
                    repeat (2) {
                        *pVVram = c;
                        ++pVVram;
                        ++c;
                    }
                    pVVram += VVramWidth - 2;
                }
            }
        }
    }
}
