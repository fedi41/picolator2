
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

    

}



void AiChatApp::render() {
    // BG
    Display::clear(CURRENT_THEME->surface[2]);

    // HEADING
    Display::drawRect(0,0,240,50, CURRENT_THEME->primary[8]);

    Display::drawCenteredString(11, "AI-CHAT", CURRENT_THEME->primary[2], Display::alpha, &Font6x8, 4, -3);
    Display::drawCenteredString(8, "AI-CHAT", CURRENT_THEME->primary[5], Display::alpha, &Font6x8, 4, -6);

    



}
void AiChatApp::update() {
    if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B))  {Navigation::pop(); }
}