#ifndef GO_H
#define GO_H

#include "main.h"
#include "globals.h"

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

#endif
