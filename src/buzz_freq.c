#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "buzz_freq.h"

#include <stdint.h>


#define N 1000
#define RATE 20000

int closeness;
int gpio;

int step0 = 0;
int offset0 = 0;
int step1 = 0;
int offset1 = 0;
float wavetable[1000];



void init_buzz_frequency_pwm()
{
    gpio_set_function(gpio,GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel_num = pwm_gpio_to_channel(gpio);

    pwm_set_clkdiv(slice_num,150);

    pwm_set_wrap(slice_num, 1000);

    pwm_set_chan_level(slice_num,channel_num,0);

    pwm_set_irq_enabled(slice_num,true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP_0,buzz);
    irq_set_enabled(PWM_IRQ_WRAP_0,true);
    pwm_set_enabled(slice_num,true);
    
}

void buzz()
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_clear_irq(slice_num);
    pwm_set_wrap(slice_num,closeness);
}

void volume()
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel_num = pwm_gpio_to_channel(gpio);
    pwm_clear_irq(slice_num);
    pwm_set_chan_level(slice_num,channel_num,closeness);
}

void buzz_handler() {
    // fill in
    uint slice_num36 = pwm_gpio_to_slice_num(36);

    uint channel_num36 = pwm_gpio_to_channel(36);

    pwm_clear_irq(slice_num36);

    offset0 += step0;
    offset1 += step1;

    if(offset0 >= (N << 16))
    {
        offset0 -= (N << 16);
    }

    if(offset1 >= (N << 16))
    {
        offset1 -= (N << 16);
    }

    uint samp = wavetable[offset0 >> 16] + wavetable[offset1 >> 16];

    samp /= 2;

    uint current_period = pwm_hw->slice[slice_num36].top;

    samp = samp * current_period / (1 << 16);

    pwm_set_chan_level(slice_num36, channel_num36, samp);
}

void init_pwm_audio() {
    // fill in
    gpio_set_function(36,GPIO_FUNC_PWM);

    uint slice_num36 = pwm_gpio_to_slice_num(36);

    uint channel_num36 = pwm_gpio_to_channel(36);

    pwm_set_clkdiv(slice_num36,150.0f);

    pwm_set_wrap(slice_num36,  (1000000 / RATE) - 1);

    pwm_set_chan_level(slice_num36, channel_num36, 0);

    init_wavetable();

    pwm_set_irq_enabled(slice_num36,true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP_0,buzz_handler);
    irq_set_enabled(PWM_IRQ_WRAP_0,true);

    pwm_set_enabled(slice_num36, true);
}

void init_wavetable(void) {
    for(int i=0; i < N; i++)
        wavetable[i] = (16383 * sin(2 * 3.14159265 * i / N)) + 16384;
}

/**
 * @brief Set buzzer frequency based on distance
 * @param distance: Distance in cm (closer = higher frequency)
 */
void set_buzz_frequency(float distance) {
    // Map distance to frequency: closer = higher frequency
    // Distance range: 0-200cm
    // Frequency range: 2000Hz (close) to 200Hz (far)
    int frequency;
    
    if (distance <= 0) {
        frequency = 2000;  // Very close
    } else if (distance >= 200) {
        frequency = 200;   // Very far
    } else {
        // Linear mapping: closer = higher frequency
        frequency = 2000 - (int)((distance / 200.0) * 1800);
    }
    
    // Set the wrap value to control frequency
    // Lower wrap value = higher frequency
    closeness = 1000000 / frequency;
    
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel_num = pwm_gpio_to_channel(gpio);
    pwm_set_wrap(slice_num, closeness);
    pwm_set_chan_level(slice_num, channel_num, closeness / 2);  // 50% duty cycle for beep
}

/**
 * @brief Stop buzzer sound
 */
void stop_buzz() {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel_num = pwm_gpio_to_channel(gpio);
    pwm_set_chan_level(slice_num, channel_num, 0);
}
