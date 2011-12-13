#include "color.h"

void scale_color(enum Color colorVal, double value, int maxVal, int minVal, int x, int y){
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

    colorValues[x][y] = returnValue << (int)colorVal*8;
}

void update_color(){
    int x = 0;
    int y = 0;

    if( strcmp(which_stock, "macro") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if(patches[x][y].macro != 0.0)
                scale_color(green, patches[x][y].macro, MAX_MACRO, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "phyto") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if( patches[x][y].phyto != 0.0)
                scale_color(green, patches[x][y].phyto, MAX_PHYTO, 0, x, y); //TODO: replace it with MAX_PHYTO
            }
        }
    }


    else if( strcmp(which_stock, "waterdecomp") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if( patches[x][y].waterdecomp != 0.0 )
                scale_color(green, patches[x][y].waterdecomp, MAX_WATERDECOMP, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "POC") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if( patches[x][y].POC != 0.0 )
                scale_color(blue, patches[x][y].POC, MAX_POC, 0, x, y);
            }
        }
    }
    /*TODO: Brown and Yellow are used as colors for the Netlogo code, but here
     * we use only green.
     */
    else if( strcmp(which_stock, "detritus") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if( patches[x][y].detritus != 0.0 )
                scale_color(green, patches[x][y].detritus, MAX_DETRITUS, 0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "sedconsumer") == 0){
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if ( patches[x][y].sedconsumer != 0.0 )
                scale_color(green, patches[x][y].sedconsumer, MAX_SEDCONSUMER, 0, x, y);
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
