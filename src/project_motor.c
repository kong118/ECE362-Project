#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define STEP_DEG 10

static float current_angle = 0;

void init_pwm(int pin, int period){
    gpio_set_func(pin, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(pin);
    pwm_set_clkdiv(slice, 3000);
    pwm_set_wrap(slice, period+1);
    pwm_set_gpio_level(pin, 0);
}

/**
 * @brief Rotate motor 10 degrees clockwise and wait 0.5s
 * @param pin: PWM pin for servo control
 * @return Current angle in degrees (0-180)
 */
float rotate_10_degrees(int pin){
    current_angle += STEP_DEG;
    
    // Reset to 0 after reaching 180
    if(current_angle > 180){
        current_angle = 0;
    }
    
    // Calculate pulse length for servo (1ms to 2ms pulse width)
    float pulse_length = 50 + (current_angle/180.0)*(50);
    pwm_set_gpio_level(pin, pulse_length);
    
    // Wait 0.5 seconds
    sleep_ms(500);
    
    return current_angle;
}

/**
 * @brief Get current motor angle without moving
 * @return Current angle in degrees (0-180)
 */
float get_current_angle(void){
    return current_angle;
}
