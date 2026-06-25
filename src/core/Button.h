#pragma once

class Button {
public:
    bool current = false;
    bool previous = false;

private:
    int releaseCounter = 0;

public:
    void update(bool state) {
        previous = current;

        // Press immediately
        if (state) {
            current = true;
            releaseCounter = 0;
        }
        // Debounce release
        else {
            if (current) {
                releaseCounter++;

                if (releaseCounter >= 2) { // adjust as needed
                    current = false;
                    releaseCounter = 0;
                }
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