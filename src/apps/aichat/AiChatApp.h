#pragma once

#include <string>


#include "core/App.h"
#include "core/Display.h"
#include "elements/Keyboard.h"
#include "Mistral.h"

enum AIchatStatus {
  THINKING, WRONG_API_KEY, NO_INTERNET, SUCCESS, CHECKING_CONNECTION
};

class AiChatApp : public App {
    public:
        
        void render() override;
        void update() override;
        void init() override;
        void onKeyboardCallback();
        void onAiCallback(std::string answer);

    private:

        std::string prompt = "";
        std::string answer = "";

        AIchatStatus status = CHECKING_CONNECTION;
        
        bool keyboardOpened = false; 
        Keyboard keyboard = Keyboard([this](){this->onKeyboardCallback();}); 

};
