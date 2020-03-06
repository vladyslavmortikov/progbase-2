#include "csv.h"

void Csv_addInt(List* Row, int val) {
    int* newItem = malloc(sizeof(int));
    if(newItem == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    *newItem = val;
    List_add(Row, newItem);
}

void Csv_addString(List* Row, char* str) {
    char* newItem = malloc(sizeof(char) * (strlen(str) + 1));
    if(newItem == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    strcpy(newItem, str);
    List_add(Row, newItem);
}

void Csv_addRow(List* Table, List* Row) {
    List_add(Table, Row);
}

void Csv_clearTable(List* Table) {
    int tSize = List_size(Table);
    for(size_t i = 0; i < tSize; ++i) {
        List* Row = (List*)List_getIndexOf(Table, i);
        int rSize = List_size(Row);
        List_clear(Row);
        List_free(Row); 
    }
}

void Csv_fillTableFromString  (List * csvTable, const char * csvString) {
    int count = csvRowsSize(csvString);
    char* str = NULL;
    int i = 0;

    for( i = 0; csvString[i] != '\n' && csvString[i] != '\0'; ++i) {
        if(csvString[i] == '"') {
            i++;
            while(csvString[i] != '"' && csvString[i] != '\0') {
                i++;
            }
        }
    }
    i++;
    
    for(size_t j = 0; j < count; ++j) {
        List *pRow = List_alloc();
        int col = 0;
        char str[256];
        int strCount = 0;
        bool flag = true;

        while(flag == true) {
            if(strCount > 255) {fprintf(stderr, "Not enough char"); abort();};
            switch(csvString[i]) {
                case '\"': {
                    i++;
                    while(1) {
                        if(strCount > 255) {fprintf(stderr, "Not enough char"); abort();};
                        if(csvString[i + 1] == ',' && csvString[i] == '\"') break;
                        else if(csvString[i+1] == '\n' && csvString[i] == '\"') break;
                        else if(csvString[i+1] == '\0' && csvString[i] == '\"') break;
                        else if(csvString[i] == '\"' && csvString[i + 1] == '\"') {
                            str[strCount] = csvString[i];
                            strCount++;
                            i += 2;
                            continue;
                        }

                        str[strCount] = csvString[i];
                        strCount++;
                        i++;
                    }
                    i++;
                    break;
                }
                case ',': {
                    str[strCount] = '\0';
                    Csv_addString(pRow, str);
                    i++;
                    col++;
                    strCount = 0;
                    break;
                }
                
                case '\0': 
                case '\n': {
                    str[strCount] = '\0';
                    Csv_addString(pRow, str);
                    flag = false;
                    col = 0;
                    break;
                }

                default: {
                    str[strCount] = csvString[i];
                    strCount++;
                    i++;
                    break;
                }
            }
        }
        ++i;
        Csv_addRow(csvTable, pRow);
    }
}

int csvRowsSize(const char * csvString) {
    int rows = 0;
    for(int i = 0; csvString[i] != '\0'; ++i) {
        if(csvString[i] == '"') {
            i++;
            while(csvString[i] != '"' && csvString[i] != '\0') {
                i++;
            }
        } else if(csvString[i] == '\n') {
            rows++;
        }  
    }
    return rows;
}


void Csv_printTable(List* Table) {
    for(size_t i = 0; i < Table->size; ++i) {
        StrStrMap* map = (StrStrMap*)Table->items[i];
        int count = 0;
        for(size_t j = 0; j < map->size; ++j, ++count) {
                printf(" |%s| ", (char*)map->values[j]);
        }
        puts("");
    }
}

char* Csv_createStringFromTable(List* Table, int n) {
    char* str = malloc(sizeof(char) * 1000); 
    if(str == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    int count  = 0;

    for(size_t i = 0; i < Table->size; ++i) {
        int col = 0;
        List* list = (List*)Table->items[i];

        char* yearStr = (char*)(list->items[2]);
        int year = atoi(yearStr);
        if(n != -1 && (year > n)) continue;


        for(size_t j = 0; j < list->size; ++j, ++col) {
                char* pStr = (char*)(list->items[j]);
                char* newStr = Csv_strToCsv(pStr);
                int len = 0;
                if(newStr != NULL) {
                    len = strlen(newStr);
                    memcpy(str + count, newStr, len);
                    free(newStr);
                } else {
                    len = strlen(pStr);
                    memcpy(str + count, pStr, len);
                }
                count += len;
            
            str[count] = ',';
            count++;
        }
        count--;
        str[count] = '\n';
        count++;
    }
    if(count != 0) count--;
    str[count] = '\0';
    return str;
}

char*   Csv_strToCsv(char* str) {
    char* csv_str = malloc(sizeof(char) * (strlen(str) + 1) * 4);
    if(csv_str == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}

    bool brackets = false;
    bool utilBrackets = false; 

    int i = 0;
    if(str[i] == '\0') {
        csv_str[0] = '\"';
        csv_str[1] = '\"';
        csv_str[2] = '\0';
        return csv_str;
    }

    while(str[i] != '\0') {
        if(str[i] == ',' || str[i] == '\n' || str[i] == '\0' || str[i] == '\"') {
            if(str[i] == '\"') utilBrackets = true;
            if(str[i] == '\0') {
                csv_str[0] = '\"';
                csv_str[1] = '\"';
                csv_str[2] = '\0';
                return csv_str;
            }
            brackets = true;
        }
        i++;
    }

    if(utilBrackets) {
        i = 0;
        int count = 0;

        csv_str[count] = '\"';
        count++;

        while(str[i] != '\0') {
            if(str[i] == '\"') {
                csv_str[count] = str[i];
                count++;
            }
            csv_str[count] = str[i];
            i++;
            count++;
        }
        csv_str[count] = '\"';
        count++;
        csv_str[count] = '\0';
        return csv_str;
         
    } else if(brackets) {
        csv_str[0] = '\"';
        memcpy(csv_str + 1, str, strlen(str) + 1);
        int len = strlen(csv_str);
        csv_str[len] = '\"';
        csv_str[len+1] = '\0';
        return csv_str;      
    }

    if(utilBrackets == false && brackets == false) {
        free(csv_str);
    }

    return NULL;
}

char*  Csv_getHeaderTableFromString(char *str) {
    char* header = malloc(sizeof(char) * 128);
    if(header == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    size_t i = 0;
    for(; str[i] != '\0'; ++i) {
        if(str[i] == '\n') {header[i] = str[i]; break;}
        header[i] = str[i];
    }
    header[i + 1] = '\0';
    return header;
}

char*  Csv_addHeaderToString(char* header, char* str) {
    int len = strlen(header) + strlen(str) + 1;
    char* csvString = malloc(sizeof(char) * len);
    if(csvString == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}

    memcpy(csvString, header, strlen(header));
    memcpy(csvString + strlen(header), str, strlen(str) + 1);
    free(header);
    free(str);
    return csvString;
}

char* Csv_createStringFromTableMap(List* Table, int n) {
    char* str = malloc(sizeof(char) * 1000); 
    if(str == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    int count  = 0;

    for(size_t i = 0; i < Table->size; ++i) {
        int col = 0;
        StrStrMap* map = (StrStrMap*)Table->items[i];

        char* yearStr = StrStrMap_get(map, "Test Time");
        int year = atoi(yearStr);
        if(n != -1 && (year > n)) continue;


        for(size_t j = 0; j < map->size; ++j, ++col) {
                char* pStr = (char*)(map->values[j]);
                char* newStr = Csv_strToCsv(pStr);
                int len = 0;
                if(newStr != NULL) {
                    len = strlen(newStr);
                    memcpy(str + count, newStr, len);
                    free(newStr);
                } else {
                    len = strlen(pStr);
                    memcpy(str + count, pStr, len);
                }
                count += len;
            
            str[count] = ',';
            count++;
        }
        count--;
        str[count] = '\n';
        count++;
    }
    if(count != 0) count--;
    str[count] = '\0';
    return str;
}
