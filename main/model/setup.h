#ifndef _SETUP
#define _SETUP

#include "globals.h"
#include "patch.h"
#include <stdio.h>

char** file_names = {"10k-", "20k-", "30k-", "40k-", "50k-", "60k-", "70k-", "80k-", "90k-", "100k-"};

/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup();

#endif
