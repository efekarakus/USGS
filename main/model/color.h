#ifndef COLOR_H
#define COLOR_H
#include "math.h"
#include "string.h"
    enum Color
    {
        red = 2,
        green = 1,
        blue = 0
    };

    /**
     * Function description copy-pasted from Netlogo documentation: 
     *
     * Reports a shade of color proportional to number.
     *
     * If range1 is less than range2, then the larger the number, 
     * the lighter the shade of color. 
     * But if range2 is less than range1, the color scaling is inverted.
     *
     * If number is less than range1, then the darkest shade of color 
     * is chosen.
     *
     * If number is greater than range2, then the lightest shade of color
     * is chosen.
     */
    void scale_color(enum Color colorVal, int value, int maxVal, int minVal, int x, int y);

    void update_color();
    
    //typedef struct _colorStruct{
    //    int colors[3]; //red, green, blue
    //}color;

    int** colorValues;
#endif
