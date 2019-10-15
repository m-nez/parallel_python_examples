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
    //std::thread thread(busy_loop);
    //thread.join();



    Py_IncRef(Py_None);
    return Py_None;
}

static PyMethodDef para_methods[] = {
    {"busy2",  para_busy2, METH_NOARGS,
     "Busy loop on 2 threads."},
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
