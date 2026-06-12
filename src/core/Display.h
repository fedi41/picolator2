#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include "graphics/Color.h"
#include <string>


class Display {
public:
    void init(int alphaColor = 1);
    void render();
    void renderIfDirty() {
        if (dirty) {
            render();
        }
    }

    void clear(int color);

    void setPixel(int x, int y, int color);

    // SHAPES
    void drawPoint(int x, int y, int color,
                   DOT_PIXEL dotPixel,
                   DOT_STYLE dotStyle);
                   
    void drawLine(int xStart, int yStart,
                  int xEnd, int yEnd,
                  int color,
                  LINE_STYLE lineStyle,
                  DOT_PIXEL lineWidth);

    void drawRectangle(int xStart, int yStart,
                       int xEnd, int yEnd,
                       int color,
                       DRAW_FILL fill,
                       DOT_PIXEL lineWidth);

    void drawCircle(int xCenter, int yCenter,
                    int radius,
                    int color,
                    DRAW_FILL fill,
                    DOT_PIXEL lineWidth);

    // TEXT
    void drawString(int x,
                    int y,
                    const std::string& text,
                    sFONT* font,
                    int bgColor,
                    int fgColor,
                    bool center = false);

    // IMAGES 

    void drawBitmap(const unsigned char* bitmap);
    void drawImage(const unsigned char *image, int xStart, int yStart, int W_Image, int H_Image);

    bool dirty = false;


private:
    UWORD* frameBuffer = nullptr;
    uint32_t bufferSize = 0;
    int alphaColor = 0;
    int width = LCD_1IN3_WIDTH;
    int height = LCD_1IN3_HEIGHT;
};
