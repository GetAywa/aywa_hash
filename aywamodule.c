#include <Python.h>

#include "aywahash.h"

static PyObject *aywa_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    aywa_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    aywa_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef AywaMethods[] = {
    { "getPoWHash", aywa_getpowhash, METH_VARARGS, "Returns the proof of work hash using aywa hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef AywaModule = {
    PyModuleDef_HEAD_INIT,
    "aywa_hash",
    "...",
    -1,
    AywaMethods
};

PyMODINIT_FUNC PyInit_aywa_hash(void) {
    return PyModule_Create(&AywaModule);
}

#else

PyMODINIT_FUNC initaywa_hash(void) {
    (void) Py_InitModule("aywa_hash", AywaMethods);
}
#endif
