#include <Python.h>
static PyObject * spam_system(PyObject *self, PyObject *args)
{
    /*
     * PyObject *self: Only be used if building a class method, this 
     *                  would be NULL since it's not a method.
     * PyObject *args: Pointer to a Python tuple object containing the
     *                  arguments it'll be passed.
     *
     * Python expression to be run: spam.system(string)
     */
    const char *command;
    int sts;

    /*
     * PyArg_ParseTuple: Returns true if all arguments have the right type
     *                      (and raises appropriate exception otherwise)
     * "s": Convert a Python string to a C pointer to character string.
     * See: http://www.fnal.gov/docs/products/python/v1_5_2/ext/parseTuple.html
     */
    if (! PyArg_ParseTuple(args, "s", &command)) {
        return NULL;
    }

    sts = system(command);
    return Py_BuildValue("i", sts);
}

static PyMethodDef SpamMethods[] = 
{
    {"system", spam_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}
};

void initspam(void) {
    PyImport_AddModule("spam");
    Py_InitModule("spam", SpamMethods);
}

int main(int argc, const char *argv[])
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initspam();
    return 0;
}
