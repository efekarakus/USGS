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

double assertRange(double value, double low, double high){
    if(value < low)
        return low;
    else if(value > high)
        return high;
    else
        return value;
}

void go_macro(int x, int y){
	Q10 = theta*exp(temperature - macro_base_temp);

	if(patches[x][y].velocity < macro_vel_max){
		patches[x][y].K = max_area * (gui_macro_mass_max - \
			(gui_macro_mass_max  / gui_macro_vel_max) * patches[x][y].velocity);
	}
	else{
		patches[x][y].K = 0.01;
	}
	//Same at bottom-light
	double macro_light = photo_radiation * exp( (-1*patches[x][y].depth) \
		* patches[x][y].turbidity );
	
	patches[x][y].gross_photo_macro = (gui_gross_macro_coef * \
		patches[x][y].macro * ( macro_light / ( macro_light + 10)) * Q10 * \
		(patches[x][y].K - patches[x][y].macro) / patches[x][y].K);

	patches[x][y].respiration_macro = (resp_macro_coef / 24) * \
		patches[x][y].macro * Q10;

	patches[x][y].senescence_macro = sen_macro_coef * patches[x][y].macro / 24;

	patches[x][y].growth_macro = patches[x][y].gross_photo_macro - \
		patches[x][y].respiration_macro - patches[x][y].senescence_macro \
		- patches[x][y].scouring_macro;

	patches[x][y].macro += patches[x][y].growth_macro;

	if(patches[x][y].macro < 0.001)
		patches[x][y].macro = 0.001; //minimum biomass based on seed bank
}

void go_phyto(int x,int y){ 
	//minimum and maximum caps on biomass
	if( patches[x][y].phyto > 900000){
		patches[x][y].phyto = 900000;
	}
	if( patches[x][y].phyto < 0.001){
		patches[x][y].phyto = 0.001;
	}
	double base_temperature = 8.0; //base temperature for nominal growth
	Q10 = theta * exp( temperature - base_temperature);
	double km = 10; //half saturation constant
	//this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
	double light_k = 0.4;
	patches[x][y].respiration_phyto = 0.1 / 24 * patches[x][y].phyto * Q10;
	double pre_ln = (0.01 + photo_radiation * e * exp(-1*patches[x][y].phyto * \
		gui_k_phyto * patches[x][y].depth));
	double be = (km + (photo_radiation * e * exp(-1 * patches[x][y].phyto * \
		gui_k_phyto * patches[x][y].depth)));
	//photosynthesis from phytoplankton derived from Huisman Weissing 1994
	patches[x][y].gross_photo_phyto = fabs(pre_ln / be) * \
	    (1 / patches[x][y].depth) * \
		(patches[x][y].phyto / patches[x][y].turbidity) * Q10;
	patches[x][y].excretion_phyto = 0.05 / 24 * patches[x][y].phyto;
	// values range between 0.05 and 3
	patches[x][y].senescence_phyto = 0.02 / 24 * patches[x][y].phyto;
	//amount of biomass phytoplankton gains
	patches[x][y].growth_phyto = patches[x][y].gross_photo_phyto - \
		patches[x][y].excretion_phyto - patches[x][y].respiration_phyto - \
		patches[x][y].senescence_phyto;
}

void go_herbivore(int x, int y){

	patches[x][y].herbivore_phyto_prey_limitation = patches[x][y].phyto \
		/ (Ai_herbivore_phyto - Gi_herbivore_phyto);
	patches[x][y].herbivore_phyto_prey_limitation = \
	    assertRange(patches[x][y].herbivore_phyto_prey_limitation, 0, 1);

    patches[x][y].herbivore_peri_prey_limitation = patches[x][y].peri \
        / (Ai_herbivore_phyto - Gi_herbivore_phyto);
    patches[x][y].herbivore_peri_prey_limitation = \
        assertRange( patches[x][y].herbivore_peri_prey_limitation, 0, 1);

    patches[x][y].herbivore_waterdecomp_prey_limitation = \
        patches[x][y].waterdecomp / \
        (Ai_herbivore_phyto - Gi_herbivore_phyto);
    patches[x][y].herbivore_waterdecomp_prey_limitation = \
        assertRange(patches[x][y].herbivore_waterdecomp_prey_limitation, 0, 1);

    patches[x][y].herbivore_space_limitation = 1 - \
        ((patches[x][y].herbivore - Aj_herbivore) / \
         (Gj_herbivore - Aj_herbivore));
    patches[x][y].herbivore_space_limitation = \
        assertRange(patches[x][y].herbivore_space_limitation, 0, 1);

    patches[x][y].herbivore_pred_phyto = pref_herbivore_phyto * \
        max_herbivore * patches[x][y].herbivore * 
        patches[x][y].herbivore_space_limitation *
        patches[x][y].herbivore_phyto_prey_limitation;

    patches[x][y].herbivore_ingest_phyto = \
        patches[x][y].herbivore_pred_phyto * (1 - herbivore_egestion);

    patches[x][y].herbivore_pred_peri = \
        pref_herbivore_peri * max_herbivore * patches[x][y].herbivore \
        * patches[x][y].herbivore_space_limitation \
        * patches[x][y].herbivore_peri_prey_limitation;

    patches[x][y].herbivore_ingest_peri = \
        patches[x][y].herbivore_pred_peri * (1 - herbivore_egestion);

    patches[x][y].herbivore_pred_waterdecomp = \
        pref_herbivore_waterdecomp * max_herbivore * \
        patches[x][y].herbivore * \
        patches[x][y].herbivore_space_limitation * \
        patches[x][y].herbivore_waterdecomp_prey_limitation;

    patches[x][y].herbivore_ingest_waterdecomp = \
        patches[x][y].herbivore_pred_waterdecomp * \
        (1 - herbivore_egestion);

    patches[x][y].herbivore_respiration = r_herbivore * \
        patches[x][y].herbivore;

    patches[x][y].herbivore_excretion = e_herbivore * \
        patches[x][y].herbivore;

    patches[x][y].herbivore_senescence = s_herbivore * \
        patches[x][y].herbivore;
}

void go_waterdecomp(int x, int y){

    patches[x][y].waterdecomp_doc_prey_limitation = patches[x][y].DOC \
        / (Ai_waterdecomp_DOC - Gi_waterdecomp_DOC);
    patches[x][y].waterdecomp_doc_prey_limitation = \
        assertRange(patches[x][y].waterdecomp_doc_prey_limitation, 0, 1);

    patches[x][y].waterdecomp_poc_prey_limitation = patches[x][y].POC \
        / (Ai_waterdecomp_POC - Gi_waterdecomp_POC);
    patches[x][y].waterdecomp_poc_prey_limitation = \
        assertRange(patches[x][y].waterdecomp_poc_prey_limitation, 0, 1);

    patches[x][y].waterdecomp_space_limitation = 1 - \
        ((patches[x][y].waterdecomp - Aj_waterdecomp) / \
         (Gj_waterdecomp - Aj_waterdecomp));
    patches[x][y].waterdecomp_space_limitation = \
        assertRange(patches[x][y].waterdecomp_space_limitation, 0, 1);

    patches[x][y].waterdecomp_pred_doc = (pref_waterdecomp_DOC \
        * max_waterdecomp * patches[x][y].waterdecomp * \
        patches[x][y].waterdecomp_space_limitation * \
        patches[x][y].waterdecomp_doc_prey_limitation);

    patches[x][y].waterdecomp_ingest_doc = \
        patches[x][y].waterdecomp_pred_doc;

    patches[x][y].waterdecomp_pred_doc = pref_waterdecomp_POC \
        * max_waterdecomp * patches[x][y].waterdecomp \
        * patches[x][y].waterdecomp_space_limitation \
        *  patches[x][y].waterdecomp_poc_prey_limitation;

    patches[x][y].waterdecomp_ingest_poc = \
        patches[x][y].waterdecomp_pred_poc;

    patches[x][y].waterdecomp_respiration = r_waterdecomp * \
        patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_excretion = e_waterdecomp * \
        patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_senescence = s_waterdecomp * \
        patches[x][y].waterdecomp;
}
