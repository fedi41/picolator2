
extern "C" {
    #include "LCD_1in3.h"
}


#include "TestApp.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "gfx/Colors.h"

void TestApp::init() {
    // Initialize the main screen app

}

void TestApp::render(Display& display) {
    // Render the main screen app
    display.clear(BLACK);
    display.drawCenteredString(10, "PICOLATOR", RED, display.alpha, &Font4x6, 5, -5);

    display.drawString(3, 50, "Lorem Ipsum!!", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 70, "Hello World!", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 90, "WOoooww", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 110, "abcdefghijklmnopqrstuvwxyz", YELLOW, display.alpha, false, &Font4x6, 2);
    //UiDraw::centeredString(10, "Hello, World!", WHITE, BLACK, false, true);
    //display.drawNumber(10, 40, counter, &Font20, WHITE, BLACK);


}

void TestApp::update() {
    // Update the main screen app
    this -> setDirty(true); // Mark the app as dirty to trigger a re-render
    counter++;
}