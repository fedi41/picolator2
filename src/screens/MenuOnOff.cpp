#include "MenuOnOff.h"

#include "gfx/Theme.h"
#include "gfx/Colors.h"
#include "core/Input.h"

#include "core/Logger.h"

void MenuOnOff::render() {
    // Logger::d("Menu render");

    // BG
    Display::clear(CURRENT_THEME->surface[2]);

    // HEADING
    Display::drawRect(0,0,240,50, CURRENT_THEME->primary[8]);

    Display::drawCenteredString(11, heading, CURRENT_THEME->primary[2], Display::alpha, &Font6x8, 4, -3);
    Display::drawCenteredString(8, heading, CURRENT_THEME->primary[5], Display::alpha, &Font6x8, 4, -6);


    // Content

    for (int i = 0; i < MIN(4,items.size()); i++) {
        int y = 50 + i * 47;

        uint16_t text_color = (states[scroll + i] ? Colors::red : Colors::green);

        uint16_t bg_color =  (states[scroll + i] ? Colors::green : Colors::red);
        //Display::drawPlaceholder(0, y, 240, y+45);
        if (pointer - scroll == i) {
            text_color = Colors::black;
        }

        Display::drawRect(2, y+3, 238, y+47, bg_color);

        Display::drawCenteredString(y+17, items[scroll + i], text_color, Display::alpha, &Font6x8, 2);
    }

    // Display::drawCenteredString(y+17, pointer, RED, Display::alpha, &Font6x8, 2);

    // Display::drawString(3, 50, "Lorem Ipsum!!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 70, "Hello World!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 90, "WOoooww", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 110, "abcdefghijklmnopqrstuvwxyz", YELLOW, Display::alpha, false, &Font4x6, 2);
    setDirty(false);
}

void MenuOnOff::update() {
    //Logger::d("Menu update");

    if (Input::justPressed(KEY_DOWN)) {
        pointer += 1;
        setDirty();
    }
    if (Input::justPressed(KEY_UP)) {
        pointer -= 1;
        setDirty();
    }
    if (Input::justPressed(KEY_A)) {
        states[pointer] = !states[pointer];         setDirty();
    }

    if (pointer >= std::size(items)) { pointer = 0; scroll = 0; }
    if (pointer < 0) { pointer = 0; }
    if (scroll + 4 <= pointer) { scroll = pointer-3; }
    if (scroll > pointer) { scroll = pointer; }

}
