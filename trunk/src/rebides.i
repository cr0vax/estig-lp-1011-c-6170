/* rebides.i */

%module rebides

%{
#include <Python.h>
extern PyObject*  tnt_per_year(int iAno);
%}

#include <Python.h>
extern PyObject*  tnt_per_year(int iAno);