#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include <string>


class Display {
public:
    void init();
    void render();
    void renderIfDirty() {
        if (Display::dirty) {
            render();
        }
    }

    void clear(int color);
    static bool dirty;
    static const int width = LCD_1IN3_WIDTH;
    static const int height = LCD_1IN3_HEIGHT;

private:
    UWORD* frameBuffer = nullptr;
    uint32_t bufferSize = 0;
};
