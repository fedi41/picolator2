#pragma once

extern "C" {
    #include "LCD_1in3.h"
}

#include <string>
#include "fonts/fonts.h"

using Color = uint16_t;

class Display {
public:
    static void init(Color alpha = 34564);
    static void render();
    static void renderIfDirty() {
        if (Display::dirty) {
            render();
        }
    }

    static void clear(Color color);

    static void setPixel(int x, int y, Color color);

    static void drawChar(
        int x, 
        int y, 
        const char c, 
        Color fgColor, 
        Color bgColor, 
        FONT* font,
        int scale = 1
    );
    static void drawString(
        int x,
        int y,
        const std::string& text,
        Color fgColor,
        Color bgColor,
        bool center, 
        FONT* font,
        int scale = 1
    );
    static void drawImage(
        const unsigned char *image, 
        int xStart, 
        int yStart, 
        int W_Image, 
        int H_Image
    );
    static void drawCenteredString(
        int y,
        const std::string& text,
        int color,
        int bgColor,
        FONT* font,
        int scale = 1,
        int offset = 0
    );
    static void drawWindow(
        int x,
        int y,
        int xx,
        int yy,
        Color
    );

    static inline bool dirty = false;
    static const int width = LCD_1IN3_WIDTH;
    static const int height = LCD_1IN3_HEIGHT;
    static inline Color alpha = 0x0000;

private:
    static inline UWORD* frameBuffer = nullptr;
    static const uint32_t bufferSize = width * height;
};
