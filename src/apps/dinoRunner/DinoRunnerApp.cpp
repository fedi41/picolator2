#include "DinoRunnerApp.h"
#include "core/Input.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "core/Navigation.h"
#include "gfx/Colors.h"
#include "assets/Image.h"


const uint16_t bgColor = HSLtoInt({0,0,0.95});
const uint16_t fgColor = HSLtoInt({0,0,0.3});




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
    if (Input::pressed(KEY_A)) {
        game.jump();
    }
    if (Input::pressed(KEY_LEFT)) {
        Navigation::pop();
        return;
    }
    
    setDirty();
}

void DinoRunnerApp::render() {
    const int dinoSize = DinoRunnerAssets::dino.width*2;
    const int floorHeight = 50;


    int dinoRectY = 240 - game.y - dinoSize - floorHeight; 
    //Logger::d(std::to_string(dinoRectY));

    // RENDER

    Display::clear(bgColor);

    Display::drawRect(0, 240-floorHeight, 240,240, fgColor);

    //Display::drawPlaceholder(20, dinoRectY, 50, dinoRectY+30);
    Display::drawImage1Bit(
        7, dinoRectY, 
        DinoRunnerAssets::dino.data, 
        DinoRunnerAssets::dino.width,
        DinoRunnerAssets::dino.height,
        fgColor, Display::alpha, 2
    );

}

