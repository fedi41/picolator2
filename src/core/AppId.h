#pragma once

enum AppId {
    MAIN_MENU,
    SETTINGS,
    TEST,
    DINO_RUNNER,
    PICOFETCH,
    AI_CHAT_APP
};

inline std::string appName(AppId id) { 
        switch(id) {
            case AppId::MAIN_MENU:
                return "main menu";

            case AppId::SETTINGS:
                return "settings";

            case AppId::TEST:
                return "test app";

            case AppId::DINO_RUNNER: 
                return "dino runner";

            case AppId::PICOFETCH:
                return "picofetch";
            
            case AppId::AI_CHAT_APP:
                return "AI chat";
        }

 
}
