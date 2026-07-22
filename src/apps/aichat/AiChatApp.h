#pragma once

#include "core/App.h"
#include "core/Display.h"
#include "elements/Keyboard.h"

class AiChatApp : public App {
    public:
        
        void render() override;
        void update() override;
        void init() override;

    private:
   
        Keyboard keyboard = Keyboard(); 
};