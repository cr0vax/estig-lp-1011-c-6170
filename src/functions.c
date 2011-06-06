#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <Python.h>
#include <malloc.h>

#define DB "rebides.db"
#define MAX_QUERY 512

/*******************************************************
	Write string to file

		pString - string to be written
*******************************************************/
void append_string_to_file(char* pString){
	FILE *fp;

	// try to open file in append mode
	if ((fp = fopen("output.txt", "a+")) == NULL)
        return;
        
    fputs( pString, fp );
    
    // try to close file
    fclose(fp);
}

/*******************************************************
	Write lists to file

		pList - list to be written
*******************************************************/
void write_list_to_file(PyObject* pList){

    int size = PyList_Size(pList);
    int i;
    int u;
    PyObject* tuple;
    PyObject* tupleItem;
    char* string = (char *) malloc(MAX_QUERY);;
    char* tupleString = (char *) malloc(MAX_QUERY);
    
	// fill the array with the list data
    for(i=0; i < size; i++){
		tuple = PyList_GetItem(pList, i);
		
		for(u=0; u < PyTuple_Size(tuple); u++){
			tupleItem = PyTuple_GetItem(tuple, u);
			
			if (PyString_CheckExact(tupleItem))
			{
				sprintf(string, "%s;", PyString_AsString(tupleItem));
			}
			else
			{
				sprintf(string, "%d;", PyInt_AsLong(tupleItem));
			}
		
			strcat(tupleString, string);
		}
		
		// write to file
		append_string_to_file(strcat(tupleString, "\n"));
		
		// clear tuple string
		strcpy(tupleString, "");
    }
    
    // free memory previously allocated
	free(string);
	free(tupleString);
}

#define DB "rebides.db"
#define MAX_QUERY 512

typedef void function();

/*******************************************************
	Callback function that counts something
	
		pCounter    - return variable
		argc		- total number of columns in the query
		argv        - values from the query
		azColName   - each column name for the query
*******************************************************/
int counterCallback(void **pCounter, int argc, char **argv, char **azColName){

	*pCounter = atoi( argv[0] ? argv[0] : "NULL");
	
	return 0;
}

/*******************************************************
	Callback function that add's a statistics register to a list
	
		pList       - return variable
		argc		- total number of columns in the query
		argv        - values from the query
		azColName   - each column name for the query
*******************************************************/
int statsListCallback(void **pList, int argc, char **argv, char **azColName){
	int iError;
	int i;
	PyObject* poTuple = PyTuple_New(argc);
	
	for (i = 0; i < argc; i++)
	{
		// check if it's the last column
		if (i < (argc - 1)) {
			PyTuple_SetItem(poTuple, i, PyString_FromFormat("%s", argv[i]));
		}
		else {
			// is the last column convert to integer
			PyTuple_SetItem(poTuple, i, PyInt_FromLong(atoi(argv[i])));
		}
	}
	
	// append the tuple to the list
	iError = PyList_Append(*pList, poTuple);
	
	// check if error ocurred
    if( iError!=0 ){
		fprintf(stderr, "statsListCallback Error: %s\n", argv[0]);
    }
}

/*******************************************************
	Callback function that add's a register to a list
	
		pList       - return variable
		argc		- total number of columns in the query
		argv        - values from the query
		azColName   - each column name for the query
*******************************************************/
int listCallback(void **pList, int argc, char **argv, char **azColName){
	int iError;
	int i;
	PyObject* poTuple = PyTuple_New(argc);
	
	// fill tuple with pulled register
	for (i = 0; i < argc; i++)
	{	
		PyTuple_SetItem(poTuple, i, PyString_FromString(argv[i]));
	}
	
	// append the tuple to the list
	iError = PyList_Append(*pList, poTuple);
	
	// check if error ocurred
    if( iError!=0 ){
		fprintf(stderr, "listCallback Error: %s\n", argv[0]);
    }
}

/*******************************************************
	Compares two integer values
	
		p1        - first integer value to be compared
		p2        - second integer value to be compared
		
		returns
			 0   objects are equal
			 1   p1 is greater then p2
			-1   p1 is lower then p2
*******************************************************/
int intcmp(int p1, int p2)
{
	int iResult;
	iResult = p1 - p2;
	
	if (iResult > 0)  { return 1;  }	 // p1 is greater than p2
	if (iResult < 0)  { return -1; }	 // p2 is greater than p1
	if (iResult == 0) { return 0;  }	 // p1 and p2 are equal
}

/*******************************************************
	Compares two Python Objects containing strings
	
		p1        - first PyObject to be compared
		p2        - second PyObject to be compared
		
		returns
			 0   objects are equal
			 1   p1 is greater then p2
			-1   p1 is lower then p2
*******************************************************/
int poStringCompare(PyObject ** p1, PyObject ** p2)
{
	
	int tuplePos = 0;
	int tupleSize = PyTuple_Size(*p1);
	int i = 0;
	
	while (tuplePos <= tupleSize && i == 0)
	{
		// compare both strings
		i = strcmp( \
				PyString_AsString(PyTuple_GetItem(*p1, tuplePos)),\
				PyString_AsString(PyTuple_GetItem(*p2, tuplePos)));
				
		// go to next tuple item
		tuplePos++;
	}
	
	return i;
}

/*******************************************************
	Compares two Python Objects containing strings
	but finalized with integer types
	
		p1        - first PyObject to be compared
		p2        - second PyObject to be compared
		
		returns
			 0   objects are equal
			 1   p1 is greater then p2
			-1   p1 is lower then p2
*******************************************************/
int poFinalizedIntCompare(PyObject ** p1, PyObject ** p2)
{
	
	int tuplePos = 0;
	int tupleSize = PyTuple_Size(*p1);
	int i = 0;
	
	while (tuplePos <= tupleSize && i == 0)
	{
		if (tuplePos < tupleSize)
		{
			// compare both strings
			i = strcmp( \
				PyString_AsString(PyTuple_GetItem(*p1, tuplePos)),\
				PyString_AsString(PyTuple_GetItem(*p2, tuplePos)));
		}
		else
		{
			// compare integer items
			i = intcmp( \
				PyInt_FromLong(PyTuple_GetItem(*p1, tuplePos)),\
				PyInt_FromLong(PyTuple_GetItem(*p2, tuplePos)));

		}
				
		// go to next tuple item
		tuplePos++;
	}

	return i;
}

/*******************************************************
	Sorts data using quicksort algorithm
	
		pList     - list to be sorted
		f		  - comparator function to be used
*******************************************************/
void qSortPyList(PyObject *pList, function f )
{
    int size = PyList_Size(pList);
    int i;
    
    // create an array of pyobjects with the size of pList
    PyObject **v = (PyObject *) malloc( sizeof(PyObject *) * size );
    
	// fill the array with the list data
    for(i=0; i < size; i++){
		v[i] = PyList_GetItem(pList, i);
    }
    
    // sort the converted list
    qsort(v, size, sizeof(PyObject*), f);
    
    // insert sorted items into pylist again
    for (i=0; i<size; ++i) {
        PyList_SetItem(pList, i, v[i]);
    }

	// free memory
    free(v);
}

/*******************************************************
	Runs queries against the database
	
		pQuery    - sql statement
		f		  - callback function to be runned
		pArgument - return argument
*******************************************************/
void queryDataBase(char* pQuery, function f, void* pArgument)
{
    sqlite3 *db;  
    char *zErrMsg = 0;
    int rc;
    
    // connect database
    rc = sqlite3_open(DB, &db);

    // executes the query aleady built
    rc = sqlite3_exec(db, pQuery, f, pArgument, &zErrMsg);
    if( rc!=SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    }
    
    // close database connection
    sqlite3_close(db);
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per year
	
		iYear - year to be counted
	
		returns the number of teachers counted
*******************************************************/
PyObject* count_teachers(int iYear){
	int iCounter;
	char* cQuery = (char *) malloc(MAX_QUERY);
	
	// builds the query
    sprintf(cQuery, "SELECT COUNT(DISTINCT id_docente) \
					FROM fichas_docencia \
					WHERE ano=%d", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, counterCallback, &iCounter);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns total number of teachers counted for desired year
	return PyInt_FromLong(iCounter);
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per establishment and per year
	
		iYear - year to be counted
	
		returns list
*******************************************************/
PyObject* count_teachers_per_establishment(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    sprintf(cQuery, "SELECT e.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN estabelecimentos e on \
						fd.id_estabelecimento = e.id_estabelecimento \
					WHERE fd.ano=%d \
						GROUP BY e.designacao", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, statsListCallback, &poList);
	
	// sorts the list
	qSortPyList(poList, poFinalizedIntCompare);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns total number of teachers counted for desired year
	return poList;
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per degree and per year
	
		iYear - year to be counted
	
		returns list
*******************************************************/
PyObject* count_teachers_per_degree(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    sprintf(cQuery, "SELECT g.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN graus g on \
						fd.id_grau = g.id_grau \
					WHERE fd.ano=%d \
						GROUP BY g.designacao", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, statsListCallback, &poList);
	
	// sorts the list
	qSortPyList(poList, poFinalizedIntCompare);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns total number of teachers counted for desired year
	return poList;
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per degree, establishment and per year

		iYear - year to be counted
	
		returns list
*******************************************************/
PyObject* count_teachers_per_degree_establishment(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    sprintf(cQuery, "SELECT e.designacao, g.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN graus g on \
						fd.id_grau = g.id_grau \
					INNER JOIN estabelecimentos e on \
						fd.id_estabelecimento = e.id_estabelecimento \
					WHERE fd.ano=%d \
						GROUP BY e.designacao, g.designacao", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, statsListCallback, &poList);
	
	// sorts the list
	qSortPyList(poList, poFinalizedIntCompare);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns list of teachers for desired year
	return poList;
}

/*******************************************************
	Generate list of establishments per year

		iYear - year to be listed
	
		returns list
*******************************************************/
PyObject* list_establishments_per_year(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    sprintf(cQuery, "SELECT e.designacao \
					FROM fichas_docencia fd \
					INNER JOIN estabelecimentos e on \
						fd.id_estabelecimento = e.id_estabelecimento \
					WHERE fd.ano=%d \
						GROUP BY e.designacao", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, listCallback, &poList);
	
	// sorts the list
	qSortPyList(poList, poStringCompare);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns list of teachers for desired year
	return poList;
}

/*******************************************************
	Generate list of holders of a degree per year

		iYear - year to be listed
	
		returns list
*******************************************************/
PyObject* list_teachers_per_degree_year(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    sprintf(cQuery, "SELECT g.designacao, d.nome_completo \
					FROM fichas_docencia fd \
					INNER JOIN graus g on \
						fd.id_grau = g.id_grau \
					INNER JOIN docentes d on \
						fd.id_docente = d.id_docente \
					WHERE fd.ano=%d \
						 GROUP BY g.designacao", iYear);
	
	// run the query against the database
	queryDataBase(cQuery, listCallback, &poList);
	
	// sorts the list
	qSortPyList(poList, poStringCompare);
	
	// free memory previously allocated
	free(cQuery);
	
	// returns list of teachers for desired year
	return poList;
}

/*******************************************************
	Generate list of personnel leaving the institution per year

		iYear - year to be listed
	
		returns list
*******************************************************/
PyObject* list_teachers_leaving_institution_year(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList;
	PyObject* poFinalList  = PyList_New(0);
	PyObject* poEstablishmentList  = PyList_New(0);
	PyObject* poTuple;
	
	int iEstablishment;
	int i, u;
	sprintf(cQuery, \
		"SELECT distinct fd.id_estabelecimento \
			FROM fichas_docencia fd \
			WHERE fd.ano=%d\
			ORDER BY fd.id_estabelecimento", iYear);

	// run the query against the database
	queryDataBase(cQuery, statsListCallback, &poEstablishmentList);
	
	for (i = 0; i < PyList_Size(poEstablishmentList); i++)
	{
		// create new list
		poList  = PyList_New(0);

		// get next establishment to be checked
		poTuple = PyList_GetItem(poEstablishmentList, i);
		iEstablishment = PyInt_AsLong(PyTuple_GetItem(poTuple, 0));
		
		// builds the query
		sprintf(cQuery, \
			"SELECT distinct e.designacao, d.nome_completo \
				FROM fichas_docencia fd \
				INNER JOIN docentes d on \
					fd.id_docente = d.id_docente \
				INNER JOIN estabelecimentos e on \
					fd.id_estabelecimento = e.id_estabelecimento \
				WHERE \
					fd.ano=%d and \
					fd.id_estabelecimento=%d and \
					d.id_docente not in ( \
						SELECT d.id_docente \
							FROM fichas_docencia fd \
							INNER JOIN docentes d on \
								fd.id_docente = d.id_docente \
							WHERE \
								fd.ano=%d and \
								fd.id_estabelecimento=%d)", \
								iYear-1, \
								iEstablishment, \
								iYear, \
								iEstablishment);

		// run the query against the database
		queryDataBase(cQuery, listCallback, &poList);
		
		// append items to final list
		for (u = 0; u < PyList_Size(poList); u++)
		{
			poTuple = PyList_GetItem(poList, u);
			PyList_Append(poFinalList, poTuple);
		}

	}
	
	// sorts the list
	qSortPyList(poFinalList, poStringCompare);
	
	// free memory previously allocated
	free(cQuery);

	// returns list of teachers for desired year
	return poFinalList;
}

/*******************************************************
	Generate list of new personnel in the institution per year

		iYear - year to be listed
	
		returns list
*******************************************************/
PyObject* list_new_teachers_institution_year(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
	PyObject* poList;
	PyObject* poFinalList  = PyList_New(0);
	PyObject* poEstablishmentList  = PyList_New(0);
	PyObject* poTuple;
	
	int iEstablishment;
	int i, u;
	sprintf(cQuery, \
		"SELECT distinct fd.id_estabelecimento \
			FROM fichas_docencia fd \
			WHERE fd.ano=%d\
			ORDER BY fd.id_estabelecimento", iYear);

	// run the query against the database
	queryDataBase(cQuery, statsListCallback, &poEstablishmentList);
	
	for (i = 0; i < PyList_Size(poEstablishmentList); i++)
	{
		// create new list
		poList  = PyList_New(0);

		// get next establishment to be checked
		poTuple = PyList_GetItem(poEstablishmentList, i);
		iEstablishment = PyInt_AsLong(PyTuple_GetItem(poTuple, 0));
		
		// builds the query
		sprintf(cQuery, \
			"SELECT distinct e.designacao, d.nome_completo \
				FROM fichas_docencia fd \
				INNER JOIN docentes d on \
					fd.id_docente = d.id_docente \
				INNER JOIN estabelecimentos e on \
					fd.id_estabelecimento = e.id_estabelecimento \
				WHERE \
					fd.ano=%d and \
					fd.id_estabelecimento=%d and \
					d.id_docente not in ( \
						SELECT d.id_docente \
							FROM fichas_docencia fd \
							INNER JOIN docentes d on \
								fd.id_docente = d.id_docente \
							WHERE \
								fd.ano=%d and \
								fd.id_estabelecimento=%d)", \
								iYear, \
								iEstablishment, \
								iYear-1, \
								iEstablishment);

		// run the query against the database
		queryDataBase(cQuery, listCallback, &poList);
		
		// append items to final list
		for (u = 0; u < PyList_Size(poList); u++)
		{
			poTuple = PyList_GetItem(poList, u);
			PyList_Append(poFinalList, poTuple);
		}

	}
	
	// sorts the list
	qSortPyList(poFinalList, poStringCompare);
	
	// free memory previously allocated
	free(cQuery);

	// returns list of teachers for desired year
	return poFinalList;
}

/*******************************************************
	Generate list header

		cTitle - List title
*******************************************************/
void generate_list_header(char * cTitle){
	char* cHeader = (char *) malloc(MAX_QUERY);
	
	strcpy(cHeader, "");
	
	// build header with title passed as argument
	sprintf(cHeader, \
"******************************************\n\
 %s\n\
******************************************\n", cTitle);
			 
	// write header to file
	append_string_to_file(cHeader);
	
	// free memory previously allocated
	free(cHeader);
}

/*******************************************************
	Generate year header

		iYear - year of the header that will be generated
*******************************************************/
void generate_year_header(int iYear){
	char* cYearHeader = (char *) malloc(MAX_QUERY);
	
	// build header with the year
	sprintf(cYearHeader, "[200%d]\n", iYear);
			 
	// write header to file
	append_string_to_file(cYearHeader);
	
	// free memory previously allocated
	free(cYearHeader);
}
