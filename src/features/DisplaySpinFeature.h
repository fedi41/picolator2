#pragma once

#include "Feature.h"

#include "core/Display.h"
#include "assets/logoImg.h"
#include "core/Navigation.h"


class DisplaySpinFeature: public Feature 
{
public:
    const char* getName() override {
        return "DisplaySpinFeature";
    }
    void update() override {

        Display::drawRotation += 90;
        if (Display::drawRotation >= 360) {
            Display::drawRotation = 0;
        }

        Display::dirty = true;
        Navigation::current()->setDirty();
    }
};