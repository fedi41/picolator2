#pragma once

#include "core/Display.h"

class App {
public:
    virtual ~App() = default;

    virtual void init() = 0;
    virtual void render(Display& display) = 0;
    virtual void update() = 0;

    void renderIfDirty(Display& display) {
        if (dirty) {
            render(display);
        }
        dirty = false;
    }
    void setDirty(bool isDirty) {
        dirty = isDirty;
    }

private:
    bool dirty = true;
};