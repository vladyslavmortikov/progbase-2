#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>

#include "list.h"
#include "csv.h"

struct Lection
{
    char title[100];
    int hours;
    char lectorer[100];
    int score;
    float testTime;
};

typedef struct Lection Lection;

void readFile(char *inputFiletitle, char string[], int len);
void outFile(char *outFiletitle, char *string);

void fillListofCoursesFromTable(List *table, List *listOfStructs);
void fillListOfStructsFromArrayOfStructs(List *listOfStructs, Lection array[], int length);
void proccesItems(List *listOfStructs, float lectLength);
void printListofCourses(List *listOfStructs);
void fillTableFromListOfCourses(List *table, List *listOfStructs);

int main(int argc, char *argv[])
{
	system("clear");
    char inputFiletitle[20] = "data.csv";
    char outputFiletitle[20] = "\0";
    float argLectLength = -1;
    int opt;

    while ((opt = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (opt)
        {
        case 'n':
        {
            argLectLength = atof(optarg);
        }
        break;
        case 'o':
        {
            strcpy(outputFiletitle, optarg);
        }
        break;
        case ':':
        {
            printf("option needs a value\n");
        }
        break;
        case '?':
        {
            printf("unknown option: %c\n", optopt);
        }
        break;
        }
    }
    for (; optind < argc; optind++)
    {
        strcpy(inputFiletitle, argv[optind]);
    }

    int stringLength = 1000;
    char csvString[stringLength];
    readFile(inputFiletitle, csvString, stringLength);

    List table;
    List_init(&table);

    Csv_fillTableFromString(&table, csvString);

    List listOfLections;
    List_init(&listOfLections);
    fillListofCoursesFromTable(&table, &listOfLections);
    if (argLectLength != -1)
    {
        proccesItems(&listOfLections, argLectLength);
    }
    if (strlen(outputFiletitle) > 0)
    {
        List parsedTable;
        List_init(&parsedTable);
        fillTableFromListOfCourses(&parsedTable, &listOfLections);
        char *p = Csv_createStringFromTable(&parsedTable);
        outFile(outputFiletitle, p);

        // freeeeee
        free(p);
        Csv_clearTable(&parsedTable);
        List_deinit(&parsedTable);
    }
    else
    {
        printListofCourses(&listOfLections);
    }

    // @freeeeee
    Csv_clearTable(&table);
    List_deinit(&table);
    for (size_t i = 0; i < List_size(&listOfLections); i++)
    {
        free(List_get(&listOfLections, i));
    }
    List_deinit(&listOfLections);

    return 0;
}

void fillListOfStructsFromArrayOfStructs(List *listOfStructs, Lection array[], int length)
{
    for (size_t i = 0; i < length; i++)
    {
        Lection *item = malloc(sizeof(Lection));
        strcpy(item->title, array[i].title);
        item->hours = array[i].hours;
        strcpy(item->lectorer, array[i].lectorer);
        item->score = array[i].score;
        item->testTime = array[i].testTime;
        List_add(listOfStructs, item);
    }
}

void proccesItems(List *listOfStructs, float lectLength)
{
    for (size_t i = 0; i < List_size(listOfStructs); i++)
    {
        Lection *item = List_get(listOfStructs, i);
        if (item->testTime > lectLength)
        {
            List_removeAt(listOfStructs, i);
            i -= 1;
        }
    }
}

void printListofCourses(List *listOfStructs)
{
    printf("Title\t\t      Hours\t\t    Lectorer\t\t  Score\t\t        Test time\n");
    for (size_t i = 0; i < List_size(listOfStructs); i++)
    {
        Lection *item = List_get(listOfStructs, i);
        printf("%-21s ", item->title);
        printf("%-21i ", item->hours);
        printf("%-21s ", item->lectorer);
        printf("%-21i ", item->score);
        printf("%-21.2f ", item->testTime);
        printf("\n");
    }
}

void readFile(char *inputFiletitle, char string[], int len)
{
    FILE *fp = fopen(inputFiletitle, "r");
    if (fp == NULL)
    {
        printf("ERROR: file with such title does not exist.\n");
        abort();
    }
    char ch = 0;
    int i = 0;
    while (ch != EOF)
    {
        ch = fgetc(fp);
        string[i] = ch;
        i++;
        if (i >= len)
        {
            abort();
        }
    }
    string[i - 1] = '\0';
    fclose(fp);
}

void fillListofCoursesFromTable(List *table, List *listOfStructs)
{
    for (size_t i = 1; i < List_size(table); i++)
    {
        Lection *item = malloc(sizeof(Lection));
        List *row = List_get(table, i);
        Csv_string(row, 0, item->title, 100);
        item->hours = Csv_int(row, 1);
        Csv_string(row, 2, item->lectorer, 100);
        item->score = Csv_int(row, 3);
        item->testTime = Csv_double(row, 4);
        List_add(listOfStructs, item);
    }
}

void outFile(char *outFiletitle, char *string)
{
    FILE *fw = NULL;
    fw = fopen(outFiletitle, "w");
    if (fw == NULL)
    {
        printf("Error opening file %s\n", outFiletitle);
        exit(EXIT_FAILURE);
    }
    printf("%s", string);
    fclose(fw);
}

void fillTableFromListOfCourses(List *table, List *listOfStructs)
{
    List *row = List_alloc();
    Csv_addString(row, "Title");
    Csv_addString(row, "Hours");
    Csv_addString(row, "Lectorer");
    Csv_addString(row, "Score");
    Csv_addString(row, "Test time");
    Csv_addRow(table, row);
    for (size_t i = 0; i < List_size(listOfStructs); i++)
    {
        row = List_alloc();
        Lection *item = List_get(listOfStructs, i);
        Csv_addString(row, item->title);
        Csv_addInt(row, item->hours);
        Csv_addString(row, item->lectorer);
        Csv_addInt(row, item->score);
        Csv_addDouble(row, item->testTime);
        Csv_addRow(table, row);
    }
}
