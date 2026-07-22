#pragma once

#include <map>
#include <memory>
#include <vector>

#include "core/App.h"

#include "apps/mainMenu/MainMenuApp.h"
#include "apps/settingsApp/SettingsApp.h"
#include "apps/testApp/TestApp.h"
#include "apps/dinoRunner/DinoRunnerApp.h"
#include "apps/picofetch/Picofetch.h"


#include "core/AppId.h"




class Navigation {
private:
    static inline std::vector<AppId> stack;

    static inline MainMenuApp mainMenuApp;
    static inline SettingsApp settingsApp;
    static inline TestApp testApp;
    static inline DinoRunnerApp dinoRunnerApp;
    static inline Picofetch picofetch;

    static App* getApp(AppId id) {

        switch(id) {
            case AppId::MAIN_MENU:
                return &mainMenuApp;

            case AppId::SETTINGS:
                return &settingsApp;

            case AppId::TEST:
                return &testApp;

            case AppId::DINO_RUNNER: 
                return &dinoRunnerApp;

            case AppId::PICOFETCH:
                return &picofetch;
        }

    return nullptr;
}

public:
    static void open(AppId appId) {
        if (!stack.empty() && stack.back() == appId)
            return; // Bereits oben

        stack.push_back(appId);
        
        Logger::d("Added app to the stack");

        getApp(appId)->init();
        getApp(appId)->setDirty();
        //app->onOpen();
    }

    static void pop() {
        if (stack.size() <= 1)
            return; // Nicht die letzte App schließen

        stack.pop_back();
        getApp(stack.back())->setDirty();

    }

    static AppId currentAppId() {
        return stack.back();
    }
    static App* current() {
        return stack.empty() ? nullptr : getApp(stack.back());
    }
};