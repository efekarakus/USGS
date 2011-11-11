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
    char* path = "./model/data/HydroSets/";
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
    // Read the files
    int i, j, tempx, tempy;
    char file[256];
    FILE* pFile;
    char str[256];
    float value;
    double temp_depth, temp_px_velocity, temp_py_vector, temp_velocity;
    char* path = "./model/data/HydroSets/";
    // Append the extension to each file
    for(i = 0;i < 1; i++)
    {
        strcpy(file, path);
        strcat(file, file_names[i]);
        strcat(file, file_extension);
        strcat(file, ".txt");
        printf("%s\n", file);
        pFile = fopen(file, "r");
        if(pFile == NULL)
        {
            printf("Failed to open the file");
            exit(1);
        }
        printf("I die after the open.\n");
        // Skip the file layout
        for(j = 0; j < 6; j++){
            fscanf(pFile, "%s", str);
            printf("%s ", str);
        }
        printf("\n");
        while(fscanf(pFile, "%s", str) != EOF)
        {
            tempx = atoi(str);
            printf("tempx %d\n",tempx);
            fscanf(pFile, "%s", str);
            tempy = atoi(str);
            printf("tempy %d\n",tempy);
            fscanf(pFile, "%f", &value);
            //temp_depth = atoi(str);
            printf("temp_depth %f\n",value);
            fscanf(pFile, "%f", &value);
            //temp_px_velocity = atoi(str);
            printf("temp_px_vel %f\n",value);
            fscanf(pFile, "%f", &value);
            //temp_py_vector = atoi(str);
            printf("temp_py_vec %f\n",value);
            fscanf(pFile, "%f", &value);
            //temp_velocity = atoi(str);
            printf("temp_velocity %f\n",value);
        }
        fclose(pFile);
    }
}


/**
 * TODO: Tom and Efe
 *
 * NOTE: STILL NEED TO IMPLEMENT UPDATE-HYDRO-MAP!!!!!!!!!!!!!!!
 * NOTE: NEED TO FREE:
 *			- photo_radiation
 *			- temperature
 *			- discharge (if fixed_environmentals == true)
 */
void setup_environmentals() 
{
    if (fixed_environmentals == 1)
    {
		hydro_group = gui_hydro_group;
		// update-hydro-map()
		photo_radiation = (int*)malloc(sizeof(int));
		*photo_radiation = gui_photo_radiation;
		temperature = (double*)malloc(sizeof(double));
		*temperature = gui_temperature;
    }

	else
	{
		set_discharge();
		set_photo_radiation();
		set_temperature();

		hydro_group = 0;
		// choose-hydro-map
		// update-hydro-map
	}
}		


void set_discharge()
{
	char* pathname = "./model/data/Environmentals/";

	char* currFile = discharge_file;
	int length = strlen(pathname) + strlen(currFile) + 1;
	char filename[length];
	filename[0] = '\0';
	strcat(filename, pathname);
	strcat(filename, currFile);

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		perror ("Error opening discharge file");
	}

	char line[256];
	int count = 0;

	while (fgets(line, 256, file) != NULL)	// Get number of elements in file
	{
		count++;
	}
	
	discharge = (int*)malloc(count * sizeof(int));

	rewind(file);
	count = 0;
	while (fgets(line, 256, file) != NULL)	// Populate discharge array
	{
		int value = atoi(line);
		discharge[count] = value;
		count++;
	}
}


void set_photo_radiation()
{
	char* pathname = "./model/data/Environmentals/";

	char* currFile = photo_radiation_file;
	int length = strlen(pathname) + strlen(currFile) + 1;
	char filename[length];
	filename[0] = '\0';
	strcat(filename, pathname);
	strcat(filename, currFile);

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		perror ("Error opening photo_radiation file");
	}

	char line[256];
	int count = 0;

	while (fgets(line, 256, file) != NULL)	// Get number of elements in file
	{
		count++;
	}

	photo_radiation = (int*)malloc(count * sizeof(int));

	rewind(file);
	count = 0;
	
	while (fgets(line, 256, file) != NULL)	// Populate discharge array
	{
		int value = atoi(line);
		photo_radiation[count] = value;
		count++;
	}
}


void set_temperature()
{
	char* pathname = "./model/data/Environmentals/";

	char* currFile = temperature_file;
	int length = strlen(pathname) + strlen(currFile) + 1;
	char filename[length];
	filename[0] = '\0';
	strcat(filename, pathname);
	strcat(filename, currFile);

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		perror ("Error opening water-temperature file");
	}

	char line[256];
	int count = 0;

	while (fgets(line, 256, file) != NULL)	// Get number of elements in file
	{
		count++;
	}

	temperature = (double*)malloc(count * sizeof(double));

	rewind(file);

	count = 0;

	while (fgets(line, 256, file) != NULL)	// Populate temperature array
	{
		double value = atof(line);
		temperature[count] = value;
		count++;
	}
}

int main() {
    setup();
}

