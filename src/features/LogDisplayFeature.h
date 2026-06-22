#pragma once

#include "Feature.h"

#include "core/Display.h"
#include "core/Logger.h"


class LogDisplayFeature: public Feature 
{
public:
    const char* getName() override {
        return "LogDisplayFeature";
    }
    void update() override {
        if (Logger::dirty) {
            needsRedraw = true;
        }
    }
    void render() override {
        
        Logger::render();
        
        needsRedraw = false;
    }
};