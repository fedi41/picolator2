

#include "MainMenuApp.h"
#include "core/Logger.h"
#include "core/Navigation.h"
#include "core/AppId.h"
#include "core/Input.h"

void MainMenuApp::init() {
    Logger::d("Initializing MainApp");
    menuScreen.items = {"Settings", "Test", "Pico-Dino", "wooooow", "heheh", "bruh", "idk"};
    apps = {AppId::SETTINGS, AppId::TEST, AppId::DINO_RUNNER, AppId::TEST, AppId::TEST, AppId::TEST, AppId::TEST};
    menuScreen.heading = "PICOLATOR";
    setDirty();
}
void MainMenuApp::update() {
    menuScreen.update();

    if (Input::justPressed(KEY_RIGHT)) {
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