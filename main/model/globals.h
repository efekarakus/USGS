#ifndef _GLOBALS
#define _GLOBALS

#include "patch.h"


// Model variables
int MAP_WIDTH;  ///< the map's width
int MAP_HEIGHT; ///< the map's height
long hours = 0;	///< Represents 1 tick (should always be [0, sizeof(long)]
double COMPARE_MAX = 0.0; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step

// GUI variables
int output_frequency = 0;
int current_day = 0; ///< Keeps track of how often output should be generated
char* file_extension = "new";
int num_hydro_files = 0;
char gui_photo_radiation_file[1024];
char gui_temperature_file[1024];
int gui_flow_corners_only = 0;
int gui_timestep_factor = 60;    ///< By how much are we speeding up the code? Increasing the factor will reduce the number of iterations required
int gui_days_to_run = 0;  ///< number of days to run the code
double gui_tss = 0.0;  ///< TSS
double gui_k_phyto = 0.4;  ///< k-phyto
double gui_k_macro = 0.4; ///< k-macro
double gui_sen_macro_coef = 0.08; ///< sen-macro-coef
double gui_resp_macro_coef = 0.04; ///< resp-macro-coef
double gui_macro_base_temp = 19.7; ///< macro-base-temp
double gui_macro_mass_max = 1000; ///< macro-mass-max
double gui_macro_vel_max = 1.0; ///< macro-vel-max
double gui_gross_macro_coef = 0.08; // gross-macro-coef
char which_stock[100]; ///< which-stock?

// GUI input hydro maps and days for each map
char** gui_filenames_array;
int* gui_days_array;
int* hydromap_index_array;
int num_unique_files = 0;
int current_file_index = 0;
char** check_filenames_array;
int gui_filenames_filesize;

// Environmental globals
double* temperature_data;	///< temp array which holds data that temp indexes
int* photo_radiation_data;	///< par array which holds data that photo_radiation indexes
int* covered_area;      ///< Area of land covered by water
int* uncovered_area;    ///< Area of land not covered by water

int temperature_index;	///< The index of the current temperature value
int photo_radiation_index;	///< The index of the current photo_radiation value

double temperature;	///< temp
int photo_radiation;	///< photo_radiation

int hydro_group;	///< hydro-group
int hydro_changed = 0;  //boolean stating if the hydro map was changed
double temp_dif = 0;	///< The percent difference from 17 degrees Celsius. (Used in update_temp)
double par_dif = 0;	///< The percent difference in par. (Used in update_par)

int nan_trigger = 0;  ///< 1 if there is a NaN value in the DOC values 0 otherwise

// convert ft to m from the SMS to .png scaling conversion
int patch_length = 30;
int max_area = 30*30;

// max gwr/unit biomass; e- excretion->DOC; r- respiration; s- senecence(natural mortality); -egestion ->POC
double MAX_MACRO = 0.0;
double MAX_PHYTO = 0.0;
double MAX_HERBIVORE = 0.0;
double MAX_WATERDECOMP = 0.0;
double MAX_SEDDECOMP = 0.0;
double MAX_SEDCONSUMER = 0.0;
double MAX_CONSUM = 0.0;
double MAX_DOC = 0.0;
double MAX_POC = 0.0;
double MAX_DETRITUS = 0.0;


double max_waterdecomp = 6.26/24.0;
double max_seddecomp = 6.26/24.0;
double max_herbivore = 1.0/24.0;
double herbivore_egestion = 0.2;
double max_sedconsumer = 0.55/24.0;
double sedconsumer_egestion_seddecomp = 0.35;
double max_consum = 0.125/24;
double e_waterdecomp = 0.173/24;
double e_seddecomp = 0.173/24;
double e_herbivore = 0.4/24;
double e_sedconsumer = 0.01/24;
double sedconsumer_egestion_detritus = 0.9;
double e_consum = 0.0032/24;
double r_waterdecomp = 0.6/24;
double r_seddecomp = 0.6/24;
double r_herbivore = 0.08/24;
double r_sedconsumer = 0.04/24;
double r_consum = 0.0125/24;
double s_waterdecomp = 0.05/24;
double s_seddecomp = 0.05/24;
double s_herbivore = 0.01/24;
double s_sedconsumer = 0.01/24;
double s_consum = 0.002/24;
double consum_egestion = 0.2;

// below variables are ripe for sensitivity analysis
// prey parameters - Ai and Gi, coded 1 -> 0
double Ai_waterdecomp_DOC = 30.0;
double Ai_waterdecomp_POC = 30.0;
double Ai_Peri_DOC = 30.0;
double Ai_Peri_POC = 30.0;
double Ai_seddecomp_detritus = 0.6;
double Ai_herbivore_phyto = 20;
double Ai_herbivore_waterdecomp = 3.0;
double Ai_herbivore_peri = 3.0;
double Ai_sedconsumer_seddecomp = 3.0;
double Ai_sedconsumer_peri = 2.0;
double Ai_sedconsumer_detritus = 3.5;
double Ai_consum_herbivore = 3.5;
double Ai_consum_sedconsumer = 4.0;
double Gi_waterdecomp_DOC = 0.05;
double Gi_waterdecomp_POC = 0.05;
double Gi_Peri_DOC = 0.05;
double Gi_Peri_POC = 0.05;
double Gi_seddecomp_detritus = 0.005;
double Gi_herbivore_phyto = 0.01;
double Gi_herbivore_waterdecomp = 0.01;
double Gi_herbivore_peri = 0.01;
double Gi_sedconsumer_seddecomp = 0.02;
double Gi_sedconsumer_peri = 0.02;
double Gi_sedconsumer_detritus = 0.02;
double Gi_consum_herbivore = 0.025;
double Gi_consum_sedconsumer = 0.04;
double pref_waterdecomp_DOC = 0.5;
double pref_waterdecomp_POC = 0.5;
double pref_Peri_DOC = 0.5;
double pref_Peri_POC = 0.5;
double pref_seddecomp_detritus = 1.0;
double pref_herbivore_phyto = 0.7;
double pref_herbivore_waterdecomp = 0.15;
double pref_herbivore_peri = 0.15;
double pref_sedconsumer_seddecomp = 0.5;
double pref_sedconsumer_peri = 0.4;
double pref_sedconsumer_detritus = 0.1;
double pref_consum_herbivore = 0.7;
double pref_consum_sedconsumer = 0.3;

// peri updated every timestep based on macro density  
// density dependent crowding effects on linear scale - capped at Aj and Gj - coded 1->0  
double Aj_phyto = 10.0;
double Aj_waterdecomp = 1.2;
double Aj_seddecomp = 0.2;
double Aj_herbivore = 2.4;
double Aj_sedconsumer = 2.0;
double Aj_consum = 0.65;
double Aj_peri;
double Gj_phyto = 100.0;
double Gj_waterdecomp = 20.0;
double Gj_seddecomp = 120.0;
double Gj_herbivore = 108.0;
double Gj_sedconsumer = 20.0;
double Gj_consum = 6.5;
double Gj_peri;

// set k-macro .4 -> taken from interface
// set k-phyto .4 -> taken from interface
double k_herbivore = 0.2;
double k_POC = 0.2;

double theta = 1.072;

//temperatue dependent coefficient for aquatic plants
double Q10;
//Slider variables
double macro_base_temp = 19.7;
double gross_macro_coef = 0.08;
double resp_macro_coef = 0.04;
double sen_macro_coef = 0.08;
double macro_mas_max = 1000.0;
double macro_vel_max = 1.0;


#endif
