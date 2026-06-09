
extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include "Display.h"


void Display::init() {
    DEV_Delay_ms(100);
    printf("LCD_1in3_test Demo\r\n");
    DEV_Module_Init();
    DEV_SET_PWM(50);
    /* LCD Init */
    printf("1.3inch LCD demo...\r\n");
    LCD_1IN3_Init(HORIZONTAL);
    LCD_1IN3_Clear(WHITE);



    Display::bufferSize = LCD_1IN3_HEIGHT * LCD_1IN3_WIDTH;

    Display::frameBuffer = new UWORD[Display::bufferSize];

    Paint_NewImage(
        (UBYTE*)Display::frameBuffer,
        LCD_1IN3_WIDTH,
        LCD_1IN3_HEIGHT,
        0,
        WHITE
    );

    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
}

void Display::clear(UWORD color) {
    Paint_Clear(color);
}



void Display::render() {
    LCD_1IN3_Display(Display::frameBuffer);
}



void Display::setPixel(UWORD x, UWORD y, UWORD color) {
    Paint_SetPixel(x, y, color);
}



void Display::drawPoint(
    UWORD x,
    UWORD y,
    UWORD color,
    DOT_PIXEL dotPixel,
    DOT_STYLE dotStyle)
{
    Paint_DrawPoint(x, y, color, dotPixel, dotStyle);
}

void Display::drawLine(
    UWORD xStart,
    UWORD yStart,
    UWORD xEnd,
    UWORD yEnd,
    UWORD color,
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
}

void Display::drawRectangle(
    UWORD xStart,
    UWORD yStart,
    UWORD xEnd,
    UWORD yEnd,
    UWORD color,
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
}

void Display::drawCircle(
    UWORD xCenter,
    UWORD yCenter,
    UWORD radius,
    UWORD color,
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
}

void Display::drawString(
    UWORD x,
    UWORD y,
    const char* text,
    sFONT* font,
    UWORD bgColor,
    UWORD fgColor)
{
    Paint_DrawString_EN(
        x,
        y,
        (char*)text,
        font,
        bgColor,
        fgColor
    );
}

void Display::drawNumber(
    UWORD x,
    UWORD y,
    int number,
    sFONT* font,
    UWORD bgColor,
    UWORD fgColor)
{
    Paint_DrawNum(
        x,
        y,
        number,
        font,
        number,
        bgColor,
        fgColor
    );
}

void Display::drawBitmap(const unsigned char* bitmap)
{
    Paint_DrawBitMap(bitmap);
}


void Display::drawImage(const unsigned char *image, UWORD xStart, UWORD yStart, UWORD W_Image, UWORD H_Image)
{
    Paint_DrawImage(image, xStart, yStart, W_Image, H_Image);
}