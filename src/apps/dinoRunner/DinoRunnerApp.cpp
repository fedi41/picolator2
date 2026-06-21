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
    Logger::d("dino game UPDATE");

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
    Logger::d("dino game RENDER");

    int dinoRectY = 240 - game.y - 30;

    // RENDER

    Display::clear(bgColor);

    Display::drawPlaceholder(20, dinoRectY, 30,30);

}

