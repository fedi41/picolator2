
#include "AiChatApp.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "core/Navigation.h"
#include "util/TextUtils.h"

#include "Mistral.h"

void AiChatApp::init() {

    

}



void AiChatApp::render() {
    // BG
    Display::clear(CURRENT_THEME->surface[2]);

    // HEADING
    Display::drawRect(0,0,240,50, CURRENT_THEME->primary[8]);

    Display::drawCenteredString(11, "AI-CHAT", CURRENT_THEME->primary[2], Display::alpha, &Font6x8, 4, -3);
    Display::drawCenteredString(8, "AI-CHAT", CURRENT_THEME->primary[5], Display::alpha, &Font6x8, 4, -6);





    if (keyboardOpened) {
        keyboard.render();
        
        
    } 
    else {

        DrawUtils::drawLines(5, 60, TextUtils::stringFit(answer, 20), CURRENT_THEME->primary[8], Display::alpha, &Font6x8, 2);

    }
}
void AiChatApp::update() {
    if (keyboardOpened) {

    } else {

    }
    if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B))  {Navigation::pop(); }



}

void AiChatApp::onKeyboardCallback() {
    prompt = keyboard.string;
}