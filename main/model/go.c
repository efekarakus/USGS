#include "go.h"
#include "globals.h"
#include "math.h"
#include "main.h"
#include "pred.c"
#include "list.c"
#include "color.c"

#include <sys/types.h>
#include <time.h>

/**
 * This function runs the model
 */
void go()
{
    
	update_environmentals();

	// Ask patches
    int x, y;

    for(y = 0; y < MAP_HEIGHT; y++) {
        for(x = 0; x < MAP_WIDTH; x++) {
            if(patches[x][y].depth > 0.0){
                update_patches(x,y);
                go_macro(x,y);
                go_phyto(x,y);
				go_herbivore(x,y);
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
				pred_waterdecomp(x,y);
				pred_sedconsumer(x,y);
                pred_detritus(x,y);
                pred_DOC(x,y);
                pred_POC(x,y);
                pred_consum(x,y);
            }
        }
    }

    // flow carbon
    int t, max_time = 60/gui_timestep_factor;
    nan_trigger = 0;      // set nan to false
    for (t = 0; t < max_time; t++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if( (patches[x][y].depth > 0.0) && (patches[x][y].velocity > 0.0) ) {
                    flow_carbon(x,y);
                    update_max(x,y);
                }
            }
        }
        if (nan_trigger) break;
    }
    // increment tick
    hours++;

    int day = hours%24;
    if (day == 0){
        update_color();
		current_day++;
		if(current_day == output_frequency){
			output_image();
			current_day = 0;
		}
	}
}


/**
 * Updates the environmental variables (Primary macrophyte routine)
 */
void update_environmentals()
{
	if ((hours % 24) == 0)	// Updates daily
	{
		if (hydro_changed == 1)
		{
			update_hydro_map();	// Updates a new hydro map based on the discharge
		    hydro_changed = 0;
        }
	}

	if ((hours % 168) == 0)	// Updates weekly
	{
		update_temp();	// Updates to a new water temperature
	}

	update_par();	// Updates hourly to a new photosynthetic radiation value
}


/**
 * Iterates through all the patches and sets the different components
 * inside the patch, it also computes the maximum_vector in the river and sets it to COMPARE_MAX 
 */
void update_hydro_map() {
    double max_vector = 0;
    int x, y;

    for(y = 0; y < MAP_HEIGHT; y++) {
        for(x = 0; x < MAP_WIDTH; x++) {
            
            // the hydro maps contained information about this patch
            // set the values of px_vector, py_vector, depth and velocity
            if(patches[x][y].available[hydro_group-1]) {
                patches[x][y].px_vector = patches[x][y].pxv_list[hydro_group-1];
                patches[x][y].py_vector = patches[x][y].pyv_list[hydro_group-1];
                patches[x][y].depth = patches[x][y].depth_list[hydro_group-1];
                patches[x][y].velocity = patches[x][y].v_list[hydro_group-1];

                if( fabs(patches[x][y].px_vector) > fabs(patches[x][y].py_vector) ) {
                    patches[x][y].max_vector = fabs(patches[x][y].px_vector);
                } else {
                    patches[x][y].max_vector = fabs(patches[x][y].py_vector);
                }
            } else {
                patches[x][y].px_vector = 0.0;
                patches[x][y].py_vector = 0.0;
                patches[x][y].depth = 0.0;
                patches[x][y].velocity = 0.0;
                patches[x][y].max_vector = 0.0;
            }
            // update miscellanous variables inside the patch
            if( (patches[x][y].current_depth > 0.0) && (patches[x][y].depth == 0.0) ) {
                patches[x][y].detritus += patches[x][y].DOC + patches[x][y].POC + patches[x][y].phyto + 
                                          patches[x][y].macro + patches[x][y].waterdecomp +
                                          patches[x][y].seddecomp + patches[x][y].herbivore + patches[x][y].sedconsumer + patches[x][y].consum;

                patches[x][y].DOC = 0.0;
                patches[x][y].POC = 0.0;
                patches[x][y].phyto = 0.0;
                patches[x][y].macro = 0.0;
                patches[x][y].waterdecomp = 0.0;
                patches[x][y].seddecomp = 0.0;
                patches[x][y].herbivore = 0.0;
                patches[x][y].sedconsumer = 0.0;
                patches[x][y].consum = 0.0;
            }
            if( (patches[x][y].current_depth == 0.0) && (patches[x][y].depth > 0.0) ){
                patches[x][y].detritus *= 0.5;
            }
            patches[x][y].current_depth = patches[x][y].depth;

            // update the max_vector value
            if(patches[x][y].max_vector > max_vector){
                max_vector = patches[x][y].max_vector;
            }
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
	temperature = temperature - ((temperature - 17.0) * temp_dif);
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
 * @return the max_timestep based on the greatest x-y vector
 */
int get_timestep() {
    if (COMPARE_MAX == 0.0)
        return 1.0;
    return (((double)patch_length)/((double)COMPARE_MAX));
}

int is_nan(int x, int y, double move_factor) {
  if ( isnan( patches[x][y].DOC + patches[x][y].DOC*move_factor ) ) {
      return 1;
  }
  if ( isnan( patches[x][y].POC + patches[x][y].POC*move_factor ) ) {
      return 1;
  }
  if ( isnan( patches[x][y].phyto + patches[x][y].phyto*move_factor ) ) {
      return 1;
  }
  if ( isnan( patches[x][y].waterdecomp + patches[x][y].waterdecomp*move_factor ) ) {
      return 1;
  }
  return 0;
}

/**
 * Flows carbon from the current patch at (x,y) to your neighbor patches
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void flow_carbon(int x, int y) {

    double corner_patch = fabs( patches[x][y].py_vector * patches[x][y].px_vector )/max_area;
    double tb_patch = fabs( patches[x][y].py_vector*( patch_length - fabs(patches[x][y].px_vector) ) )/max_area;
    double rl_patch = fabs( patches[x][y].px_vector*( patch_length - fabs(patches[x][y].py_vector) ) )/max_area;

    // if a neighbor patch is dry, the carbon does not move in that direction
    int max_timestep = get_timestep();
    int tb_moved = 0, corner_moved = 0, rl_moved = 0;

    int px = (int)(((double)max_timestep)*patches[x][y].px_vector);
    int py = (int)(((double)max_timestep)*patches[x][y].py_vector);

    if (gui_flow_corners_only)
    {
        if (px >= 1) px = 1;
        else if (px <= -1) px = -1;
        else px = 0;

        if (py >= 1) py = 1;
        else if (py <= -1) py = -1;
        else py = 0;
    }
    
    // flow carbon to the top/bottom patches
    if ( is_valid_patch(x, y+py) && (py!=0) )
    {
        if (is_nan(x,y+py,tb_patch)) {
            nan_trigger = 1;  
        }
        else
        {
            patches[x][y+py].DOC += patches[x][y].DOC*tb_patch;
            patches[x][y+py].POC += patches[x][y].POC*tb_patch;
            patches[x][y+py].phyto += patches[x][y].phyto*tb_patch;
            patches[x][y+py].waterdecomp += patches[x][y].waterdecomp*tb_patch;
            tb_moved = 1;
        }
    }

    // flow carbon to the corner patch
    if ( is_valid_patch(x+px, y+py) && (px!=0) && (py!=0))
    {
        if (is_nan(x+px,y+py,corner_patch)) {
            nan_trigger = 1;
        }
        else
        {
            patches[x+px][y+py].DOC += patches[x][y].DOC*corner_patch;
            patches[x+px][y+py].POC += patches[x][y].POC*corner_patch;
            patches[x+px][y+py].phyto += patches[x][y].phyto*corner_patch;
            patches[x+px][y+py].waterdecomp += patches[x][y].waterdecomp*corner_patch;
            corner_moved = 1;
        }
    }

    // flow carbon to the left/right patches
    if ( is_valid_patch(x+px, y) && (px!=0) ) 
    {
        if ( is_nan(x+px,y,rl_patch) ) {
            nan_trigger = 1;
        }
        else
        {
            patches[x+px][y].DOC += patches[x][y].DOC*rl_patch;
            patches[x+px][y].POC += patches[x][y].POC*rl_patch;
            patches[x+px][y].phyto += patches[x][y].phyto*rl_patch;
            patches[x+px][y].waterdecomp += patches[x][y].waterdecomp*rl_patch;
            rl_moved = 1;
        }
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
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
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

/**
 * Populates the flow_patches linked list with patches that have a velocity > 0 and depth > 0
 */
void get_flow_patches(List* flow_patches) {
    LL_init(flow_patches);
  
    int x, y;
    for(y = 0; y < MAP_HEIGHT; y++) {
        for(x = 0; x < MAP_WIDTH; x++) {
            if (patches[x][y].depth > 0.0 && patches[x][y].velocity > 0.0)
            {
                LL_insert(flow_patches, &patches[x][y]);
            }
        }
    }

}

/**
 * Updates the global variables for the stocks
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void update_max(int x, int y) {

    if ( patches[x][y].macro > MAX_MACRO ) {
        MAX_MACRO = patches[x][y].macro;
    }
    if ( patches[x][y].phyto > MAX_PHYTO ) {
        MAX_PHYTO = patches[x][y].phyto;
    }
    if ( patches[x][y].herbivore > MAX_HERBIVORE ) {
        MAX_HERBIVORE = patches[x][y].herbivore;
    }
    if ( patches[x][y].waterdecomp > MAX_WATERDECOMP ) {
        MAX_WATERDECOMP = patches[x][y].waterdecomp;
    }
    if ( patches[x][y].seddecomp > MAX_SEDDECOMP ) {
        MAX_SEDDECOMP = patches[x][y].seddecomp;
    }
    if ( patches[x][y].sedconsumer > MAX_SEDCONSUMER ) {
        MAX_SEDCONSUMER = patches[x][y].sedconsumer;
    }
    if ( patches[x][y].consum > MAX_CONSUM ) {
        MAX_CONSUM = patches[x][y].consum;
    }
    if ( patches[x][y].DOC > MAX_DOC ) {
        MAX_DOC = patches[x][y].DOC;
    }
    if ( patches[x][y].POC > MAX_POC ) {
        MAX_POC = patches[x][y].POC;
    }
    if ( patches[x][y].detritus > MAX_DETRITUS ) {
        MAX_DETRITUS = patches[x][y].detritus;
    }
}
