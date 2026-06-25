#pragma once

#include <cstdint>

namespace Colors {
    constexpr uint16_t magenta = 0x1FF8;
    constexpr uint16_t white = 0xFFFF;
    constexpr uint16_t black = 0x0000;
    constexpr uint16_t red = 0x00f8;
    constexpr uint16_t blue = 0x1f00;
    constexpr uint16_t green = 0xe007;
};

#define TW_COUNT 11
// 
// using uint8_t = unsigned char;
// using uint16_t = unsigned short;
// 


struct ColorHSL {
    float h; // 0-360
    float s; // 0-1
    float l; // 0-1
};
struct ColorRGB
{
    uint8_t r, g, b;
};

class TailwindPalette {
    public:
        uint16_t shades[11];
        int baseColorId = 5;

        constexpr uint16_t base() const {
            return shades[baseColorId]; // 500
        }

        uint16_t operator[](int i) {
            if (mirrorPallete) {
                return shades[11-i];
            }
            return shades[i];
        }

        static TailwindPalette fromHSL(ColorHSL hsl);
        static inline bool mirrorPallete = false;
    
    private:
        TailwindPalette(const uint16_t colors[11], int baseColorId);
       
};


ColorRGB HSLtoRGB(ColorHSL hsl);
uint16_t RGBtoInt(ColorRGB rgb);
uint16_t HSLtoInt(ColorHSL hsl);
ColorHSL tailwindShade(ColorHSL base, int shade);
// TailwindColor HSLtoTailwindColor(ColorHSL base);
// TailwindColor RGBtoTailwindColor(ColorRGB base);