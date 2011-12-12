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
    int days = 0;
    while(days < 3*24) {
	  go();
      days++;
    }
    cleanup();
    return Py_BuildValue("i", tss);
}


/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
