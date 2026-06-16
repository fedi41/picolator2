
#include "Colors.h"
#include <cstdint>
#include <cmath>
#include <algorithm>

uint16_t RGBtoInt(ColorRGB rgb) {
    return ((rgb.r >> 3) << 11) |
           ((rgb.g >> 2) << 5)  |
           (rgb.b >> 3);
}

ColorRGB HSLtoRGB(ColorHSL hsl) {
    float h = hsl.h;
    float s = hsl.s;
    float l = hsl.l;

    // Hue in [0, 360)
    h = fmodf(h, 360.0f);
    if (h < 0)
        h += 360.0f;

    // Sonderfall: Graustufen
    if (s <= 0.0f) {
        uint8_t gray = static_cast<uint8_t>(l * 255.0f + 0.5f);
        return {gray, gray, gray};
    }

    float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = l - c / 2.0f;

    float r1, g1, b1;

    if (h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    return {
        static_cast<uint8_t>((r1 + m) * 255.0f + 0.5f),
        static_cast<uint8_t>((g1 + m) * 255.0f + 0.5f),
        static_cast<uint8_t>((b1 + m) * 255.0f + 0.5f)
    };
}
uint16_t HSLtoInt(ColorHSL hsl) {
    float h = fmodf(hsl.h, 360.0f);
    if (h < 0) h += 360.0f;

    float s = hsl.s;
    float l = hsl.l;

    float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = l - c / 2.0f;

    float r1, g1, b1;

    if (h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    uint8_t r = (uint8_t)((r1 + m) * 255.0f + 0.5f);
    uint8_t g = (uint8_t)((g1 + m) * 255.0f + 0.5f);
    uint8_t b = (uint8_t)((b1 + m) * 255.0f + 0.5f);

    return ((r >> 3) << 11) |
           ((g >> 2) << 5)  |
           (b >> 3);
}

// Relative Änderungen gegenüber der Basisfarbe (=500)
static const float lightnessDelta[] = {
    +0.35f, // 50
    +0.28f, // 100
    +0.20f, // 200
    +0.12f, // 300
    +0.06f, // 400
     0.00f, // 500
    -0.08f, // 600
    -0.16f, // 700
    -0.26f, // 800
    -0.38f, // 900
    -0.48f  // 950
};

// Weniger Sättigung an den Extremen
static const float saturationMul[] = {
    0.35f, // 50
    0.50f, // 100
    0.70f, // 200
    0.85f, // 300
    0.95f, // 400
    1.00f, // 500
    0.95f, // 600
    0.85f, // 700
    0.70f, // 800
    0.55f, // 900
    0.40f  // 950
};

ColorHSL tailwindShade(ColorHSL base, int shade) {


    ColorHSL out = base;
    float shadePercent = float(shade)/11;

    out.l += shadePercent-0.5;
    //out.s *= saturationMul[shade];

    // Clamp
    out.l = std::clamp(out.l, 0.0f, 1.0f);
    out.s = std::clamp(out.s, 0.0f, 1.0f);

    return out;
}

TailwindPalette TailwindPalette::fromHSL(ColorHSL hsl) {
    uint16_t out[11];

    int baseColorId = hsl.l * 11;
    int shadeOffset = baseColorId - 5;

    for (int i = 0; i < 11; ++i) {
        //out[i] = HSLtoInt(simpleTailwindShade(hsl, i));
        out[i] = HSLtoInt(tailwindShade(hsl, i-shadeOffset));

    }
    
    
    return TailwindPalette(out, baseColorId);
}
TailwindPalette::TailwindPalette(const uint16_t *colors, int baseColorId) {
    for (int i = 0; i < 11; ++i) {
        shades[i] = colors[i];
    }
    this->baseColorId = baseColorId;
}