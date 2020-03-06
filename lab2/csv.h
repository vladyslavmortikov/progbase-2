#include "list.h" 

void Csv_addInt(List *row, int value);            // malloc a string and write value in it
void Csv_addDouble(List *row, double value);      // malloc a str and write value in it
void Csv_addString(List *row, char *value); // malloc a string and copy value

int Csv_int(List *row, int index);                         // get item (str) and convert it to int
double Csv_double(List *row, int index);                   // get str and convert it to double
int Csv_string(List *row, int index, char *buf, int nBuf); // get str & copy it to buf

void Csv_addRow(List *table, List *row); // add row to table as an item
List *Csv_row(List *table, int index);   // get item from table as List *

void Csv_fillTableFromString(List *csvTable, const char *csvStr); // parse csv & fill table
int Csv_fillStringFromTable(List *csvTable, char *buf, int nBuf); // fill buf with csv
char *Csv_createStringFromTable(List *csvTable);                  // malloc string array and fill it with csv
void Csv_clearTable(List *csvTable);                              // free all table allocated memory