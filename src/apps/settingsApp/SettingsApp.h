#pragma once

#include "core/App.h"
#include "screens/Menu.h"
#include "screens/ThemePreview.h"

enum SettingsPage {
    SETTINGS_MAIN, SETTINGS_DISPLAY, SETTINGS_THEME, SETTINGS_DEBUG
};


class SettingsApp : public App {

    void init() override;
    void update() override;
    void render() override;

    private:
        ThemePreview themePreviewScreen = ThemePreview();
        Menu mainSettingsMenuScreen = Menu();

        int themePreviewIndex = 0;
        
        SettingsPage currentPage = SettingsPage::SETTINGS_MAIN;

};