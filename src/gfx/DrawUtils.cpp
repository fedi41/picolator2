

#include "DrawUtils.h"

void DrawUtils::drawTailwindShade(int x, int y, int xx, int yy, TailwindPalette palette) {
        int wi = (xx-x) / 12;
        for (int i = 0; i < 12; i++) {
            if (i == palette.baseColorId) {
                Display::drawRect(
                    x+wi*i, y, x+wi*i+wi, yy, palette[i]^0xFFFF
                );
                Display::drawRect(
                    x+wi*i+2, y+2, x+wi*i+wi-2, yy-2, palette[i] 
                );
            } else {
                Display::drawRect(
                    x+wi*i, y, x+wi*i+wi, yy, palette[i] 
                );
            }
        }
}
// BRUH
void DrawUtils::drawNoise(int x, int y, int xx, int yy) {
    uint16_t *ptr = 0;
    Display::drawImageData(ptr, x, y, xx, yy);
}