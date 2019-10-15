#include <Python.h>
#include <thread>
#include <stdio.h>

void busy_loop() {
    printf("enter busy_loop\n");
    for (;;) {}
}

static PyObject *
para_busy2(PyObject *self, PyObject *args)
{
    int num_threads = 2;

    std::thread* threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = new std::thread(busy_loop);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i]->join();
        delete threads[i];
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
make_garbage(PyObject *self, PyObject *args)
{
    long v = 1337;
    PyObject* wrapped_long = PyLong_FromLong(v);
    Py_INCREF(wrapped_long);
    Py_DECREF(wrapped_long);
    Py_DECREF(wrapped_long);
    Py_DECREF(wrapped_long);
    return wrapped_long;
}

static PyMethodDef para_methods[] = {
    {"busy2",  para_busy2, METH_NOARGS,
     "Busy loop on 2 threads."},
    {"make_garbage",  make_garbage, METH_NOARGS,
     "Return a value which has no references."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef para_module = {
    PyModuleDef_HEAD_INIT,
    "para",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    para_methods
};

PyMODINIT_FUNC
PyInit_para(void)
{
    return PyModule_Create(&para_module);
}
