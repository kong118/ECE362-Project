#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "buzz_freq.h"

#define BUZZER_PIN 36
#define MIN_FREQUENCY 200
#define MAX_FREQUENCY 2000
#define MAX_DISTANCE 200.0

void init_buzzer() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel_num = pwm_gpio_to_channel(BUZZER_PIN);
    
    pwm_set_clkdiv(slice_num, 150);
    pwm_set_wrap(slice_num, 1000);
    pwm_set_chan_level(slice_num, channel_num, 0);
    pwm_set_enabled(slice_num, true);
}

void set_buzzer_frequency(float distance) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel_num = pwm_gpio_to_channel(BUZZER_PIN);
    
    int frequency;
    
    if (distance <= 0) {
        frequency = MAX_FREQUENCY;
    } else if (distance >= MAX_DISTANCE) {
        frequency = MIN_FREQUENCY;
    } else {
        frequency = MAX_FREQUENCY - (int)((distance / MAX_DISTANCE) * (MAX_FREQUENCY - MIN_FREQUENCY));
    }
    
    uint32_t wrap = 1000000 / frequency;
    
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, channel_num, wrap / 2);
}

void stop_buzzer() {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel_num = pwm_gpio_to_channel(BUZZER_PIN);
    pwm_set_chan_level(slice_num, channel_num, 0);
}
