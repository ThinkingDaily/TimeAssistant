#include <python2.7/Python.h>

#include <string>

PyObject *
add_string_fn(PyObject *self, PyObject *args)
{
	const char *x = nullptr;
	const char *y = nullptr;

	if (!PyArg_ParseTuple(args, "ss", &x, &y)) {
		printf("add_string(): parse failed.\n");
		return nullptr;
	}

	std::string ret = std::string(x) + std::string(y);
	return Py_BuildValue("is", ret.length(), ret.c_str());
}

PyObject *
add_int_fn(PyObject *self, PyObject *args)
{
	int x, y;

	if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
		printf("add_int(): parse failed.\n");
		return nullptr;
	}

	return Py_BuildValue("i", x + y);
}

static PyMethodDef add_fns_methods[] = {
	{"add_string", add_string_fn, METH_VARARGS, "add string"},
	{"add_int", add_int_fn, METH_VARARGS, "add int number"},
	{nullptr, nullptr, 0, nullptr}
};

extern "C" void initadd_fns()
{
	Py_InitModule("add_fns", add_fns_methods);
}