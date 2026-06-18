//#include <stdio.h>
//#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"
extern "C" {
    #include "LCD_1in3.h"
    #include "ImageData.h"
}

#include "core/Display.h"
#include "core/Input.h"
#include "apps/TestApp.h"
#include "apps/App.h"
#include "apps/MainApp.h"
#include "core/AppManager.h"
#include "core/Logger.h"
#include "gfx/Colors.h"
#include "assets/logoImg.h"
#include "assets/logoImg.h"
#include "assets/testImg.h"

int main(void)
{
    // LCD_1in3_test();
    
    // CONFIG
    Logger::displayAfterPush = false;
    TailwindPalette::mirrorPallete = false;


    Display::init();
    Display::clear(BLACK);
    //DISPLAY CONFIG
    Display::renderOverlay = true;
    Display::drawBlendMode = NORMAL;
    Display::overlayBlendMode = DIFFERENCE;

    //Display::drawPlaceholder(0,0,240,240);

    Display::overlayMode = true;
    Display::clear(0);
    Display::drawImage(logoImage, 0,0,240,240);
    // Display::drawImage(testImage, 0,0,120,60);
    Display::overlayMode = false;

    Logger::d("Display initialized");

    Input::init();

    Logger::d("Input initialized");
    
    // Display::drawImage(gImage_1inch3_1, 0, 0, 240, 240); // Display the image on the screen

    // Display::render();

    // DEV_Delay_ms(250);


    // Display::render();


    TestApp testApp;
    MainApp mainApp;

    AppManager::push(&mainApp);

    Logger::d("AppManager Initialized");

    while (true) {
        if (Input::isKeyPressed(KEY_Y)) {AppManager::push(&testApp);}
        else {AppManager::push(&mainApp);}
        // if (Input::isKeyPressed(KEY_X)) {Display::renderOverlay = true;}
        // else {Display::renderOverlay = false;}


        AppManager::current()->update();

        AppManager::current()->renderIfDirty(); // Only render if there are changes to the app
        Display::render(); // Only render if there are changes to the display
    }

    return 0;
}