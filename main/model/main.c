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
 * Computes the tss value and returns twice as much 
 * @param self: the python object calling this C function
 * @param args: the TSS slider value
 * @return 2*TSS
 */
static PyObject* py_goCommand(PyObject* self, PyObject* args) {
    int tss;
    PyArg_ParseTuple(args, "i", &tss);
    tss = 2*tss;
    setup();
    int x,y;
/*  for(x = 0; x < MAP_WIDTH; x++) {
      for(y = 0; y < MAP_HEIGHT; y++) {
        patch p = patches[x][y];
        int pxcor = p.pxcor;
        int pycor = p.pycor;
        double depth = p.depth;
        double px_vector = p.px_vector;
        double py_vector = p.py_vector;
        short cell_type = p.cell_type;
        int phyto = p.phyto;
        printf("patch[%d][%d] has: (pxcor: %d, pycor: %d, depth: %f, px_vector: %f, py_vector: %f, cell_type: %d, phyto: %d)\n", x, y, pxcor, pycor, depth, px_vector, py_vector, cell_type, phyto);
      }
    }
*/
    while( (hours / 24) < gui_days_to_run)
	    go();
//    PyObject* data = build_data();
    /*int col;
    PyObject*** list = malloc(MAP_WIDTH*sizeof(PyObject**));
    for(col = 0; col < MAP_WIDTH; col++){
        list[col] = malloc(MAP_HEIGHT*sizeof(PyObject*));
    }


    for( y=0; y < MAP_HEIGHT; y++){
        for( x= 0; x < MAP_WIDTH; x++){
            list[x][y] = Py_BuildValue("(iii)", colorValues[x][y]);
        }
    }
      */
    //int test[2][3] = {{3, 1, 1}, {3, 2, 2}};
    //PyObject* tuple = Py_BuildValue("(OO)", test);
    cleanup();
 /*   PyObject* tupleOne = Py_BuildValue("(ii)", 1,2);
    PyObject* tupleTwo = Py_BuildValue("(ii)", 3, 4);
    PyObject* data = Py_BuildValue("(OO)", tupleOne, tupleTwo);
    */
    return Py_BuildValue("i", tss);
    //return tuple;
}
/*
PyObject* build_data(){
}       
*/
/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
