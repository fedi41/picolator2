
extern "C" {
    #include "LCD_1in3.h"
    #include "GUI_Paint.h"
}

#include <string>
#include <sstream>
#include "Display.h"

bool Display::dirty = false;
void Display::init() {
    Display::dirty = false;
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
};
