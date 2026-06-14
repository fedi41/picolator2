
extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}


#include "TestApp.h"
#include "core/Display.h"

void TestApp::init() {
    // Initialize the main screen app

}

void TestApp::render(Display& display) {
    // Render the main screen app
    display.clear(BLACK);
    display.drawCenteredString(10, "PICOLATOR", RED, display.alpha, &Font, 2);
    display.drawChar(50, 50, 'H', YELLOW, display.alpha, &Font20, 2);
    //UiDraw::centeredString(10, "Hello, World!", WHITE, BLACK, false, true);
    //display.drawNumber(10, 40, counter, &Font20, WHITE, BLACK);


}

void TestApp::update() {
    // Update the main screen app
    this -> setDirty(true); // Mark the app as dirty to trigger a re-render
    counter++;
}