#include "Input.h"
#include "hardware/gpio.h"

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
    pins[KEY_A] = keyA;
    pins[KEY_B] = keyB;
    pins[KEY_X] = keyX;
    pins[KEY_Y] = keyY;

    pins[KEY_UP] = up;
    pins[KEY_DOWN] = down;
    pins[KEY_LEFT] = left;
    pins[KEY_RIGHT] = right;

    pins[KEY_CTRL] = ctrl;

    for (int i = 0; i < KEY_COUNT; i++) {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], GPIO_IN);
        gpio_pull_up(pins[i]);
    }
}

void Input::update() {
    for (int i = 0; i < KEY_COUNT; i++) {
        buttons[i].update(gpio_get(pins[i]) == 0);
    }
}

bool Input::pressed(Key key) {
    return buttons[key].pressed();
}

bool Input::justPressed(Key key) {
    return buttons[key].justPressed();
}

bool Input::justReleased(Key key) {
    return buttons[key].justReleased();
}