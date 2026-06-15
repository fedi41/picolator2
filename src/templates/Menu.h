#pragma once



#include "apps/App.h"
#include "core/Display.h"

class Menu : public App {

    void render(Display& display) override;

    void update() override;

};