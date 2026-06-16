//#include <stdio.h>
//#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"
extern "C" {
    #include "LCD_1in3.h"
    #include "LCD_Test.h" 
    #include "ImageData.h"
}

#include "core/Display.h"
#include "core/Input.h"
#include "apps/TestApp.h"
#include "apps/App.h"
#include "apps/MainApp.h"

int main(void)
{
    // LCD_1in3_test();



    Display::init();
    Display::clear(BLACK);
    Input::init();
    
    Display::drawImage(gImage_1inch3_1, 0, 0, 240, 240); // Display the image on the screen

    Display::render();

    DEV_Delay_ms(250);

    Display::drawPlaceholder(0,0,240,240);
    Display::render();


    TestApp testApp;
    MainApp mainApp;
    App* currentApp = &testApp;
    currentApp->init();

    currentApp->render();


    while (true) {

        currentApp->update();

        currentApp->renderIfDirty(); // Only render if there are changes to the app
        Display::renderIfDirty(); // Only render if there are changes to the display
    }

    return 0;
}