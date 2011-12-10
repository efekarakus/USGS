#ifndef MAIN_H
#define MAIN_H

/** 
 *  * To compile the code:
 *   * gcc -m32 -shared -I/usr/include/python2.7/ -lpython2.7 -o MainModule.so main.c
 *    * Don't forget to cp MainModule.so ../controller
 *     */
#include <Python.h>
#include "setup.h"
#include "patch.h"

/* Python calls this to let us initialize our module */
void initMainModule();

/* Hello World function to be called from Python */
static PyObject* py_goCommand(PyObject* self, PyObject* args);

#endif
