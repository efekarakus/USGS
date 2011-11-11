#include "setup.h"
#include "string.h"
#include <stdio.h>

/**
 * Reads one of the 
 */
void init_patches() {

}

/**
 * TODO: Nathan and Chris
 */
void import_hydro() {
    // Read the files
    int i, j;
    char file[256];
    FILE* pFile;
    char* str;
    double value;
    // Append the extension to each file
    for(i = 0;i < 10; i++)
    {
        strcpy(file, file_name[i]);
        strcat(file, file_extension);
        pFile = fopen(file, "r");
        
	// Skip the file layout
        for(j = 0; j < 6; j++){
            fscanf(pFile, "%s", str);
        }

        while(fscanf(pFile, "%s", str) != EOF)
        {
            value = atoi(str);
        }
    }
}

/**
 * TODO: Tom and Efe
 */
void setup_environmentals() 
{

}
/**
 * Calls the helper functions import_hydro and setup_environmentals
 * TODO: detailed comments
 */
void setup() {
    init_patches();
    import_hydro();
    setup_environmentals();
}

