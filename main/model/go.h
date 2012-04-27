#ifndef GO_H
#define GO_H

#include "globals.h"

/* Runs the model */
void go();

/* Updates the environmental variables (Primary macrophyte routine) */
void update_environmentals();

/**
 * Gives the value 1 if the two hydros are different to hydro_changed else 0
 * @param old_hydro: the previous value of the hydro_group
 * @param new_hydro: the new value of the hydro_group
 */
void update_hydro_changed(int old_hydro, int new_hydro);

/**
 * Iterates through all the patches and sets the different components
 * inside the patch, it also computes the maximum_vector in the river and sets it to COMPARE_MAX 
 */
void update_hydro_map();

/**
 * Updates the temperature variable
 */
void update_temp();

/**
 * Updates the photosynthetic radiation variable
 */
void update_par();

/**
 * @return the max_timestep based on the greatest x-y vector
 */
int get_timestep();

/**
 * @return 1 if DOC, POC, phyto, waterdecomp are NaN 0 otherwise
 */
int is_nan(int x, int y, double move_factor);
/**
 * Flows carbon from the current patch at (x,y) to your neighbor patches
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void flow_carbon(int x, int y);

/**
 * Checks if the x, y values for the patch is within boundaries of the map
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 * @return 1 if valid, 0 otherwise
 */
int is_valid_patch(int x, int y);

/**
 * @return the number of days that have passed since the start of the code
 */
int get_day();

/**
 * Updates the global variables for the stocks
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void update_max(int x, int y);
#endif
