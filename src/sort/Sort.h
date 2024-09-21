#ifndef DS_SORT_H
#define DS_SORT_H

namespace dsa
{
    template <typename T>
    void merge(T* array, T* aux, int low, int mid, int high);

    template <typename T>
    int partition(T* array, int low, int high);

    template <typename T>
    void msort(T* array, int size);

    template <typename T>
    void qsort(T* array, int size);
}

#endif