#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef void function();

void append_string_to_file(char* pString);
void write_list_to_file(PyObject* pList);
int counterCallback(void **pCounter, int argc, char **argv, char **azColName);
int statsListCallback(void **pList, int argc, char **argv, char **azColName);
int listCallback(void **pList, int argc, char **argv, char **azColName);
int intcmp(int p1, int p2);
int poStringCompare(PyObject ** p1, PyObject ** p2);
int poFinalizedIntCompare(PyObject ** p1, PyObject ** p2);
void qSortPyList(PyObject *pList, function f );
void queryDataBase(char* pQuery, function f, void* pArgument);
PyObject* count_teachers(int iYear);
PyObject* count_teachers_per_establishment(int iYear);
PyObject* count_teachers_per_degree(int iYear);
PyObject* count_teachers_per_degree_establishment(int iYear);
PyObject* list_establishments_per_year(int iYear);
PyObject* list_teachers_per_degree_year(int iYear);
PyObject* list_teachers_leaving_institution_year(int iYear);
PyObject* list_new_teachers_institution_year(int iYear);
void generate_list_header(char * cTitle);
void generate_year_header(int iYear);

#endif /*FUNCTIONS_H_*/