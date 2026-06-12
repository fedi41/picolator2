#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
    #include "lib/Fonts/fonts.h"
}

#include "core/Display.h"
#include "graphics/Theme.h"

class UiDraw {
public:
    // TEXT
    static void string(
        int x, int y,
        const std::string& text, 
        int color, int backgroundColor, 
        bool center = false,     
        bool bgTransparent=false, bool fgTransparent=false, 
        sFONT* font = &Font20);
    static void centeredString(
        int y, const std::string& text, int color, int backgroundColor,
        bool bgTransparent=false, bool fgTransparent=false, 
        sFONT* font = &Font20);
    static void heading(
        const std::string& text, int color, int backgroundColor, int borderColor, sFONT* font = &Font24
    );



    // IMAGES
    static void image(const unsigned char* image, int x, int y, int width, int height);

};