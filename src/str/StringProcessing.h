#ifndef DS_STRING_PROCESSING_H
#define DS_STRING_PROCESSING_H

#include <string>

namespace dsa
{
    std::string longest_repeating_substring(std::string &s);

    int knuth_morris_pratt(std::string& text, std::string& pattern);
}

#endif