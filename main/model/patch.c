#include "patch.h"

//finish me
void update_patches(int x, int y){
	turbidity = ( .29587 + TSS) + (k-phyto * (phyto / 900) ) + \
				(k-macro * (macro / 900) );
	if(turbidity > 30){
		turbidity = 30;
	}
	if(turbidity < 0){
		turbidity = 0.01;
	}
	//the amount of light that reaches the bottom of a water column
	bottom_light = (photo_radiation * exp ( (-1*depth) *  turbidity )); 
	AJ_peri = patch[x][y].macro / 10 ;
}

//finish me - list problem
void go_macro(){
	
}
