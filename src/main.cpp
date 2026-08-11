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
#include "gfx/Colors.h"
#include "assets/Image.h"
#include "assets/logoLagImg.h"
#include "storage/Storage.h"

#include "features/FeatureManager.h"

#include "core/Wifi.h"

#include <stdio.h>

int main(void)
{
 


//===================================================================================//
//============================INITIALISATION=========================================//
//===================================================================================//
    stdio_init_all();

    printf("Picolator2 starting...\n");


    // CONFIG
    TailwindPalette::mirrorPallete = false;
    Display::blendMode = NORMAL;

    Display::init();
    Display::clear(Colors::black);
    Display::render();
    printf("Display initialized\n");


    Display::clear(0);
    Display::drawImage(LogoImage::normal, 0, 0);
    Display::render();


    Storage::load();
    printf("Storage loaded\n");
    // Logger::d("Magic: " +  Storage::data.magic);
    printf(("SSID: " + std::string(Storage::data.wifiSSID)).data());
    printf(("\nPASS: " + std::string(Storage::data.wifiPASS)).data());
    printf(("\nPico-Dino Highscore: " + std::to_string(Storage::data.dinoRunnerHighScore)).data());


    Input::init(15, 17, 19, 21, 2, 18, 16, 20, 3);
    printf("\nInput initialized\n");

    printf("Trying to connect to WiFi\n");
    Wifi::init();
    Wifi::connect();
    Wifi::wifiConnected ? printf("WiFi connected\n")  :  printf("WiFi not connected\n");

    FeatureManager::init();
    printf("FeatureManager initialized\n");

    FeatureManager::setEnabled("LogoOverlayFeature", false);
    FeatureManager::setEnabled("DisplaySpinFeature", false);

    Navigation::open(AppId::MAIN_MENU);
    printf("started main menu app\n");

    printf("-- READY --\n"); 

    printf("--- Starting the main loop ---\n");

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