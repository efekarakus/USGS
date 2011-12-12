#include "color.h"

void scale_color(enum Color colorVal, int value, int maxVal, int minVal, int x, int y){
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

void update_color(){
    int x = 0;
    int y = 0;

    if( strcmp(which_stock, "macro") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(green, patches[x][y].macro, 600000, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "phyto") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(green, patches[x][y].phyto, 75000, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "waterdecomp") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(green, patches[x][y].macro, 30, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "POC") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(blue, patches[x][y].POC, 10, 0, x, y);
            }
        }
    }
    /*TODO: Brown and Yellow are used as colors for the Netlogo code, but here
     * we use only green.
     */
    else if( strcmp(which_stock, "detritus") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(green, patches[x][y].detritus, 400, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "sedconsumer") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                scale_color(green, patches[x][y].sedconsumer, 15, 0, x, y);
            }
        }
    }

    /*TODO: Need to find the min and max values for the following variables
     * befor this code can be completed for the following values:
     * seddecomp
     * herbivore
     * consum
     * DOC
     */
}
