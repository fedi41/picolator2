
extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include <string>
#include <sstream>
#include "Display.h"
#include "graphics/Color.h"


void Display::init(int alphaColor) {
    this->alphaColor = alphaColor;

    DEV_Delay_ms(100);
    printf("LCD_1in3_test Demo\r\n");
    DEV_Module_Init();
    DEV_SET_PWM(50);
    /* LCD Init */
    printf("1.3inch LCD demo...\r\n");
    LCD_1IN3_Init(HORIZONTAL);
    LCD_1IN3_Clear(WHITE);

    Display::bufferSize = width * height;

    Display::frameBuffer = new UWORD[Display::bufferSize];

    Paint_NewImage(
        (UBYTE*)Display::frameBuffer,
        width,
        height,
        0,
        WHITE
    );

    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
}
void Display::clear(int color) {
    Paint_Clear(color);
        Display::dirty = true;
}
void Display::render() {
    LCD_1IN3_Display(Display::frameBuffer);
    Display::dirty = false;
}
void Display::setPixel(int x, int y, int color) {
    Paint_SetPixel(x, y, color);
}




void Display::drawPoint(
    int x,
    int y,
    int color,
    DOT_PIXEL dotPixel,
    DOT_STYLE dotStyle)
{
    Paint_DrawPoint(x, y, color, dotPixel, dotStyle);
        Display::dirty = true;

}



void Display::drawLine(
    int xStart,
    int yStart,
    int xEnd,
    int yEnd,
    int color,
    LINE_STYLE lineStyle,
    DOT_PIXEL lineWidth)
{
    Paint_DrawLine(
        xStart, yStart,
        xEnd, yEnd,
        color,
        lineWidth,
        lineStyle
    );
        Display::dirty = true;
}




void Display::drawRectangle(
    int xStart,
    int yStart,
    int xEnd,
    int yEnd,
    int color,
    DRAW_FILL fill,
    DOT_PIXEL lineWidth)
{
    Paint_DrawRectangle(
        xStart, yStart,
        xEnd, yEnd,
        color,
        lineWidth,
        fill
    );
        Display::dirty = true;
}




void Display::drawCircle(
    int xCenter,
    int yCenter,
    int radius,
    int color,
    DRAW_FILL fill,
    DOT_PIXEL lineWidth)
{
    Paint_DrawCircle(
        xCenter,
        yCenter,
        radius,
        color,
        lineWidth,
        fill
    );
        Display::dirty = true;
}


void Display::drawString(
    int x,
    int y,
    const std::string& text,
    sFONT* font,
    int bgColor,
    int fgColor,
    bool center
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
        //Debug("Paint_DrawString_EN Input exceeds the normal display range\r\n");
        return;
    }

    const char* pString = text.c_str();
    
    while (*pString != '\0')
    {
        Paint_DrawChar(Xpoint, Ypoint, *pString, font, fgColor, bgColor, fgColor == alphaColor, bgColor == alphaColor);

        // The next character of the address
        pString++;

        // The next word of the abscissa increases the font of the broadband
        Xpoint += font->Width;
    }

        Display::dirty = true;
}




void Display::drawBitmap(const unsigned char* bitmap)
{
    Paint_DrawBitMap(bitmap);
        Display::dirty = true;
}

void Display::drawImage(const unsigned char *image, int xStart, int yStart, int W_Image, int H_Image)
{
    Paint_DrawImage(image, xStart, yStart, W_Image, H_Image);
        Display::dirty = true;
}