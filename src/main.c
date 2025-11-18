#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "ultrasound.h"
#include "TFT.h"
#include "lcd.h"
//#include "project_motor.h"

int main() {
    stdio_init_all();
    ultrasound_init();
    //init_pwm(37, 999);
    //init_buzz_frequency_pwm();
    LCD_Setup();
    draw_init();
    
    while (1) {
        //spin_5_degrees();
        sleep_ms(30);
        float* distance = ultrasound_measure_distance();
        if (distance != NULL) {
            printf("Distance: %.2f cm\n", *distance);
            draw_location(15, *distance);
            draw_location(345, *distance);
        } else {
            printf("No object detected\n");
        }
        sleep_ms(500);
    }
    
    return 0;
}
