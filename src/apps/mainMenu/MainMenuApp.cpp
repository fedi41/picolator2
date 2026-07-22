

#include "MainMenuApp.h"
#include "core/Logger.h"
#include "core/Navigation.h"
#include "core/AppId.h"
#include "core/Input.h"

void MainMenuApp::init() {
    Logger::d("Initializing MainApp");
    menuScreen.items = {"Picofetch", "Settings", "Pico-Dino", "AI chat", "..."};
    apps = {AppId::PICOFETCH, AppId::SETTINGS, AppId::DINO_RUNNER, AppId::AI_CHAT_APP, AppId::TEST};
    menuScreen.heading = "PICOLATOR";
    setDirty();
}
void MainMenuApp::update() {
    menuScreen.update();

    if (Input::justPressed(KEY_CTRL) || Input::justPressed(KEY_A) || Input::justPressed(KEY_RIGHT)) {
        Navigation::open(apps[menuScreen.pointer]);
    }

    if (menuScreen.isDirty()) {setDirty();}
}
void MainMenuApp::render() {
    menuScreen.render();
}

// void MainMenuApp::onClick() {
//     Navigation::open(apps[pointer]);    
// }