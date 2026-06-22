#include "DinoRunnerApp.h"
#include "core/Input.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "core/Navigation.h"
#include "gfx/Colors.h"


uint16_t bgColor = HSLtoInt({0,0,0.95});


int toScreenUnit(float gameUnit) {
    return (int) gameUnit;
}
int toScreenY(float gameY) {
    return 240 - toScreenUnit(gameY);
}

void DinoRunnerApp::init() {

    

}

void DinoRunnerApp::update() {

    game.update();
    if (Input::pressed(KEY_CTRL)) {
        game.jump();
    }
    if (Input::pressed(KEY_B)) {
        Navigation::pop();
        return;
    }
    
    setDirty();
}

void DinoRunnerApp::render() {


    int dinoRectY = 240 - game.y - 60 - 40; 
    //Logger::d(std::to_string(dinoRectY));

    // RENDER

    Display::clear(bgColor);

    Display::drawPlaceholder(20, dinoRectY, 80, dinoRectY+60);

}

