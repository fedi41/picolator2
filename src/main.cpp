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

int main(void)
{
    // LCD_1in3_test();


    Display display;
    Input input;

    display.init();
    // display.clear(BLACK);
    input.init();
    
    display.drawImage(gImage_1inch3_1, 0, 0, 240, 240); // Display the image on the screen

    display.render();

    DEV_Delay_ms(1000);


    TestApp testApp;
    App* currentApp = &testApp;
    currentApp->init();


    while (true) {

        currentApp->update();

        currentApp->renderIfDirty(display); // Only render if there are changes to the app
        display.renderIfDirty(); // Only render if there are changes to the display
    }

    return 0;
}