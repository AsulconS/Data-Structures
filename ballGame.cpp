#include <memory>
#include <iostream>

#include "core/common.hpp"

template <typename T>
void print(const T* data, const size_t count)
{
    std::cout << "[ ";
    for(size_t i = 0; i < count; ++i)
        std::cout << data[i] << ' ';
    std::cout << "]\n";
}

template <typename T>
void copy(T* destination, T* source, const size_t count)
{
    for(size_t i = 0; i < count; ++i)
        destination[i] = source[i];
}

template <typename TArg, typename T>
void insertAt(TArg&& val, const uint32 pos, T*& data, const size_t size)
{
    T* newData = new T[size + 1];
    copy(newData, data, pos);

    newData[pos] = std::forward<TArg>(val);

    copy(newData + pos + 1, data + pos, size - pos);

    delete[] data;
    data = newData;
}

template <typename T>
void deleteAt(const uint32 pos, T*& data, const size_t size)
{
    T* newData = new T[size - 1];
    copy(newData, data, pos);

    copy(newData + pos, data + pos + 1, size - pos);

    delete[] data;
    data = newData;
}

int main()
{
    int size  {};
    int count {};

    std::cout << "Ingrese el tamano: ";
    std::cin >> size;

    int* data = new int[size];

    std::cout << "Ingrese los elementos: ";
    for(size_t i = 0; i < size; ++i)
        std::cin >> data[i];
    
    std::cout << "Ingrese el indice: ";
    std::cin >> count;

    std::cout << std::endl;
    print(data, size);

    int index {};
    while(size > 1)
    {
        index += count % size;
        if(index >= size) index -= size;

        deleteAt(index, data, size--);
        print(data, size);
    }
    
    std::cout << "El ganador es . . . ";
    print(data, size);

    return 0;
}
