#pragma once

extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}


#define KEY_A 0
#define KEY_B 1
#define KEY_X 2
#define KEY_Y 3


#define KEY_DOWN 5
#define KEY_LEFT 6
#define KEY_RIGHT 7
#define KEY_UP 8
#define KEY_CTRL 9


class Input {
    public:
        static void init(  
                    short keyA = 15,
                    short keyB = 17,
                    short keyX = 19, 
                    short keyY = 21,

                    short up = 2,
	                short down = 18,
	                short left = 16,
	                short right = 20,
	                short ctrl = 3
                );
        static bool isKeyPressed(int button);
        static void update();

        static inline bool showDebug = false;

    private:
        static inline short keyA = 15;
        static inline short keyB = 17;
        static inline short keyX = 19; 
        static inline short keyY = 21;

        static inline short up = 2;
	    static inline short down = 18;
	    static inline short left = 16;
	    static inline short right = 20;
	    static inline short ctrl = 3;

        static inline bool keyAPressed = false;
        static inline bool keyBPressed = false;
        static inline bool keyXPressed = false;
        static inline bool keyYPressed = false;
        static inline bool keyCtrlPressed = false;
        static inline bool keyUpPressed = false;
        static inline bool keyLeftPressed = false;
        static inline bool keyRightPressed = false;
        static inline bool keyDownPressed = false;

        static void drawDebug();
};