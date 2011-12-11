#ifndef _CLEANUP
#define _CLEANUP

#include "patch.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Frees the allocated structures:
 *   -- 2D patches array
 *   -- discharge_data array
 *   -- photo_radiation_data array
 *   -- temperature_data array
 */
void cleanup();

/**
 * Frees up the 2D array of patches
 */
void clean_patches();


/**
 * Frees the discharge_data array
 */
void clean_discharge_data();

/**
 * Frees the photo_radiation_data array
 */
void clean_photo_radiation_data();

/**
 * Frees the temperature_data array
 */
void clean_temperature_data();


#endif
