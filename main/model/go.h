#ifndef GO_H
#define GO_H

#include "main.h"

// Variables
long hours = 0;	//> This represents 1 tick (Should always be [0, sizeof(long)])

double temp_dif = 0;	//> The percent difference from 17 degrees Celsius. (Used in update_temp



/* Runs the model */
void go();

/* Updates the environmental variables (Primary macrophyte routine) */
void update_environmentals();

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


#endif
