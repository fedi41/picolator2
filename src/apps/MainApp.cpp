

#include "MainApp.h"
#include "core/Display.h"
#include "gfx/Theme.h"
#include "gfx/Colors.h"
#include "core/Input.h"


void MainApp::init() {

}

void MainApp::render(Display& display) {
    // BG
    display.clear(CURRENT_THEME.surface);

    // HEADING
    display.drawWindow(0,0,240,50, CURRENT_THEME.onSurface);

    display.drawCenteredString(8, "PICOLATOR", CURRENT_THEME.primary,display.alpha, &Font6x8, 4, -6);
    display.drawCenteredString(11, "PICOLATOR", CURRENT_THEME.onPrimary, display.alpha, &Font6x8, 4, -3);

    // Content


    display.drawString(3, 50, "Lorem Ipsum!!", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 70, "Hello World!", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 90, "WOoooww", YELLOW, display.alpha, false, &Font6x8, 2);
    display.drawString(3, 110, "abcdefghijklmnopqrstuvwxyz", YELLOW, display.alpha, false, &Font4x6, 2);
}

void MainApp::update() {
    if (Input::isKeyPressed(KEY_UP)) {
        
    }
}