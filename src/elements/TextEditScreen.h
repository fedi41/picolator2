#include "elements/Element.h"
#include "elements/Keyboard.h"

class AiChatPage : public Element {
public:
    void update() override {
        if (keboardActive) {
            keyboard.update();
            if (keyboard.isDirty()) setDirty();
            if (Input::justPressed(KEY_X)) {
                keboardActive = false;
                setDirty();
            }
            if (Input::justPressed(KEY_Y)) {
                keboardActive = false;
                
                onSave();
               
                setDirty();
            }
        }
        else {
            if (Input::justPressed(KEY_A)) {
                keboardActive = true;
                setDirty();
            }
            if (Input::justPressed(KEY_B)) {
                onExit();
                setDirty();
            }
        }
    };

    void keyboardCallback() {
        string = keyboard.string;
        setDirty();
    };

    void render() override {

        setDirty(false);

        Display::clear(CURRENT_THEME->surface[2]);

        Display::drawString(0, 5, "-->" + string, Display::alpha, CURRENT_THEME->surface[9], false, &Font6x8, 1);

        if (keboardActive) {
            
            Display::drawString(0, 90, "Press Y to save", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);
            Display::drawString(0, 70, "Press X to discard", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);

            keyboard.render();
        } else {

            Display::drawString(0, 50, "Press A to edit", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);
            Display::drawString(0, 60, "Press B to exit", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);

       }
    };
     
    std::string string = "";
    std::function<void()> onSave;
    std::function<void()> onExit;
    bool keboardActive = false;
    Keyboard keyboard =  Keyboard([this](){keyboardCallback();});
};







