#include "StringProcessing.h"
#include <vector>
#include "../sort/Sort.h"
#include <iostream>

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

int dsa::knuth_morris_pratt(std::string& text, std::string& pattern)
{
    int m = pattern.length();
    std::vector<std::vector<int>> state_machine(128, std::vector<int>(m, 0));
    state_machine[static_cast<unsigned char>(pattern.at(0))][0] = 1;
    for (int X = 0, j = 1; j < m; j++)
    {
        for (int c = 0; c < 128; c++)
            state_machine[c][j] = state_machine[c][X];
        state_machine[static_cast<unsigned char>(pattern.at(j))][j] = j + 1;
        X = state_machine[static_cast<unsigned char>(pattern.at(j))][X];
    }

    int i, j;
    int N = text.size();
    for (i = 0, j = 0; i < N && j < m; i++)
        j = state_machine[static_cast<unsigned char>(text.at(i))][j];
    if (j == m) return i - m;
    else return N;
}