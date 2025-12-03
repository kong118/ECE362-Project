#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define SERVO_CW_LEVEL 300
#define SERVO_CCW_LEVEL 810
#define SERVO_STOP_LEVEL 500
#define ROTATION_TIME_MS 2000

void servo_pwm_init(int pin, int period){
    gpio_set_function(pin, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(pin);
    pwm_set_clkdiv(slice, 3000);
    pwm_set_wrap(slice, period);
    pwm_set_enabled(slice, true);
    pwm_set_gpio_level(pin, SERVO_STOP_LEVEL);
}

void servo_rotate_cw(int pin){
    pwm_set_gpio_level(pin, SERVO_CW_LEVEL);
}

void servo_rotate_ccw(int pin){
    pwm_set_gpio_level(pin, SERVO_CCW_LEVEL);
}

void servo_stop(int pin){
    pwm_set_gpio_level(pin, SERVO_STOP_LEVEL);
}

void servo_sweep(int pin){
    servo_rotate_cw(pin);
    sleep_ms(ROTATION_TIME_MS);
    servo_stop(pin);
    sleep_ms(300);
    
    servo_rotate_ccw(pin);
    sleep_ms(ROTATION_TIME_MS);
    servo_stop(pin);
    sleep_ms(300);
}




