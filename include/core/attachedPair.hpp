#ifndef ATTACHED_PAIR_HPP
#define ATTACHED_PAIR_HPP

#include "core/common.hpp"

template <typename T>
struct AttachedPair
{
public:
    int pk;
    T body;
};

template <typename T>
inline bool operator==(const AttachedPair<T>& tl, const AttachedPair<T>& tr)
{
    return (tl.pk == tr.pk) && (tl.body == tr.body);
}

template <typename T>
inline bool operator!=(const AttachedPair<T>& tl, const AttachedPair<T>& tr)
{
    return (tl.pk != tr.pk) || (tl.body != tr.body);
}

template <typename T>
inline bool operator<(const AttachedPair<T>& tl, const AttachedPair<T>& tr)
{
    return tl.pk < tr.pk;
}

template <typename T>
inline bool operator>(const AttachedPair<T>& tl, const AttachedPair<T>& tr)
{
    return tl.pk > tr.pk;
}

namespace std
{
template <typename T>
std::string to_string(const AttachedPair<T>& ap)
{
    return std::to_string(ap.pk) + ": " + std::to_string(ap.body);
}

} // namespace std

#endif // ATTACHED_PAIR_HPP
