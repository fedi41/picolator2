#pragma once

#include <cstdint>
#include <string>
#include "core/Display.h"
#include "Element.h"

class TaskBar : public Element {

    public:
    void render() override;
    void update() override;
    
    std::string currentAppName = "no app running xD";
    bool wlanConnected = false;
};
