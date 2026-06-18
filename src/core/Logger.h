#pragma once


#include <list>
#include <string>

#include "core/Display.h"
// #include <s>

class Logger {
public:
    static inline std::list<std::string> log = {};

    static void render();
    static void clear() {
        log = {};
    }
    static void d(std::string message) {
        log.push_back(message);
        if (displayAfterPush) {
            render();
            Display::render();
        }
    }
    static inline bool displayAfterPush = false;


};