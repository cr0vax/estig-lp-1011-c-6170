/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c - Auto-generated by Anjuta's Makefile project wizard
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <Python.h>
#include <malloc.h>

//#include "count_teachers.h"

#define DB "rebides.db"
#define MAX_QUERY 300

typedef void function();

/*******************************************************
	Callback function that counts something
	
		pCounter    - return variable
		argc		- total number of columns in the query
		argv        - values from the query
		azColName   - each column name for the query
*******************************************************/
static int counterCallback(void **pCounter, int argc, char **argv, char **azColName){
	*pCounter = atoi( argv[0] ? argv[0] : "NULL");
    
	return 0;
}

/*******************************************************
	Callback function that add's a register to a list
	
		pList       - return variable
		argc		- total number of columns in the query
		argv        - values from the query
		azColName   - each column name for the query
*******************************************************/
static int listCallback(void **pList, int argc, char **argv, char **azColName){
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
		fprintf(stderr, "listCallback Error: %s\n", argv[0]);
    }
    
    //(*pList)++;
	return 0;
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
    char* cYear = (char *) malloc(sizeof(char));
	
	// builds the query
    strcpy(cQuery, "SELECT COUNT(DISTINCT id_docente) FROM fichas_docencia WHERE ano=");
    sprintf(cYear, "%d", iYear); // converts year to string
    strcat(cQuery, cYear);       // concatenate year to string
	
	// run the query against the database
	queryDataBase(cQuery, counterCallback, &iCounter);
	
	// free memory previously allocated
	free(cQuery);
	free(cYear);
	
	// returns total number of teachers counted for desired year
	return PyInt_FromLong(iCounter);
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per establishment and per year
	
		iYear - year to be counted
	
		returns the number of teachers counted
*******************************************************/
PyObject* count_teachers_per_establishment(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
    char* cYear = (char *) malloc(sizeof(char));
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    strcpy(cQuery, "SELECT e.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN estabelecimentos e on \
						fd.id_estabelecimento = e.id_estabelecimento \
					WHERE fd.ano=");
					
    sprintf(cYear, "%d", iYear); // converts year to string
    strcat(cQuery, cYear);       // concatenate year to string
    strcat(cQuery, " GROUP BY e.designacao");
	
	// run the query against the database
	queryDataBase(cQuery, listCallback, &poList);
	
	// free memory previously allocated
	free(cQuery);
	free(cYear);
	
	// returns total number of teachers counted for desired year
	return poList;
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per degree and per year
	
		iYear - year to be counted
	
		returns the number of teachers counted
*******************************************************/
PyObject* count_teachers_per_degree(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
    char* cYear = (char *) malloc(sizeof(char));
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    strcpy(cQuery, "SELECT g.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN graus g on \
						fd.id_grau = g.id_grau \
					WHERE fd.ano=");
					
    sprintf(cYear, "%d", iYear); // converts year to string
    strcat(cQuery, cYear);       // concatenate year to string
    strcat(cQuery, " GROUP BY g.designacao");
	
	// run the query against the database
	queryDataBase(cQuery, listCallback, &poList);
	
	// free memory previously allocated
	free(cQuery);
	free(cYear);
	
	// returns total number of teachers counted for desired year
	return poList;
}

/*******************************************************
	Counts total number of teachers	in the higher
	edutation system per degree, establishment and per year

		iYear - year to be counted
	
		returns the number of teachers counted
*******************************************************/
PyObject* count_teachers_per_degree_establishment(int iYear){
	char* cQuery = (char *) malloc(MAX_QUERY);
    char* cYear = (char *) malloc(sizeof(char));
	PyObject* poList  = PyList_New(0);
	
	// builds the query
    strcpy(cQuery, "SELECT e.designacao, g.designacao, COUNT(id_docente) \
					FROM fichas_docencia fd \
					INNER JOIN graus g on \
						fd.id_grau = g.id_grau \
					INNER JOIN estabelecimentos e on \
						fd.id_estabelecimento = e.id_estabelecimento \
					WHERE fd.ano=");
    sprintf(cYear, "%d", iYear); // converts year to string
    strcat(cQuery, cYear);       // concatenate year to string
    strcat(cQuery, " GROUP BY e.designacao, g.designacao");
	
	// run the query against the database
	queryDataBase(cQuery, listCallback, &poList);
	
	// free memory previously allocated
	free(cQuery);
	free(cYear);
	
	// returns total number of teachers counted for desired year
	return poList;
}