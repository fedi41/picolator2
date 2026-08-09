#pragma once

#include "core/App.h"
#include "core/Display.h"
#include "elements/Keyboard.h"
#include <string>


class AiChatApp : public App {
    public:
        
        void render() override;
        void update() override;
        void init() override;
        void onKeyboardCallback();

    private:

        std::string prompt = "";
        std::string answer = "gsgkfhkgjhfghkjdfhguhdfgjkndfiughdfjklgdfiughdfjkgniuhfughjkghuhjgiudfhgkhfgher";
        
        bool keyboardOpened = false; 
        Keyboard keyboard = Keyboard([this](){this->onKeyboardCallback();}); 

};