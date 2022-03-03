#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include "sort_alg.h"

#define TEST_N 4

static struct {
    unsigned short FLAG_NUM : 12;
    unsigned short FLAG_TIME : 1;
    unsigned short FLAG_TEST : 1;
    unsigned short FLAG_SWAP : 1;
    unsigned short FLAG_ARRAY : 1;
} FLAGS = {0, 0, 0, 0, 0};

static void print_array(elem_t* targetArray, size_t N) {
    // error processing
    assert(targetArray != NULL);
    if (N < 0) {
        fprintf(stderr, "ERROR: INCORRECT [N] - NUMBER OF ARRAY ELEMENTS");
        return;
    }
    for (size_t i = 0; i < N; ++i) printf("%d\t", targetArray[i]);
    printf("\n");
}

// TESTING
void test_algorithms(size_t SIZE) {
    srand(time(NULL));

    elem_t array_Bubble[SIZE];
    elem_t array_Quick[SIZE];

    for (size_t j = 0; j < SIZE; ++j) {
        elem_t temp = rand();
        array_Bubble[j] = temp;
        array_Quick[j] = temp;
    }
    if (FLAGS.FLAG_ARRAY) {
        printf("RANDOM ARRAY[%d]:", SIZE);
        print_array(array_Bubble, SIZE);
    }
    // BUBBLE SORT
    clock_t start = clock();
    BubbleSort(array_Bubble, SIZE);
    clock_t end = clock();

    if (FLAGS.FLAG_SWAP) printf("SWAPS/COMPARISONS BUBBLE-SORT: %d/%d\n", SWAPS, COMPARISONS);
    SWAPS = COMPARISONS = 0;

    if (FLAGS.FLAG_TIME) printf("BUBBLE SORT: %lf sec.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    // QUICK SORT
    start = clock();
    QuickSort(array_Quick, 0, SIZE - 1);
    end = clock();

    if (FLAGS.FLAG_SWAP) printf("SWAPS/COMPARISONS QUICK-SORT: %d/%d\n", SWAPS, COMPARISONS);
    SWAPS = COMPARISONS = 0;

    if (FLAGS.FLAG_TIME) printf("QUICK SORT: %lf sec.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    // ===================
    if (FLAGS.FLAG_ARRAY) {
        printf("SORTED ARRAY[%d]:", SIZE);
        print_array(array_Quick, SIZE);
    }
    if (FLAGS.FLAG_SWAP || FLAGS.FLAG_ARRAY || FLAGS.FLAG_TIME) {
        printf("========================================================");
    }
}

int main (int argc, char *argv[]) {
    int TEST_SIZE[TEST_N] = {10, 100, 1000, 10000};

    // command-line arguments
    int rez = 0;
    while ( (rez = getopt(argc, argv, "htosaN:")) != -1){
        switch (rez) {
            case 'h': printf("BUBBLE SORT && QUICK SORT (RECURSIVE, THE PIVOT is LAST)\n"
                             "==========================HELP==========================\n"
                             "-t \t show execution time of sorting algorithms\n"
                             "-o \t activate testing sorts\n"
                             "-s \t show numbers of swaps and comparisons\n"
                             "-a \t original and sorted array\n"
                             "-N <num> creating a random array of <num> (no more than 4095) elements and sorting\n"
                             "========================================================\n"); break;

            case 't': FLAGS.FLAG_TIME = 1; break;
            case 'o': FLAGS.FLAG_TEST = 1; break;
            case 's': FLAGS.FLAG_SWAP = 1; break;
            case 'a': FLAGS.FLAG_ARRAY = 1; break;
            case 'N': FLAGS.FLAG_NUM = atoi(optarg); break;
        } // switch
    } // while

    if (FLAGS.FLAG_NUM) {
        test_algorithms(FLAGS.FLAG_NUM);
    }
    if (FLAGS.FLAG_TEST) {
        for (size_t i = 0; i < TEST_N; ++i) {
            test_algorithms(TEST_SIZE[i]);
        }
    }
    return 0;
}
