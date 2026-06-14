#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "lib/Fonts/fonts.h"
}

#include <string>

using Color = uint16_t;

class Display {
public:
    void init(Color alpha = 34535);
    void render();
    void renderIfDirty() {
        if (Display::dirty) {
            render();
        }
    }

    void clear(Color color);

    void setPixel(int x, int y, Color color);

    void drawChar(
        int x, 
        int y, 
        const char c, 
        Color fgColor, 
        Color bgColor, 
        sFONT* font,
        int scale = 1
    );
    void drawString(
        int x,
        int y,
        const std::string& text,
        Color fgColor,
        Color bgColor,
        bool center, 
        sFONT* font,
        int scale = 1
    );
    void drawImage(
        const unsigned char *image, 
        int xStart, 
        int yStart, 
        int W_Image, 
        int H_Image
    );
    void drawCenteredString(
        int y,
        const std::string& text,
        int color,
        int bgColor,
        sFONT* font,
        int scale = 1
    );
    void drawWindow(
        int x,
        int y,
        int xx,
        int yy,
        Color
    );

    bool dirty = false;
    static const int width = LCD_1IN3_WIDTH;
    static const int height = LCD_1IN3_HEIGHT;
    Color alpha;

private:
    UWORD* frameBuffer = nullptr;
    static const uint32_t bufferSize = width * height;
};
