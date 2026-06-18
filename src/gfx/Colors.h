#pragma once

#define WHITE          0xFFFF
#define BLACK          0x0000
// #define BLUE           0x001F
// #define BRED           0XF81F
// #define GRED           0XFFE0
// #define GBLUE          0X07FF
// #define RED            0xF800
#define MAGENTA        0x1FF8
// #define GREEN          0x07E0
// #define CYAN           0x7FFF
// #define YELLOW         0xFFE0
// #define BROWN          0XBC40
// #define BRRED          0XFC07
// #define GRAY           0X8430


#define TW_COUNT 11
// 
// using uint8_t = unsigned char;
// using uint16_t = unsigned short;
// 
#include <cstdint>

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

        constexpr uint16_t operator[](int i) const {
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