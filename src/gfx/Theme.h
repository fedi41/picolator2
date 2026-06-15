#pragma once

struct Theme
{
    int surface;
    int onSurface;
    
    int primary;
    int onPrimary;
    int primaryContainer;

    int secondary;
    int onSecondary;
    int secondaryContainer;
};


extern Theme classicTheme;
extern Theme CURRENT_THEME;