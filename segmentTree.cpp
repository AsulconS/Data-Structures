#include <limits>
#include <iostream>

template <typename Summable>
void create(Summable* arr, Summable*& tree, const std::size_t size)
{
    tree = new Summable[size << 0x1];
    tree[0] = Summable {};

    for(std::size_t i = 0; i < size; ++i)
    {
        tree[size + i] = arr[i];
    }

    for(std::size_t i = size - 1; i > 0; --i)
    {
        tree[i] = tree[i << 0x1] + tree[i << 0x1 | 0x1];
    }
}

template <typename Summable>
void update(Summable&& val, Summable*& tree, std::size_t pos, const std::size_t size)
{
    pos += size;
	tree[pos] = std::forward<Summable>(val);

    while(pos > 1)
    {
        pos >>= 0x1;
        tree[pos] = tree[pos << 0x1] + tree[pos << 0x1 | 0x1];
    }
}

template <typename Summable>
Summable sum(std::size_t left, std::size_t right, Summable*& tree, const std::size_t size)
{
    Summable ret {};

    left += size;
    right += size + 1;

    while (left < right)
    {
        if (left & 0x1)
        {
            ret += tree[left++];
        }
        if (right & 0x1)
        {
            ret += tree[--right];
        }

        left >>= 0x1;
        right >>= 0x1;
    }

    return ret;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* tree;

    std::size_t size = sizeof(arr) / sizeof(arr[0]);

    // build tree
    create(arr, tree, size);

    for(int i = 0; i < size << 0x1; ++i)
        std::cout << tree[i] << ' ';
    std::cout << std::endl;

    std::cout << sum<int>(1, 3, tree, size) << std::endl;

    update(1, tree, 2, size);

    for(int i = 0; i < size << 0x1; ++i)
        std::cout << tree[i] << ' ';
    std::cout << std::endl;

    std::cout << sum<int>(1, 3, tree, size) << std::endl;

    return 0;
}
