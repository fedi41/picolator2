#include "storage/Storage.h"
#include "AiChatApp.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "core/Navigation.h"
#include "util/TextUtils.h"

#include "Mistral.h"

void AiChatApp::init() {

    

}

void AiChatApp::render() {

    printf("ai chat app render\n");

    // BG
    Display::clear(CURRENT_THEME->surface[2]);

    // HEADING
    Display::drawRect(0,0,240,60, CURRENT_THEME->primary[8]);

    Display::drawCenteredString(21, "AI-CHAT", CURRENT_THEME->primary[2], Display::alpha, &Font6x8, 4, -3);
    Display::drawCenteredString(18, "AI-CHAT", CURRENT_THEME->primary[5], Display::alpha, &Font6x8, 4, -6);

    

    // primary - ai bot
    // secondary - user

    if (thinking) {

        Display::drawCenteredString(58, "---THINKING---", CURRENT_THEME->primary[9], Display::alpha, &Font6x8, 2);

    } else if (keyboardOpened) {
        keyboard.render();

        printf("rendering promt ig...\n");
        printf(prompt.data());
        printf("\n");
        DrawUtils::drawLines(5, 70, TextUtils::stringFit(prompt, 19), CURRENT_THEME->secondary[8], Display::alpha, &Font6x8, 2);
    } 
    else {
        if (result.success()) {
          if (result.content.empty()) {
            Display::drawCenteredString(68, "Answer is empty", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
            //DrawUtils::drawLines(5, 75, TextUtils::stringFit(prompt, 19), CURRENT_THEME->primary[8], Display::alpha, &Font6x8, 2); 
          } else {
            Display::drawCenteredString(68, "Response:", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
            DrawUtils::drawLines(5, 85, TextUtils::stringFit(answer, 19), CURRENT_THEME->primary[8], Display::alpha, &Font6x8, 2); 
          }
        } else if (result.error == MistralError::INVALID_API_KEY) {
          Display::drawCenteredString(68, "Invalid API-KEY", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
        } else if (result.error == MistralError::CONNECTION_ERROR) {
          Display::drawCenteredString(68, "connection error", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
        } else if (result.error == MistralError::UNKNOWN_ERROR) {
          Display::drawCenteredString(68, "UNKNOWN ERROR", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
          DrawUtils::drawLines(5, 85, TextUtils::stringFit("probably because I suck at cpp", 19), CURRENT_THEME->primary[8], Display::alpha, &Font6x8, 1); 
        } else {
          Display::drawCenteredString(68, "unhandled error", CURRENT_THEME->primary[10], Display::alpha, &Font6x8, 2);
          DrawUtils::drawLines(5, 85, TextUtils::stringFit("because I am to lazy to write handlers for all errors :3", 19), CURRENT_THEME->primary[8], Display::alpha, &Font6x8, 2); 
        }
    }
}
void AiChatApp::update() {
    if (keyboardOpened) {
        if (Input::justPressed(KEY_X)) {
            keyboardOpened = false;
            setDirty();
        }

        keyboard.update();
        if (keyboard.isDirty()) setDirty(); 
    } else {
        if (Input::justPressed(KEY_A)) {
            keyboardOpened = true;
            setDirty();
        }
        if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B))  {Navigation::pop(); }
    }

    if (Input::justPressed(KEY_Y)) {
        keyboardOpened = false;

        thinking = true;
        std::string apiKey = Storage::data.mistralApiKey; 

        send_promt(prompt, apiKey,[this](MistralResult result) {
            onAiCallback(result);
        });

        setDirty();
    }
}

void AiChatApp::onAiCallback(
        MistralResult result
    ) {
    thinking = false; 

    result = result;
    printf(result.content.data());
    setDirty();
    
}

void AiChatApp::onKeyboardCallback() {
    prompt = keyboard.string;
    setDirty();
    // log stuff
    printf("ai chat prompt: ");
    printf(prompt.data());
    printf("\n");
}
