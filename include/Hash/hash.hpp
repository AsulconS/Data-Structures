#ifndef HASH_HPP
#define HASH_HPP

#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "core/common.hpp"
#include "core/pair.hpp"

template <typename T, int N>
class Hash
{
public:
    Hash() : data(N + 1, {{}}) {}
    virtual ~Hash() {}

    void insert(const BinaryPair<T>& key);

    void initialize();

    void allNum(int l);

private:
    std::vector<BinaryPair<BinaryPair<T>>> data;
};

#endif // HASH_HPP
