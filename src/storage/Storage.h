#pragma once
#include "SaveData.h"


class Storage {
public:
    static SaveData load();
    static void save();

    static inline SaveData data = load();
};


