#pragma once

#include "App.h"

class MainApp : public App {
    public:
        void init() override;
        void render(Display& display) override;
        void update() override;

    private:
        int app_list ;
        int pointer_pos ; 
};