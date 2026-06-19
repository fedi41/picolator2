#pragma once

#include "App.h"
#include "screens/Menu.h"
#include "core/AppId.h"





class MainMenuApp : public App {

    void init() override;
    void update() override;
    void render() override;

    private:
        Menu menuScreen = Menu();
        std::vector<AppId> apps = {};
};