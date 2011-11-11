#include "setup.h"

/**
 * Calls the helper functions import_hydro and setup_environmentals
 * TODO: detailed comments
 */
void setup() {
    find_map_sizes();
    init_patches();
    import_hydro();
    setup_environmentals();
}

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes() {
    // open the first hydro map
    char* hydro_map = file_names[0];
    char* path = "./data/HydroSets/";
    int length = strlen(path) + strlen(hydro_map) + strlen(file_extension) + strlen(".txt") + 1;
    char hydro_path[length];
    strcpy(hydro_path, path);
    strcat(hydro_path, hydro_map);
    strcat(hydro_path, file_extension);
    strcat(hydro_path, ".txt");
     
    FILE* file = fopen(hydro_path, "r");
    if (file == NULL) {
        fputs("error openning the hydro map", stderr);
        exit(-1);
    }

    find_map_width_height(file); // find the width and height of the maps
    fclose(file);
}


/**
 * Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * @param hydro_file
 */
void find_map_width_height(FILE* hydro_file) {
    int patch_info_size = 6;    // first line in the file, pxcor/pycor/depth/px-vector/py-vector/velocity
    int word_size = 100;

    char word[word_size];
    word[0] = '\0';

    int max_x = 0;
    int max_y = 0;
    int counter = 0;
    while(fscanf(hydro_file, "%s", word) != EOF) {
        // pxcor
        if(counter%patch_info_size == 0) {
            int value = atoi(word);
            if(value > max_x)
                    max_x = value;
                    
        }        
        // pycor
        else if(counter%patch_info_size == 1) {
            int value = atoi(word);
            if(value > max_y)
                max_y = value;
        }
        counter++;
    }
    MAP_WIDTH = max_x;
    MAP_HEIGHT = max_y;
}

/**
 * Creates the 2D array of patches
 */
void init_patches() {
    // initialize the patches
    int row = 0;
    patches = malloc(MAP_WIDTH*sizeof(patch*));
    for(row = 0; row < MAP_WIDTH; row++) {
        patches[row] = malloc(MAP_HEIGHT*sizeof(patch));
    }
}

/**
 * TODO: Nathan and Chris
 */
void import_hydro() {

}

/**
 * TODO: Tom and Efe
 */
void setup_environmentals() 
{

}

int main() {
    setup();
}

