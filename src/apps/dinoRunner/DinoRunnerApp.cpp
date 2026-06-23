#include "DinoRunnerApp.h"
#include "core/Input.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "core/Navigation.h"
#include "gfx/Colors.h"
#include "assets/Image.h"



const uint16_t bgColor = HSLtoInt({0,0,0.3});
const uint16_t fgColor =  HSLtoInt({0,0,0.95});




int toScreenUnit(float gameUnit) {
    return (int) gameUnit;
}
int toScreenY(float gameY) {
    return 240 - toScreenUnit(gameY);
}

void DinoRunnerApp::init() {

    

}

void DinoRunnerApp::update() {

    if (Input::pressed(KEY_LEFT)) {
        Navigation::pop();
        return;
    } 

    if (!game.gameOver) {
        game.update();
        if (Input::pressed(KEY_UP) || Input::pressed(KEY_CTRL) || Input::pressed(KEY_A)) {
            game.jump();
        } 
        if (Input::pressed(KEY_DOWN) || Input::pressed(KEY_B)) {
            game.sneaking = true;
        } else {game.sneaking = false;}
        setDirty();
    }

    if (Input::anyPressed() && game.gameOver == true) {
        game.restart();
        Display::clear(fgColor);
        Display::drawImage1Bit(
            120-DinoRunnerAssets::restart.width, 120-DinoRunnerAssets::restart.height, 
            DinoRunnerAssets::restart.data, 
            DinoRunnerAssets::restart.width,
            DinoRunnerAssets::restart.height,
            bgColor, Display::alpha, 2
        );  
        Display::render();
        DEV_Delay_ms(450);
    }

}

void DinoRunnerApp::render() {
    int dinoRectY = 240 - game.dinoY - game.dinoTexture->height; 

    // RENDER

    Display::clear(bgColor);

    // FLOOR
    Display::drawImage1Bit(
        -(((int)game.levelScroll)%1200), 240-FLOOR_HEIGHT-10, 
        DinoRunnerAssets::floor.data, 
        DinoRunnerAssets::floor.width,
        DinoRunnerAssets::floor.height,
        fgColor, Display::alpha, 1
    );

    // CACTUS
    Display::drawImage1Bit(
        game.currentCactus.x, 240-FLOOR_HEIGHT-game.currentCactus.texture->height, 
        game.currentCactus.texture->data, 
        game.currentCactus.texture->width,
        game.currentCactus.texture->height,
        fgColor, Display::alpha, 1
    );

    // DINO
    Display::drawImage1Bit(
        DINO_SCREEN_X, dinoRectY, 
        game.dinoTexture->data, 
        game.dinoTexture->width,
        game.dinoTexture->height,
        fgColor, Display::alpha, 1
    );

    // SCORE 
    Display::drawCenteredString(
        30, std::to_string(game.score), fgColor, Display::alpha, &Font6x8, 2
    );
    Display::drawCenteredString(
        10, std::to_string(Storage::data.dinoRunnerHighScore), fgColor, Display::alpha, &Font6x8, 2
    );

    if (game.gameOver) {
        Display::drawImage1Bit(
            120-DinoRunnerAssets::restart.width, 120-DinoRunnerAssets::restart.height, 
            DinoRunnerAssets::restart.data, 
            DinoRunnerAssets::restart.width,
            DinoRunnerAssets::restart.height,
            fgColor, Display::alpha, 2
        );  
    }
}

