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
 * Reads the Hydo map files and sets up the proper (x,y) patches
 * Input in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this must be the first line in the file.
 */
void import_hydro() {
    int i, j, temp_x, temp_y;
    char file[256];
    FILE* pFile;
    char str[256];
    float value;
    double temp_depth, temp_px_vector, temp_py_vector, temp_velocity;
    char* path = "./model/data/HydroSets/";

    for(i = 0;i < num_hydro_files; i++)
    {
        // Append the extension to get the correct hydro map
        strcpy(file, path);
        strcat(file, file_names[i]);
        strcat(file, file_extension);
        strcat(file, ".txt");
        pFile = fopen(file, "r");

        if(pFile == NULL)
        {
            printf("Failed to open the hydromap");
            exit(1);
        }

        // Skip the file layout
        for(j = 0; j < 6; j++)
        {
            fscanf(pFile, "%s", str);
        }

        // Scan through the files and retrieve the values
        while(fscanf(pFile, "%s", str) != EOF)
        {
            temp_x = atoi(str);
            fscanf(pFile, "%s", str);
            temp_y = atoi(str);
            fscanf(pFile, "%f", &value);
            temp_depth = value;
            fscanf(pFile, "%f", &value);
            temp_px_vector = value;
            fscanf(pFile, "%f", &value);
            temp_py_vector = value;
            fscanf(pFile, "%f", &value);
            temp_velocity = value;
        }
        fclose(pFile);
    }

    //Read in the cell-type file and set the patches
    strcpy(file, "./model/data/Environmentals/cell-type.txt");
    pFile = fopen(file, "r");

    if(pFile == NULL)
    {
        printf("Failed to open cell-type.txt");
        exit(1);
    }

    // Go through the cell-type.txt file and set the appropriate patches
    char temp_cell_type[256];
    while(fscanf(pFile, "%s", str) != EOF)
    {
        temp_x = atoi(str);
        fscanf(pFile, "%s", str);
        temp_y = atoi(str);
        fscanf(pFile, "%s", str);
        strcpy(temp_cell_type,  str);
    }
    fclose(pFile);
}


/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 *
 * NOTE: STILL NEED TO IMPLEMENT "UPDATE-HYDRO-MAP" AND "CHOOSE-HYDRO-MAP"
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

/**
 * Sets up the 10 stocks, currently has default values
 * Will get these values as input later
 */
void setup_stocks()
{
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++)
    {
        for(y = 0; y < MAP_HEIGHT; y++)
        {
            if(patches[x][y].depth > 0)
            {
                patches[x][y].macro = 1;
                patches[x][y].phyto = 10;
                patches[x][y].waterdecomp = 10;
                patches[x][y].seddecomp = 1;
                patches[x][y].herbivore = 1;
                patches[x][y].sedconsumer = 1;
                patches[x][y].DOC = 10;
                patches[x][y].POC = 10;
                patches[x][y].detritus = 1;
                patches[x][y].consum = .1;
            }
        }
    }
}

/**
 * Reads the discharge.txt file and initializes the discharge array variable
 */
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


/*
 * Reads the "par.txt" file and initializes the photo_radiation array variable 
 */
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


/**
 * Reads the "water-temp.txt" file and initializes the temperature array variable
 */
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

