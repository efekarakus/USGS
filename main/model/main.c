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
	{"extract_macro_base_temp", py_extract_macro_base_temp, METH_VARARGS},
	{"extract_gross_macro_coef", py_extract_gross_macro_coef, METH_VARARGS},
	{"extract_resp_macro_coef", py_extract_resp_macro_coef, METH_VARARGS},
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
	PyArg_ParseTuple(args, "f", &gui_macro_base_temp);

	printf("\n\nTHIS IS THE VALUE OF MACRO_BASE_TEMP: %f\n", gui_macro_base_temp);

}


/**
 * Extracts the gross_macro_coef from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The gross_macro_coef slider value
*/
static PyObject* py_extract_gross_macro_coef(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "f", &gui_gross_macro_coef);

	printf("\n\nGROSS_MACRO_COEF: %f\n", gui_gross_macro_coef);
}


/**
 * Extracts the resp_macro_coef from the GUI and assigns it in globals.h
 * @param self The python object calling this C function
 * @param args The resp_macro_coef slider value
*/
static PyObject* py_extract_resp_macro_coef(PyObject* self, PyObject* args)
{
	PyArg_ParseTuple(args, "f", &gui_resp_macro_coef);
	printf("\n\nRESP_MACRO_COEF: %f\n", gui_resp_macro_coef);
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
