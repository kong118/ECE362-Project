#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int closeness;
int gpio;

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