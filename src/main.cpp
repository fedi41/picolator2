//#include <stdio.h>
//#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"
extern "C" {
    #include "LCD_1in3.h"
    #include "LCD_Test.h" 
    #include "ImageData.h"
}

#include "core/Display.h"

int main(void)
{
    Display display;
    display.init();
    display.clear(BLACK);
    display.drawImage(gImage_1inch3_1, 0, 0, 240, 240); // Display the image on the screen
    // display.setPixel(10, 10, RED); // Set a pixel at (10, 10) to red
    display.render();

    // // Initialise the Wi-Fi chip
    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed\n");
    //     return -1;
    // }

    // // Example to turn on the Pico W LED
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    // bool led = true;

    // while (true) {
    //     printf("Hello, world!\n");
    //     led = !led;
    //     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led);
        
    //     sleep_ms(1000);
        
    // }
    return 0;
}