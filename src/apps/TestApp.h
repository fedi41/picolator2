

#include "App.h"
#include "core/Display.h"

class TestApp : public App {
    public:
        void init() override;
        void render() override;
        void update() override;

    private:
        int counter = 0; // Example of a private member variable
};