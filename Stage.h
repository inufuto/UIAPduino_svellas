#pragma once
#include "cate.h"

constexpr byte ColumnCount = 6;
constexpr byte RowCount = 4;

constexpr byte Panel_Left = 0x01;
constexpr byte Panel_Right = 0x02;
constexpr byte Panel_Top = 0x04;
constexpr byte Panel_Bottom = 0x08;
constexpr byte Panel_Exist = 0x10;
// constexpr byte Panel_Movable = 0x20;
constexpr byte Panel_Star = 0x40;

struct Stage {
    byte bytes[ColumnCount * RowCount];
    byte start;
    byte monsterCount;
    constptr<byte> pMonsters;
};

extern constptr<Stage> pStage;
extern byte PanelMap[];
extern byte StarCount;

extern byte ToCoord(byte a);
extern void InitStage();
extern void InitTrying();
extern void StartMovingPanel();
extern void MovePanel();
extern ptr<byte> MapPtr(byte column, byte row);
