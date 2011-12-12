#include "go.h"
#include "globals.h"
#include "math.h"
#include "pred.c"

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

    printf("hydro group %d for hour: %ld\n", hydro_group, hours);
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
            go_DOC(x,y);
            go_POC(x,y);
            go_detritus(x,y);

            pred_phyto(x,y);
            pred_herbivore(x,y);
            pred_seddecomp(x,y);
            pred_detritus(x,y);
            pred_DOC(x,y);
            pred_POC(x,y);
            pred_consum(x,y);
        }
    }
  
    avg_output();

    // flow carbon
    int max_timestep = get_timestep();
    int time, max_time = 3600/max_timestep;

    printf("before DOC: %f\n", patches[210][1162].DOC);

    //TODO: change to a list that contains depths>0 and velocity >0
    //TODO: see if you can get rid of the time for-loop, by multiplying it with max_time
    for (time = 0; time < max_time; time++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            for (x = 0; x < MAP_WIDTH; x++) {
                if( (patches[x][y].depth > 0) && (patches[x][y].velocity > 0) )
                {
                    flow_carbon(x,y);
                }
            }
        }
    }

    printf("after DOC: %f\n", patches[210][1162].DOC);

    // increment tick
    hours++;
    int day = get_day();
    if(day >= gui_days_to_run) {
        //TODO: break out of the while loop!
    }

    printf("DONE -- go() hours: %ld\n", hours);
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
                patches[x][y].px_vector = patches[x][y].pxv_list[hydro_group-1];
                patches[x][y].py_vector = patches[x][y].pyv_list[hydro_group-1];
                patches[x][y].depth = patches[x][y].depth_list[hydro_group-1];
                patches[x][y].velocity = patches[x][y].v_list[hydro_group-1];

                if( fabs(patches[x][y].px_vector) > fabs(patches[x][y].py_vector) ) {
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


/**
 * Go through all the patches with cell-type = 'output' and take the 
 * mean of the Stock variables
 */
void avg_output() {
    
    int x,y;
    int count = 0;
    double sum_macro = 0;
    double sum_phyto = 0;
    double sum_herbivore = 0;
    double sum_waterdecomp = 0;
    double sum_seddecomp = 0;
    double sum_sedconsumer = 0;
    double sum_consum = 0;
    double sum_DOC = 0;
    double sum_POC = 0;
    double sum_detritus = 0;

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            // output cells
            if(!patches[x][y].cell_type)
            {
                sum_macro += patches[x][y].macro;
                sum_phyto += patches[x][y].phyto;
                sum_herbivore += patches[x][y].herbivore;
                sum_waterdecomp += patches[x][y].waterdecomp;
                sum_seddecomp += patches[x][y].seddecomp;
                sum_sedconsumer += patches[x][y].consum;
                sum_DOC += patches[x][y].DOC;
                sum_POC += patches[x][y].POC;
                sum_detritus += patches[x][y].detritus;
                count++;
            }
        }
    }

    out_macro = sum_macro/count;
    out_phyto = sum_phyto/count;
    out_herbivore = sum_herbivore/count;
    out_waterdecomp = sum_waterdecomp/count;
    out_seddecomp = sum_seddecomp/count;
    out_sedconsumer = sum_sedconsumer/count;
    out_consum = sum_consum/count;
    out_DOC = sum_DOC/count;
    out_POC = sum_POC/count;
    out_detritus = sum_detritus/count;
}

/**
 * @return the max_timestep based on the greatest x-y vector
 */
int get_timestep() {
    return patch_length/COMPARE_MAX;
}

/**
 *
 */
void flow_carbon(int x, int y) {

    double corner_patch = fabs( patches[x][y].py_vector - patches[x][y].px_vector )/max_area;
    double tb_patch = fabs( patches[x][y].py_vector*( patch_length - fabs(patches[x][y].px_vector) ) )/max_area;
    double rl_patch = fabs( patches[x][y].px_vector*( patch_length - fabs(patches[x][y].py_vector) ) )/max_area;

    //TODO: loop-output

    // if a neighbor patch is dry, the carbon does not move in that direction
    int tb_moved = 0, corner_moved = 0, rl_moved = 0;
    int px = 0, py = 0;
    if ( patches[x][y].px_vector >= 0 ) px = 1; else px = -1;
    if ( patches[x][y].py_vector >= 0 ) py = 1; else py = -1;

    // flow carbon to the top/bottom patches
    if ( is_valid_patch(x, y+py) )
    {
        patches[x][y+py].DOC += patches[x][y].DOC*tb_patch;
        patches[x][y+py].POC += patches[x][y].POC*tb_patch;
        patches[x][y+py].phyto += patches[x][y].phyto*tb_patch;
        patches[x][y+py].waterdecomp += patches[x][y].waterdecomp*tb_patch;
        tb_moved = 1;
    }

    // flow carbon to the corner patch
    if ( is_valid_patch(x+px, y+py) )
    {
        patches[x+px][y+py].DOC += patches[x][y].DOC*corner_patch;
        patches[x+px][y+py].POC += patches[x][y].POC*corner_patch;
        patches[x+px][y+py].phyto += patches[x][y].phyto*corner_patch;
        patches[x+px][y+py].waterdecomp += patches[x][y].waterdecomp*corner_patch;
        corner_moved = 1;
    }

    // flow carbon to the left/right patches
    if ( is_valid_patch(x+px, y) ) 
    {
        patches[x+px][y].DOC += patches[x][y].DOC*rl_patch;
        patches[x+px][y].POC += patches[x][y].POC*rl_patch;
        patches[x+px][y].phyto += patches[x][y].phyto*rl_patch;
        patches[x+px][y].waterdecomp += patches[x][y].waterdecomp*rl_patch;
        rl_moved = 1;
    }

    // how much components did we loose
    double patch_loss = tb_patch*tb_moved + corner_patch*corner_moved + rl_patch*rl_moved;
    patches[x][y].DOC = patches[x][y].DOC - patches[x][y].DOC*patch_loss;
    patches[x][y].POC = patches[x][y].POC - patches[x][y].POC*patch_loss;
    patches[x][y].phyto = patches[x][y].phyto - patches[x][y].phyto*patch_loss;
    patches[x][y].waterdecomp = patches[x][y].waterdecomp - patches[x][y].waterdecomp*patch_loss;
}

/**
 * Checks if the x, y values for the patch is within boundaries of the map
 * @return 1 if valid, 0 otherwise
 */
int is_valid_patch(int x, int y) {
    if (x <0 || y < 0) return 0;
    if (x >= MAP_WIDTH || y>= MAP_HEIGHT) return 0;
    return 1;
}

/**
 * @return the number of days that have passed since the start of the code
 */
int get_day() {
    return hours/24;
}
