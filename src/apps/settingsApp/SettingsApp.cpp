
#include "SettingsApp.h"
#include "core/Input.h"
#include "core/Navigation.h"
#include "gfx/Theme.h"
#include "gfx/DrawUtils.h"
#include "features/FeatureManager.h"

Theme* themes[3] = {&THEMES::classicTheme, &THEMES::testTheme, &THEMES::hackerTheme};

void SettingsApp::init() {
    mainSettingsMenuScreen.items = {"Display", "Theme", "Features", "Wifi"};
    mainSettingsMenuScreen.heading = "Settings";

    featureMenu.heading = "Features";
    featureMenu.items = {};
    featureMenu.states = {};

    wifiPage.ssid = Storage::data.wifiSSID;
    wifiPage.password = Storage::data.wifiPASS;
    
    for (Feature* feature : FeatureManager::features) {
        featureMenu.items.push_back(feature->getName());
        featureMenu.states.push_back(false);
    }
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
        themePreviewScreen.render();
        break;
    case SETTINGS_FEATURES:
        featureMenu.render();
        break;
    case SETTINGS_WIFI:
        wifiPage.render();
        break;
    default:
        break;
    }

}
void SettingsApp::update() {

    if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B)) {
        if (currentPage == SETTINGS_WIFI & wifiPage.keboardActive) {}
        else if (currentPage == SETTINGS_MAIN) {
            Navigation::pop();
        }
        else {
            currentPage = SETTINGS_MAIN;
            setDirty();
        }
    }
    
    switch (currentPage) {
        case SETTINGS_MAIN:
            mainSettingsMenuScreen.update();

            if (Input::justPressed(KEY_CTRL) || Input::justPressed(KEY_A) || Input::justPressed(KEY_RIGHT)) {
                switch (mainSettingsMenuScreen.pointer)
                {
                case 0:
                    currentPage = SETTINGS_DISPLAY;
                    break;
                case 1:
                    currentPage = SETTINGS_THEME;
                    break;
                case 2:
                    currentPage = SETTINGS_FEATURES;
                    break;
                case 3:
                    currentPage = SETTINGS_WIFI;
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
            if (Input::justPressed(KEY_CTRL)) {
                themePreviewIndex ++;
                if (themePreviewIndex >= 3) {
                    themePreviewIndex = 0;
                }
                CURRENT_THEME = themes[themePreviewIndex];
                setDirty();
            }
            break;
        case SETTINGS_FEATURES:
            featureMenu.update();

            for (Feature* feature : FeatureManager::features) {
                feature->enabled = featureMenu.states[FeatureManager::featureIds[feature->getName()]];
            }
            if (featureMenu.isDirty()) {setDirty();}
            break;
        case SETTINGS_WIFI:
            wifiPage.update();
            if (wifiPage.isDirty()) {setDirty();}
            break;
        default:
            break;
    }


    
}



// void SettingsApp::onClick() {
    
// }