/** -----------------------------------------------------------------
 * main.c
 * @brief Comparing sorting algorithms implemented in C and assembly
 * @author Kristjan Eimre
 * @date 04.01.2016
 * ------------------------------------------------------------------
 */

#include <stdio.h>      // printf
#include <stdlib.h>     // qsort, rand
#include <time.h>       // time
#include <string.h>     // memcpy
#include <stdbool.h>    // boolean 

#include "libsortasm.h"

/**
 * Leiab mediaani kolmest sisseantud t2isarvust
 */
int median(int a, int b, int c) {
    if ((b < a && a < c) || (b > a && a > c)) return a;
    else if ((a < b && b < c) || (a > b && b > c)) return b;
    else return c;
}

/**
 * @param a - sorteeritava jada esimese elemendi pointer
 * @param n - sorteeritava jada pikkus
 */
void cQuickSort(int* a, int n) {
    if (n < 2)
        return;
    // pivoti valimiseks on hea võtta keskmine element
    int p = a[n/2];
    // mediaani kasutades pivotina on algoritm kiirem, kuid
    // assembleriga võrdluseks kasutan sama algritmi
    //int p = median(a[0], a[n/2], a[n-1]);
    
    // jaotame pivoti järgi jada kaheks pooleks
    int i = 0;
    int j = n-1;
    int t;
    while (1) {
        // liigume vasakult poolt elemente pidi kuni
        // jõuame pivotist suuremani või võrdseni
        while (a[i]<p) i++;
        // sama paremalt poolt alustades
        while (a[j]>p) j--;
        // kui m6lemad osad sama kaugel, on jada l2bi vaadatud
        if (i>=j)
            break;
        
        // vahetame leitud elemendid
        t=a[i]; a[i]=a[j]; a[j]=t;
        // astume edasi (siis vaja, kui on pivotiga v6rdne v22rtus ees)
        i++;
        j--;
    }
    // kordame sama protseduuri pivotist
    // väiksemate ja suuremate alamjadade jaoks
    cQuickSort(a, i);
    cQuickSort(a+i, n-i);
      
}

/**
 * @param a - sorteeritava jada esimese elemendi pointer
 * @param n - sorteeritava jada pikkus
 */
void cInsertionSort(int* a, int n) {
    // algorithmi puhul k2ime jada alguses pealt l2bi
    // ja arvestame, et eelnev jada on juba sorteeritud
    int i = 1, j, t;
    while (i < n) {
        t = a[i];
        j = i - 1;
        // käime elemendile i eelneva, sorteeritud osa l2bi
        // ja lykkame t-st suuremad elemendid yhe v6rra edasi
        while (j >= 0 && a[j] > t) {
            a[j+1] = a[j];
            j--;
        }
        // a[j] oli v2iksem kui t, seega t sobib
        // t2pselt a[j+1] kohale
        a[j+1] = t;
        i++;
    }
}

/**
 * T2isarvude v6rdlemise funktsioon qsort-le
 */
int comp (const void * elem1, const void * elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

/**
 * T2idab sisseantud jada juhusliku t2isarvudega
 */
void randomizeArray(int* arr, int n) {
    srand ( time(NULL) );
    for (int i = 0; i<n; i++)
        arr[i] = rand()%100;
}

/**
 * V2ljastab jada stdout-i
 */
void printArray(int* arr, int n) {
    for (int i = 0 ; i < n ; i++)
        printf ("%d ", arr[i]);
    printf("\n");
}

/**
 * V6rreldavate algoritmide hulk
 */ 
typedef enum {
    QSORT,          // C standardteegi sorteerimine qsort()
    C_QUICK,        // C-s kirjutatud quicksort cQuickSort()
    ASM_QUICK,      // Assembleris kirjutatud quicksort (sama algoritm nagu C_QUICK)
    C_INSERT,       // C-s kirjutatud insertion sort cInsertionSort()
    ASM_INSERT      // Assembleris kirjutatud insertion sort (sama algoritm nagu C_INSERT)
} algorithm;


/**
 * Teeb etteantud jadast <arr> koopia ja jooksutab algorithmi <alg> selle peal.
 * Samuti m66dab aega ja vajadusel v2ljastab sorteeritud jada.
 */
void sortAndTime(const int* arr, int LEN, algorithm alg, bool print) {
    int *a = malloc(LEN*sizeof(int));
    memcpy(a, arr, LEN*sizeof(*arr));
    clock_t start = clock();
    switch (alg) {
        case QSORT:
            printf("Running qsort(); ");
            qsort(a, LEN, sizeof(*a), comp);
            break;
        case C_QUICK:
            printf("Running cQuickSort(); ");
            cQuickSort(a, LEN);
            break;
        case ASM_QUICK:
            printf("Running asmQuickSort(); ");
            asmQuickSort(a, LEN);
            break;
        case C_INSERT:
            printf("Running cInsertionSort(); ");
            cInsertionSort(a, LEN);
            break;
        case ASM_INSERT:
            printf("Running asmInsertionSort(); ");
            asmInsertionSort(a, LEN);
            break;
        default:
            printf("Algorithm not recognized.");
    }
    clock_t end = clock();
    int msec = ((end-start))*1000 / CLOCKS_PER_SEC;
    printf("time taken: %d ms \n", msec);
    
    if (print) {
        printf("Result:\n");
        printArray(a, LEN);
    }
    free(a);
}


int main() {
    
    #define LEN  10000000   // nlogn algoritmide jada pikkus
    #define LEN2 100000     // n^2 algoritmide jada pikkus
    bool print = false;     // kas v2ljastada jadad stdouti?
    
    int *arr = malloc(LEN*sizeof(int));
    randomizeArray(arr, LEN);
    printf("Length of array: %d \n", LEN);
    if (print) {
        printf("Initial array:\n");
        printArray(arr, LEN);
    }
    
    sortAndTime(arr, LEN, QSORT, print);
    sortAndTime(arr, LEN, C_QUICK, print);
    sortAndTime(arr, LEN, ASM_QUICK, print);
    
    // Insertion sort on oluliselt aeglasem kui teised,
    // seega ei saa seda sama jada pikkuse juures m66ta
    
    int *arr2 = malloc(LEN2*sizeof(int));
    randomizeArray(arr2, LEN2);
    printf("Length of array2: %d \n", LEN2);
    if (print) {
        printf("Initial array2:\n");
        printArray(arr2, LEN2);
    }
    sortAndTime(arr2, LEN2, C_INSERT, print);
    sortAndTime(arr2, LEN2, ASM_INSERT, print);
    
    free(arr);
    free(arr2);
    return 0;
}

