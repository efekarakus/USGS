#ifndef DUMP_H
#define DUMP_H

#include "globals.h"
#include "patch.h"
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

const char* data_path = "./results/"; /* Folder under which we place the data files */
char* data_template = "map_data_"; /* Each simulation data file has the name 'map_data_timestamp' */
char* format = ".dat"; /* file format is .dat */

/**
 * The file format is as follows:
 * First line: GUI_VARIABLES separated by a comma
 * Each line represents one coordinate (x,y) in the River and holds the values of the DOCs in a patch.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int write_data();

/**
 * Creates a folder <data_path> and places all the results from running the model into this file.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int dump_data();

#endif
