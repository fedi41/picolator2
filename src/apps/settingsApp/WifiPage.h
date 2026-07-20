
#include "elements/Element.h"
#include "elements/Keyboard.h"
#include "core/Wifi.h"

class WifiPage : public Element {
public:

    void update() override {

    
        if (keboardActive) {
            keyboard.update();
            if (keyboard.isDirty()) setDirty();
            if (Input::justPressed(KEY_B)) {
                keboardActive = false;
                setDirty();
            }
        }
        else {
            if (Input::justPressed(KEY_A)) {
                keboardActive = true;
                setDirty();
            }
            if (Input::justPressed(KEY_X)) {
                
                strncpy(Storage::data.wifiSSID, ssid.c_str(), sizeof(Storage::data.wifiSSID) - 1);
                Storage::data.wifiSSID[sizeof(Storage::data.wifiSSID) - 1] = '\0'; // sicherstellen, dass Nullterminator gesetzt ist

                strncpy(Storage::data.wifiPASS, password.c_str(), sizeof(Storage::data.wifiPASS) - 1);
                Storage::data.wifiPASS[sizeof(Storage::data.wifiPASS) - 1] = '\0';

                Storage::save();
                
                Wifi::connect();
                setDirty();
            }


            if (Input::justPressed(KEY_UP) || Input::justPressed(KEY_DOWN)) {
                pointer = pointer == 0 ? 1 : 0;

                keyboard.string = (pointer == 0 ? ssid : password);
                
                setDirty();
            }
        }
    };

    void keyboardCallback() {
        switch (pointer) {
            case 0:
                ssid = keyboard.string;
                break;
            case 1:
                password = keyboard.string;
                break;
            default:
                break;
        }
        setDirty();
    };


    void render() override {

        setDirty(false);

        Display::clear(CURRENT_THEME->surface[2]);

        Display::drawString(0, 5, "SSID: " + ssid, (pointer == 0 ? Display::alpha : 0x0000), (pointer == 1 ? Display::alpha : 0x0000), false, &Font6x8, 1);
        Display::drawString(0, 20, "PASS: " + password, (pointer == 1 ? Display::alpha : 0x0000), (pointer == 0 ? Display::alpha : 0x0000), false, &Font6x8, 1);

        if (keboardActive) {
            
            Display::drawString(0, 90, "Press B to exit edit", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);

            keyboard.render();
        } else {

            Display::drawString(0, 50, "Press A to edit", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);
            Display::drawString(0, 60, "Press X to save", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);
            Display::drawString(0, 70, "Press B to discard", CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 1);

            if (Wifi::wifiConnected) {
                Display::drawString(0, 80, "!! WIFI CONNECTED !!",  CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 2);
            } else {
                Display::drawString(0, 80, "!!connection error!!",  CURRENT_THEME->surface[8], Display::alpha, false, &Font6x8, 2);
            }
        }
    };



    int pointer = 0;

    std::string ssid = "";
    std::string password = "";
    bool keboardActive = false;
    Keyboard keyboard =  Keyboard([this](){keyboardCallback();});
};
