#include "main.h"
#include <stdio.h>
#include "setup.c"
#include "go.c"
#include "patch.c"
#include "dump.c"
#include "cleanup.c"
#include "globals.h"


/* Bind Python function names to our C functions */
static PyMethodDef MainModule_methods[] = {
    {"goCommand", py_goCommand, METH_VARARGS},
    {"extract_timestep_Command", py_extract_timestep, METH_VARARGS},
    {"extract_whichstock_Command", py_extract_whichstock, METH_VARARGS},
	{"extract_TSS_Command", py_extract_TSS, METH_VARARGS},
	{"extract_macro_base_temp_Command", py_extract_macro_base_temp, METH_VARARGS},
	{"extract_gross_macro_coef_Command", py_extract_gross_macro_coef, METH_VARARGS},
	{"extract_resp_macro_coef_Command", py_extract_resp_macro_coef, METH_VARARGS},
	{"extract_sen_macro_coef_Command", py_extract_sen_macro_coef, METH_VARARGS},
	{"extract_macro_mass_max_Command", py_extract_macro_mass_max, METH_VARARGS},
	{"extract_macro_vel_max_Command", py_extract_macro_vel_max, METH_VARARGS},
	{"extract_k_phyto_Command", py_extract_k_phyto, METH_VARARGS},
	{"extract_k_macro_Command", py_extract_k_macro, METH_VARARGS},
    {"setup_Command", py_setup_command, METH_VARARGS},
    {"cleanup_Command", py_cleanup_command, METH_VARARGS},
    {"extract_filenames_Command", py_extract_filenames, METH_VARARGS},
    {"extract_par_file_Command", py_extract_par_file, METH_VARARGS},
    {"extract_temperature_file_Command", py_extract_temperature_file, METH_VARARGS},
    {"extract_flowcorners_Command", py_extract_flow_corners, METH_VARARGS},
	{"extract_output_frequency", py_extract_output_frequency, METH_VARARGS},
    {NULL, NULL}
};

void count_unique_files(int index)
{
  int i;
  for(i = 0; i < index; i++)
  {
    if(strcmp(gui_filenames_array[i], gui_filenames_array[index]) == 0)
      return;
  }
  num_unique_files++;
}

static PyObject* py_extract_filenames(PyObject* self, PyObject* args) {
    char* filenames;
    PyArg_ParseTuple(args, "s", &filenames);
    char* filename;
    int index = 0;
    num_unique_files = 0;
    
    // First value howmany files the use selected in the GUI
    filename = strtok(filenames, "?");
    int fileSize = atoi(filename);
    gui_filenames_filesize = fileSize;
    num_hydro_files = fileSize;
    gui_filenames_array = (char**)malloc(fileSize*sizeof(char*));
    gui_days_array = (int*)malloc(fileSize*sizeof(int));
    hydromap_index_array = (int*)malloc(fileSize*sizeof(int));
    
    // Parse the file name if one exists
    while((filename = strtok(NULL, "?")) != NULL)
    {
        gui_filenames_array[index] = (char*)malloc((strlen(filename)+1)*sizeof(char));
        strcpy(gui_filenames_array[index],filename);
        count_unique_files(index);
        filename = strtok(NULL, "?");
        gui_days_array[index] = atoi(filename); //Parse howmany days to run current file
        index++;
    }
    
    check_filenames_array = (char**)malloc(num_unique_files*sizeof(char*));
    
    return Py_None;
}

static PyObject* py_extract_par_file(PyObject* self, PyObject* args) {
    char* filename;
    PyArg_ParseTuple(args, "s", &filename);
    strcpy(gui_photo_radiation_file, filename);
    return Py_None;
}

static PyObject* py_extract_timestep(PyObject* self, PyObject* args) {
    PyArg_ParseTuple(args, "i", &gui_timestep_factor);
    return Py_None;
}

static PyObject* py_extract_temperature_file(PyObject* self, PyObject* args) {
    char* filename;
    PyArg_ParseTuple(args, "s", &filename);
    strcpy(gui_temperature_file, filename);   
    return Py_None;
}

static PyObject* py_setup_command(){
  setup();
  return Py_None;
}

static PyObject* py_cleanup_command(){
  cleanup();
  return Py_None;
}

void output_image(){
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;

    // Build the name object
    pName = PyString_FromString("RiverImage");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, "output_image");
    if (PyCallable_Check(pFunc)) 
    {
		PyObject* list = (PyObject*)build_data();
		// parse the list into a tuple
		PyObject* pArgs = Py_BuildValue("(N)", list);
        pValue = PyObject_CallObject(pFunc, pArgs);
    } else 
    {
        PyErr_Print();
    }

    // Clean up - Python uses reference counting
    Py_DECREF(pModule);
    Py_DECREF(pName);
}

/** 
* TODO: update the comments of this function
* Computes the tss value and returns twice as much 
* @param self: the python object calling this C function
* @param args: the TSS slider value
* @return 2*TSS
*/
static PyObject* py_goCommand(PyObject* self, PyObject* args) {
	PyErr_Print();
    int day;
    int index;
    setup();
    
    gui_days_to_run = 0;
    for(index = 0; index < gui_filenames_filesize; index++)
    {
        printf("RUNNING FILE: %s FOR %d DAYS\n", gui_filenames_array[index], gui_days_array[index]);
        printf("FILE INDEX: %d\n", hydromap_index_array[index]);
        gui_days_to_run += gui_days_array[index];  //Set howmany days to run the new hydromap
        hydro_group = (hydromap_index_array[index] + 1); //Set the new hydromap that will run
        hydro_changed = 1;  //Confirm that a new hydro map has been loaded
        
        while( (day = (hours / 24)) < gui_days_to_run)
        {   
            printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
            go();
        }   
        printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
    }
    PyObject* data = (PyObject*)build_data();    
    if (!dump_data()) {
        printf("Could not create folder './results' and write the data from the patches\n");
    }
    cleanup();
    return data;
}

/**
 * Extracts the whichstocks value from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The whichstock value
 */
static PyObject* py_extract_whichstock(PyObject* self, PyObject* args)
{
    char* str;
    PyArg_ParseTuple(args, "s", &str);
    strcpy(which_stock,str);
    Py_INCREF(Py_None);
    return Py_None;
}

/**
 * Extracts the TSS value from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The TSS slider value
*/
static PyObject* py_extract_TSS(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_tss);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the macro_base_temp value from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The macro_base_temp slider value
*/
static PyObject* py_extract_macro_base_temp(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_macro_base_temp);

	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the gross_macro_coef from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The gross_macro_coef slider value
*/
static PyObject* py_extract_gross_macro_coef(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_gross_macro_coef);

	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the resp_macro_coef from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The resp_macro_coef slider value
*/
static PyObject* py_extract_resp_macro_coef(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_resp_macro_coef);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the sen_macro_coef from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The sen_macro_coef slider value
*/
static PyObject* py_extract_sen_macro_coef(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_sen_macro_coef);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the macro_mass_max from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The macro_mass_max slider value
*/
static PyObject* py_extract_macro_mass_max(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "i", &gui_macro_mass_max);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the macro_vel_max from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The macro_vel_max slider value
*/
static PyObject* py_extract_macro_vel_max(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_macro_vel_max);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the k_phyto from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The k_phyto slider value
*/
static PyObject* py_extract_k_phyto(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_k_phyto);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the k_macro from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The k_macro slider value
*/
static PyObject* py_extract_k_macro(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "d", &gui_k_macro);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* py_extract_output_frequency(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "i", &output_frequency);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* py_extract_flow_corners(PyObject* self, PyObject* args)
{
    PyArg_ParseTuple(args, "i", &gui_flow_corners_only);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* build_data(){
    int size = MAP_WIDTH*MAP_HEIGHT + 2;
    int index;
    PyObject* list = PyList_New(size);
    if(!list)
        return NULL;
    PyObject* num =  Py_BuildValue("i", MAP_WIDTH);
    PyList_SET_ITEM(list, 0, num);
	num = Py_BuildValue("f", hue);
	PyList_SET_ITEM(list, 1, num);
    for(index = 2; index < size; index++)
    {
        num = Py_BuildValue("f", colorValues[(index-1)%MAP_WIDTH][(index-1)/MAP_WIDTH]);
        PyList_SET_ITEM(list, index, num);
    }
    return list;
}

/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
