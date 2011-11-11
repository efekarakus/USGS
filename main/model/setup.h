#ifndef _SETUP
#define _SETUP

#include "globals.h"
#include "patch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* file_names[] = {"10k-", "20k-", "30k-", "40k-", "50k-", "60k-", "70k-", "80k-", "90k-", "100k-"};

char* discharge_file = "discharge.txt";
char* photo_radiation_file = "par.txt";
char* temperature_file = "water-temp.txt";

/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup();

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes();

/**
 * Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * @param hydro_file
 */
void find_map_width_height(FILE* hydro_file);

void init_patches();

void import_hydro();

void setup_environmentals();

void set_discharge();
void set_photo_radiation();
void set_temperature();

#endif
