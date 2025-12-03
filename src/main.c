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
    servo_pwm_init(27, 999);
    init_buzzer();
    LCD_Setup();
    draw_init();
    
    float angle = 0;
    const float sweep_time_ms = 2000;
    const float max_angle = 180;
    const int samples = 18;
    const float angle_step = max_angle / samples;
    const float time_per_step = sweep_time_ms / samples;
    
    while (1) {
        servo_rotate_cw(27);
        
        for(int i = 0; i <= samples; i++){
            angle = i * angle_step;
            
            float* distance = ultrasound_measure_distance();
            if (distance != NULL) {
                draw_location(angle, *distance);
                set_buzzer_frequency(*distance);
            } else {
                stop_buzzer();
            }
            
            sleep_ms(time_per_step);
        }
        
        servo_stop(27);
        sleep_ms(300);
        
        servo_rotate_ccw(27);
        
        for(int i = samples; i >= 0; i--){
            angle = i * angle_step;
            
            float* distance = ultrasound_measure_distance();
            if (distance != NULL) {
                draw_location(angle, *distance);
                set_buzzer_frequency(*distance);
            } else {
                stop_buzzer();
            }
            
            sleep_ms(time_per_step);
        }
        
        servo_stop(27);
        sleep_ms(300);
        
        draw_init();
    }
    
    return 0;
}
