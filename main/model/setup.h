#ifndef _SETUP
#define _SETUP

#include "globals.h"
#include "list.h"
#include "go.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int num_hydro_files = 10;
char* file_names[] = {"10k-", "20k-", "30k-", "40k-", "50k-", "60k-", "70k-", "80k-", "90k-", "100k-"};

char* discharge_file = "discharge.txt";
char* photo_radiation_file = "par.txt";
char* temperature_file = "water-temp.txt";

char* cell_type_path = "./model/data/Environmentals/cell-type.txt";
char* environmentals_path = "./model/data/Environmentals/";
char* hydrosets_path = "./model/data/HydroSets/";

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

/**
 * Creates the 2D array of patches
 */
void init_patches();

/**
 * Creates the 2D array of colors
 */
void init_color_values();

/**
 * Reads the Hydo map files and sets up the proper (x,y) patches
 * Input in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this must be the first line in the file.
 */
void import_hydro();

/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 */
void setup_environmentals();

/**
 * Reads the "discharge.txt" file and initializes the discharge variables
 */
void set_discharge();

/**
 * Reads the "par.txt" file and initializes the photo_radiation array variables
 */
void set_photo_radiation();

/**
 * Reads the "water-temp.txt" file and initializes the temperature array variable
 */
void set_temperature();

/**
 * Sets up the 10 stocks, currently has default values
 * Will get these values as input later
 */
void setup_stocks();
#endif
