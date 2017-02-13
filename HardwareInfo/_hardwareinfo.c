#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <Python.h>
#include "hardwareinfo.h"

#define MAKE_STRING_FUNCTION(name) \
static PyObject* name(PyObject* self, PyObject* args) \
{ \
	PyObject* res; \
	char *s = _##name(); \
	res = Py_BuildValue("s", s); \
	free(s); \
	return res; \
} \

/* Available functions */
MAKE_STRING_FUNCTION(getVideoResolutions)

/* Module specification */
static PyMethodDef hardwareinfoMethods[] = {
	{ "getVideoResolutions", getVideoResolutions, METH_NOARGS, NULL },
	{ NULL, NULL, 0, NULL }
};

/* Initialize the module */
void inithardwareinfo() {
	Py_InitModule("hardwareinfo", hardwareinfoMethods);
}
