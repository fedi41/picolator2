#pragma once
#include "Colors.h"


struct Theme
{

    TailwindPalette surface;
    TailwindPalette primary;
    TailwindPalette secondary;
    
};


namespace THEMES {
    extern Theme classicTheme;
    extern Theme testTheme;
    extern Theme hackerTheme;
};
extern Theme* CURRENT_THEME;