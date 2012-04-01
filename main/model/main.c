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
	{"extract_days_to_run_Command", py_extract_days_to_run, METH_VARARGS},
	{"extract_TSS_Command", py_extract_TSS, METH_VARARGS},
	{"extract_macro_base_temp_Command", py_extract_macro_base_temp, METH_VARARGS},
	{"extract_gross_macro_coef_Command", py_extract_gross_macro_coef, METH_VARARGS},
	{"extract_resp_macro_coef_Command", py_extract_resp_macro_coef, METH_VARARGS},
	{"extract_sen_macro_coef_Command", py_extract_sen_macro_coef, METH_VARARGS},
	{"extract_macro_mass_max_Command", py_extract_macro_mass_max, METH_VARARGS},
	{"extract_macro_vel_max_Command", py_extract_macro_vel_max, METH_VARARGS},
	{"extract_k_phyto_Command", py_extract_k_phyto, METH_VARARGS},
	{"extract_k_macro_Command", py_extract_k_macro, METH_VARARGS},
	{"extract_fixed_temperature_Command", py_extract_fixed_temperature, METH_VARARGS},
    {"extract_fixed_photo_radiation_Command", py_extract_fixed_photo_radiation, METH_VARARGS},
    {"setup_Command", py_setup_command, METH_VARARGS},
    {"cleanup_Command", py_cleanup_command, METH_VARARGS},
    {"extract_filenames_Command", py_extract_filenames, METH_VARARGS},
    {NULL, NULL}
};


static PyObject* py_extract_filenames(PyObject* self, PyObject* args) {
  char* filename;
  PyArg_ParseTuple(args, "s", &filename);
  printf("Selected File: %s\n", filename);
  hydro_group = atoi(filename)/10;
  hydro_changed = 1;
  return Py_None;
}

static PyObject* py_setup_command(){
  setup();
  return Py_None;
}

static PyObject* py_cleanup_command(){
  cleanup();
  printf("Finished Cleaning!\n");
  return Py_None;
}

/** 
* TODO: update the comments of this function
* Computes the tss value and returns twice as much 
* @param self: the python object calling this C function
* @param args: the TSS slider value
* @return 2*TSS
*/
static PyObject* py_goCommand(PyObject* self, PyObject* args) {

    //TODO: remove this section
    //int tss;
    //PyArg_ParseTuple(args, "i", &tss);
    //tss = 2*tss;
    printf("MAX_PHYTO: %f\n", MAX_PHYTO);

    int day;
    //setup();
    while( (day = (hours / 24)) < gui_days_to_run)
    {   
        printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
        go();
    }   
    printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
    PyObject* data = (PyObject*)build_data();    
    if (!dump_data()) {
        printf("Could not create folder './results' and write the data from the patches\n");
    }   
    //cleanup();
    return data;
}

/**
 * Extracts the days to run value from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The days to run input value
*/
static PyObject* py_extract_days_to_run(PyObject* self, PyObject* args)
{
	char* read_String;

	PyArg_ParseTuple(args, "s", &read_String);
	
	int read_Int = atoi(read_String);
	gui_days_to_run += read_Int;

	printf("\n\nDAYS TO RUN: %d\n", gui_days_to_run);
	
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
	PyArg_ParseTuple(args, "i", &gui_tss);
	printf("\n\nTSS: %d\n", gui_tss);
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

	printf("\n\nMACRO_BASE_TEMP: %f\n", gui_macro_base_temp);
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

	printf("\n\nGROSS_MACRO_COEF: %f\n", gui_gross_macro_coef);
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
	printf("\n\nRESP_MACRO_COEF: %f\n", gui_resp_macro_coef);
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
	printf("\n\nSEN_MACRO_COEF: %f\n", gui_sen_macro_coef);
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
	printf("\n\nMACRO_MASS_MAX: %d\n", gui_macro_mass_max);
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
	printf("\n\nMACRO_VEL_MAX: %f\n", gui_macro_vel_max);
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
	printf("\n\nK_PHYTO: %f\n", gui_k_phyto);
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
	printf("\n\nK_MACRO: %f\n", gui_k_macro);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the fixed_temp from the Gui and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The fixed_temp slider value
*/
static PyObject* py_extract_fixed_temperature(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "i", &gui_temperature);
	printf("\n\nTEMPERATURE: %d\n", gui_temperature);
	Py_INCREF(Py_None);
	return Py_None;
}


/**
 * Extracts the fixed_photo_radiation from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @args The fixed_photo_radiation slider value
*/
static PyObject* py_extract_fixed_photo_radiation(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "i", &gui_photo_radiation);
	printf("\n\nPHOTO RADIATION: %d\n", gui_photo_radiation);
	Py_INCREF(Py_None);
	return Py_None;
}

/**
 * Extracts the selected hydro map and days to run pair from the GUI
 * @param self The python object calling this C function
 * @args The hydro_map slider value
 */
 static PyObject* py_extract_hydro_map(PyObject* self, PyObject* args)
 {
    PyArg_ParseTuple(args, "i", &gui_hydro_group);
    printf("\n\nHYDRO MAP: %d\n", gui_hydro_group);
    Py_INCREF(Py_None);
    return Py_None;
 }


PyObject* build_data(){
    int size = MAP_WIDTH*MAP_HEIGHT + 1;
    int index;
    PyObject* list = PyList_New(size);
    if(!list)
        return NULL;

    PyObject* num =  Py_BuildValue("i", MAP_WIDTH);
    PyList_SET_ITEM(list, 0, num);
    for(index = 1; index < size; index++)
    {
        num = Py_BuildValue("i", colorValues[(index-1)%MAP_WIDTH][(index-1)/MAP_WIDTH]);
        PyList_SET_ITEM(list, index, num);
    }
    return list;
}

/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
