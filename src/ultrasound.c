#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define TRIG_PIN 10
#define ECHO_PIN 11
#define TIMEOUT_US 30000  // 30ms timeout (~5 meters max range)
#define SOUND_SPEED_CM_PER_US 0.0343f  // 0.0343 cm/us

void ultrasound_init() {
    gpio_init(TRIG_PIN);
    gpio_init(ECHO_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    gpio_put(TRIG_PIN, 0);
    
    sleep_ms(10);
}


float* ultrasound_measure_distance() {
    static float distance;

    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);
    
    // start of echo
    absolute_time_t start_time = get_absolute_time();
    absolute_time_t timeout_time = make_timeout_time_us(TIMEOUT_US);
    
    while (gpio_get(ECHO_PIN) == 0) {
        if (absolute_time_diff_us(start_time, get_absolute_time()) > TIMEOUT_US) {
            return NULL;
        }
    }
    
    absolute_time_t echo_start = get_absolute_time();
    
    // end of echo
    while (gpio_get(ECHO_PIN) == 1) {
        if (absolute_time_diff_us(echo_start, get_absolute_time()) > TIMEOUT_US) {
            return NULL;//no valid echo received
        }
    }
    
    absolute_time_t echo_end = get_absolute_time();
    uint64_t pulse_duration = absolute_time_diff_us(start_time, echo_start);
    distance = (pulse_duration * SOUND_SPEED_CM_PER_US) / 2.0;

    if (distance < 2.0 || distance > 400.0) {
        return NULL;
    }
    
    return &distance;
}

float* ultrasound_init_and_measure() {
    ultrasound_init();
    sleep_ms(50);
    return ultrasound_measure_distance();
}