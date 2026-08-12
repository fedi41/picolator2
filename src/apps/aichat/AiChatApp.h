#pragma once

#include <string>


#include "core/App.h"
#include "core/Display.h"
#include "elements/Keyboard.h"
#include "Mistral.h"



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

        bool thinking = false;
        
        bool keyboardOpened = false; 
        Keyboard keyboard = Keyboard([this](){this->onKeyboardCallback();}); 

};