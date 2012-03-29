#include "patch.h"

void update_patches(int x, int y){

	patches[x][y].turbidity = ( .29587 + TSS) + (gui_k_phyto * (patches[x][y].phyto/ 900.0) ) + (gui_k_macro * (patches[x][y].macro / 900.0) );

	if(patches[x][y].turbidity > 30.0){
		patches[x][y].turbidity = 30.0;
	}
	if(patches[x][y].turbidity < 0.0){
		patches[x][y].turbidity = 0.01;
	}

    //TODO: missing if isNaN turbidity [show "NaN"]

	//the amount of light that reaches the bottom of a water column
	patches[x][y].bottom_light = (photo_radiation * exp( (-1*patches[x][y].depth)*patches[x][y].turbidity )); 
	Aj_peri = patches[x][y].macro / 10.0 ;
	Gj_peri = patches[x][y].macro / 2.0;
	Aj_seddecomp = patches[x][y].detritus / 20.0;
	Gj_seddecomp = patches[x][y].detritus / 5.0;
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
	Q10 = pow(theta, (temperature - macro_base_temp));

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
	Q10 = pow(theta, (temperature - base_temperature));
	double km = 10; //half saturation constant
	//this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
	double light_k = 0.4;
	patches[x][y].respiration_phyto = 0.1 / 24 * patches[x][y].phyto * Q10;
	double pre_ln = (0.01 + photo_radiation  * exp(-1*patches[x][y].phyto * \
		gui_k_phyto * patches[x][y].depth));
	double be = (km + (photo_radiation * exp(-1 * patches[x][y].phyto * \
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
        / (Ai_herbivore_peri - Gi_herbivore_peri);
    patches[x][y].herbivore_peri_prey_limitation = \
        assertRange( patches[x][y].herbivore_peri_prey_limitation, 0, 1);

    patches[x][y].herbivore_waterdecomp_prey_limitation = \
        patches[x][y].waterdecomp / \
        (Ai_herbivore_waterdecomp - Gi_herbivore_waterdecomp);
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

    patches[x][y].waterdecomp_pred_poc = pref_waterdecomp_POC \
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


void go_seddecomp(int x, int y) {
    
    // update seddecomp_detritus_prey_limitation
    patches[x][y].seddecomp_detritus_prey_limitation = patches[x][y].detritus / (Ai_seddecomp_detritus - Gi_seddecomp_detritus);
    if(patches[x][y].seddecomp_detritus_prey_limitation > 1)
        patches[x][y].seddecomp_detritus_prey_limitation = 1;
    else if(patches[x][y].seddecomp_detritus_prey_limitation < 0)
        patches[x][y].seddecomp_detritus_prey_limitation = 0;

    // update seddecomp_space_limitation
    if( (Gj_seddecomp - Aj_seddecomp) != 0 ) {
        patches[x][y].seddecomp_space_limitation = 1 - ((patches[x][y].seddecomp - Aj_seddecomp)/(Gj_seddecomp - Aj_seddecomp));
    } else {
        patches[x][y].seddecomp_space_limitation = 0;
    }
    if(patches[x][y].seddecomp_space_limitation > 1)
        patches[x][y].seddecomp_space_limitation = 1;
    else if(patches[x][y].seddecomp_space_limitation < 0)
        patches[x][y].seddecomp_space_limitation = 0;

    // update seddecomp_pred_detritus
    patches[x][y].seddecomp_pred_detritus = pref_seddecomp_detritus*max_seddecomp*patches[x][y].seddecomp*
                                            patches[x][y].seddecomp_detritus_prey_limitation *
                                            patches[x][y].seddecomp_space_limitation;

    // update seddecomp_ingest_detritus
    patches[x][y].seddecomp_ingest_detritus = patches[x][y].seddecomp_pred_detritus;

    // update seddecomp_respiration
    patches[x][y].seddecomp_respiration = r_seddecomp * patches[x][y].seddecomp;

    // update seddecomp_excretion
    patches[x][y].seddecomp_excretion = e_seddecomp * patches[x][y].seddecomp;

    // update seddecomp_senescence
    patches[x][y].seddecomp_senescence = s_seddecomp * patches[x][y].seddecomp;
}

void go_sedconsumer(int x, int y) {
    
    // update sedconsumer_seddecomp_prey_limitation
    patches[x][y].sedconsumer_seddecomp_prey_limitation = patches[x][y].seddecomp / (Ai_sedconsumer_seddecomp - Gi_sedconsumer_seddecomp);
    if( patches[x][y].sedconsumer_seddecomp_prey_limitation > 1 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 1;
    else if ( patches[x][y].sedconsumer_seddecomp_prey_limitation < 0 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 0;

    // update sedconsumer_peri_prey_limitation
    patches[x][y].sedconsumer_peri_prey_limitation = patches[x][y].peri / (Ai_sedconsumer_peri - Gi_sedconsumer_peri);
    if( patches[x][y].sedconsumer_peri_prey_limitation > 1 )
        patches[x][y].sedconsumer_peri_prey_limitation = 1;
    else if (patches[x][y].sedconsumer_peri_prey_limitation < 0)
        patches[x][y].sedconsumer_peri_prey_limitation = 0;

    // update sedconsumer_detritus_prey_limitation
    patches[x][y].sedconsumer_detritus_prey_limitation = patches[x][y].detritus / (Ai_sedconsumer_detritus - Gi_sedconsumer_detritus);
    if( patches[x][y].sedconsumer_detritus_prey_limitation > 1 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 1;
    else if ( patches[x][y].sedconsumer_detritus_prey_limitation < 0 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 0;

    // update sedconsumer_space_limitation
    patches[x][y].sedconsumer_space_limitation = 1 - ((patches[x][y].sedconsumer - Aj_sedconsumer)/(Gj_sedconsumer - Aj_sedconsumer));
    if( patches[x][y].sedconsumer_space_limitation > 1 )
        patches[x][y].sedconsumer_space_limitation = 1;
    else if ( patches[x][y].sedconsumer_space_limitation < 0 )
        patches[x][y].sedconsumer_space_limitation = 0;

    // update sedconsumer_pred_peri
    patches[x][y].sedconsumer_pred_peri = pref_sedconsumer_peri * max_sedconsumer * patches[x][y].sedconsumer *
                                          patches[x][y].sedconsumer_space_limitation * 
                                          patches[x][y].sedconsumer_peri_prey_limitation;

    // update sedconsumer_ingest_peri
    patches[x][y].sedconsumer_ingest_peri = patches[x][y].sedconsumer_pred_peri * (1 - sedconsumer_egestion_seddecomp);

    // update sedconsumer_pred_seddecomp
    patches[x][y].sedconsumer_pred_seddecomp = pref_sedconsumer_seddecomp * max_sedconsumer * patches[x][y].sedconsumer *
                                               patches[x][y].sedconsumer_space_limitation *
                                               patches[x][y].sedconsumer_seddecomp_prey_limitation;

    // update sedconsumer_ingest_seddecomp
    patches[x][y].sedconsumer_ingest_seddecomp = patches[x][y].sedconsumer_pred_seddecomp * (1 - sedconsumer_egestion_seddecomp);

    // update sedconsumer_pred_detritus
    patches[x][y].sedconsumer_pred_detritus = pref_sedconsumer_detritus * max_sedconsumer * patches[x][y].sedconsumer *
                                              patches[x][y].sedconsumer_space_limitation * 
                                              patches[x][y].sedconsumer_detritus_prey_limitation;

    // update sedconsumer_ingest_detritus
    patches[x][y].sedconsumer_ingest_detritus = patches[x][y].sedconsumer_pred_detritus * (1 - sedconsumer_egestion_detritus);

    // update sedconsumer_respiration
    patches[x][y].sedconsumer_respiration = r_sedconsumer * patches[x][y].sedconsumer;

    // update sedconsumer_excretion
    patches[x][y].sedconsumer_excretion = e_sedconsumer * patches[x][y].sedconsumer;

    // update sedconsumer_senescence
    patches[x][y].sedconsumer_senescence = s_sedconsumer * patches[x][y].sedconsumer;
}

void go_consum(int x,int y) {

    // update consum_sedconsumer_prey_limitation
    patches[x][y].consum_sedconsumer_prey_limitation = patches[x][y].sedconsumer / (Ai_consum_sedconsumer - Gi_consum_sedconsumer);
    if( patches[x][y].consum_sedconsumer_prey_limitation > 1 )
        patches[x][y].consum_sedconsumer_prey_limitation = 1;
    else if ( patches[x][y].consum_sedconsumer_prey_limitation < 0 )
        patches[x][y].consum_sedconsumer_prey_limitation = 0;

    // update consum_herbivore_prey_limitation
    patches[x][y].consum_herbivore_prey_limitation = patches[x][y].herbivore / (Ai_consum_herbivore - Gi_consum_herbivore);
    if( patches[x][y].consum_herbivore_prey_limitation > 1 )
        patches[x][y].consum_herbivore_prey_limitation = 1;
    else if ( patches[x][y].consum_herbivore_prey_limitation < 0 )
        patches[x][y].consum_herbivore_prey_limitation = 0;

    // update consum_space_limitation
    patches[x][y].consum_space_limitation = 1 - ((patches[x][y].consum - Aj_consum)/(Gj_consum - Aj_consum));
    if( patches[x][y].consum_space_limitation > 1 )
        patches[x][y].consum_space_limitation = 1;
    else if ( patches[x][y].consum_space_limitation < 0 )
        patches[x][y].consum_space_limitation = 0;

    // update consum_pred_herbivore
    patches[x][y].consum_pred_herbivore = pref_consum_herbivore * max_consum * patches[x][y].consum *
                                          patches[x][y].consum_space_limitation * 
                                          patches[x][y].consum_herbivore_prey_limitation;

    // update consum_ingest_herbivore
    patches[x][y].consum_ingest_herbivore = patches[x][y].consum_pred_herbivore * (1- consum_egestion);

    // update consum_pred_sedconsumer
    patches[x][y].consum_pred_sedconsumer = pref_consum_sedconsumer * max_consum * patches[x][y].consum *
                                            patches[x][y].consum_space_limitation *
                                            patches[x][y].consum_sedconsumer_prey_limitation;

    // update consum_ingest_sedconsumer
    patches[x][y].consum_ingest_sedconsumer = patches[x][y].consum_pred_sedconsumer * (1 - consum_egestion);

    // update consum_respiration
    patches[x][y].consum_respiration = r_consum * patches[x][y].consum;

    // update consum_excretion
    patches[x][y].consum_excretion = e_consum * patches[x][y].consum;

    // update consum_senescence
    patches[x][y].consum_senescence = s_consum * patches[x][y].consum;
}

void go_DOC(int x, int y)
{
    // 4% of photosynthetic gets released into the water column. Wetzel lit.
    patches[x][y].macro_exudation = .04 * patches[x][y].macro;

    // Dead objects < 1um are considered DOC in Wetzel book..
    patches[x][y].micro_death = patches[x][y].senescence_macro * .01 + patches[x][y].senescence_phyto * .01;

    // *need reference
    patches[x][y].excretion = patches[x][y].herbivore_excretion + patches[x][y].waterdecomp_excretion + 
                              patches[x][y].seddecomp_excretion + patches[x][y].sedconsumer_excretion + 
                              patches[x][y].consum_excretion + patches[x][y].excretion_phyto + patches[x][y].peri_excretion;

    // *need reference
    patches[x][y].flocculation = .01 * patches[x][y].DOC;

    patches[x][y].DOC_growth = patches[x][y].macro_exudation + patches[x][y].micro_death + patches[x][y].excretion;
}

void go_POC(int x, int y)
{
    if(patches[x][y].velocity > 0)
    {
        // exchange between POC and detritus determined by an approximation of Stoke's Law
        patches[x][y].detritus_POC_transfer = patches[x][y].detritus * (.25 * log10(((patches[x][y].velocity / 40 ) + .0001) + 1));
    }

    if(patches[x][y].detritus_POC_transfer > 1)
    {
        // cap at 100%. *need reference
        patches[x][y].detritus_POC_transfer = 1;
    }

    // approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
    patches[x][y].small_death = patches[x][y].senescence_macro * .09 + patches[x][y].senescence_phyto * .09 + 
                                patches[x][y].scouring_macro * .1 + patches[x][y].waterdecomp_senescence * 
                                .7 + .3 * patches[x][y].peri_senescence;

    // flocculation, leaching approximation
    patches[x][y].POC_growth = patches[x][y].flocculation + patches[x][y].detritus_POC_transfer;
}

void go_detritus(int x, int y)
{
    if(patches[x][y].velocity > 0)
    {
        // *need reference
        patches[x][y].POC_detritus_transfer = patches[x][y].POC * (1 - (.25 * log10((( patches[x][y].velocity / 40) + .0001) + 1)));
    }

    if(patches[x][y].POC_detritus_transfer < 0)
    {
        // *need reference
        patches[x][y].POC_detritus_transfer = 0;
    }

    if(patches[x][y].velocity == 0)
    {
        // *need reference. almost all material falls to the bottom in stagnant water
        patches[x][y].POC_detritus_transfer = patches[x][y].POC * .9; 
    }

    if(patches[x][y].gross_photo_macro < 0)
    {
        // to incorporate scoured macrophytes into detritus
        patches[x][y].macro_death = 0 - patches[x][y].gross_photo_macro;
    }

    // Dead objects > 10um will sink Wetzel book..
    patches[x][y].large_death = patches[x][y].senescence_macro * .9 + patches[x][y].scouring_macro * .9 + 
                                patches[x][y].senescence_phyto * .9 + patches[x][y].seddecomp_senescence + 
                                patches[x][y].waterdecomp_senescence * .3 + patches[x][y].herbivore_senescence + 
                                patches[x][y].sedconsumer_senescence + patches[x][y].consum_senescence + .07 * patches[x][y].peri_senescence;

    patches[x][y].egestion = herbivore_egestion + patches[x][y].sedconsumer_egestion + consum_egestion;

    // *need reference
    patches[x][y].detritus_growth = patches[x][y].large_death + patches[x][y].POC_detritus_transfer + 
                                    patches[x][y].egestion + patches[x][y].macro_death;
}
