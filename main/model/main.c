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
 * Extracts the TSS value from the GUI and assigns it globals.h
 * @param self The python object calling this C function
 * @param arggs The TSS slider value
*/
static PyObject* py_extract_TSS(PyObject* self, PyObject* args)
{
	int tss;
	PyArg_ParseTuple(args, "i", &tss);
	printf("\n\nTHIS IS THE VALUE OF TSS (Tom is awesome): %d\n", tss);
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
