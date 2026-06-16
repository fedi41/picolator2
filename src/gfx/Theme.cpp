


#include "gfx/Theme.h"
#include "gfx/Colors.h"


// THEMES
Theme classicTheme = {
    TailwindPalette::fromHSL({242, 0.43, 0.87}),
    TailwindPalette::fromHSL({198, 0.82, 0.23}),
    TailwindPalette::fromHSL({81, 0.37, 0.67}),
    
    BLACK,
    WHITE,
    BLACK
};

Theme CURRENT_THEME = classicTheme;