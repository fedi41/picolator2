


#include "gfx/Theme.h"
#include "gfx/Colors.h"


// THEMES
Theme classicTheme = {
    TailwindPalette::fromHSL({242, 0.43, 0.87}),
    TailwindPalette::fromHSL({198, 0.82, 0.23}),
    TailwindPalette::fromHSL({81, 0.37, 0.67}),
};
Theme testTheme = {
    TailwindPalette::fromHSL({31, 0.33, 0.88}),
    TailwindPalette::fromHSL({286, 0.58, 0.16}),
    TailwindPalette::fromHSL({354, 0.65, 0.59}),
};
Theme hackerTheme {
    TailwindPalette::fromHSL({0, 0, 0}),
    TailwindPalette::fromHSL({119, 0.68, 0.43}),
    TailwindPalette::fromHSL({133, 1, 0.50}),
};

Theme CURRENT_THEME = classicTheme;