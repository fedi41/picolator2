#pragma once

#include <stdint.h>


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

namespace DinoRunnerAssets {

    extern const Image1Bit dino;

}