#include "cate.h"
#include "Status.h"
#include "Vram.h"
#include "Main.h"
#include "Sprite.h"
#include "Print.h"
#include "Chars.h"
#include "VVram.h"
#include "ScanKeys.h"
#include "Oled.h"

constexpr byte Char_Remain = Char_Man;
constexpr auto LeftX = 24;

static word PrintS(word vram, constptr<char> p)
{
    byte c;
    while ((c = *p) != 0) {
        vram = PrintC(vram, c);
        ++p;
    }
    return vram;
}

void PrintStatus() 
{
    PrintS(Vram + VramRowSize * 0 + LeftX * VramStep, "SCORE");   
    PrintS(Vram + VramRowSize * 3 + LeftX * VramStep, "STAGE");
    PrintByteNumber2(Vram + VramRowSize * 3 + (LeftX + 6) * VramStep, CurrentStage + 1);
    PrintS(Vram+ VramRowSize * 5 + LeftX * VramStep, "TIME");
    {
        word vram;
        vram = Vram + VramRowSize * 7 + LeftX * VramStep;
        if (RemainCount > 1) {
            byte i;
            i = RemainCount - 1;
            if (i > 2) {
                vram = Put2C(vram, Char_Remain);
                vram = PrintC(vram, Char_Space);
                vram = PrintC(vram, i + 0x30);
            }
            else {
                do {
                    vram = Put2C(vram, Char_Remain);
                    --i;
                } while (i > 0);
            }
        }
    }
    PrintScore();
    PrintTime();
}

void PrintScore()
{
    auto vram = PrintNumber5(Vram + VramRowSize * 1 + (LeftX + 2) * VramStep, Score);
    PrintC(vram, '0');
}

void PrintTime()
{
    PrintByteNumber3(Vram + VramRowSize * 5 + (LeftX + 5) * VramStep, StageTime);
}

void PrintGameOver()
{
    PrintS(Vram + VramRowSize * 4 + 8 * VramStep, "GAME OVER");
}

void PrintTimeUp() 
{
    PrintS(Vram + VramRowSize * 4 + 9 * VramStep, "TIME UP");
}

void PrintPerfect() 
{
    PrintS(Vram + VramRowSize * 4 + 9 * VramStep, "PERFECT");
}


byte Title()
{
    ClearScreen(); 
    HideAllSprites();
    PrintStatus(); 
    {
        static const byte TitleBytes[] = {
            0x0e, 0x05, 0x0b, 0x00, 
            0x0d, 0x0a, 0x02, 0x0c, 
            0x0a, 0x00, 0x0f, 0x04, 
            0x04, 0x05, 0x01, 0x00, 
            0x00, 0x00, 0x00, 0x00, 
            0x03, 0x0f, 0x0c, 0x07, 
            0x0b, 0x07, 0x0c, 0x07, 
            0x04, 0x00, 0x04, 0x05, 
            0x00, 0x00, 0x00, 0x00, 
            0x01, 0x0f, 0x00, 0x0c, 
            0x01, 0x0f, 0x00, 0x0c, 
            0x01, 0x05, 0x05, 0x04, 
            0x00, 0x00, 0x00, 0x00, 
            0x03, 0x00, 0x0e, 0x0d, 
            0x03, 0x00, 0x0f, 0x0e, 
            0x05, 0x01, 0x05, 0x04, 
            0x00, 0x0e, 0x05, 0x0b, 
            0x02, 0x0d, 0x0a, 0x02, 
            0x03, 0x0a, 0x00, 0x0f, 
            0x01, 0x04, 0x05, 0x01, 
        };
        constexpr auto TitleLength = 5;
        constexpr auto TitleLeft = (VVramWidth - 4 * TitleLength) / 2;
        auto pVVram = VVramFront + VVramWidth * 2 + TitleLeft;
        auto p = TitleBytes;
        repeat (TitleLength) {
            repeat (4) {
                repeat (4) {
                    *pVVram++ = *p++;
                }
                pVVram += VVramWidth - 4;
            }
            pVVram += 4 - VVramWidth * 4;
        }
        VVramToVram();
        PrintS(Vram + VramRowSize * 3 + (TitleLeft + 4 * TitleLength - 5) * VramStep, "MINI");
    }
    // {
    //     auto pVVram = VVram;
    //     byte c = 0;
    //     for (auto i = 0; i < Char_End; ++i) {
    //         *pVVram++ = c++;
    //         if ((c & 15) == 0) {
    //             pVVram += VVramWidth - 16;
    //         }
    //     }
    // }
    // VVramToVram();
    PrintS(Vram + VramRowSize * 7 + 12 * VramStep, "INUFUTO 2026");
    {
        constexpr auto ArrowX = 8;
        PrintS(Vram + VramRowSize * 5 + (ArrowX + 1) * VramStep, "START");
        PrintS(Vram + VramRowSize * 6 + (ArrowX + 1) * VramStep, "CONTINUE");
        byte selection = 0;
        bool changed = true;
        while (true) {
            auto vram = Vram + VramRowSize * 5 + ArrowX * VramStep;
            if (changed) {
                changed = false;
                for (byte i = 0; i < 2; ++i) {
                    if (i == selection) {
                        vram = PrintC(vram, '>');
                    }
                    else {
                        vram = PrintC(vram, ' ');
                    }
                    vram += VramRowSize - 1 * VramStep;
                }
            }
            byte key = ScanKeys();
            if ((key & Keys_Button0) != 0) return selection;
            if ((key & Keys_Dir) != 0) {
                auto newSelection = selection ^ 1;
                changed = (newSelection != selection);
                selection = newSelection;
                while (ScanKeys() != 0);
            }
        }
    }
}