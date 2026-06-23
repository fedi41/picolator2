

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

bool DrawUtils::overlap(
    int x1, int y1, const Image1Bit& a,
    int x2, int y2, const Image1Bit& b
) {
    int left   = std::max(x1, x2);
    int top    = std::max(y1, y2);
    int right  = std::min(x1 + a.width,  x2 + b.width);
    int bottom = std::min(y1 + a.height, y2 + b.height);

    if (left >= right || top >= bottom)
        return false;

    int bytesPerRowA = (a.width + 7) / 8;
    int bytesPerRowB = (b.width + 7) / 8;

    for (int y = top; y < bottom; y++) {
        int ay = y - y1;
        int by = y - y2;

        for (int x = left; x < right; x++) {

            int ax = x - x1;
            int bx = x - x2;

            int byteA = ay * bytesPerRowA + ax / 8;
            int byteB = by * bytesPerRowB + bx / 8;

            bool bitA = a.data[byteA] & (0x80 >> (ax & 7));
            bool bitB = b.data[byteB] & (0x80 >> (bx & 7));

            if (bitA && bitB)
                // Display::drawRect(x-5,y-5,x+5,y+5, Colors::red);
                // Display::drawCenteredString(10, "bruh", Colors::red, Display::alpha, &Font6x8, 2);
                // Display::render();
                // Display::frozen = true;
                return true;
        }
    }

    return false;
}