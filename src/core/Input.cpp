
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
                    short dowm,
                    short left,
                    short right,
                    short ctrl
                ) {
    this->keyA = keyA;
    this->keyB = keyB;
    this->keyX = keyX;
    this->keyY = keyY;

    this->up = up;
    this->dowm = dowm;
    this->left = left;
    this->right = right;
    this->ctrl = ctrl;

    SET_Infrared_PIN(keyA);    
    SET_Infrared_PIN(keyB);
    SET_Infrared_PIN(keyX);
    SET_Infrared_PIN(keyY);
		 
	SET_Infrared_PIN(up);
    SET_Infrared_PIN(dowm);
    SET_Infrared_PIN(left);
    SET_Infrared_PIN(right);
    SET_Infrared_PIN(ctrl);
}

bool Input::isButtonPressed(int button) {
    switch (button) {
        case KEY_A:
            return DEV_Digital_Read(this->keyA) == 0;
        case KEY_B:
            return DEV_Digital_Read(this->keyB) == 0;
        case KEY_X:
            return DEV_Digital_Read(this->keyX) == 0;
        case KEY_Y:
            return DEV_Digital_Read(this->keyY) == 0;
        case KEY_UP:
            return DEV_Digital_Read(this->up) == 0;
        case KEY_DOWN:
            return DEV_Digital_Read(this->dowm) == 0;
        case KEY_LEFT:
            return DEV_Digital_Read(this->left) == 0;
        case KEY_RIGHT:
            return DEV_Digital_Read(this->right) == 0;
        case KEY_CTRL:
            return DEV_Digital_Read(this->ctrl) == 0;
        default:
            return false; // Invalid button
    }
}