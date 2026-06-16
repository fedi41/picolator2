


#include "gfx/Theme.h"
#include "gfx/Colors.h"


// THEMES
Theme classicTheme = {
    TailwindColor::fromHSL({242, 0.43, 0.87}),
    TailwindColor::fromHSL({198, 0.82, 0.23}),
    TailwindColor::fromHSL({81, 0.37, 0.67}),
    
    BLACK,
    WHITE,
    BLACK
};

Theme CURRENT_THEME = classicTheme;