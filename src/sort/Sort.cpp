#include "Sort.h"
#include <cstdlib>

template <typename T>
static void swap(T* array, int i, int j)
{
    T _temp = array[i];
    array[i] = array[j];
    array[j] = _temp;
}

template <typename T>
void shuffle(T* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int random = std::rand() % (i + 1);
        swap(array, i, random);
    }
}

template <typename T>
void dsa::merge(T *array, T *aux, int low, int mid, int high)
{
    for (int k = low; k <= high; ++k) {
        aux[k] = array[k];
    }

    int i = low;
    int j = mid + 1;

    for (int k = low; k <= high; k++)
    {
        if (i > mid) {
            array[k] = aux[j++];
        }
        else if (j > high) {
            array[k] = aux[i++];
        }
        else if (aux[j] < aux[i]) {
            array[k] = aux[j++];
        }
        else {
            array[k] = aux[i++];
        }
    }
}

template <typename T>
static void msort_helper(T *array, T *aux, int low, int high)
{
    if (high <= low)
        return;
    
    int mid = (low + high) / 2;
    msort_helper(array, aux, low, mid);
    msort_helper(array, aux, mid + 1, high);

    dsa::merge(array, aux, low, mid, high);
}

template <typename T>
void dsa::msort(T *array, int size)
{
    T *aux = new T[size];
    msort_helper(array, aux, 0, size - 1);
    delete[] aux;
}

template <typename T>
int dsa::partition(T* array, int low, int high)
{
    int i = low + 1;
    int j = high;

    while (true)
    {
        while (i <= high && array[i] < array[low])
            i++;
        
        while (j > low && array[j] > array[low])
            j--;
        
        if (i >= j)
            break;
        
        swap(array, i, j);
    }

    swap(array, low, j);
    return j;
}

template <typename T>
void qsort_helper(T* array, int low, int high)
{
    if (low >= high)
        return;
    int pivot = dsa::partition(array, low, high);
    qsort_helper(array, low, pivot - 1);
    qsort_helper(array, pivot + 1, high);
}

template <typename T>
void dsa::qsort(T* array, int size)
{
    shuffle(array, size);
    qsort_helper(array, 0, size - 1);
}