#include "cleanup.h"

/**
 * Frees the allocated structures:
 *   -- 2D patches array
 *   -- discharge_data array
 *   -- photo_radiation_data array
 *   -- temperature_data array
 */
void cleanup() {
    clean_patches();
    clean_discharge_data();
    clean_photo_radiation_data();
    clean_temperature_data();
    clean_gui_filenames_and_days();
    clean_hydromap_index_array();
    clean_check_filenames_array();
}

/**
 * Frees up the 2D array of patches
 */
void clean_patches() {
    int x,y;
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            free( patches[x][y].available );
            free( patches[x][y].pxv_list );
            free( patches[x][y].pyv_list );
            free( patches[x][y].depth_list );
            free( patches[x][y].v_list );
        }
        free( patches[x] );
        free( colorValues[x] );
    }
	free( covered_area );
	free( uncovered_area );
    free( patches );
    free( colorValues );
}

/**
 * Frees the discharge_data array
 */
void clean_discharge_data() {
    free( discharge_data );
}

void clean_gui_filenames_and_days() {
    int index;
    for(index = 0; index < gui_filenames_filesize; index++){
        free(gui_filenames_array[index]);
    }
    free(gui_filenames_array);
    free(gui_days_array);
}

void clean_hydromap_index_array() {
  free(hydromap_index_array);
}

void clean_check_filenames_array() {
  int index;
  for(index = 0; index < num_unique_files; index++){
    free(check_filenames_array[index]);
  }
  free(check_filenames_array);
}

/**
 * Frees the photo_radiation_data array
 */
void clean_photo_radiation_data() {
    free( photo_radiation_data );
}

/**
 * Frees the temperature_data array
 */
void clean_temperature_data() {
    free( temperature_data );
}
