#include "Keyboard.h"

void Keyboard::render() {


    Display::drawRect(
        0,137,240,140, CURRENT_THEME->secondary[7]
    );
    Display::drawRect(
        0,140,240,240, CURRENT_THEME->secondary[3]
    );

    for (int i = 0; i < 40; i++) {
        int x = i%10*24;
        int y = i/10*24+144;
        
        if (i == pointer) {
            Display::drawRect(
                x,y,x+24,y+24,CURRENT_THEME->secondary[5]
            );
        }
        Display::drawChar(
            x, y, layoutNormal[i], CURRENT_THEME->secondary[7], Display::alpha, &Font6x8, 3
        );
    }

    setDirty(false);


};
void Keyboard::update() {

    if (Input::justPressed(KEY_LEFT)) {
        pointer -= 1;
    }
    if (Input::justPressed(KEY_RIGHT)) {
        pointer += 1;
    }
    if (Input::justPressed(KEY_UP)) {
        pointer -= 10;
    }
    if (Input::justPressed(KEY_DOWN)) {
        pointer += 10;
    }

    setDirty();
        

};