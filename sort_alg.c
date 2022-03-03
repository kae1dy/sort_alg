#include <stdio.h>
#include <assert.h>

#ifndef elem_t
#define elem_t int
#endif

int SWAPS, COMPARISONS;

// O(n^2)
void BubbleSort (elem_t *targetArray, size_t N) {
    // error processing
    assert(targetArray != NULL);
    if (N < 0) {
        fprintf(stderr, "ERROR: INCORRECT [N] - NUMBER OF ARRAY ELEMENTS");
        return;
    }
    // Bubble-Sort algorithm
    for (size_t i = 0; i < N-1; ++i) {
        for (size_t j = 0; j < N-i-1; ++j) {
            ++COMPARISONS;
            // compare
            if (targetArray[j] < targetArray[j+1]) {
                ++SWAPS;
                // swap
                elem_t temp = targetArray[j];
                targetArray[j] = targetArray[j+1];
                targetArray[j+1] = temp;
            }
        }
    }
}
// MAIN ELEMENT - LAST
int Partition (elem_t *targetArray, int start, int end) {
    elem_t value = targetArray[end];
    int pos = start;

    for (size_t i = start; i < end; ++i) {
        ++COMPARISONS;
        // compare
        if (targetArray[i] >= value) {
            ++SWAPS;
            // swap
            elem_t temp = targetArray[i];
            targetArray[i] = targetArray[pos];
            targetArray[pos] = temp;

            ++pos;
        }
    }
    targetArray[end] = targetArray[pos];
    targetArray[pos] = value;
    return pos;
}
// O(n log n)
void QuickSort (elem_t *targetArray, int start, int end) {
    // error processing
    assert(targetArray != NULL);

    if (start >= end || start < 0) return;

    int pos = Partition(targetArray, start, end);

    QuickSort(targetArray, start, pos-1);
    QuickSort(targetArray, pos+1, end);
}