#pragma once

#define WHITE          0xFFFF
#define BLACK          0x0000
#define BLUE           0x001F
#define BRED           0XF81F
#define GRED           0XFFE0
#define GBLUE          0X07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN          0XBC40
#define BRRED          0XFC07
#define GRAY           0X8430


#define TW_COUNT 11
// 
// using uint8_t = unsigned char;
// using uint16_t = unsigned short;
// 
#include <cstdint>


enum TailwindShade {
    TW50, TW100, TW200, TW300, TW400,
    TW500, TW600, TW700, TW800, TW900, TW950
};

struct ColorHSL {
    float h; // 0-360
    float s; // 0-1
    float l; // 0-1
};
struct ColorRGB
{
    uint8_t r, g, b;
};
struct TailwindColor {
    uint16_t shades[11];

    constexpr uint16_t base() const {
        return shades[5]; // 500
    }

    constexpr uint16_t operator[](int i) const {
        return shades[i];
    }

    static TailwindColor fromHSL(ColorHSL hsl);
};


ColorRGB HSLtoRGB(ColorHSL hsl);
uint16_t RGBtoInt(ColorRGB rgb);
uint16_t HSLtoInt(ColorHSL hsl);
ColorHSL tailwindShade(ColorHSL base, TailwindShade shade);
// TailwindColor HSLtoTailwindColor(ColorHSL base);
// TailwindColor RGBtoTailwindColor(ColorRGB base);