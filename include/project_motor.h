#ifndef __MOTOR_H
#define __MOTOR_H

void init_pwm(int pin, int period);

/**
 * @brief Rotate motor 10 degrees clockwise and wait 0.5s
 * @param pin: PWM pin for servo control
 * @return Current angle in degrees (0-180)
 */
float rotate_10_degrees(int pin);

/**
 * @brief Get current motor angle without moving
 * @return Current angle in degrees (0-180)
 */
float get_current_angle(void);

#endif