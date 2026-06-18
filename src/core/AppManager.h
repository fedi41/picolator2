#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "apps/App.h"

class AppManager {
private:
    static inline std::vector<App*> stack;

public:
    static void push(App* app) {
        if (!stack.empty() && stack.back() == app)
            return; // Bereits oben

        stack.push_back(app);
        app->init();
        //app->onOpen();
    }

    static void pop() {
        if (stack.size() <= 1)
            return; // Nicht die letzte App schließen

        //stack.back()->onClose();
        stack.pop_back();
    }

    static App* current() {
        return stack.empty() ? nullptr : stack.back();
    }
};