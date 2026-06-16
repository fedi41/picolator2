#pragma once

#include "core/Display.h"

class App {
public:
    virtual ~App() = default;

    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update() = 0;

    void renderIfDirty() {
        if (dirty) {
            render();
        }
        dirty = false;
    }
    void setDirty(bool isDirty) {
        dirty = isDirty;
    }

private:
    bool dirty = true;
};