#pragma once


#include <vector>
#include <string>
#include <functional>

#include "core/Display.h"
// #include <s>

class Logger {
public:
    static inline std::vector<std::string> log = {};

    static void render();
    static void clear() {
        log = {};
    }
    static void d(std::string message) {
        log.push_back(message);

        onLog ? onLog() : void();
        // if (displayAfterPush) {
        //     render();
        //     Display::render();
        // }
        dirty = true;
    }
    // static inline bool displayAfterPush = false;

    static inline bool dirty = false;
    static inline std::function<void()> onLog = nullptr;
};