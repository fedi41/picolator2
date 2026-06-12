
extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include "graphics/UiDraw.h"
#include "core/Display.h" 

// void Draw::setPixel(int x, int y, int color) {
//     Paint_SetPixel(x, y, color);
// }




// void Display::drawPoint(
//     int x,
//     int y,
//     int color,
//     DOT_PIXEL dotPixel,
//     DOT_STYLE dotStyle)
// {
//     Paint_DrawPoint(x, y, color, dotPixel, dotStyle);
//         Display::dirty = true;

// }



// void Display::drawLine(
//     int xStart,
//     int yStart,
//     int xEnd,
//     int yEnd,
//     int color,
//     LINE_STYLE lineStyle,
//     DOT_PIXEL lineWidth)
// {
//     Paint_DrawLine(
//         xStart, yStart,
//         xEnd, yEnd,
//         color,
//         lineWidth,
//         lineStyle
//     );
//         Display::dirty = true;
// }




// void Display::drawRectangle(
//     int xStart,
//     int yStart,
//     int xEnd,
//     int yEnd,
//     int color,
//     DRAW_FILL fill,
//     DOT_PIXEL lineWidth)
// {
//     Paint_DrawRectangle(
//         xStart, yStart,
//         xEnd, yEnd,
//         color,
//         lineWidth,
//         fill
//     );
//         Display::dirty = true;
// }




// void Display::drawCircle(
//     int xCenter,
//     int yCenter,
//     int radius,
//     int color,
//     DRAW_FILL fill,
//     DOT_PIXEL lineWidth)
// {
//     Paint_DrawCircle(
//         xCenter,
//         yCenter,
//         radius,
//         color,
//         lineWidth,
//         fill
//     );
//         Display::dirty = true;
// }


void UiDraw::string(
    int x,
    int y,
    const std::string& text,
    int color,
    int bgColor,
    bool center, 
    bool bgTransparent,
    bool fgTransparent,
    sFONT* font
)
{

    int Xpoint = x;
    int Ypoint = y;

    if (center) {
        int textWidth = text.length() * font->Width;
        Xpoint = x - textWidth / 2; 
    }


    if (x > Paint.Width || y > Paint.Height)
    {
        return;
    }

    const char* pString = text.c_str();
    
    while (*pString != '\0')
    {
        Paint_DrawChar(Xpoint, Ypoint, *pString, font, color, bgColor, fgTransparent, bgTransparent);

        // The next character of the address
        pString++;

        Xpoint += font->Width;
    }

        Display::dirty = true;
}


void UiDraw::centeredString(
    int y,
    const std::string& text,
    int color,
    int bgColor,
    bool bgTransparent, 
    bool fgTransparent,
    sFONT* font 
)
{   
    UiDraw::string(
        Display::width/2,
        y,
        text,
        color,
        bgColor,
        true,
        fgTransparent,
        bgTransparent,
        font
    );
}


void UiDraw::heading(
    const std::string& text,
    int color,
    int bgColor,
    int borderColor,
    sFONT* font 
) {
    Paint_DrawRectangle(0,0, Display::width, 
        font->Height*2, 
        bgColor, 
        DOT_PIXEL::DOT_PIXEL_1X1, 
        DRAW_FILL::DRAW_FILL_FULL);

    
    UiDraw::centeredString(font->Height*0.5, text, color, BLACK, true, false, font);
    
}




// void Display::drawBitmap(const unsigned char* bitmap)
// {
//     Paint_DrawBitMap(bitmap);
//         Display::dirty = true;
// }

void UiDraw::image(const unsigned char *image, int xStart, int yStart, int W_Image, int H_Image)
{
    Paint_DrawImage(image, xStart, yStart, W_Image, H_Image);
}