#pragma once


#include <string>
#include <sstream>
#include <vector>
#include "core/Display.h"
#include "screens/Screen.h"

class Menu : public Screen {

    public:
    void render() override;
    void update() override;
    
    int scroll = 0;
    int pointer = 0;
    std::vector<std::string> items = {"Hello", "World"};
    std::string heading = "<<MENU>>";
};