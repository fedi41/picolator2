#pragma once

class Button {
public:
    bool current = false;
    bool previous = false;

    void update(bool state) {
        previous = current;
        current = state;
    }

    bool pressed() const {
        return current;
    }

    bool justPressed() const {
        return current && !previous;
    }

    bool justReleased() const {
        return !current && previous;
    }
};