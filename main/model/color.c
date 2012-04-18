#include "color.h"
#include <math.h>

void scale_color(double value, double maxVal, double minVal, int x, int y){
    float returnValue;
    if(maxVal == minVal){
        printf("Max and min value are equal in scale_color.\n");
        returnValue = 0.0;
        colorValues[x][y] = returnValue;
        return;
        //exit(1);
    }

    if(value <= minVal || isnan(value) ){
        returnValue = 0.0;
    }
    else if(value >= maxVal){
        returnValue = 1.0;
    }
    else{
        float rangeValues = abs(maxVal - minVal);
        returnValue = (value / rangeValues);
    }
	
    colorValues[x][y] = returnValue;
}

void update_color(){
    int x = 0;
    int y = 0;


    if( strcmp(which_stock, "macro") == 0){
        printf("I enter macro\n");
		hue = 120.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;//(222 << 16) | (184 << 8) | 135;
                }
                else
                  scale_color(patches[x][y].macro, MAX_MACRO, 0.0, x, y); //TODO: replace it with MAX_MACRO
            }
        }
    }


    else if( strcmp(which_stock, "phyto") == 0){
        printf("I enter phyto\n");
		hue = 120.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                  scale_color(patches[x][y].phyto, MAX_PHYTO, 0.0, x, y); //TODO: replace it with MAX_PHYTO
            }
        }
    }


    else if( strcmp(which_stock, "waterdecomp") == 0){
        printf("I enter waterdecomp\n");
		hue = 120.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                    scale_color(patches[x][y].waterdecomp, MAX_WATERDECOMP, 0.0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "POC") == 0){
        printf("I enter POC\n");
		hue = 240.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                    scale_color(patches[x][y].POC, MAX_POC, 0.0, x, y);
            }
        }
    }
    /*TODO: Brown and Yellow are used as colors for the Netlogo code, but here
     * we use only green.
     */
    else if( strcmp(which_stock, "detritus") == 0){
        printf("I enter detritus\n");
		hue = 19.6 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                    scale_color(patches[x][y].detritus, MAX_DETRITUS, 0.0, x, y);
            }
        }
    }


    else if( strcmp(which_stock, "sedconsumer") == 0){
        printf("I enter sedconsumer\n");
		hue = 60.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                    scale_color(patches[x][y].sedconsumer, MAX_SEDCONSUMER, 0.0, x, y);
            }
        }
    }

	else if( strcmp(which_stock, "seddecomp") == 0){
        printf("I enter seddecomp\n");
		hue = 240.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else //Magic numbers taken from original Netlogo code
					scale_color(patches[x][y].seddecomp, MAX_SEDDECOMP, 0.0, x, y);
			}
		}
	}
	
	else if( strcmp(which_stock, "herbivore") == 0){
        printf("I enter herbivore\n");
		hue = 300.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else //Magic numbers taken from original Netlogo code
					scale_color(patches[x][y].herbivore, MAX_HERBIVORE, 0.0, x, y);
			}
		}
	}
	
	else if( strcmp(which_stock, "consum") == 0){
        printf("I enter consum\n");
		hue = 300.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else //Magic numbers taken from original Netlogo code
					scale_color(patches[x][y].consum, MAX_CONSUM, 0.0, x, y);
			}
		}
	}
	
	else if( strcmp(which_stock, "DOC") == 0){
        printf("I enter DOC\n");
		hue = 60.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else //Magic numbers taken from original Netlogo code
					scale_color(patches[x][y].herbivore, MAX_DOC, 0.0, x, y);
			}
		}
	}
}
