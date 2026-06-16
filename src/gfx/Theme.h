#pragma once
#include "Colors.h"


struct Theme
{

    TailwindColor surface;
    TailwindColor primary;
    TailwindColor secondary;

    uint16_t onSurface;
    uint16_t onPrimary;
    uint16_t onSecondary;
};


extern Theme classicTheme;
extern Theme CURRENT_THEME;