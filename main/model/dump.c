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
	char buffer[80];
	//strftime(buffer, 80, "%b_%a_%d_%I:%M:%S%p", timeinfo);
	strftime(buffer, 80, "%b_%a_%d_%I_%M_%S", timeinfo);
	
    char file_name[300]; file_name[0] = '\0';
    strcat(file_name,data_path);
    strcat(file_name,data_template);
    //strcat(file_name, asctime(timeinfo) );
	strcat(file_name, buffer);
    strcat(file_name, format);
	
	file_name[strlen(file_name)] = '\0';
    FILE* f = fopen(file_name, "w");
    if (f == NULL) { 
        printf("file name: %s could not be opened\n", file_name);
        return 0;
    }

    // GUI variables used    
    fprintf(f,"%s\n","# timestep_factor,hydro_group,days_to_run,tss,k_phyto,k_macro,sen_macro_coef,resp_macro_coef,macro_base_temp,macro_mass_max,macro_vel_max,gross_macro_coef,which_stock");
    
    fprintf(f,"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%s\n",gui_timestep_factor,gui_days_to_run,gui_tss,gui_k_phyto,gui_k_macro,gui_sen_macro_coef
                                                              ,gui_resp_macro_coef,gui_macro_base_temp,gui_macro_mass_max
                                                              ,gui_macro_vel_max,gui_gross_macro_coef,which_stock);
    
    fprintf(f,"%s\n","# pxcor,pycor,pcolor,px_vector,py_vector,depth,velocity,assimilation,detritus,DOC,POC,waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum");

    int x,y;
    int pxcor,pycor,pcolor;
    double px_vector,py_vector,depth,velocity;
    double assimilation,detritus,DOC,POC,waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum;

    for(x = 0; x < MAP_WIDTH; x++) {
        for(y=0;y < MAP_HEIGHT; y++) {
            pxcor = patches[x][y].pxcor;
            pycor = patches[x][y].pycor;
            pcolor = patches[x][y].pcolor;
            px_vector = patches[x][y].px_vector;
            py_vector = patches[x][y].py_vector;
            depth = patches[x][y].depth;
            velocity = patches[x][y].velocity;
            assimilation = patches[x][y].assimilation;
            detritus = patches[x][y].detritus;
            DOC = patches[x][y].DOC;
            POC = patches[x][y].POC;
            waterdecomp = patches[x][y].waterdecomp;
            seddecomp = patches[x][y].seddecomp;
            macro = patches[x][y].macro;
            phyto = patches[x][y].phyto;
            herbivore = patches[x][y].herbivore;
            sedconsumer = patches[x][y].sedconsumer;
            peri = patches[x][y].peri;
            consum = patches[x][y].consum;


            fprintf(f,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",pxcor,pycor,pcolor,px_vector,py_vector,depth,
                      velocity,assimilation,detritus,DOC,POC,
                      waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum);
        }
    }
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
