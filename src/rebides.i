/* rebides.i */

%module rebides

%{
#include <Python.h>
extern PyObject* count_teachers(int iYear);
extern PyObject* count_teachers_per_establishment(int iYear);
extern PyObject* count_teachers_per_degree(int iYear);
extern PyObject* count_teachers_per_degree_establishment(int iYear);

extern PyObject* list_establishments_per_year(int iYear);
extern PyObject* list_teachers_per_degree_year(int iYear);
%}

#include <Python.h>
extern PyObject* count_teachers(int iYear);
extern PyObject* count_teachers_per_establishment(int iYear);
extern PyObject* count_teachers_per_degree(int iYear);
extern PyObject* count_teachers_per_degree_establishment(int iYear);

extern PyObject* list_establishments_per_year(int iYear);
extern PyObject* list_teachers_per_degree_year(int iYear);