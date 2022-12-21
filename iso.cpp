#include <string>
#include <cstring>
#include <iostream>

#define MAXC 256

#define DSTR_IMPLEMENTATION
#include "dataStructures.hpp"

bool areIso(const std::string& a, const std::string& b)
{
    std::size_t m = a.length();
    std::size_t n = b.length();

    if(m != n)
    {
        return false;
    }

    bool marked[MAXC] = { false };

    int hash[MAXC];
    memset(hash, -1, sizeof(hash));

    for(std::size_t i = 0; i < n; ++i)
    {
        if (hash[a[i]] == -1)
        {
            if (marked[b[i]])
            {
                return false;
            }

            marked[b[i]] = true;
            hash[a[i]] = b[i];
        }
        else if (hash[a[i]] != b[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
   std::cout << areIso("IEEE", "XZZZ") << std::endl;
   std::cout << areIso("ADRIAN", "DZMODL") << std::endl;
   std::cout << areIso("CSUNSA", "ABCDEF") << std::endl;
   std::cout << areIso("XYZ", "AB") << std::endl;

   return 0;
}
