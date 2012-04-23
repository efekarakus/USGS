#include "globals.h"
#include "setup.h"
#include "color.h"


/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup() 
{
    printf("calling find_map_sizes()\n");
	find_map_sizes();
    printf("finished find_map_sizes\n");
    init_patches();
    init_color_values();
    printf("calling import_hydro\n");
    import_hydro();
    printf("finished import_hydro\n");
    setup_environmentals();
    setup_stocks();
    printf("SUCCESS -- setup\n");
}

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes() 
{    
    int max_map_width = 0;
    int max_map_height = 0;

    int index;
    for(index = 0; index < num_hydro_files; index++) 
	{
		FILE* file = fopen(gui_filenames_array[index], "r");
		if (file == NULL) 
		{
			fputs("error opening the hydro map", stderr);
			exit(-1);
		}

		find_map_width_height(file); // find the width and height of the maps
		if(MAP_WIDTH > max_map_width) 
		{
			max_map_width = MAP_WIDTH;
		}
		if(MAP_HEIGHT > max_map_height) 
		{
			max_map_height = MAP_HEIGHT;
		}
		
		fclose(file);
    }

    MAP_WIDTH = max_map_width;
    MAP_HEIGHT = max_map_height;
}


/**
 * Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * @param hydro_file the hydrolic file with data regarding patches
*/
void find_map_width_height(FILE* hydro_file) 
{
    int patch_info_size = 6;    // first line in the file, pxcor/pycor/depth/px-vector/py-vector/velocity
    int word_size = 100;

    char word[word_size];
    word[0] = '\0';

    int max_x = 0;
    int max_y = 0;
    int counter = 0;
    while(fscanf(hydro_file, "%s", word) != EOF) 
	{
        // pxcor
        if(counter%patch_info_size == 0) 
		{
            int value = atoi(word);
            if(value > max_x)
                    max_x = value;            
        }        
        // pycor
        else if(counter%patch_info_size == 1) 
		{
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
void init_patches() 
{
    // initialize the patches
    int row = 0;
    int col = 0;

	covered_area = (int*)malloc(num_unique_files*sizeof(int));
	uncovered_area = (int*)malloc(num_unique_files*sizeof(int));
    patches = malloc(MAP_WIDTH*sizeof(patch*));
    for(col = 0; col < MAP_WIDTH; col++) 
	{
        patches[col] = malloc(MAP_HEIGHT*sizeof(patch));
    }

    // initialize the arrays for each patch
    for(col = 0; col < MAP_WIDTH; col++)
	{
        for(row = 0; row < MAP_HEIGHT; row++) 
		{
            patches[col][row].max_vector = 0.0;
            patches[col][row].pxcor = col; 
            patches[col][row].pycor = row;
            patches[col][row].pcolor = 0;
            patches[col][row].current_depth = 0;

            patches[col][row].available = malloc(num_unique_files*sizeof(int));
            
            patches[col][row].pxv_list = malloc(num_unique_files*sizeof(double));
            patches[col][row].pyv_list = malloc(num_unique_files*sizeof(double));
            patches[col][row].depth_list = malloc(num_unique_files*sizeof(double));
            patches[col][row].v_list = malloc(num_unique_files*sizeof(double));
            int index;
            for(index = 0; index < num_unique_files; index++)
            {
              patches[col][row].pxv_list[index] = 0.0;
              patches[col][row].available[index] = 0;
              patches[col][row].pyv_list[index] = 0.0;
              patches[col][row].depth_list[index] = 0.0;
              patches[col][row].v_list[index] = 0.0;
            }
        }
    }
}

/**
 * Creates the 2D array of colors
 */
void init_color_values() 
{
    int row = 0;
    int col = 0;

	//initialize colors corresponding to each patch
    colorValues = malloc(MAP_WIDTH*sizeof(int*));
    for( col = 0; col < MAP_WIDTH; col++) 
	{
        colorValues[col] = malloc(MAP_HEIGHT*sizeof(int));       
    }   

    for( col = 0; col < MAP_WIDTH; col++) 
	{
        for(row = 0; row < MAP_HEIGHT; row++)
		{
            colorValues[col][row] = (255 << 16 ) | (255 << 8) | 255;  // white background
        }   
    }
}

int check_duplicate_files(int index)
{
  if(index == 0)
  {
    check_filenames_array[index] = (char*)malloc((strlen(gui_filenames_array[index]) + 1)*sizeof(char));
    strcpy(check_filenames_array[index], gui_filenames_array[index]);
    hydromap_index_array[index] = index;
    return 0;
  }
  int i;
  for(i = 0; i < current_file_index; i++)
  {
    // We found a duplicate file
    if(strcmp(check_filenames_array[i], gui_filenames_array[index]) == 0)
    {
      hydromap_index_array[index] = i;
      return 1;
    }
  }
  // Not a duplicate fil,e so add to the unique file array
  check_filenames_array[current_file_index] = (char*)malloc((strlen(gui_filenames_array[index]) + 1)*sizeof(char));
  strcpy(check_filenames_array[current_file_index], gui_filenames_array[index]);
  hydromap_index_array[index] = current_file_index;
  return 0;
}

/**
 * Reads the Hydro map files and sets up the proper (x,y) patches
 * Input is in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this word formation must be the first line in the file.
*/
void import_hydro() 
{
    int i, j, temp_x, temp_y;
    char file[256];
    FILE* pFile;
    char str[256];
    float value;
    double temp_depth, temp_px_vector, temp_py_vector, temp_velocity;
    char* path = hydrosets_path;

    for(i = 0;i < num_hydro_files; i++)
    {
        // Do not import a file we have already processed
        if(check_duplicate_files(i) == 1)
          continue;
        
        pFile = fopen(gui_filenames_array[i], "r");
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
		int covered_cells = 0;
		int uncovered_cells = 0;

        // Scan through the files and assign the values
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
            
            patches[temp_x][temp_y].available[current_file_index] = 1;
            patches[temp_x][temp_y].pxcor = temp_x;
            patches[temp_x][temp_y].pycor = temp_y;
            patches[temp_x][temp_y].pxv_list[current_file_index] = temp_px_vector;
            patches[temp_x][temp_y].pyv_list[current_file_index] = temp_py_vector;
            patches[temp_x][temp_y].v_list[current_file_index] = temp_velocity;
            patches[temp_x][temp_y].aqa_point = -999;
			patches[temp_x][temp_y].depth_list[current_file_index] = temp_depth;
			covered_cells++;
        }
		uncovered_cells = MAP_WIDTH*MAP_HEIGHT - covered_cells;
		covered_area[current_file_index] = max_area*covered_cells;
		uncovered_area[current_file_index] = max_area*uncovered_cells;
        current_file_index++;
        fclose(pFile);
    }

    int k;
    for(k = 0; k < current_file_index; k++)
      printf("%d ", hydromap_index_array[k]);
    printf("\n");

    //Read in the cell-type file and set the patches
    strcpy(file, cell_type_path);
    pFile = fopen(file, "r");

    if(pFile == NULL)
    {
        printf("Failed to open cell-type.txt");
        exit(1);
    }

    // Go through the cell-type.txt file and set the appropriate patches
    char temp_cell_type[256];

    // skip the file layout
    for(j = 0; j < 3; j++) 
	{
        fscanf(pFile, "%s", str);
    }

    while(fscanf(pFile, "%s", str) != EOF)
    {
        temp_x = atoi(str);
        fscanf(pFile, "%s", str);
        temp_y = atoi(str);
        fscanf(pFile, "%s", str);
        strcpy(temp_cell_type,  str);

        // assign the cell_type to the patches
        if(strcmp(temp_cell_type,"\"output\"") == 0)
        {
            patches[temp_x][temp_y].cell_type = 0;
        }
        else
        {
            patches[temp_x][temp_y].cell_type = 1;
        }
    }

    fclose(pFile);
}


/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 */
void setup_environmentals() 
{
	temp_dif = 0;
	par_dif = 0;
	set_photo_radiation();
	set_temperature();
}

/*
 * Reads the "par.txt" file and initializes the photo_radiation array variables
 */
void set_photo_radiation()
{
	char* pathname = environmentals_path;

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
	char* pathname = environmentals_path;

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
            if(patches[x][y].depth > 0.0)
            {
                patches[x][y].macro = 1.0;
                patches[x][y].phyto = 10.0;
                patches[x][y].waterdecomp = 10.0;
                patches[x][y].seddecomp = 1.0;
                patches[x][y].herbivore = 1.0;
                patches[x][y].sedconsumer = 1.0;
                patches[x][y].DOC = 10.0;
                patches[x][y].POC = 10.0;
                patches[x][y].detritus = 1.0;
                patches[x][y].consum = 0.1;
            }
        }
    }
}
