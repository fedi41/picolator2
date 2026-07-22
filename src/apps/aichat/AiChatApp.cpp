
#include "AiChatApp.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "gfx/Colors.h"
#include "gfx/Theme.h"
#include "assets/Image.h"

#include "core/Input.h"
#include "core/Navigation.h"

#include "gfx/DrawUtils.h"


void AiChatApp::init() {
    // Initialize the main screen app

}



void AiChatApp::render() {

    Display::clear(Colors::black);

    Display::drawImage(Stardance::logo, 0,0);

}

void AiChatApp::update() {
    if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B))  {Navigation::pop(); }
}