#pragma once

#include "Feature.h"

#include "core/Display.h"
#include "assets/logoImg.h"


class LogoOverlayFeature: public Feature 
{
public:
    const char* getName() override {
        return "LogoOverlayFeature";
    }
    void render() override {
        Display::overlayMode = true;

            Display::clear(0);
            Display::drawImage(logoImage, 0,0,240,240);

        Display::overlayMode = false;
    }

};