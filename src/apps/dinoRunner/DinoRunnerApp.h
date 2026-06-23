#pragma once

#include "core/App.h"
#include "screens/Menu.h"
#include "core/AppId.h"
#include "dinoGame.h"


class DinoRunnerApp : public App {

    void init() override;
    void update() override;
    void render() override;

    private:
        DinoGame game = DinoGame();
        int runAnimCounter = 0; 

};