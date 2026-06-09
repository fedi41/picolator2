//#include <stdio.h>
//#include "pico/stdlib.h"
//#include "pico/cyw43_arch.h"
//#include "LCD_1in3.h"
#include "LCD_Test.h" 

int main(void)
{
    LCD_1in3_test();

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