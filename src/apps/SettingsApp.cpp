
#include "SettingsApp.h"
#include "core/Input.h"
#include "core/Navigation.h"


void SettingsApp::init() {
    mainSettingsMenuScreen.items = {"Display", "Theme", "Debug"};
    mainSettingsMenuScreen.heading = "Settings";
    setDirty();
}
void SettingsApp::render() {
    switch (currentPage)
    {
    case SETTINGS_MAIN:
        mainSettingsMenuScreen.render();
        break;
    case SETTINGS_DISPLAY:
        Display::drawPlaceholder(0,0,240,240);
        break;  
    case SETTINGS_THEME:
        Display::drawPlaceholder(0,0,240,240);
        break;
    case SETTINGS_DEBUG:
        Display::drawPlaceholder(0,0,240,240);
        break;
    default:
        break;
    }

}
void SettingsApp::update() {
    
    switch (currentPage) {
        case SETTINGS_MAIN:
            mainSettingsMenuScreen.update();

            if (Input::isKeyPressed(KEY_A)) {
                switch (mainSettingsMenuScreen.pointer)
                {
                case 0:
                    currentPage = SETTINGS_DISPLAY;
                    break;
                case 1:
                    currentPage = SETTINGS_THEME;
                    break;
                case 2:
                    currentPage = SETTINGS_DEBUG;
                    break;
                
                default:
                    break;
                }
                setDirty();
            }
        
            if (mainSettingsMenuScreen.isDirty()) {setDirty();}
            break;
        case SETTINGS_DISPLAY:
            break;
        case SETTINGS_THEME:
            break;
        case SETTINGS_DEBUG:
            break;
        default:
            break;
    }

    if (Input::isKeyPressed(KEY_B)) {
        if (currentPage == SETTINGS_MAIN) {
            Navigation::pop();
        } else {
            currentPage = SETTINGS_MAIN;
            setDirty();
        }
    }
    
}



// void SettingsApp::onClick() {
    
// }