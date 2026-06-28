#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include "core/Display.h"
#include "screens/Screen.h"
#include "core/Input.h"
#include "gfx/Theme.h"
#include "fonts/fonts.h"

class Keyboard : public Screen {

    public:
    void render() override;
    void update() override;
    
    int pointer = 0;
    const char* layoutNormal = "1234567890qwertyuiopasdfghjkl-zxcvbnm---";
    //const char* layoutNormal = "1234567890qwertyuiopasdfghjkl-zxcvbnm---";
};