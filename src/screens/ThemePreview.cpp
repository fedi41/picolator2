

#include "ThemePreview.h"
#include "core/Display.h"
#include "gfx/Colors.h"
#include "gfx/Theme.h"
#include "gfx/DrawUtils.h"


void ThemePreview::render() {

    Display::clear(Colors::black);

    int w = 240 / 11;
    int h = 240 / 3;

    DrawUtils::drawTailwindShade(
        0, 0, 240, h, CURRENT_THEME->surface
    );
    DrawUtils::drawTailwindShade(
        0, h, 240, h+h, CURRENT_THEME->primary
    );
    DrawUtils::drawTailwindShade(
        0, h+h, 240, 240, CURRENT_THEME->secondary
    );

}

void ThemePreview::update() {}