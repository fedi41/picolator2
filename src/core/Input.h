#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}


#define KEY_A 0
#define KEY_B 1
#define KEY_X 2
#define KEY_Y 3

#define KEY_UP 4
#define KEY_DOWN 5
#define KEY_LEFT 6
#define KEY_RIGHT 7
#define KEY_CTRL 8


class Input {
    public:
        void init(  
                    short keyA = 15,
                    short keyB = 17,
                    short keyX = 19, 
                    short keyY = 21,

                    short up = 2,
	                short dowm = 18,
	                short left = 16,
	                short right = 20,
	                short ctrl = 3
                );
        bool isButtonPressed(int button);

    private:
        short keyA;
        short keyB;
        short keyX; 
        short keyY;

        short up;
        short dowm;
        short left;
        short right;
        short ctrl;
};