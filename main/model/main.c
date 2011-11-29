#include "main.h"
#include <stdio.h>
#include "setup.c"
/* Bind Python function names to our C functions */
static PyMethodDef MainModule_methods[] = {
	    {"goCommand", py_goCommand, METH_VARARGS},
		    {NULL, NULL}
};

/** 
 *  * Computes the tss value and returns twice as much 
 *   * @param self: the python object calling this C function
 *    * @param args: the TSS slider value
 *     * @return 2*TSS
 *      */
static PyObject* py_goCommand(PyObject* self, PyObject* args) {
		int tss;
			PyArg_ParseTuple(args, "i", &tss);
				tss = 2*tss;
				    setup();
						return Py_BuildValue("i", tss);
}


/* Python calls this function to let us initialize our module */
void initMainModule() {
		(void) Py_InitModule("MainModule", MainModule_methods);
}
