#ifndef PACK_HPP
#define PACK_HPP

#include <cstdio>

template <typename...>
struct Pack{};

template <typename..., typename... Args>
void printTypes(Args...){
  std::puts(__PRETTY_FUNCTION__);
}



template <typename P, typename... T> struct PackPushBackImpl;

template <template<typename...> typename P, typename... Ts, typename... T>
struct PackPushBackImpl<P<Ts...>, T...> {
  using type = P<Ts..., T...>;
};

template <typename P, typename... T>
using PackPushBack = typename PackPushBackImpl<P, T...>::type;



template <typename P, typename T> struct packContainsImpl;

template<typename P, typename T>
struct packContainsImpl{
  static constexpr bool value = false;
};

template<template<typename...> typename P, typename T, typename... Ts>
struct packContainsImpl<P<T, Ts...>, T> {
  static constexpr bool value = true;
};

template<template<typename...> typename P, typename T, typename F, typename... Ts>
struct packContainsImpl<P<F, Ts...>, T>{
  static constexpr bool value = packContainsImpl<P<Ts...>, T>::value;
};

template <typename P, typename T>
constexpr bool packContains = packContainsImpl<P, T>::value;

#endif
