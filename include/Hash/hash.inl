template <typename T, int N>
void Hash<T, N>::insert(const BinaryPair<T>& key)
{
    std::size_t index = key.hb * key.hb * key.hb + key.lb * key.lb * key.lb;
    std::cout << index << std::endl;
    if(data[index].hb.hb == 0 && data[index].hb.lb == 0)
        data[index].hb = key;
    else
        data[index].lb = key;
}

template <typename T, int N>
void Hash<T, N>::initialize()
{
    for(int i = 0; i < floor(cbrt(N)); ++i)
    {
        for(int j = i + 1; j <= floor(cbrt(N)); ++j)
        {
            insert({i, j});
        }
    }
}

template <typename T, int N>
void Hash<T, N>::allNum(int l)
{
    for(std::size_t i = 0; i < l; ++i)
    {
        if((data[i].hb.hb != 0 || data[i].hb.lb != 0) && (data[i].lb.hb != 0 || data[i].lb.lb != 0))
            std::cout << i << std::endl;
    }
}
