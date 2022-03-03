#ifndef SORT_ALG_H
#define SORT_ALG_H

#ifndef elem_t
#define elem_t int
#endif
extern int SWAPS, COMPARISONS;

extern void BubbleSort (elem_t *targetArray, size_t N);
extern void QuickSort (elem_t *targetArray, int start, int end);
extern int Partition (elem_t *targetArray, int start, int end);
#endif //SORT_ALG_H





