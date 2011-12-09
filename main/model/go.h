#ifndef GO_H
#define GO_H

#include "main.h"
#include "globals.h"



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
