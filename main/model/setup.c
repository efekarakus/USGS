#include "globals.h"
#include "setup.h"
#include "color.h"


/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup() 
{
	reset_globals();
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
 * Resets all the values in globals.h
 */
void reset_globals() 
{
	MAP_WIDTH = 0;
	MAP_HEIGHT = 0;
	hours = 0;
	COMPARE_MAX = 0.0;

	current_file_index = 0;

	temp_dif = 0.0;
	par_dif = 0.0;

	nan_trigger = 0;

	MAX_MACRO = 0.0;
	MAX_PHYTO = 0.0;
	MAX_HERBIVORE = 0.0;
	MAX_WATERDECOMP = 0.0;
	MAX_SEDDECOMP = 0.0;
	MAX_SEDCONSUMER = 0.0;
	MAX_CONSUM = 0.0;
	MAX_DOC = 0.0;
	MAX_POC = 0.0;
	MAX_DETRITUS = 0.0;

	max_waterdecomp = 6.26/24.0;
	max_seddecomp = 6.26/24.0;
	max_herbivore = 1.0/24.0;
	herbivore_egestion = 0.2;
	max_sedconsumer = 0.55/24.0;
	sedconsumer_egestion_seddecomp = 0.35;
	max_consum = 0.125/24.0;
	e_waterdecomp = 0.173/24.0;
	e_seddecomp = 0.173/24.0;
	e_herbivore = 0.4/24.0;
	e_sedconsumer = 0.01/24.0;
	sedconsumer_egestion_detritus = 0.9;
	e_consum = 0.0032/24.0;
	r_waterdecomp = 0.6/24.0;
	r_seddecomp = 0.6/24.0;
	r_herbivore = 0.08/24.0;
	r_sedconsumer = 0.04/24.0;
	r_consum = 0.0125/24.0;
	s_waterdecomp = 0.05/24.0;
	s_seddecomp = 0.05/24.0;
	s_herbivore = 0.01/24.0;
	s_sedconsumer = 0.01/24.0;
	s_consum = 0.002/24.0;
	consum_egestion = 0.2;

	Ai_waterdecomp_DOC = 30.0;
	Ai_waterdecomp_POC = 30.0;
	Ai_Peri_DOC = 30.0;
	Ai_Peri_POC = 30.0;
	Ai_seddecomp_detritus = 0.6;
	Ai_herbivore_phyto = 20;
	Ai_herbivore_waterdecomp = 3.0;
	Ai_herbivore_peri = 3.0;
	Ai_sedconsumer_seddecomp = 3.0;
	Ai_sedconsumer_peri = 2.0;
	Ai_sedconsumer_detritus = 3.5;
	Ai_consum_herbivore = 3.5;
	Ai_consum_sedconsumer = 4.0;
	Gi_waterdecomp_DOC = 0.05;
	Gi_waterdecomp_POC = 0.05;
	Gi_Peri_DOC = 0.05;
	Gi_Peri_POC = 0.05;
	Gi_seddecomp_detritus = 0.005;
	Gi_herbivore_phyto = 0.01;
	Gi_herbivore_waterdecomp = 0.01;
	Gi_herbivore_peri = 0.01;
	Gi_sedconsumer_seddecomp = 0.02;
	Gi_sedconsumer_peri = 0.02;
	Gi_sedconsumer_detritus = 0.02;
	Gi_consum_herbivore = 0.025;
	Gi_consum_sedconsumer = 0.04;
	pref_waterdecomp_DOC = 0.5;
	pref_waterdecomp_POC = 0.5;
	pref_Peri_DOC = 0.5;
	pref_Peri_POC = 0.5;
	pref_seddecomp_detritus = 1.0;
	pref_herbivore_phyto = 0.7;
	pref_herbivore_waterdecomp = 0.15;
	pref_herbivore_peri = 0.15;
	pref_sedconsumer_seddecomp = 0.5;
	pref_sedconsumer_peri = 0.4;
	pref_sedconsumer_detritus = 0.1;
	pref_consum_herbivore = 0.7;
	pref_consum_sedconsumer = 0.3;

	Aj_phyto = 10.0;
	Aj_waterdecomp = 1.2;
	Aj_seddecomp = 0.2;
	Aj_herbivore = 2.4;
	Aj_sedconsumer = 2.0;
	Aj_consum = 0.65;
	Gj_phyto = 100.0;
	Gj_waterdecomp = 20.0;
	Gj_seddecomp = 120.0;
	Gj_herbivore = 108.0;
	Gj_sedconsumer = 20.0;
	Gj_consum = 6.5;

	k_herbivore = 0.2;
	k_POC = 0.2;

	theta = 1.072;

	macro_base_temp = 19.7;
	TSS = 10.0;
	gross_macro_coef = 0.08;
	resp_macro_coef = 0.04;
	sen_macro_coef = 0.08;
	macro_mas_max = 1000.0;
	macro_vel_max = 1.0;
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

void init_patch_values(int col, int row){

	patches[col][row].max_vector = 0.0;
    patches[col][row].pxcor = col; 
    patches[col][row].pycor = row;
    patches[col][row].pcolor = 0;
    patches[col][row].current_depth = 0;
	patches[col][row].px_vector = 0.0;
	patches[col][row].py_vector = 0.0;
	patches[col][row].max_vector = 0.0;
	patches[col][row].depth = 0.0;
	patches[col][row].current_depth = 0.0;
	patches[col][row].velocity = 0.0;
	patches[col][row].aqa_point = 0;
	patches[col][row].waterdecomp_doc_prey_limitation = 0.0;
	patches[col][row].waterdecomp_poc_prey_limitation = 0.0;
	patches[col][row].peri_doc_prey_limitation = 0.0;
	patches[col][row].peri_poc_prey_limitation = 0.0;
	patches[col][row].seddecomp_detritus_prey_limitation = 0.0;
	patches[col][row].herbivore_phyto_prey_limitation = 0.0;
	patches[col][row].herbivore_waterdecomp_prey_limitation = 0.0;
	patches[col][row].herbivore_peri_prey_limitation = 0.0;
	patches[col][row].sedconsumer_seddecomp_prey_limitation = 0.0;
	patches[col][row].sedconsumer_peri_prey_limitation = 0.0;
	patches[col][row].sedconsumer_detritus_prey_limitation = 0.0;
	patches[col][row].consum_herbivore_prey_limitation = 0.0;
	patches[col][row].consum_sedconsumer_prey_limitation = 0.0;
	
	patches[col][row].peri_space_limitation = 0.0;
	patches[col][row].waterdecomp_space_limitation = 0.0;
	patches[col][row].seddecomp_space_limitation = 0.0;
	patches[col][row].herbivore_space_limitation = 0.0;
	patches[col][row].sedconsumer_space_limitation = 0.0;
	patches[col][row].consum_space_limitation = 0.0;
	patches[col][row].assimilation = 0.0;
	patches[col][row].detritus = 0.0;
	patches[col][row].DOC = 0.0;
	patches[col][row].POC = 0.0;
	patches[col][row].waterdecomp = 0.0;
	patches[col][row].seddecomp = 0.0;
	patches[col][row].macro = 0.0;
	patches[col][row].phyto = 0.0;
	patches[col][row].herbivore = 0.0;
	patches[col][row].sedconsumer = 0.0;
	patches[col][row].peri = 0.0;
	patches[col][row].consum = 0.0;
	patches[col][row].bottom_light = 0.0;
	patches[col][row].consumer = 0.0;
	patches[col][row].consum_consumption = 0.0;
	patches[col][row].consum_ingest_herbivore = 0.0;
	patches[col][row].consum_pred_herbivore = 0.0;
	patches[col][row].consum_ingest_sedconsumer = 0.0;
	patches[col][row].consum_pred_sedconsumer = 0.0;
	patches[col][row].consum_excretion = 0.0;
	patches[col][row].consum_sda = 0.0;
	patches[col][row].consum_senescence = 0.0;
	patches[col][row].consum_respiration = 0.0;
	patches[col][row].consum_growth = 0.0;
	patches[col][row].detritus_growth = 0.0;
	patches[col][row].detritus_POC_transfer = 0.0;
	patches[col][row].seddecomp_pred_detritus = 0.0;
	patches[col][row].sedconsumer_pred_detritus = 0.0;
	patches[col][row].direction = 0.0;
	patches[col][row].DOC_growth = 0.0;
	patches[col][row].DOC_pred = 0.0;
	patches[col][row].egestion = 0.0;
	patches[col][row].excretion = 0.0;
	patches[col][row].excretion_phyto = 0.0;
	patches[col][row].flocculation = 0.0;
	patches[col][row].gross_photo = 0.0;
	patches[col][row].gross_photo_macro = 0.0;
	patches[col][row].gross_photo_phyto = 0.0;
	patches[col][row].growth_herbivore = 0.0;
	patches[col][row].growth_detritus = 0.0;
	patches[col][row].growth_macro = 0.0;
	patches[col][row].growth_sedconsumer = 0.0;
	patches[col][row].growth_phyto = 0.0;
	patches[col][row].growth_waterdecomp = 0.0;
	patches[col][row].herbivore_consumption = 0.0;
	patches[col][row].herbivore_ingest_peri = 0.0;
	patches[col][row].herbivore_pred_peri = 0.0;
	patches[col][row].herbivore_ingest_phyto = 0.0;
	patches[col][row].herbivore_pred_phyto = 0.0;
	patches[col][row].herbivore_ingest_waterdecomp = 0.0;
	patches[col][row].herbivore_pred_waterdecomp = 0.0;
	patches[col][row].herbivore_excretion = 0.0;
	patches[col][row].herbivore_sda = 0.0;
	patches[col][row].herbivore_senescence = 0.0;
	patches[col][row].herbivore_respiration = 0.0;
	patches[col][row].herbivore_growth = 0.0;
	patches[col][row].K = 0.0;
	patches[col][row].large_death = 0.0;
	patches[col][row].light = 0.0;
	patches[col][row].light_k = 0.0;
	patches[col][row].macro_death = 0.0;
	patches[col][row].macro_exudation = 0.0;
	patches[col][row].micro_death = 0.0;
	patches[col][row].phyto_maximum_growth_rate = 0.0;
	patches[col][row].phyto_pred = 0.0;
	patches[col][row].POC_detritus_transfer = 0.0;
	patches[col][row].POC_growth = 0.0;
	patches[col][row].POC_pred = 0.0;
	patches[col][row].phyto_density = 0.0;
	patches[col][row].peri_ingest_doc = 0.0;
	patches[col][row].peri_pred_doc = 0.0;
	patches[col][row].peri_ingest_poc = 0.0;
	patches[col][row].peri_pred_poc = 0.0;
	patches[col][row].peri_respiration = 0.0;
	patches[col][row].peri_excretion = 0.0;
	patches[col][row].peri_senescence = 0.0;
	patches[col][row].senescence = 0.0;
	patches[col][row].scouring = 0.0;
	patches[col][row].small_death = 0.0;
	patches[col][row].respiration = 0.0;
	patches[col][row].respiration_macro = 0.0;
	patches[col][row].respiration_phyto = 0.0;
	patches[col][row].scouring_macro = 0.0;
	patches[col][row].sedconsumer_ingest_peri = 0.0;
	patches[col][row].sedconsumer_pred_peri = 0.0;
	patches[col][row].senescence_macro = 0.0;
	patches[col][row].senescence_phyto = 0.0;
	patches[col][row].sedconsumer_consumption = 0.0;
	patches[col][row].sedconsumer_ingest_detritus = 0.0;
	patches[col][row].sedconsumer_ingest_seddecomp = 0.0;
	patches[col][row].sedconsumer_pred_seddecomp = 0.0;
	patches[col][row].sedconsumer_excretion = 0.0;
	patches[col][row].sedconsumer_egestion = 0.0;
	patches[col][row].sedconsumer_senescence = 0.0;
	patches[col][row].sedconsumer_respiration = 0.0;
	patches[col][row].sedconsumer_growth = 0.0;
	patches[col][row].seddecomp_consumption = 0.0;
	patches[col][row].seddecomp_ingest_detritus = 0.0;
	patches[col][row].seddecomp_excretion = 0.0;
	patches[col][row].seddecomp_growth = 0.0;
	patches[col][row].seddcomp_ingest_peri = 0.0;
	patches[col][row].seddecomp_pred_peri = 0.0;
	patches[col][row].seddecomp_respiration = 0.0;
	patches[col][row].seddecomp_senescence = 0.0;
	patches[col][row].velpoc = 0.0;
	patches[col][row].waterdecomp_consumption = 0.0;
	patches[col][row].waterdecomp_ingest_doc = 0.0;
	patches[col][row].waterdecomp_sda = 0.0;
	patches[col][row].waterdecomp_excretion = 0.0;
	patches[col][row].waterdecomp_ingest_poc = 0.0;
	patches[col][row].waterdecomp_pred_doc = 0.0;
	patches[col][row].waterdecomp_pred_poc = 0.0;
	patches[col][row].waterdecomp_respiration = 0.0;
	patches[col][row].waterdecomp_senescence = 0.0;
	patches[col][row].turbidity = 0.0;


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
			init_patch_values(col, row);
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
      printf("%d ", hydromap_index_array[k]); //TODO problem here on second run
    printf("\n");
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
