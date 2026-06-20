#pragma once

class Feature {
public:
    virtual void update() {}
    virtual void render() {}
    virtual const char* getName() = 0;

    bool enabled = false;
};