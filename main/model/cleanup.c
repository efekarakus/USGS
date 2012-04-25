#include "cleanup.h"

/**
 * Frees the allocated structures:
 *   -- 2D patches array
 *   -- photo_radiation_data array
 *   -- temperature_data array
 */
void cleanup() {
    clean_patches();
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
            printf("cleaned available\n")
            free( patches[x][y].pxv_list );
            printf("cleaned pxv_list\n");
            free( patches[x][y].pyv_list );
            printf("cleaned pyv_list\n");
            free( patches[x][y].depth_list );
            printf("cleaned depth_list\n");
            free( patches[x][y].v_list );
            printf("cleaned v_list\n");
        }
        free( patches[x] );
        printf("cleaned pacthes X\n");
        free( colorValues[x] );
        printf("cleaned colorvalues X\n")
    }
	free( covered_area );
    printf("cleaned covered_area\n");
	free( uncovered_area );
    printf("cleaned uncovered_area\n");
    free( patches );
    printf("cleaned patches\n");
    free( colorValues );
    printf("cleaned colorvalues\n");
}

void clean_gui_filenames_and_days() {
    int index;
    for(index = 0; index < gui_filenames_filesize; index++){
        free(gui_filenames_array[index]);
        printf("cleaned gui_filenames_array index\n");
    }
    free(gui_filenames_array);
    printf("cleaned gui_filenames_array\n");
    free(gui_days_array);
    printf("cleaned gui_days_array\n");
}

void clean_hydromap_index_array() {
  free(hydromap_index_array);
  printf("cleaned hydromap_index_array\n")
}

void clean_check_filenames_array() {
  int index;
  for(index = 0; index < num_unique_files; index++){
    free(check_filenames_array[index]);
    printf("cleaned check_filenames_array index\n", );
  }
  free(check_filenames_array);
  printf("cleaned check_filenames_array\n");
}

/**
 * Frees the photo_radiation_data array
 */
void clean_photo_radiation_data() {
    free( photo_radiation_data );
    printf("cleaned photo_radiation_data\n");
}

/**
 * Frees the temperature_data array
 */
void clean_temperature_data() {
    free( temperature_data );
    printf("cleaned temperature_data\n");
}
