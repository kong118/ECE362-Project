#ifndef __BUZZ_FREQ_H
#define __BUZZ_FREQ_H

void init_buzz_frequency_pwm();

void buzz();

void volume();

/**
 * @brief Set buzzer frequency based on distance
 * @param distance: Distance in cm (closer = higher frequency)
 */
void set_buzz_frequency(float distance);

/**
 * @brief Stop buzzer sound
 */
void stop_buzz();

#endif