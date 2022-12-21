#include <random>
#include <iostream>

#define DSTR_IMPLEMENTATION
#include "dataStructures.hpp"

int main()
{
    /*std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_real_distribution<double> dist(0, 512);

    std::vector<int> randomData;
    for(int i = 0; i < 64; ++i)
    {
        randomData.push_back(dist(mt));
    }*/

    Hash<int, 1000000> hash;

    hash.initialize();
    hash.allNum(100);

    return 0;
}
