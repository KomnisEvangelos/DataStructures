#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MTgen.h"


unsigned int* createArray(int n);
void fillArray(unsigned  int* p, int n);
void initArrASC(unsigned  int* p, int n);
void initArrDESC(unsigned  int* p, int n);
void printArray(unsigned  int* p, int n);
void copyArray(unsigned  int* p, unsigned  int* q, int n);
void selectionSort(unsigned  int* p, int n);
void insertionSort(unsigned  int* p, int n);
void shellSort(unsigned  int* p, int n);
void quickSort(unsigned  int* p, int left, int right);
int sortAndPartition(int p[], int left, int right);
void writeResultsToFile(FILE* f, char arrTypeLabels[3][7], char sortNames[4][11], float times[4][3], int n);
void printsystemspecs();
//void clearscreen();
int main() {

    unsigned int* initArr, * copyArr, n;
    clock_t  c0, c1;
    float times[4][3];
    FILE* f = NULL;
    char arrTypeLabels[3][7] = { "Random\0", " ASC \0"," DESC\0" }, sortNames[4][11] = { "Selection\0", "Insertion\0","Shell\0","Quick\0" };

    sMTrand(time(NULL));

    printsystemspecs();

    printf("Give array lenght: ");
    scanf("%d", &n);

    initArr = createArray(n);
    copyArr = createArray(n);
    fillArray(initArr, n);

    printf("\nArray type = Random\n");

    copyArray(initArr, copyArr, n);
    printf("Sorting ==> Selection...");
    c0 = clock();
    selectionSort(copyArr, n);
    c1 = clock();
    times[0][0] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    copyArray(initArr, copyArr, n);
    printf("Insertion...");
    c0 = clock();
    insertionSort(copyArr, n);
    c1 = clock();
    times[1][0] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    copyArray(initArr, copyArr, n);
    printf("Shell...");
    c0 = clock();
    shellSort(copyArr, n);
    c1 = clock();
    times[2][0] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    copyArray(initArr, copyArr, n);
    printf("Quick...");
    c0 = clock();
    quickSort(copyArr, 0, n - 1);
    c1 = clock();
    times[3][0] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("DONE!");

    printf("\n\nArray type = ASC\n");

    initArrASC(initArr, n);

    copyArray(initArr, copyArr, n);
    printf("Sorting ==> Selection...");
    c0 = clock();
    selectionSort(copyArr, n);
    c1 = clock();
    times[0][1] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Insertion...");
    c0 = clock();
    insertionSort(copyArr, n);
    c1 = clock();
    times[1][1] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Shell...");
    c0 = clock();
    shellSort(copyArr, n);
    c1 = clock();
    times[2][1] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Quick...");
    c0 = clock();
    quickSort(copyArr, 0, n - 1);
    c1 = clock();
    times[3][1] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("DONE!");

    printf("\n\nArray type = DESC\n");

    initArrDESC(initArr, n);

    printf("Sorting ==> Selection...");
    copyArray(initArr, copyArr, n);
    c0 = clock();
    selectionSort(copyArr, n);
    c1 = clock();
    times[0][2] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Insertion...");
    copyArray(initArr, copyArr, n);
    c0 = clock();
    insertionSort(copyArr, n);
    c1 = clock();
    times[1][2] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Shell...");
    copyArray(initArr, copyArr, n);
    c0 = clock();
    shellSort(copyArr, n);
    c1 = clock();
    times[2][2] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("Quick...");
    copyArray(initArr, copyArr, n);
    c0 = clock();
    quickSort(copyArr, 0, n - 1);
    c1 = clock();
    times[3][2] = (float)(c1 - c0) / CLOCKS_PER_SEC;

    printf("DONE!\n");



    writeResultsToFile(f, arrTypeLabels, sortNames, times, n);

    // printf("\n\nMaking Excel file...\n\n");
    // system("start TextToExcel.py");
    // system("start out.xlsx");
     //clearscreen();

    return 0;
}

// FUNCTIONS
unsigned int* createArray(int n)
{
    int* p;

    p = (int*)malloc(n * sizeof(int));

    if (p == NULL)
    {
        printf("Memory Error...");
        exit(1);
    }
    return p;
}

void fillArray(unsigned int* p, int n)
{
    int i;

    for (i = 0; i < n; i++)
        p[i] = MTrand();
}

void initArrASC(unsigned  int* p, int n) {

    quickSort(p, 0, n - 1);

}

void initArrDESC(unsigned  int* p, int n) {
    int i, j;

    int* b = malloc(n * sizeof(int));

    for (i = n - 1, j = 0; i >= 0; i--, j++)
        b[j] = p[i];

    for (i = 0; i < n; i++)
        p[i] = b[i];

    free(b);
}

void printArray(unsigned int* p, int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%u\n", p[i]);

}

void copyArray(unsigned int* p, unsigned int* q, int n)
{
    int i;

    for (i = 0; i < n; i++)
        q[i] = p[i];
}


void selectionSort(unsigned int* p, int n)
{
    int k, i, j;
    unsigned int min;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        min = p[i];
        for (j = i + 1; j < n; j++)
        {
            if (p[j] < min)
            {
                k = j;
                min = p[j];
            }
        }
        p[k] = p[i];
        p[i] = min;
    }

}

void insertionSort(unsigned  int* p, int n) {

    int i, j, x;
    for (i = 1; i < n; i++)
    {
        x = p[i];
        j = i - 1;
        while (j >= 0 && x < p[j])
        {
            p[j + 1] = p[j];
            j = j - 1;
        }
        p[j + 1] = x;

    }
}

void shellSort(unsigned  int* p, int n) {

    int initInter, h, i, j, x;
    initInter = n / 2;
    for (h = initInter; h > 0; h = h / 2)
    {
        for (i = h; i < n; i++)
        {
            x = p[i];
            j = i - h;
            while (j >= 0 && x < p[j])
            {
                p[j + h] = p[j];
                j = j - h;
            }
            p[j + h] = x;
        }
    }
}

void quickSort(unsigned  int* p, int left, int right) {

    int partPos;
    if (left < right)
    {
        partPos = sortAndPartition(p, left, right);
        quickSort(p, left, partPos);
        quickSort(p, partPos + 1, right);
    }
}

int sortAndPartition(int p[], int left, int right)
{
    int mid, i, j, pivot, temp;
    mid = (left + right) / 2;
    pivot = p[mid];
    i = left - 1;
    j = right + 1;
    while (i < j)
    {
        do
        {
            i = i + 1;
        } while (p[i] < pivot);
        do
        {
            j = j - 1;
        } while (p[j] > pivot);
        if (i < j)
        {
            temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
    }
    return j;
}

void writeResultsToFile(FILE* f, char arrTypeLabels[3][7], char sortNames[4][11], float times[4][3], int n) {


    f = fopen("TIMES.txt", "w+");

    if (f == NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    fprintf(f, "Array size: %d\n", n);
    fprintf(f, "==============\n");
    fprintf(f, "\t\t    ");
    for (int i = 0; i < 3; i++)
        fprintf(f, "%s\t     ", arrTypeLabels[i]);
    fprintf(f, "\n");
    for (int i = 0; i < 4; i++)
    {
        fprintf(f, "%s", sortNames[i]);
        fprintf(f, "\t");
        if (i >= 2)
            fprintf(f, "\t");
        for (int j = 0; j < 3; j++)
            fprintf(f, "%10.3f\t", times[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void printsystemspecs() {
    printf("System Specs: \n");
    printf("\n");
    printf("Processor: \n\n");
    printf(" AMD Ryzen 5 3500U Mobile CPU \n");
    printf("   Base Clock 2.1GHz \n\n");
    printf("RAM: \n\n");
    printf("   8.00 GB \n");
    printf("   7.87 GB usable \n");
    printf("\n");
    printf("\n");
}

/*
void clearscreen(){
system("@cls||clear");
}
*/


