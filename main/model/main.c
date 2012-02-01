#include "main.h"
#include <stdio.h>
#include "setup.c"
#include "go.c"
#include "patch.c"
#include "cleanup.c"
#include "globals.h"

/* Bind Python function names to our C functions */
static PyMethodDef MainModule_methods[] = {
    {"goCommand", py_goCommand, METH_VARARGS},
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
	{NULL, NULL}
};


/** 
 * TODO: update the comments of this function
 * Computes the tss value and returns twice as much 
 * @param self: the python object calling this C function
 * @param args: the TSS slider value
 * @return 2*TSS
 */
static PyObject* py_goCommand(PyObject* self, PyObject* args) {

    //TODO: remove this section
    int tss;
    PyArg_ParseTuple(args, "i", &tss);
    tss = 2*tss;

    int day;
    setup();
    while( (day = (hours / 24)) < gui_days_to_run)
    {
        printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
	    go();
    }
    printf("Day number: %d, MAX_PHYTO: %f\n", day, MAX_PHYTO);
    PyObject* data = (PyObject*)build_data();                                                  
    cleanup();
    return data;
}


/**
 * Extracts the TSS value from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The TSS slider value
*/
static PyObject* py_extract_TSS(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "i", &gui_tss);

	printf("\n\nTHIS IS THE VALUE OF TSS (Tom is awesome): %d\n", gui_tss);
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
