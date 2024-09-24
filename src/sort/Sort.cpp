#include "Sort.h"
#include "../collection/Heap.h"
#include <cstdlib>
#include <iostream>
#include <string>

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

template <typename T>
void dsa::hsort(T* array, int size)
{
    auto f = [](int x, int y)
    {
        if (x < y) return 1;
        else if (x > y) return -1;
        else return 0;
    };

    auto heap = Heap<int>(f);
    for (int i = 0; i < size; i++)
    {
        heap.push(array[i]);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        array[i] = heap.pop();
    }
}

template <typename T>
void dsa::key_indexed_count(T* array, int size, int radix)
{
    // Performs a key indexed sort - requires no
    // comparison between elements.
    // Should be used when we have to sort an array
    // of length N with at most R unique entries, with
    // R << N.
    // This is the basis of Radix Sort.
    T *count = new T[radix + 1];

    for (int i = 0; i < size; i++)
    {
        // Compute frequency of elements. Store the
        // frequency of array[i] into position
        // array[i] + 1.
        count[array[i] + 1]++; 
    }

    for (int r = 0; r < radix; r++)
    {
        // Compute 'prefix counts'.
        // If freq[1] = 2, freq[2] = 3, then
        // freq[2] becomes 5.
        // This tells us how many keys smaller than
        // r there are.
        count[r + 1] += count[r];
    }

    T* aux = new T[size];
    for (int i = 0; i < size; i++)
    {
        aux[count[array[i]]++] = array[i];
    }

    for (int i = 0; i < size; i++)
    {
        array[i] = aux[i];
    }

    delete[] aux, count;
}

void dsa::lsd_radix_sort(std::vector<std::string>& array, int max_length)
{
    int radix = 256; // ASCII radix
    int size = array.size();
    std::vector<std::string> aux(size);

    for (int d = max_length - 1; d >= 0; d--)
    {
        int* count = new int[radix + 1](); // Zero-initialize the count array
        for (int i = 0; i < size; i++)
        {
            count[static_cast<unsigned char>(array[i][d]) + 1]++;
        }
        for (int r = 0; r < radix; r++)
        {
            count[r + 1] += count[r];
        }
        for (int i = 0; i < size; i++)
        {
            aux[count[static_cast<unsigned char>(array[i][d])]++] = array[i];
        }
        for (int i = 0; i < size; i++)
        {
            array[i] = aux[i];
        }
        delete[] count;
    }
}

static int char_at(const std::string& s, int d)
{
    return d < s.size() ? static_cast<unsigned char>(s[d]) : -1;
}

static void msd_sort_helper(std::vector<std::string>& array, std::vector<std::string>& aux, int low, int high, int d)
{
    if (high <= low) return;
    int radix = 256;
    int* count = new int[radix + 2]();

    for (int i = low; i <= high; i++)
    {
        int c = char_at(array[i], d);
        count[c + 2]++;
    }
    for (int r = 0; r <= radix; r++)
        count[r + 1] += count[r];
    for (int i = low; i <= high; i++)
    {
        int c = char_at(array[i], d);
        aux[count[c + 1]++] = array[i];
    }

    for (int i = low; i <= high; i++)
        array[i] = aux[i - low];

    for (int r = 0; r <= radix; r++)
    {
        msd_sort_helper(array, aux, low + count[r], low + count[r + 1] - 1, d + 1);
    }

    delete[] count;
}

void dsa::msd_radix_sort(std::vector<std::string>& array)
{
    std::vector<std::string> aux(array.size());
    msd_sort_helper(array, aux, 0, array.size() - 1, 0);
}

static void str_exch(std::vector<std::string>& array, int i, int j)
{
    std::string& _temp = array[i];
    array[i] = array[j];
    array[j] = _temp;
}

static void radix_quicksort_helper(std::vector<std::string>& array, int low, int high, int d)
{
    if (high <= low) return;
    int lt = low, gt = high;
    int v = char_at(array[low], d);
    int i = low + 1;
    while (i <= gt)
    {
        int t = char_at(array[i], d);
        if (t < v) str_exch(array, lt++, i++);
        else if (t > v) str_exch(array, i, gt--);
        else i++;
    }

    radix_quicksort_helper(array, low, lt - 1, d);
    if (v >= 0) radix_quicksort_helper(array, lt, gt, d + 1);
    radix_quicksort_helper(array, gt + 1, high, d);
}

void dsa::radix_quick_sort(std::vector<std::string>& array)
{
    radix_quicksort_helper(array, 0, array.size() - 1, 0);
}