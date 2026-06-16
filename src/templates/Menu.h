#pragma once


#include <string>
#include <sstream>
#include <vector>
#include "apps/App.h"
#include "core/Display.h"

class Menu : public App {

    void render() override;
    void init() override;
    void update() override;

    protected:
        int scroll = 0;
        int pointer = 0;
        std::vector<std::string> items = {"Hello", "World"};
        std::string heading = "<<MENU>>";
};