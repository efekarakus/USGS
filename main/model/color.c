#include "color.h"

void scale_color(Color colorVal, int value, int maxVal, int minVal, int x, int y){
    int returnValue = 0;
    if(maxVal == minVal){
        printf("Error in use of scale_color. Max and min value are equal.\n");
        exit(1);
    }

    if(value < minVal){
        returnValue = 0; //Darkest shade of color
    }
    else if(value > maxVal){
        returnValue = 255; //Lightest shade of color
    }
    else{
        int rangeValues = abs(maxVal - minVal);
        returnValue = (int)(value * 255 / rangeValues);
    }
    //Check if color scaling should be inverted
    if( maxVal < minVal){
        returnValue = 255 - returnValue;
    }
    colorValues[x][y].colors[(int)colorVal] = returnValue;
}
