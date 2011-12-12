#include "main.h"
#include <stdio.h>
#include "setup.c"
#include "go.c"
#include "patch.c"
#include "cleanup.c"

/* Bind Python function names to our C functions */
static PyMethodDef MainModule_methods[] = {
    {"goCommand", py_goCommand, METH_VARARGS},
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
//    while( (day = (hours / 24)) < gui_days_to_run)
//    {
	    go();
//    }
    PyObject* data = (PyObject*)build_data();                                                  
    cleanup();
    return Py_BuildValue("i", tss);
}

PyObject* build_data(){
    int dimensions[2];
    int** buffer;
    PyArrayObject *result;
    int x, y;

    dimensions[0] = MAP_WIDTH;
    dimensions[1] = MAP_HEIGHT;
    result = (PyArrayObject *) PyArray_FromDims(2, dimensions, PyArray_INT);
    
    buffer = result->data;
    for( y=0; y < MAP_HEIGHT; y++){
        for( x= 0; x < MAP_WIDTH; x++){
            buffer[x][y] = colorValues[x][y];
        }
    }

    return PyArray_Return(result);
}

/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
