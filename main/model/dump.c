#include "dump.h"

/**
 * The file format is as follows:
 * First line: GUI_VARIABLES separated by a comma
 * Each line represents one coordinate (x,y) in the River and holds the values of the DOCs in a patch.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int write_data() {
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char file_name[300]; file_name[0] = '\0';
    strcat(file_name,data_path);
    strcat(file_name,data_template);
    strcat(file_name, asctime(timeinfo) );
    strcat(file_name, format);

    FILE* f = fopen(file_name, "w");
    if (!f) { 
        printf("file name: %s could not be opened\n", file_name);
        return 0;
    }

    // GUI variables used
    /*
    fprintf(f,"%s\n","# timestep_factor,temperature,photo_radiation,hydro_group,days_to_run,tss, \ 
                      k_phyto,k_macro,sen_macro_coef,resp_macro_coef,macro_base_temp,macro_mass_max,macro_vel_max \
                        ,gross_macro_coef,which_stock");
    */
    fprintf(f,"%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%d,%f,%f,%s\n",gui_timestep_factor,gui_temperature,gui_photo_radiation,gui_hydro_group
                                                              ,gui_days_to_run,gui_tss,gui_k_phyto,gui_k_macro,gui_sen_macro_coef
                                                              ,gui_resp_macro_coef,gui_macro_base_temp,gui_macro_mass_max
                                                              ,gui_macro_vel_max,gui_gross_macro_coef,which_stock);

    fclose(f);
    return 1;
}

/**
 * Creates a folder <data_path> and places all the results from running the model into this file.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int dump_data() {
    return write_data();
}
