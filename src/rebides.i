/* rebides.i */

%module rebides

%{
#include <Python.h>
extern PyObject*  count_teachers(int iAno);
%}

#include <Python.h>
extern PyObject*  count_teachers(int iAno);