#pragma once


#include "core/Display.h"
#include "gfx/Colors.h"

namespace DrawUtils {


    void drawTailwindShade(int x, int y, int xx, int yy, TailwindPalette palette);
    void drawNoise(int x, int y, int xx, int yy);
    bool overlap(int x1, int y1, const Image1Bit& a,int x2, int y2, const Image1Bit& b);
}