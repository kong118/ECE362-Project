#include "lcd.h"
#include <math.h>

#define RADAR_CENTER_X 120
#define RADAR_CENTER_Y 200
#define RADAR_MAX_RADIUS 100
#define MAX_DISTANCE 200


void draw_init(void)
{
    // Clear
    LCD_Clear(BLACK);
    
    // range rings
    LCD_Circle(RADAR_CENTER_X, RADAR_CENTER_Y, RADAR_MAX_RADIUS, 0, GREEN);
    LCD_Circle(RADAR_CENTER_X, RADAR_CENTER_Y, RADAR_MAX_RADIUS * 3 / 4, 0, GREEN);
    LCD_Circle(RADAR_CENTER_X, RADAR_CENTER_Y, RADAR_MAX_RADIUS / 2, 0, GREEN);
    LCD_Circle(RADAR_CENTER_X, RADAR_CENTER_Y, RADAR_MAX_RADIUS / 4, 0, GREEN);
    
    // center point
    LCD_Circle(RADAR_CENTER_X, RADAR_CENTER_Y, 2, 1, GREEN);
    
    // baseline
    LCD_DrawLine(RADAR_CENTER_X - RADAR_MAX_RADIUS, RADAR_CENTER_Y,
                 RADAR_CENTER_X + RADAR_MAX_RADIUS, RADAR_CENTER_Y, GREEN);
    
    // reference lines
    LCD_DrawLine(RADAR_CENTER_X, RADAR_CENTER_Y,
                 RADAR_CENTER_X, RADAR_CENTER_Y - RADAR_MAX_RADIUS, GREEN);
}


void draw_location(float degree, float distance)
{
    if (distance <= MAX_DISTANCE && distance > 0) {
        float radian = degree * 3.14159265 / 180.0;
        float scaled_distance = distance / MAX_DISTANCE * RADAR_MAX_RADIUS;

        int obj_x = RADAR_CENTER_X + (int)(scaled_distance * cos(radian));
        int obj_y = RADAR_CENTER_Y - (int)(scaled_distance * sin(radian));

        LCD_Circle(obj_x, obj_y, 3, 1, RED);
    }
}
