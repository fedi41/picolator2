#pragma once

#include <vector>
#include <string>

#include "core/Display.h"
#include "gfx/Colors.h"

namespace DrawUtils {


    void drawTailwindShade(int x, int y, int xx, int yy, TailwindPalette palette);
    void drawNoise(int x, int y, int xx, int yy);
    bool overlap(int x1, int y1, const Image1Bit& a,int x2, int y2, const Image1Bit& b);
    void drawLines(int x, int y, std::vector<std::string> lines, uint16_t fgColor, uint16_t bgColor, FONT* font, int scale = 1);

}