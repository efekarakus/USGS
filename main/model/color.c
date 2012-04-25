#include "color.h"
#include <math.h>

void scale_color(double value, double maxVal, double minVal, int x, int y){
    float returnValue;
    if(maxVal == minVal){
        printf("Max and min value are equal in scale_color.\n");
        returnValue = 0.0;
        colorValues[x][y] = returnValue;
        return;
    }

    if(value <= minVal || isnan(value) ){
        returnValue = 0.0;
    }
    else if(value >= maxVal){
        returnValue = 1.0;
    }
    else{
        float rangeValues = fabs(maxVal - minVal);
        returnValue = (value / rangeValues);
    }
    colorValues[x][y] = returnValue;
}

void update_color(){
    int x = 0;
    int y = 0;


    if( strcmp(which_stock, "macro") == 0){
		hue = 120.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                {
                  scale_color(patches[x][y].macro, MAX_MACRO, 0.0, x, y); 
                }
            }
        }
    }


    else if( strcmp(which_stock, "phyto") == 0){
		hue = 120.0 / 360.0;
        double total_phyto = 0;
        int num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++){
          for(x = 0; x < MAP_WIDTH; x++){
            if(patches[x][y].depth > 0.0){
              total_phyto +=patches[x][y].phyto;
              num_patches++;
            }
          }
        }
        double AVG_phyto = total_phyto/num_patches;

        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else
                {
                  scale_color(patches[x][y].phyto, AVG_phyto, 0.0, x, y);
                }
            }
        }
    }


    else if( strcmp(which_stock, "waterdecomp") == 0){
		hue = 120.0 / 360.0;
        double total_waterdecomp = 0;
        int num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++){
          for(x = 0; x < MAP_WIDTH; x++){
            if(patches[x][y].depth > 0.0){
              total_waterdecomp +=patches[x][y].waterdecomp;
              num_patches++;
            }
          }
        }
        double AVG_waterdecomp = total_waterdecomp/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else{
                    scale_color(patches[x][y].waterdecomp, AVG_waterdecomp, 0.0, x, y);
                }
            }
        }
    }


    else if( strcmp(which_stock, "POC") == 0){
		hue = 240.0 / 360.0;
        double total_POC = 0;
        int num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++){
          for(x = 0; x < MAP_WIDTH; x++){
            if(patches[x][y].depth > 0.0){
              total_POC +=patches[x][y].POC;
              num_patches++;
            }
          }
        }
        double AVG_POC = total_POC/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                if (patches[x][y].depth == 0.0) {
                    colorValues[x][y] = -1;
                }
                else{
                    scale_color(patches[x][y].POC, AVG_POC, 0.0, x, y);
                }
            }
        }
    }
    /*TODO: Brown and Yellow are used as colors for the Netlogo code, but here
     * we use only green.
     */
    else if( strcmp(which_stock, "detritus") == 0){
		hue = 19.6 / 360.0;
        double total_detritus = 0;
        int num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++){
          for(x = 0; x < MAP_WIDTH; x++){
            if(patches[x][y].depth > 0.0){
              total_detritus +=patches[x][y].detritus;
              num_patches++;
            }
          }
        }
          double AVG_detritus = total_detritus/num_patches;
          for(y = 0; y < MAP_HEIGHT; y++){
              for(x = 0; x < MAP_WIDTH; x++){
                  if (patches[x][y].depth == 0.0) {
                      colorValues[x][y] = -1;
                  }
                  else{
                      scale_color(patches[x][y].detritus, AVG_detritus, 0.0, x, y);
                  }
              }
          }
      }


      else if( strcmp(which_stock, "sedconsumer") == 0){
          hue = 60.0 / 360.0;
          for(y = 0; y < MAP_HEIGHT; y++){
              for(x = 0; x < MAP_WIDTH; x++){
                  if (patches[x][y].depth == 0.0) {
                      colorValues[x][y] = -1;
                  }
                  else{
                      scale_color(patches[x][y].sedconsumer, MAX_SEDCONSUMER, 0.0, x, y);
                  }
              }
          }
      }

      else if( strcmp(which_stock, "seddecomp") == 0){
          hue = 240.0 / 360.0;
          double total_seddecomp = 0;
          int num_patches = 0;
          
          for(y=0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
              if(patches[x][y].depth > 0.0){
                total_seddecomp +=patches[x][y].seddecomp;
                num_patches++;
              }
            }
          }
        double AVG_seddecomp = total_seddecomp/num_patches;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else{ //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].seddecomp, AVG_seddecomp, 0.0, x, y);
			    }
            }
		}
	}
	
	else if( strcmp(which_stock, "herbivore") == 0){
		hue = 300.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else{ //Magic numbers taken from original Netlogo code
               scale_color(patches[x][y].herbivore, MAX_HERBIVORE, 0.0, x, y);
            }
			}
		}
	}
	
	else if( strcmp(which_stock, "consum") == 0){
		hue = 300.0 / 360.0;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else{ //Magic numbers taken from original Netlogo code
					scale_color(patches[x][y].consum, MAX_CONSUM, 0.0, x, y);
                }
			}
		}
	}
	
	else if( strcmp(which_stock, "DOC") == 0){
		hue = 60.0 / 360.0;
        double total_DOC = 0;
        int num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++){
          for(x = 0; x < MAP_WIDTH; x++){
            if(patches[x][y].depth > 0.0){
              total_DOC +=patches[x][y].DOC;
              num_patches++;
            }
          }
        }
        double AVG_DOC = total_DOC/num_patches;
		for(y = 0; y < MAP_HEIGHT; y++){
			for(x = 0; x < MAP_WIDTH; x++){
				if(patches[x][y].depth == 0.0){
					colorValues[x][y] = -1;
				}
				else{ //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].DOC, AVG_DOC, 0.0, x, y);
                }
			}
		}
	}
}
