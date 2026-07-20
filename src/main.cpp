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

#include "core/App.h"

#include "core/Navigation.h"
#include "core/Logger.h"
#include "gfx/Colors.h"
#include "assets/Image.h"
#include "assets/logoLagImg.h"
#include "storage/Storage.h"

#include "features/FeatureManager.h"

#include "core/Wifi.h"

int main(void)
{
 


//===================================================================================//
//============================INITIALISATION=========================================//
//===================================================================================//


    printf("Picolator2 starting...\n");


    // CONFIG
    TailwindPalette::mirrorPallete = false;
    Logger::onLog = []() {
        Display::clear(Colors::black);
        Logger::render();
        Display::render();
    };
    Display::blendMode = NORMAL;

    Display::init();
    Display::clear(Colors::black);
    Display::render();
    Logger::d("Display initialized");

    Storage::load();
    Logger::d("Storage loaded");
    // Logger::d("Magic: " +  Storage::data.magic);
    Logger::d("SSID: " + std::string(Storage::data.wifiSSID));
    Logger::d("PASS: " + std::string(Storage::data.wifiPASS));
    Logger::d("Pico-Dino Highscore: " + std::to_string(Storage::data.dinoRunnerHighScore));


    Input::init(15, 17, 19, 21, 2, 18, 16, 20, 3);
    Logger::d("Input initialized");

    Logger::d("Trying to connect to WiFi");
    Wifi::init();
    Wifi::connect();
    Wifi::wifiConnected ? Logger::d("WiFi connected") : Logger::d("WiFi not connected");

    FeatureManager::init();
    Logger::d("FeatureManager initialized");

    FeatureManager::setEnabled("LogoOverlayFeature", false);
    FeatureManager::setEnabled("DisplaySpinFeature", false);
    FeatureManager::setEnabled("LogDisplayFeature", false);

    Navigation::open(AppId::MAIN_MENU);
    Logger::d("started main menu app");


    Logger::d("-- READY --"); 

    // logo splash
    // Display::clear(0);
    // Display::drawImage(LogoImage::lag, 0, 0);
    // Display::render();
    // DEV_Delay_ms(500);

    Logger::d("--- Starting the main loop");

    Logger::onLog = []() {};

//===================================================================================//
//======================================MAIN=LOOP====================================//
//===================================================================================//


    while (true) {
        // INPUT
        Input::update();

        // APP UPDATE
        Navigation::current()->update();
        // FEATURE UPDATE
        FeatureManager::update();

        // APP DRAW
        Navigation::current()->renderIfDirty(); // Only render if there are changes to the app
        // FEATURE DRAW
        FeatureManager::render(Display::dirty);
        //Display::dirty = true;
        Display::update();

        // if (Input::pressed(KEY_X)) {Display::frozen = true;}

        if (Display::dirty) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            Display::render();
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
    }

    return 0;
}