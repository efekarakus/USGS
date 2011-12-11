#include "go.h"
#include "globals.h"
#include "math.h"

/**
 * This function runs the model
 * TODO implement anything after update_patches
 */
void go()
{
	if (fixed_environmentals == 0) {
		update_environmentals();	// This is flagged to run every 24 hours in the function
	} else {
		if (sin((hours - 6) * (360 / 24)) <= 0)	// This is a sinusoidal wave to fluctuate PAS rom )
        {
			photo_radiation = 0;
		} else {
			photo_radiation = gui_photo_radiation * sin((hours - 6) * (360 / 24));
		}
	}


	// Ask patches
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            update_patches(x,y);
            go_macro(x,y);
            go_phyto(x,y);
            go_waterdecomp(x,y);
            go_seddecomp(x,y);
            go_sedconsumer(x,y);
            go_consum(x,y);
        }
    }

    hours++;
}


/**
 * Updates the environmental variables (Primary macrophyte routine)
 */
void update_environmentals()
{
	if ((hours % 24) == 0)	// Updates daily
	{
		update_discharge();	// Pulls next discharge from a data array
		choose_hydro_map();	// Chooses a new hydro map based on the discharge
		if (hydro_changed == 1)
		{
			update_hydro_map();	// Updates a new hydro map based on the discharge
		}
	}

	if ((hours % 168) == 0)	// Updates weekly
	{
		update_temp();	// Updates to a new water temperature
	}

	update_par();	// Updates hourly to a new photosynthetic radiation value
}

/**
 * Updates the values of hydro_changed and hydro_group based on the current value of discharge
 */
void choose_hydro_map() {
    hydro_changed = 0;
    int old_hydro = hydro_group;
    
    if(discharge <= 20000) {
        hydro_group = 10;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 30000) {
        hydro_group = 9;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 40000) {
        hydro_group = 8;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 50000) {
        hydro_group = 7;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 60000) {
        hydro_group = 6;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 70000) {
        hydro_group = 5;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 80000) {
        hydro_group = 4;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 90000) {
        hydro_group = 3;
        update_hydro_changed(old_hydro, hydro_group);
    } else if (discharge <= 100000) {
        hydro_group = 2;
        update_hydro_changed(old_hydro, hydro_group);
    } else {
        hydro_group = 1;
        update_hydro_changed(old_hydro, hydro_group);
    }
}

/**
 * Gives the value 1 if the two hydros are different to hydro_changed else 0
 * @param old_hydro: the previous value of the hydro_group
 * @param new_hydro: the new value of the hydro_group
 */
void update_hydro_changed(int old_hydro, int new_hydro) {
    if(old_hydro != new_hydro) hydro_changed = 1;
    else hydro_changed = 0;
}

/**
 * Iterates through all the patches and sets the different components
 * inside the patch, it also computes the maximum_vector in the river and sets it to COMPARE_MAX 
 */
void update_hydro_map() {
    double max_vector = 0;
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            
            // the hydro maps contained information about this patch
            // set the values of px_vector, py_vector, depth and velocity
            if(patches[x][y].available) {
                patches[x][y].px_vector = patches[x][y].pxv_list[hydro_group];
                patches[x][y].py_vector = patches[x][y].pyv_list[hydro_group];
                patches[x][y].depth = patches[x][y].depth_list[hydro_group];
                patches[x][y].velocity = patches[x][y].v_list[hydro_group];

                if( abs(patches[x][y].px_vector) > abs(patches[x][y].py_vector) ) {
                    patches[x][y].max_vector = patches[x][y].px_vector;
                } else {
                    patches[x][y].max_vector = patches[x][y].py_vector;
                }
            } else {
                patches[x][y].px_vector = 0.0;
                patches[x][y].py_vector = 0.0;
                patches[x][y].depth = 0.0;
                patches[x][y].velocity = 0.0;
                patches[x][y].max_vector = 0.0;
            }

            // update miscellanous variables inside the patch
            if(patches[x][y].current_depth > 0 && patches[x][y].depth == 0) {
                patches[x][y].detritus += patches[x][y].DOC + patches[x][y].POC + patches[x][y].phyto + 
                                          patches[x][y].macro + patches[x][y].macro + patches[x][y].waterdecomp +
                                          patches[x][y].seddecomp + patches[x][y].herbivore + patches[x][y].sedconsumer + patches[x][y].consum;

                patches[x][y].DOC = 0;
                patches[x][y].POC = 0;
                patches[x][y].phyto = 0;
                patches[x][y].macro = 0;
                patches[x][y].waterdecomp = 0;
                patches[x][y].seddecomp = 0;
                patches[x][y].herbivore = 0;
                patches[x][y].sedconsumer = 0;
                patches[x][y].consum = 0;
            }
            if(patches[x][y].current_depth == 0 && patches[x][y].depth > 0 ){
                patches[x][y].detritus *= 0.5;
            }
            patches[x][y].current_depth = patches[x][y].depth;

            // update the max_vector value
            if(patches[x][y].max_vector > max_vector) 
                max_vector = patches[x][y].max_vector;
        }// endfor y
    }// endfor x

    // update the maximum vector for the timestep
    COMPARE_MAX = max_vector;
}


/**
 * Updates the temperature variable
 */
void update_temp()
{
	temperature_index++;
	temperature = temperature_data[temperature_index];
	temperature = temperature - ((temperature - 17) * temp_dif);
}

/**
 * Updates the photosynthetic radiation variable
 */
void update_par()
{
	photo_radiation_index++;
	photo_radiation = photo_radiation_data[photo_radiation_index];
	photo_radiation = photo_radiation - (photo_radiation * par_dif);
}

/**
 * Updates the discharge variable
 */
void update_discharge()
{
	discharge_index++;
	discharge = discharge_data[discharge_index];
} 
