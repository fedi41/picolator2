#pragma once

#include "App.h"
#include "screens/Menu.h"

enum SettingsPage {
    SETTINGS_MAIN, SETTINGS_DISPLAY, SETTINGS_THEME, SETTINGS_DEBUG
};


class SettingsApp : public App {

    void init() override;
    void update() override;
    void render() override;

    private:
        Menu mainSettingsMenuScreen = Menu();
        SettingsPage currentPage = SettingsPage::SETTINGS_MAIN;
};