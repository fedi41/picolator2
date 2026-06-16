#include "Menu.h"

#include "gfx/Theme.h"
#include "gfx/Colors.h"

void Menu::render() {

    // BG
    Display::clear(CURRENT_THEME.surface[TW400]);

    // HEADING
    Display::drawRect(0,0,240,50, CURRENT_THEME.primary[TW300]);

    Display::drawCenteredString(8, heading, CURRENT_THEME.primary[TW900], Display::alpha, &Font6x8, 4, -6);
    Display::drawCenteredString(11, heading, CURRENT_THEME.primary[TW500], Display::alpha, &Font6x8, 4, -3);

    // Content

    for (int i = 0; i < MIN(4,items.size()); i++) {
        int y = 50 + i * 47;
        //Display::drawPlaceholder(0, y, 240, y+45);

        Display::drawRect(2, y+3, 238, y+47, CURRENT_THEME.secondary[TW300]);

        Display::drawCenteredString(y+17, items[i], CURRENT_THEME.secondary[TW900], Display::alpha, &Font6x8, 2);
    }

    // Display::drawString(3, 50, "Lorem Ipsum!!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 70, "Hello World!", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 90, "WOoooww", YELLOW, Display::alpha, false, &Font6x8, 2);
    // Display::drawString(3, 110, "abcdefghijklmnopqrstuvwxyz", YELLOW, Display::alpha, false, &Font4x6, 2);

}

void Menu::init() {}
void Menu::update() {}