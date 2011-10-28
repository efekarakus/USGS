#ifndef _SETUP
#define _SETUP

/** 
 * To compile the code:
 * gcc -m32 -shared -I/usr/include/python2.7/ -lpython2.7 -o myModule.so setup.c
 */

#include <Python.h>


/* Python calls this to let us initialize our module */
void initSetupModule();

/* Hello World function to be called from Python */
static PyObject* py_computeTSS(PyObject* self, PyObject* args);

#endif
