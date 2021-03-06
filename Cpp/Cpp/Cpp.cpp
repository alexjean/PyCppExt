//  Python3 的Extension Module
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fac(int n)
{
	if (n < 2) return 1;
	return n*fac(n - 1);
}

char *reverse(char *s)
{
	register char t, *p = s, *q = (s + (strlen(s) - 1)); 
	while (p < q)
	{
		t = *p;
		*p++ = *q;
		*q-- = t;
	}
	return s;
}

int test()
{
	char s[BUFSIZ];
	printf("4! == %d\n", fac(4));
	printf("8! == %d\n", fac(8));
	printf("12! == %d\n", fac(12));
	strcpy_s(s, "abcdef");
	printf("reversing 'abcdef', we get '%s'\n", reverse(s));
	strcpy_s(s, "madam");
	printf("reversing 'madam', we get '%s'\n", reverse(s));
	return 0;
}

#include "Python.h"

static PyObject *Ext_fac(PyObject *self, PyObject *args)
{
	int num;
	if (!PyArg_ParseTuple(args, "i", &num))
		return NULL;
	return(PyObject *)Py_BuildValue("i", fac(num));
}

static PyObject *Ext_doppel(PyObject *self, PyObject *args)
{
	char *orig_str;
	char *dupe_str;
	PyObject *retval;

	if (!PyArg_ParseTuple(args, "s", &orig_str)) 
		return NULL;
	retval = (PyObject *)Py_BuildValue("ss", orig_str, dupe_str = reverse(_strdup(orig_str)));
	free(dupe_str);
	return retval;
}

static PyObject *Ext_test(PyObject *self, PyObject *args)
{
	test();
	return(PyObject *)Py_BuildValue("");
}

static PyObject *ExtError;

static PyObject *Ext_system(PyObject *self, PyObject *args)
{
	const char *command;
	int sts;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);
	if (sts < 0) 
	{
		PyErr_SetString(ExtError, "System command failed!");
		return NULL;
	}
	return PyLong_FromLong(sts);
}

static PyMethodDef ExtMethods[] =
{   { "system"	, Ext_system, METH_VARARGS, "Execute a shell command."},
	{ "fac"		, Ext_fac	, METH_VARARGS, "Recursive Factorial call."},
	{ "doppel"	, Ext_doppel, METH_VARARGS, "Doplicate string"},
	{ "test"	, Ext_test	, METH_VARARGS, "Test..."},
	{NULL, NULL,0,NULL}  // Sentinel 哨兵 守衛
};

static struct PyModuleDef ExtModule = 
{
	PyModuleDef_HEAD_INIT,
	"Cpp",    // name of module
	NULL,	  // module documentation, may be NULL
	-1  ,     // size of pre-interpreter state of the module or -1 if the module keeps state in global variables
	ExtMethods
};

PyMODINIT_FUNC PyInit_Cpp(void)
{
	PyObject *m;

	m = PyModule_Create(&ExtModule);
	if (m == NULL) return NULL;

	ExtError = PyErr_NewException("Cpp.error", NULL, NULL);
	Py_INCREF(ExtError);
	PyModule_AddObject(m, "error", ExtError);
	return m;
}


