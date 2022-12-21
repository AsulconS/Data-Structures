#ifndef CORE_UTILS_HPP
#define CORE_UTILS_HPP

template<typename T> struct argument_type;
template<typename T, typename U> struct argument_type<T(U)> { typedef U type; };

#define unparentheses_type(T) argument_type<void(T)>::type

#endif // CORE_UTILS_HPP
