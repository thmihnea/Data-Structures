#include "StringProcessing.h"
#include <vector>
#include <iostream>
#include "../sort/Sort.h"

std::string lcp(std::string& a, std::string& b)
{
    int min_size = std::min(a.size(), b.size()), idx;
    for (idx = 0; idx < min_size && a[idx] == b[idx]; idx++);
    return a.substr(0, idx);
}

std::string dsa::longest_repeating_substring(std::string &s)
{
    int size = s.size();
    std::vector<std::string> suffixes(size);
    for (int i = 0; i < size; i++)
    {
        suffixes[i] = s.substr(i, size);
    }
    
    radix_quick_sort(suffixes);
    std::string lrs = "";

    for (int i = 0; i < size - 1; i++)
    {
        std::string prefix = lcp(suffixes[i], suffixes[i + 1]);
        if (prefix.size() > lrs.size())
            lrs = prefix;
    }

    return lrs;
}