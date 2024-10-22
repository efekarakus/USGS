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
#include <sys/types.h>
#include <stdlib.h>

/* Python calls this to let us initialize our module */
void initMainModule();

/* Calls the Python function to output an image */
void output_image();

/* Extract the hydro map filenames that the user has selected */
static PyObject* py_extract_filenames(PyObject* self, PyObject* args);

static PyObject* py_extract_par_file(PyObject* self, PyObject* args);

static PyObject* py_extract_timestep(PyObject* self, PyObject* args);

static PyObject* py_extract_temperature_file(PyObject* self, PyObject* args);

static PyObject* py_extract_output_frequency(PyObject* self, PyObject* args);

/* */
static PyObject* py_goCommand(PyObject* self, PyObject* args);

/* Extracts the which stock from the GUI and assigns it in globals.h */
static PyObject* py_extract_whichstock(PyObject* self, PyObject* args);

/* Extracts the TSS value from the GUI and assigns it in globals.h */
static PyObject* py_extract_TSS(PyObject* self, PyObject* args);

/* Extracts the macro_base_temp from the GUI and assigns it in globals.h */
static PyObject* py_extract_macro_base_temp(PyObject* self, PyObject* args);

/* Extracts the gross_macro_coef from the GUI and assigns it in globals.h */
static PyObject* py_extract_gross_macro_coef(PyObject* self, PyObject* args);

/* Extracts the resp_macro_coef from the GUI and assigns it in globals.h */
static PyObject* py_extract_resp_macro_coef(PyObject* self, PyObject* args);

/* Extracts the sen_macro_coef from the GUI and assigns it in globals.h*/
static PyObject* py_extract_sen_macro_coef(PyObject* self, PyObject* args);

/* Extracts the macro_mass_max from the GUI and assigns it in globals.h */
static PyObject* py_extract_macro_mass_max(PyObject* self, PyObject* args);

/* Extracts the macro_vel_max from the GUI and assigns it in globals.h */
static PyObject* py_extract_macro_vel_max(PyObject* self, PyObject* args);

/* Extracts the k_phyto from the GUI and assigns it in globals.h */
static PyObject* py_extract_k_phyto(PyObject* self, PyObject* args);

/* Extracts the k_macro from the GUI and assigns it in globals.h */
static PyObject* py_extract_k_macro(PyObject* self, PyObject* args);

/* Extracts the flow corners check box button value and assigns it in globals.h */
static PyObject* py_extract_flow_corners(PyObject* self, PyObject* args);

PyObject* build_data();

#endif
