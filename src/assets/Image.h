#pragma once

#include <stdint.h>
#include <algorithm>

struct ImageRGB {
    uint16_t width;
    uint16_t height;
    const uint16_t* data;
};
struct Image1Bit
{
    uint16_t width;
    uint16_t height;
    const uint8_t* data;
};


namespace LogoImage {
    extern const ImageRGB normal;
    extern const ImageRGB lag;
}

namespace Stardance {
    extern const ImageRGB logo;
}

namespace DinoRunnerAssets {

    namespace Dino
    {
        extern const Image1Bit idle;
        extern const Image1Bit run1;
        extern const Image1Bit run2;
        extern const Image1Bit scared;
        extern const Image1Bit sneak1;
        extern const Image1Bit sneak2;

    } // namespace Dino
    
    extern const Image1Bit floor;
    extern const Image1Bit restart;

    namespace Cactus {
        extern const Image1Bit cactus_small1;
        extern const Image1Bit cactus_big1;
        extern const Image1Bit cactus_multi;
        extern const Image1Bit cactus_giga;

    }
}

