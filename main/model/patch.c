#include "patch.h"

//finish me
void update_patches(){
	turbidity = ( .29587 + TSS) + (k-phyto * (phyto / 900) ) + \
				(k-macro * (macro / 900) );
	if(turbidity > 30){
		turbidity = 30;
	}
	if(turbidity < 0){
		turbidity = 0.01;
	}
	//Can't continue here until we understand par
	//the amount of light that reaches the bottom of a water column
	//bottom_light = (par * exp ( (- depth) *  turbidity )); 
}

//finish me - list problem
void go_macro(){
	
}
