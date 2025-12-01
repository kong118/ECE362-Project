#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "ultrasound.h"
#include "lcd.h"
#include "TFT.h"
#include "project_motor.h"
#include "buzz_freq.h"

int main() {
    stdio_init_all();
    ultrasound_init();
    init_pwm(37, 999);
    init_buzz_frequency_pwm();
    LCD_Setup();
    draw_init();
    
    while (1) {
        // Rotate 10 degrees clockwise (includes 0.5s delay)
        float angle = rotate_10_degrees(37);
        
        // Measure distance
        float* distance = ultrasound_measure_distance();
        if (distance != NULL) {
            printf("Angle: %.1f deg, Distance: %.2f cm\n", angle, *distance);
            draw_location(angle, *distance);
            
            // Beep buzzer with frequency based on distance
            // Closer object = higher frequency
            set_buzz_frequency(*distance);
            sleep_ms(100);  // Short beep
            stop_buzz();
        } else {
            printf("Angle: %.1f deg, No object detected\n", angle);
            stop_buzz();  // No beep if no object
        }
        
        // Reset radar display after full sweep (when angle wraps to 0)
        if (angle == 0) {
            sleep_ms(1000);
            draw_init();
        }
    }
    
    return 0;
}
