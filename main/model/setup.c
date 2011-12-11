#include "globals.h"
#include "setup.h"

/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup() {
    find_map_sizes();
    printf("PASSED -- find_map_sizes\n");
    init_patches();
    printf("PASSED -- init_patches\n");
    import_hydro();
    printf("PASSED -- import_hydro()\n");
    setup_environmentals();
    printf("PASSED -- setup_environmentals()\n");
    setup_stocks();
    printf("PASSED -- setup_stocks()\n");
}

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes() {
    
    int max_map_width = 0;
    int max_map_height = 0;

    int index;
    for(index = 0; index < num_hydro_files; index++) {
      char* hydro_map = file_names[index];
      char* path = "./model/data/HydroSets/";
      int length = strlen(path) + strlen(hydro_map) + strlen(file_extension) + strlen(".txt") + 1;
      char hydro_path[length];
      strcpy(hydro_path, path);
      strcat(hydro_path, hydro_map);
      strcat(hydro_path, file_extension);
      strcat(hydro_path, ".txt");
     
      FILE* file = fopen(hydro_path, "r");
      if (file == NULL) {
          fputs("error opening the hydro map", stderr);
          exit(-1);
      }

      find_map_width_height(file); // find the width and height of the maps
      if(MAP_WIDTH > max_map_width) {
          max_map_width = MAP_WIDTH;
      }
      if(MAP_HEIGHT > max_map_height) {
          max_map_height = MAP_HEIGHT;
      }
      fclose(file);
    }

    MAP_WIDTH = max_map_width;
    MAP_HEIGHT = max_map_height;
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
    MAP_WIDTH = max_x+1;
    MAP_HEIGHT = max_y+1;
}

/**
 * Creates the 2D array of patches
 */
void init_patches() {
    // initialize the patches
    int row = 0;
    int col = 0;

    patches = malloc(MAP_WIDTH*sizeof(patch*));
    for(col = 0; col < MAP_WIDTH; col++) {
        patches[col] = malloc(MAP_HEIGHT*sizeof(patch));
    }

    // initialize the arrays for each patch
    for(col = 0; col < MAP_WIDTH; col++){
        for(row = 0; row < MAP_HEIGHT; row++) {
            patches[col][row].pxcor = col; 
            patches[col][row].pycor = row;
            patches[col][row].pcolor = 0;
            patches[col][row].current_depth = 0;
            patches[col][row].available = 0;  // we have not seen this patch yet

            patches[col][row].pxv_list = malloc(num_hydro_files*sizeof(double));
            patches[col][row].pyv_list = malloc(num_hydro_files*sizeof(double));
            patches[col][row].depth_list = malloc(num_hydro_files*sizeof(double));
            patches[col][row].v_list = malloc(num_hydro_files*sizeof(double));
        }
    }

}

/**
 * Reads the Hydro map files and sets up the proper (x,y) patches
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


            // assign the values to patches:
            patches[temp_x][temp_y].available = 1;
            patches[temp_x][temp_y].pxcor = temp_x;
            patches[temp_x][temp_y].pycor = temp_y;
            patches[temp_x][temp_y].depth_list[i] = temp_depth;
            patches[temp_x][temp_y].pxv_list[i] = temp_px_vector;
            patches[temp_x][temp_y].pyv_list[i] = temp_py_vector;
            patches[temp_x][temp_y].v_list[i] = temp_velocity;
            patches[temp_x][temp_y].aqa_point = -999;

        }
        fclose(pFile);
    }

    //Read in the cell-type file and set the patches
    strcpy(file, "./model/data/Environmentals/cell-type.txt");  //TODO: make this file path more generic by moving it to the header file
    pFile = fopen(file, "r");

    if(pFile == NULL)
    {
        printf("Failed to open cell-type.txt");
        exit(1);
    }

    // Go through the cell-type.txt file and set the appropriate patches
    char temp_cell_type[256];
   
    // skip the file layout
    for(j = 0; j < 3; j++) {
        fscanf(pFile, "%s", str);
    }
    
    while(fscanf(pFile, "%s", str) != EOF)
    {
        temp_x = atoi(str);
        fscanf(pFile, "%s", str);
        temp_y = atoi(str);
        fscanf(pFile, "%s", str);
        strcpy(temp_cell_type,  str);


        temp_x--;
        temp_y--;
        // assign the cell_type to the patches
        if(strcmp(temp_cell_type,"output") == 0) {
            patches[temp_x][temp_y].cell_type = 0;
        } else { 
            patches[temp_x][temp_y].cell_type = 1;
        }

    }
    fclose(pFile);
}


/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 *
 * TODO: STILL NEED TO IMPLEMENT "UPDATE-HYDRO-MAP"
 *		 
 *		 STILL NEED TO FREE:
 *			- photo_radiation
 *			- temperature
 *			- discharge (if fixed_environmentals == true)
 */
void setup_environmentals() 
{
	temp_dif = 0;
	par_dif = 0;

    if (fixed_environmentals == 1)	// Read environmental data from the GUI
    {
		hydro_group = gui_hydro_group;
		update_hydro_map();
		photo_radiation = gui_photo_radiation;
		temperature = gui_temperature;
    }
	else	// Read environmental data from the txt files
	{
		set_discharge();
		set_photo_radiation();
		set_temperature();

		hydro_group = 0;
		choose_hydro_map();
		update_hydro_map();
	}
}




/**
 * Reads the discharge.txt file and initializes the discharge variables
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
	
	discharge_data = (int*)malloc(count * sizeof(int));

	rewind(file);
	count = 0;
	while (fgets(line, 256, file) != NULL)	// Populate discharge_data array
	{
		int value = atoi(line);
		discharge_data[count] = value;
		count++;
	}

	discharge_index = 0;	// Initialize discharge index to represent current index
	discharge = discharge_data[discharge_index];	// Assign first value of discharge

	fclose(file);
}


/*
 * Reads the "par.txt" file and initializes the photo_radiation array variables
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

	photo_radiation_data = (int*)malloc(count * sizeof(int));

	rewind(file);
	count = 0;
	
	while (fgets(line, 256, file) != NULL)	// Populate discharge array
	{
		int value = atoi(line);
		photo_radiation_data[count] = value;
		count++;
	}
	
	photo_radiation_index = 0;	// Initialize photo_radiation index to represent current index
	photo_radiation = photo_radiation_data[photo_radiation_index];	// Assign first value of photo_radiation

	fclose(file);
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

	temperature_data = (double*)malloc(count * sizeof(double));

	rewind(file);

	count = 0;

	while (fgets(line, 256, file) != NULL)	// Populate temperature array
	{
		double value = atof(line);
		temperature_data[count] = value;
		count++;
	}

	temperature_index = 0;	// Initialize temperature index to represent current index
	temperature = temperature_data[temperature_index];	// Assign first value of temperature

	fclose(file);
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

