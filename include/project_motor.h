#ifndef __MOTOR_H
#define __MOTOR_H

void servo_pwm_init(int pin, int period);

void servo_rotate_cw(int pin);

void servo_rotate_ccw(int pin);

void servo_stop(int pin);

void servo_sweep(int pin);


#endif

