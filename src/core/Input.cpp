
extern "C" {
    #include "Infrared.h"
}

#include "Input.h"

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
            return DEV_Digital_Read(keyA) == 0;
        case KEY_B:
            return DEV_Digital_Read(keyB) == 0;
        case KEY_X:
            return DEV_Digital_Read(keyX) == 0;
        case KEY_Y:
            return DEV_Digital_Read(keyY) == 0;
        case KEY_UP:
            return DEV_Digital_Read(up) == 0;
        case KEY_DOWN:
            return DEV_Digital_Read(down) == 0;
        case KEY_LEFT:
            return DEV_Digital_Read(left) == 0;
        case KEY_RIGHT:
            return DEV_Digital_Read(right) == 0;
        case KEY_CTRL:
            return DEV_Digital_Read(ctrl) == 0;
        default:
            return false; // Invalid button
    }
};