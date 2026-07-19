#include "Keyboard.h"

void Keyboard::render() {



    //Display::drawCenteredString(20, string, CURRENT_THEME->primary[5], Display::alpha, &Font6x8, 2);

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
            x, y, (shift ? layoutShift[i] : layoutNormal[i]), CURRENT_THEME->secondary[7], Display::alpha, &Font6x8, 3
        );
    }

    setDirty(false);


};
void Keyboard::update() {

    if (Input::justPressed(KEY_LEFT)) {
        pointer -= 1;
        setDirty();
    }
    if (Input::justPressed(KEY_RIGHT)) {
        pointer += 1;
        setDirty();
    }
    if (Input::justPressed(KEY_UP)) {
        pointer -= 10;
        setDirty();
    }
    if (Input::justPressed(KEY_DOWN)) {
        pointer += 10;
        setDirty();
    }
    if (Input::justPressed(KEY_A)) {
        string = string + (shift ? layoutShift[pointer] : layoutNormal[pointer]);
        setDirty();
        onChanged();
    }
    if (Input::justPressed(KEY_X)) {
        string.pop_back();
        setDirty();
        onChanged();
    }

    if (Input::pressed(KEY_CTRL)) {
        if (!shift) {
            setDirty();
        }
        shift = true;
    } else {
        if (shift) {
            setDirty();
        }
        shift = false;
    }

        

};