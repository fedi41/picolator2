
extern "C" {
    #include "LCD_1in3.h"
}

#include <string>
#include <sstream>
#include "Display.h"
#include "gfx/Colors.h"
#include "fonts/fonts.h"
#include "core/Logger.h"
#include "pico/time.h"
#include "core/Input.h"

uint32_t millis() {
    return to_ms_since_boot(get_absolute_time());
}

static inline uint16_t swap565(uint16_t c) {
    return (c >> 8) | (c << 8);
}

uint16_t blend565(uint16_t A, uint16_t B)
{
    A = swap565(A);
    B = swap565(B);

    return swap565(((A & 0xF7DE) + (B & 0xF7DE)) >> 1);
}

void Display::wakeUp() {
    lastInteraction = millis();

    if (displaySleeping) {
        displaySleeping = false;
        DEV_SET_PWM(90);
    }
}

void Display::update() {
    
    if (Input::anyPressed()) {
        wakeUp();
    }

    if (!displaySleeping &&
        millis() - lastInteraction > TIMEOUT_MS) {

        displaySleeping = true;
        DEV_SET_PWM(0); 
    }
}

void Display::init(uint16_t a) {
    DEV_Module_Init();

    LCD_1IN3_Init(HORIZONTAL);
    LCD_1IN3_Clear(Colors::white);

    frameBuffer = new UWORD[bufferSize];
    frameBufferOverlay = new UWORD[bufferSize];

    clear(Colors::white);

    alpha = a;

    uint16_t c = blend565(Colors::red, Colors::blue);
    Logger::d(std::to_string(c));
    // alphaSwapped = (a >> 8) | (a << 8);
}
void Display::clear(uint16_t color) {
    if (overlayMode) {
        for (int i = 0; i < bufferSize; i++) {
            frameBufferOverlay[i] = color;
        }
    } else {
        for (int i = 0; i < bufferSize; i++) {
            frameBuffer[i] = color;
        }
    }

    dirty = true;
}

bool Display::render() {
    if (!dirty || displaySleeping) {
        return false;
    }

    //Logger::d("render!");

    if (renderOverlay) {
        UWORD* displayBuffer = new UWORD[bufferSize];
        for (int i = 0; i < bufferSize; i++) {
            if (frameBufferOverlay[i] == alpha) {
                displayBuffer[i] = frameBuffer[i];
            } else {
                switch (overlayBlendMode)
                {
                case NORMAL:
                    displayBuffer[i] = frameBufferOverlay[i];
                    break;
                case DIFFERENCE:
                    displayBuffer[i] = frameBufferOverlay[i]^frameBuffer[i];
                    break;
                case MIX:
                    displayBuffer[i] = blend565(frameBuffer[i], frameBufferOverlay[i]);
                    break;
                default:
                    break;
                }
            }
        }
        LCD_1IN3_Display(displayBuffer);
        delete[] displayBuffer;
    } else {
        LCD_1IN3_Display(frameBuffer);
    }
    dirty = false;

    return true;
}

int rotateIndex(int x, int y, int width, int height, int rotation)
{
    switch(rotation)
    {
        case 0:
            return y * width + x;

        case 90:
            return x * height + (height - 1 - y);

        case 180:
            return (height - 1 - y) * width + (width - 1 - x);

        case 270:
            return (width - 1 - x) * height + y;
    }

    return -1;
}

void Display::setPixel(
    int x,
    int y,
    uint16_t color
) {
    if (color == alpha) {return;}

    if (
        x < 0 || x >= width ||
        y < 0 || y >= height
    ) {
        return;
    }


    int id = rotateIndex(x,y,width,height,drawRotation);

    uint16_t c = color;
    switch (drawBlendMode)
    {
    case DIFFERENCE:
        c = color ^ (overlayMode ? frameBufferOverlay[id] : frameBuffer[id]);
        break;
    case MIX:
        c = blend565((overlayMode ? frameBufferOverlay[id] : frameBuffer[id]), color);
        break;
    default:
        break;
    }

    if (overlayMode) {
        frameBufferOverlay[id] = c;
    } else {
        frameBuffer[id] = c;
    }
    dirty = true;
}

//// SECOND LEVEL METHODS ////

void Display::drawChar(
    int x,
    int y,
    const char asciiChar,
    uint16_t fgColor,
    uint16_t bgColor,
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
    uint16_t fgColor,
    uint16_t bgColor,
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
        uint16_t color,
        uint16_t bgColor,
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

void Display::drawRect(int Xstart, int Ystart, int Xend, int Yend, uint16_t Color)
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


void Display::drawImage(const uint16_t *image, int xStart, int yStart, int W_Image, int H_Image)
{
    for (int y = yStart; y < H_Image; y++) {
        for (int x = xStart; x < W_Image; x++) {
            setPixel(x, y, image[y * W_Image + x]);
        }
    }
}

void Display::drawPlaceholder(int x, int y, int xx, int yy) {

    int w2 = (xx-x)/2;
    int h2 = (yy-y)/2;

    drawRect(x,y,x+w2,y+h2,Colors::magenta);
    drawRect(x+w2,y,xx,y+h2,Colors::black);
    drawRect(x,y+h2,x+w2,yy,Colors::black);
    drawRect(x+w2,y+h2,xx,yy,Colors::magenta);

}