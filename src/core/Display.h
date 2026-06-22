#pragma once

extern "C" {
    #include "LCD_1in3.h"
}

#include <string>
#include "fonts/fonts.h"

enum BlendMode {
    NORMAL, DIFFERENCE, MIX
};

class Display {
public:
    static void init(uint16_t alpha = 34564);
    static bool render();
    static void update();
    static void wakeUp(); 

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
        const uint16_t *image, 
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
    
    static const int width = 240;
    static const int height = 240;

    static inline uint16_t alpha = 0;
    static inline int drawRotation = 0;
    static inline BlendMode blendMode = NORMAL;
private:
    static inline uint16_t* frameBuffer = nullptr;
    static const uint32_t bufferSize = width * height;

    static inline bool displaySleeping = false;
    static inline uint32_t lastInteraction = 0; 
    static const uint32_t TIMEOUT_MS = 30000; // 30 seconds
};

