#include "patch.h"

void update_patches(int x, int y){

	patches[x][y].turbidity = ( .29587 + TSS) +
		(gui_k_phyto * (patches[x][y].phyto/ 900) ) +
		(gui_k_macro * (patches[x][y].macro / 900) );

	if(patches[x][y].turbidity > 30){
		patches[x][y].turbidity = 30;
	}
	if(patches[x][y].turbidity < 0){
		patches[x][y].turbidity = 0.01;
	}
	//the amount of light that reaches the bottom of a water column
	patches[x][y].bottom_light = (photo_radiation * 
			exp( (-1*patches[x][y].depth)*patches[x][y].turbidity )); 
	Aj_peri = patches[x][y].macro / 10 ;
	Gj_peri = patches[x][y].macro / 2;
	Aj_seddecomp = patches[x][y].detritus / 5 ;
	Gj_seddecomp = patches[x][y].detritus / 5;
}

//finish me - list problem
void go_macro(int x, int y){
	
}
