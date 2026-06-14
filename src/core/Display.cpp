
extern "C" {
    #include "LCD_1in3.h"
}

#include <string>
#include <sstream>
#include "Display.h"
#include "graphics/Colors.h"
#include "fonts/fonts.h"

void Display::init(Color alpha) {
    DEV_Module_Init();

    DEV_SET_PWM(50);

    LCD_1IN3_Init(HORIZONTAL);
    LCD_1IN3_Clear(WHITE);

    frameBuffer = new UWORD[bufferSize];

    clear(WHITE);

    this->alpha = alpha;
}
void Display::clear(uint16_t color) {
    for (int i = 0; i < bufferSize; i++) {
        frameBuffer[i] = color;
    }

    dirty = true;
}
void Display::render() {
    if (!dirty) {
        return;
    }

    LCD_1IN3_Display(frameBuffer);

    dirty = false;
}

void Display::setPixel(
    int x,
    int y,
    Color color
) {
    if (color == alpha) {return;}

    if (
        x < 0 || x >= width ||
        y < 0 || y >= height
    ) {
        return;
    }

    frameBuffer[y * width + x] =
    (color >> 8) |
    (color << 8);

    dirty = true;
}

void Display::drawChar(
    int x,
    int y,
    const char asciiChar,
    Color fgColor,
    Color bgColor,
    FONT* font,
    int scale
) {
    if (x >= width || y >= height) {
        return;
    }

    const char* glyph =
        font->table + asciiChar * font->Height;

    for (int row = 0; row < font->Height; row++) {
        uint8_t bits = glyph[row];

        for (int col = 0; col < font->Width; col++) {
            bool pixelSet = bits & (0x80 >> col);
            
            const int scaledCol = (font->Width - col)*scale;
            const int scaledRow = row*scale;

            if (pixelSet) {
                for (int ox = 0; ox < scale; ox++){
                    for (int oy = 0; oy < scale; oy++){
                        setPixel(
                            x + scaledCol + ox,
                            y + scaledRow + oy,
                            fgColor
                        );
                    }
                }
            } else {
                for (int ox = 0; ox < scale; ox++){
                    for (int oy = 0; oy < scale; oy++){
                        setPixel(
                            x + scaledCol + ox,
                            y + scaledRow + oy,
                            bgColor
                        );
                    }
                }
            }
        }
    }
}

void Display::drawString(
    int x,
    int y,
    const std::string& text,
    Color fgColor,
    Color bgColor,
    bool center,
    FONT* font,
    int scale
)
{

    int Xpoint = x;
    int Ypoint = y;

    if (center) {
        int textWidth = text.length() * font->Width * scale;
        Xpoint = x - textWidth / 2; 
    }


    if (x > width || y > height)
    {
        return;
    }

    const char* pString = text.c_str();
    
    while (*pString != '\0')
    {
        drawChar(Xpoint, Ypoint, *pString, fgColor, bgColor, font, scale);

        // The next character of the address
        pString++;

        Xpoint += font->Width * scale;
    }

        Display::dirty = true;
}
void Display::drawCenteredString(
        int y,
        const std::string& text,
        int color,
        int bgColor,
        FONT* font,
        int scale,
        int offset
    ) 
{
    drawString(
        width / 2 + offset,
        y,
        text,
        color, 
        bgColor,
        true,
        font,
        scale
    );
}

void Display::drawWindow(int Xstart, int Ystart, int Xend, int Yend, Color Color)
{
    int X, Y;
    for (Y = Ystart; Y < Yend; Y++)
    {
        for (X = Xstart; X < Xend; X++)
        { // 8 pixel =  1 byte
            setPixel(X, Y, Color);
        }
    }
}


void Display::drawImage(const unsigned char *image, int xStart, int yStart, int W_Image, int H_Image)
{
    int i, j;
    for (j = 0; j < H_Image; j++)
    {
        for (i = 0; i < W_Image; i++)
        {
            if (xStart + i < width && yStart + j < height) // Exceeded part does not display
                setPixel(xStart + i, yStart + j, (*(image + j * W_Image * 2 + i * 2 + 1)) << 8 | (*(image + j * W_Image * 2 + i * 2)));
            // Using arrays is a property of sequential storage, accessing the original array by algorithm
            // j*W_Image*2 			   Y offset
            // i*2              	   X offset
        }
    }
}

