#include <stdio.h>    // Для друку в термінал
#include <math.h>     // Для математичних функцій
#include <stdlib.h>   // Деякі додаткові функції
#include <stdbool.h>
#include <time.h>
#include <ctype.h> 
#include <string.h>
#include <assert.h>
#include <progbase.h> // Спрощений ввід і вивід даних у консоль
#include <unistd.h>  
#include <getopt.h>

#include "csv.h"
#include "strstrmap.h"
#include "list.h"
#include "bintree.h"



typedef struct Lection Lection;
struct Lection
{
    int id;
    char* title;
    int score;
    char* lecturer;
    int students;
    double testTime;
};

void test(int N, char* outFile);

StrStrMap * createLectionMap(Lection* lection);
void cleanupMaps(List* list);
void createTableMapfromTableList(List* table, List* tableMap);

int main(int argc, char *argv[]) {
    int opt;  
    int N = -1;
    char* inFile = "data.csv";
    char* outFile = NULL;
    bool binaryTree = false;

    while((opt = getopt(argc, argv, "bn:o:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'n': 
                N = atoi(optarg);
                if(N < 0) return EXIT_FAILURE; 
                break;
            case 'o':  
                outFile = optarg; 
                break; 
            case 'b':
                binaryTree = true;
                break; 
            case ':':   
                fprintf(stderr, "option needs a value\n"); 
                return EXIT_FAILURE;
                break;  
            case '?':   
                fprintf(stderr, "unknown option: \n"); 
                return EXIT_FAILURE;
                break;  
        }  
    }  
      
    if(optind < argc) {
        inFile = argv[optind];
    }

    if(inFile != NULL) {
        FILE *fp;
        fp = fopen(inFile, "r");
        if(fp == NULL) {fprintf(stderr, "FILE ISN'T OPENED"); return EXIT_FAILURE;};

        char ch = '\0';
        Vec* vec = Vec_init(10);

        while((ch = fgetc(fp)) != EOF) {
            Vec_add(vec, ch); 
        }
        Vec_add(vec, '\0');

        char* str = Vec_toStr(vec);
        if(strlen(str) == 0) {Vec_deinit(vec); return 0;};
        char* header = Csv_getHeaderTableFromString(str);

        List table;
        List_init(&table);
        List tableMap;
        List_init(&tableMap);

        Csv_fillTableFromString(&table, str);
        createTableMapfromTableList(&table, &tableMap);
        Csv_clearTable(&table);
        List_deinit(&table);

        if(binaryTree == true) {
            BSTree* tree = BSTree_alloc();

            for(int i = 0; i < tableMap.size; ++i) {
                BSTree_insert(tree, tableMap.items[i]);
            }
            
            puts("================================================");
            BSTree_print(tree);
            puts("================================================");

            if(N != -1) {
                BSTree_delete(tree, N);
                puts("*************************************************");
                BSTree_print(tree);
                puts("*************************************************");
            }

            BSTree_free(tree);
        }

        Csv_printTable(&tableMap);
        puts("");

        char* test = Csv_createStringFromTableMap(&tableMap, N); 
        char* csvTabelStr = Csv_addHeaderToString(header, test);

        if(outFile != NULL) {
            FILE *fout;
            fout = fopen(outFile, "w");
            if(fout == NULL) {fprintf(stderr, "FILE ISN'T OPENED"); abort();};
            fprintf(fout, "%s", csvTabelStr);
            fclose(fout);
        } else {
            puts(csvTabelStr);
        }

        cleanupMaps(&tableMap);
        List_deinit(&tableMap);
        Vec_deinit(vec);
        free(csvTabelStr);
        fclose(fp);
    } else {
        test(N, outFile);
    }
    return 0;
}

StrStrMap * createLectionMap(Lection* lection) {
    char * idValue = String_allocFromInt(lection->id);
    char * titleValue = String_allocCopy(lection->title);
    char * scoreValue = String_allocFromInt(lection->score);
    char * lecturerValue = String_allocCopy(lection->lecturer);
    char * studentsValue = String_allocFromInt(lection->students);
    char * testTimeValue = String_allocFromDouble(lection->testTime);
    //
    StrStrMap * map = StrStrMap_alloc();
    StrStrMap_add(map, "id", idValue);
    StrStrMap_add(map, "title", titleValue);
    StrStrMap_add(map, "score", studentsValue);
    StrStrMap_add(map, "lecturer", lecturerValue);
    StrStrMap_add(map, "students", scoreValue);
    StrStrMap_add(map, "test time", testTimeValue);

    //
    assert(StrStrMap_contains(map, "id"));
    assert(StrStrMap_contains(map, "title"));
    assert(StrStrMap_contains(map, "score"));
    assert(StrStrMap_contains(map, "lecturer"));
    assert(StrStrMap_contains(map, "students"));
    assert(StrStrMap_contains(map, "test time"));
    //
    return map;
}

void cleanupMaps(List* list) {
    for(int i = 0; i < list->size; ++i) {
        StrStrMap_clear((StrStrMap *)list->items[i]);
        Map_free((StrStrMap *)list->items[i]);
    }
}

void test(int N, char* outFile) {

    struct Lection lections[] = {   
            {1,"History of Ukraine",     100, "Anton Ivko",   120, 12.23},
            {2,"C++programming",          97, "Liza Valilec",  97, 13.50},
            {3,"Math",   77,             "Victor Legeza", 12, 19.40}
        };

        int stLength = sizeof(lections) / sizeof(lections[0]);
        List table; 
        List_init(&table);

        BSTree* tree = BSTree_alloc();

        for(int i = 0; i < stLength; ++i) {
            Lection *lection = &lections[i];
            StrStrMap * lectionMap = createLectionMap(lection);
            List_add(&table, lectionMap);     
            BSTree_insert(tree, lectionMap); 
        }
        Csv_printTable(&table);
        puts("");

        BSTree_print(tree);
        puts("");

        BSTree_delete(tree, 1815);

        puts("------------------------------");
        BSTree_print(tree);
        puts("");
        

        char* csvString = Csv_createStringFromTableMap(&table, N);
        
        if(outFile != NULL) {
            FILE *fout;
                fout = fopen(outFile, "w");
                if(fout == NULL) {fprintf(stderr, "FILE ISN'T OPENED"); abort();};
                fprintf(fout, "%s", csvString);
                fclose(fout);
        } else {
            puts(csvString);
        }

        free(csvString);
        cleanupMaps(&table);
        List_deinit(&table);
        BSTree_free(tree);
}

void createTableMapfromTableList(List* table, List* tableMap) {
    for(int i = 0; i < table->size; ++i) {
        List* list = (List*)table->items[i];
        StrStrMap* map = StrStrMap_alloc();
        for(int j = 0; j < list->size; j++) {
            char* value = (char*)list->items[j];
            int lenValue = strlen(value);
            char* newVal = malloc(sizeof(char) * (lenValue + 1));
            strcpy(newVal, value);

            switch(j) {
                case 0: {
                    StrStrMap_add(map, "id", newVal);
                    break;
                }

                case 1: {
                    StrStrMap_add(map, "title", newVal);
                    break;
                }

                case 2: {
                    StrStrMap_add(map, "students", newVal);
                    break;
                }

                case 3: {
                    StrStrMap_add(map, "lecturer", newVal);
                    break;
                }
                
                case 4: {
                    StrStrMap_add(map, "score", newVal);
                    break;
                }

                case 5: {
                    StrStrMap_add(map, "test time", newVal);
                    break;
                }
            }
        }
        List_add(tableMap, map);
    }
}
