#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

class Display {
public:
    void init();
    void render();

    void clear(UWORD color);

    void setPixel(UWORD x, UWORD y, UWORD color);

    void drawPoint(UWORD x, UWORD y, UWORD color,
                   DOT_PIXEL dotPixel,
                   DOT_STYLE dotStyle);

    void drawLine(UWORD xStart, UWORD yStart,
                  UWORD xEnd, UWORD yEnd,
                  UWORD color,
                  LINE_STYLE lineStyle,
                  DOT_PIXEL lineWidth);

    void drawRectangle(UWORD xStart, UWORD yStart,
                       UWORD xEnd, UWORD yEnd,
                       UWORD color,
                       DRAW_FILL fill,
                       DOT_PIXEL lineWidth);

    void drawCircle(UWORD xCenter, UWORD yCenter,
                    UWORD radius,
                    UWORD color,
                    DRAW_FILL fill,
                    DOT_PIXEL lineWidth);

    void drawString(UWORD x,
                    UWORD y,
                    const char* text,
                    sFONT* font,
                    UWORD bgColor,
                    UWORD fgColor);

    void drawNumber(UWORD x,
                    UWORD y,
                    int number,
                    sFONT* font,
                    UWORD bgColor,
                    UWORD fgColor);

    void drawBitmap(const unsigned char* bitmap);
    void drawImage(const unsigned char *image, UWORD xStart, UWORD yStart, UWORD W_Image, UWORD H_Image);

private:
    UWORD* frameBuffer = nullptr;
    uint32_t bufferSize = 0;
};
