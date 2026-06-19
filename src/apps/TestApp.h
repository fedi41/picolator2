#pragma once



#include "App.h"
#include "core/Display.h"

class TestApp : public App {
    public:
        
        void render() override;
        void update() override;
        void init() override;

    private:


        int counter = 0; // Example of a private member variable
};