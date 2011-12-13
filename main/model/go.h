#ifndef GO_H
#define GO_H

#include "main.h"
#include "globals.h"
#include "list.h"

/* Runs the model */
void go();

/* Updates the environmental variables (Primary macrophyte routine) */
void update_environmentals();

/**
 * Updates the values of hydro_changed and hydro_group based on the current value of discharge
 */
void choose_hydro_map();

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
 * Updates the discharge variable
 */
void update_discharge();

/**
 * Go through all the patches with cell-type = 'output' and take the 
 * mean of the Stock variables
 */
void avg_output();

/**
 * @return the max_timestep based on the greatest x-y vector
 */
int get_timestep();

/**
 * Flows carbon from the current patch at (x,y) to your neighbor patches
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void flow_carbon(int x, int y);

/**
 * If the gui_loop_output is set to 1, for every cell of type 'input', we
 * change its stock values to the global variable values
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void loop_output(int x, int y);

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
 * Populates the flow_patches linked list with patches that have a velocity > 0 and depth > 0
 */
void get_flow_patches(List* flow_patches);

/**
 * Updates the global variables for the stocks
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void update_max(int x, int y);
#endif
