#pragma once

#include "core/Display.h"
#include "core/Logger.h"

class App {
public:
    virtual ~App() = default;

    virtual void render() = 0;
    virtual void update() = 0;

    virtual void init() = 0;

    bool renderIfDirty() {
        if (dirty) {
            render();
            dirty = false;
            return true;
        }
        return false;
    }
    void setDirty(bool isDirty = true) {
        dirty = isDirty;
    } 

private:
    bool dirty = true;
    bool initialized = false;
};