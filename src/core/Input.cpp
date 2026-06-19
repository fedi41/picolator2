
extern "C" {
    #include "Infrared.h"
}

#include "Input.h"
#include "core/Display.h"
#include "gfx/Colors.h"

void Input::init(  
                    short keyA,
                    short keyB,
                    short keyX, 
                    short keyY,

                    short up,
                    short down,
                    short left,
                    short right,
                    short ctrl
                ) {
    keyA = keyA;
    keyB = keyB;
    keyX = keyX;
    keyY = keyY;

    up = up;
    down = down;
    left = left;
    right = right;
    ctrl = ctrl;

    SET_Infrared_PIN(keyA);    
    SET_Infrared_PIN(keyB);
    SET_Infrared_PIN(keyX);
    SET_Infrared_PIN(keyY);
		 
	SET_Infrared_PIN(up);
    SET_Infrared_PIN(down);
    SET_Infrared_PIN(left);
    SET_Infrared_PIN(right);
    SET_Infrared_PIN(ctrl);
}

bool Input::isKeyPressed(int button) {
    switch (button) {
        case KEY_A:
            return keyAPressed;
        case KEY_B:
            return keyBPressed;
        case KEY_X:
            return keyXPressed;
        case KEY_Y:
            return keyYPressed;
        case KEY_UP:
            return keyUpPressed;
        case KEY_DOWN:
            return keyDownPressed;
        case KEY_LEFT:
            return keyLeftPressed;
        case KEY_RIGHT:
            return keyRightPressed;
        case KEY_CTRL:
            return keyCtrlPressed;
        default:
            return false; // Invalid button
    }
};

void Input::update() {


    keyAPressed = DEV_Digital_Read(keyA) == 0;
    keyBPressed = DEV_Digital_Read(keyB) == 0;
    keyXPressed = DEV_Digital_Read(keyX) == 0;
    keyYPressed = DEV_Digital_Read(keyY) == 0;

    keyCtrlPressed = DEV_Digital_Read(ctrl) == 0;
    keyUpPressed = DEV_Digital_Read(up) == 0;
    keyLeftPressed = DEV_Digital_Read(left) == 0;
    keyRightPressed = DEV_Digital_Read(right) == 0;
    keyDownPressed = DEV_Digital_Read(down) == 0;

    if (showDebug) {
        drawDebug();
    }

}

void Input::drawDebug() {

    Display::overlayMode = true;

        Display::clear(Display::alpha);

        if(keyAPressed){
            Display::drawRect(208, 15, 236, 45, Colors::black);
        }
        else{
     //       Display::drawPlaceholder(208, 15, 236, 45);
        }
            
        if(keyBPressed){
            Display::drawRect(208, 75, 236, 105, Colors::black);
        }
        else{
    //        Display::drawPlaceholder(208, 75, 236, 105);
        }
        
        if(keyXPressed){
            Display::drawRect(208, 135, 236, 165, Colors::black);
        }
        else{
            // Display::drawPlaceholder(208, 135, 236, 165);
        }
            
        if(keyYPressed){
            Display::drawRect(208, 195, 236, 225, Colors::black);
        }
        else{
            // Display::drawPlaceholder(208, 195, 236, 225);
        }


        if(keyUpPressed){
            Display::drawRect(60, 60, 90, 90, Colors::black);
        }
        else{
            // Display::drawPlaceholder(60, 60, 90, 90);
        }

        if(keyDownPressed){
            Display::drawRect(60, 150, 90, 180, Colors::black);
        }
        else{
            // Display::drawPlaceholder(60, 150, 90, 180);
        }
        
        if(keyLeftPressed){
            Display::drawRect(15, 105, 45, 135, Colors::black);
        }
        else{
      //      Display::drawPlaceholder(15, 105, 45, 135);
        }
            
        if(keyRightPressed){
            Display::drawRect(105, 105, 135, 135, Colors::black);
        }
        else{
            // Display::drawPlaceholder(105, 105, 135, 135);
        }
        
        if(keyCtrlPressed){
            Display::drawRect(60, 105, 90, 135, Colors::black);
        }
        else{
            // Display::drawPlaceholder(60, 105, 90, 135);
        }

    Display::overlayMode = false;
}