#pragma once

#include "pico/time.h"

class Button {
public:
    bool current = false;
    bool previous = false;

private:
    uint32_t releaseStart = 0;
    bool releasePending = false;

public:
    void update(bool state) {
        previous = current;

        if (state) {
            // Press immediately
            current = true;
            releasePending = false;
        }
        else {
            // Start release timer
            if (current && !releasePending) {
                releasePending = true;
                releaseStart = time_us_32();
            }

            // Release only after 5 ms
            if (releasePending &&
                time_us_32() - releaseStart >= 5000) {
                current = false;
                releasePending = false;
            }
        }
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