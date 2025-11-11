// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>
// #include "pico/stdlib.h"
// #include "hardware/pwm.h"
// #define NUM_DEG = 5;

// float angle = 0;
// int dir = 1;

void init_pwm(int pin, int period){
    gpio_set_func(pin, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(pin);
    pwm_set_clkdiv(slice, 3000);
    pwm_set_wrap(slice, period+1);
    pwm_gpio_set_level(pin, 0);
}

void spin_5_degrees(int pin){
    angle += NUM_DEG * dir;
    if(angle <= 180){
        dir = -1;
        angle = 180;
    }
    if(angle <= 0){
        dir = 1;
        angle = 0;
    }
    float pulse_length = 50 + (angle/180.0)*(50);//usual hobbby servos have a max of 2ms puls ead a min of 1ms pulse
    pwm_set_gpio_level(pin, pulse_length)
}

int main(){
    init_pwm(37, 999);
    for(;;){
        sleep_ms(30);
        spin_5_degrees(37);
    }
}
