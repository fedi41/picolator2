#pragma once

#include "Button.h"

enum Key {
    KEY_A,
    KEY_B,
    KEY_X,
    KEY_Y,

    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,

    KEY_CTRL,

    KEY_COUNT
};

class Input {
public:
    static void init(
        short keyA,
        short keyB,
        short keyX,
        short keyY,
        short up,
        short down,
        short left,
        short right,
        short ctrl
    );

    static void update();

    static bool pressed(Key key);
    static bool justPressed(Key key);
    static bool justReleased(Key key);
    static bool anyPressed();
    

private:
    static inline Button buttons[KEY_COUNT];
    static inline short pins[KEY_COUNT];
    static inline bool wasAnyPressed = false;
};