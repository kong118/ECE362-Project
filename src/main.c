#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "ultrasound.h"

int main() {
    stdio_init_all();
    ultrasound_init();
    
    while (1) {
        float* distance = ultrasound_measure_distance();
        
        if (distance != NULL) {
            printf("Distance: %.2f cm\n", *distance);
        } else {
            printf("No object detected\n");
        }
        
        sleep_ms(500);
    }
    
    return 0;
}
