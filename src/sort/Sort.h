#ifndef DS_SORT_H
#define DS_SORT_H

#include <string>
#include <vector>

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

    template <typename T>
    void hsort(T* array, int size);

    template <typename T>
    void key_indexed_count(T* array, int size, int radix);

    void lsd_radix_sort(std::vector<std::string>& array, int max_length);

    void msd_radix_sort(std::vector<std::string>& array);

    void radix_quick_sort(std::vector<std::string>& array);
}

#endif