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

extern PyObject* list_teachers_leaving_institution_year(int iYear);
extern PyObject* list_new_teachers_institution_year(int iYear);

extern void count_teachers_to_file();
extern void count_teachers_per_establishment_to_file();
extern void count_teachers_per_degree_to_file();
extern void count_teachers_per_degree_establishment_to_file();

extern void list_establishments_per_year_to_file();
extern void list_teachers_per_degree_year_to_file();
%}

#include <Python.h>
extern PyObject* count_teachers(int iYear);
extern PyObject* count_teachers_per_establishment(int iYear);
extern PyObject* count_teachers_per_degree(int iYear);
extern PyObject* count_teachers_per_degree_establishment(int iYear);

extern PyObject* list_establishments_per_year(int iYear);
extern PyObject* list_teachers_per_degree_year(int iYear);

extern PyObject* list_teachers_leaving_institution_year(int iYear);
extern PyObject* list_new_teachers_institution_year(int iYear);

extern void count_teachers_to_file();
extern void count_teachers_per_establishment_to_file();
extern void count_teachers_per_degree_to_file();
extern void count_teachers_per_degree_establishment_to_file();

extern void list_establishments_per_year_to_file();
extern void list_teachers_per_degree_year_to_file();
