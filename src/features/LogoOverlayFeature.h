#pragma once

#include "Feature.h"

#include "core/Display.h"
#include "assets/Image.h"


class LogoOverlayFeature: public Feature 
{
public:
    const char* getName() override {
        return "LogoOverlayFeature";
    }
    void render() override {
        Display::blendMode = DIFFERENCE;
        Display::drawImage(LogoImage::lag, 0,0);
        Display::blendMode = NORMAL;

        needsRedraw = false;
    }
};