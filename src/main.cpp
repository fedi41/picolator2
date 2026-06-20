//#include <stdio.h>
//#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"
extern "C" {
    #include "LCD_1in3.h"
    #include "ImageData.h"
}

#include "pico/stdlib.h"

#include "pico/cyw43_arch.h"

#include "core/Display.h"
#include "core/Input.h"

#include "apps/App.h"

#include "core/Navigation.h"
#include "core/Logger.h"
#include "gfx/Colors.h"
#include "assets/logoImg.h"
#include "assets/testImg.h"

int main(void)
{
    // LCD_1in3_test();
    
    // CONFIG
    cyw43_arch_init();


    Display::init();
    Display::clear(Colors::black);

    // CONFIG

    Logger::displayAfterPush = false;    
    TailwindPalette::mirrorPallete = false;
    Display::renderOverlay = true;
    Display::drawBlendMode = NORMAL;
    Display::overlayBlendMode = DIFFERENCE;

    //Display::drawPlaceholder(0,0,240,240);

    Display::clear(0);
    Display::drawPlaceholder(0,0,240,240);
    // Display::drawImage(logoImage, 0,0,240,240);
    // Display::drawImage(testImage, 0,0,120,60);
    Display::render();

// 
//     Display::overlayMode = true;
//         // 
//         Display::clear(0);
//         Display::drawImage(logoImage, 0,0,240,240);
// //
//     Display::overlayMode = false;


    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    DEV_Delay_ms(2000);

    Logger::d("Display initialized");

    Input::init(15, 17, 19, 2, 2, 18, 16, 20, 3);

    Logger::d("Input initialized");
    
    // Display::drawImage(gImage_1inch3_1, 0, 0, 240, 240); // Display the image on the screen

    // Display::render();

    // DEV_Delay_ms(250);


    // Display::render();



    Navigation::open(AppId::MAIN_MENU);

    Logger::d("--- Starting the main loop");

    while (true) {
        // if (Input::isKeyPressed(KEY_Y)) {Navigation::open(AppId::TEST);}
        // else {Navigation::open(AppId::MAIN_MENU);}
        // if (Input::isKeyPressed(KEY_X)) {Display::renderOverlay = true;}
        // else {Display::renderOverlay = false;}
        //if (Input::isKeyPressed(KEY_B))  {Navigation::pop(); }
        Input::update();
        Navigation::current()->update();

        Navigation::current()->renderIfDirty(); // Only render if there are changes to the app

        if (Display::dirty) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            Display::render();
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
    }

    return 0;
}