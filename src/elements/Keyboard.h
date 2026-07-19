#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include "core/Display.h"
#include "Element.h"
#include "core/Input.h"
#include "gfx/Theme.h"
#include "fonts/fonts.h"
#include <functional>

class Keyboard : public Element {

    public:
    void render() override;
    void update() override;
    
    int pointer = 0;
    const char* layoutNormal = "1234567890qwertyuiopasdfghjkl'zxcvbnm,./";
    const char* layoutShift  = "!@#$%^&*()QWERTYUIOPASDFGHJKL-ZXCVBNM<>?";


    
    std::function<void()> onChanged;
    bool shift = false;
    std::string string = "";
    //const char* layoutNormal = "1234567890qwertyuiopasdfghjkl-zxcvbnm---";


    Keyboard(std::function<void()> callback = [](){}) {
        onChanged = callback;
    }
};