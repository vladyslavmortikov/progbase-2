#pragma once

#include "stdbool.h"

#include "list.h"
#include "vec.h"
#include "strstrmap.h"

void   Csv_fillTableFromString  (List * csvTable, const char * csvString);
void   Csv_addInt(List* Row, int val);
void   Csv_addString(List* Row, char* str);
void   Csv_addRow(List* Table, List* Row);
void   Csv_clearTable(List* Table);
int    csvRowsSize(const char * csvString);
char*  Csv_createStringFromTable(List* Table, int n);
void   Csv_printTable(List* Table);
char*  Csv_strToCsv(char* str);
char*  Csv_getHeaderTableFromString(char *str);
char*  Csv_addHeaderToString(char* header, char* str);
char* Csv_createStringFromTableMap(List* Table, int n);
