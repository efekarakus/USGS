#include "setup.h"

/* Bind Python function names to our C functions */
static PyMethodDef SetupModule_methods[] = {
    {"computeTSS", py_computeTSS, METH_VARARGS},
    {NULL, NULL}
};

/** 
 * Computes the tss value and returns twice as much 
 * @param self: the python object calling this C function
 * @param args: the TSS slider value
 * @return 2*TSS
 */
static PyObject* py_computeTSS(PyObject* self, PyObject* args) {
	int tss;
	PyArg_ParseTuple(args, "i", &tss);
	tss = 2*tss;
	return Py_BuildValue("i", tss);
}


/* Python calls this function to let us initialize our module */
void initSetupModule() {
	(void) Py_InitModule("SetupModule", SetupModule_methods);
}
 
