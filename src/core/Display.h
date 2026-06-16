#pragma once

extern "C" {
    #include "LCD_1in3.h"
}

#include <string>
#include "fonts/fonts.h"


class Display {
public:
    static void init(uint16_t alpha = 34564);
    static void render();
    static void renderIfDirty() {
        if (Display::dirty) {
            render();
        }
    }

    static void clear(uint16_t color);

    static void setPixel(int x, int y, uint16_t color);

    static void drawChar(
        int x, 
        int y, 
        const char c, 
        uint16_t fgColor, 
        uint16_t bgColor, 
        FONT* font,
        int scale = 1
    );
    static void drawString(
        int x,
        int y,
        const std::string& text,
        uint16_t fgColor,
        uint16_t bgColor,
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
        uint16_t color,
        uint16_t bgColor,
        FONT* font,
        int scale = 1,
        int offset = 0
    );
    static void drawRect(
        int x,
        int y,
        int xx,
        int yy,
        uint16_t color
    );
    static void drawPlaceholder(
        int x,
        int y,
        int xx,
        int yy
    );

    static inline bool dirty = false;
    static const int width = LCD_1IN3_WIDTH;
    static const int height = LCD_1IN3_HEIGHT;
    static inline uint16_t alpha = 0x0000;

private:
    static inline UWORD* frameBuffer = nullptr;
    static const uint32_t bufferSize = width * height;
};
