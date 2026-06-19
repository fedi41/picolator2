
extern "C" {
    #include "LCD_1in3.h"
}


#include "TestApp.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "gfx/Colors.h"
#include "gfx/Theme.h"

#include "core/Input.h"
#include "core/Navigation.h"


void TestApp::init() {
    // Initialize the main screen app

}


void drawTailwindShade(int x, int y, int xx, int yy, TailwindPalette palette) {
    int wi = (xx-x) / 12;
    for (int i = 0; i < 12; i++) {
        if (i == palette.baseColorId) {
            Display::drawRect(
                x+wi*i, y, x+wi*i+wi, yy, palette[i]^0xFFFF
            );
            Display::drawRect(
                x+wi*i+2, y+2, x+wi*i+wi-2, yy-2, palette[i] 
            );
        } else {
            Display::drawRect(
                x+wi*i, y, x+wi*i+wi, yy, palette[i] 
            );
        }
    }
}

void TestApp::render() {
    // Render the main screen app
    // Display::clear(BLACK);
    // Display::drawCenteredString(10, "PICOLATOR", RED, Display::alpha, &Font4x6, 5, -5);

    // Display::drawString(3, 50, "Lorem Ipsum!!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 70, "Hello World!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 90, "WOoooww", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 110, "abcdefghijklmnopqrstuvwxyz", YELLOW, Display::alpha, false, &Font4x6, 2);
    // //UiDraw::centeredString(10, "Hello, World!", WHITE, BLACK, false, true);
    // //display.drawNumber(10, 40, counter, &Font20, WHITE, BLACK);
    Display::clear(Colors::black);

    int w = 240 / 11;
    int h = 240 / 3;

    drawTailwindShade(
        0, 0, 240, h, CURRENT_THEME.surface
    );
    drawTailwindShade(
        0, h, 240, h+h, CURRENT_THEME.primary
    );
    drawTailwindShade(
        0, h+h, 240, 240, CURRENT_THEME.secondary
    );


}

void TestApp::update() {
    if (Input::isKeyPressed(KEY_B))  {Navigation::pop(); }

    
    //this -> setDirty(true); // Mark the app as dirty to trigger a re-render
    //counter++;
}