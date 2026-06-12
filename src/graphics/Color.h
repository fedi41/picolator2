#pragma once

class Color {
    public: 
        bool transparent;
        int color;
        Color(int color, bool transparent = false) : color(color), transparent(transparent) {}
};