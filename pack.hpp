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



template <typename P> struct ReverseImpl;

template <template<typename...> typename P, typename T, typename... Ts>
struct ReverseImpl<P<T, Ts...>> {
  using type = PackPushBack<typename ReverseImpl<P<Ts...>>::type, T>;
};

template <template<typename...> typename P>
struct ReverseImpl<P<>> {
  using type = P<>;
};

template <typename P>
using Reverse = typename ReverseImpl<P>::type;



template <bool C, typename T, typename F> struct IfImpl;

template <typename T, typename F>
struct IfImpl<true, T, F> {
  using type = T;
};

template <typename T, typename F>
struct IfImpl<false, T, F> {
  using type = F;
};

template <bool C, typename T, typename F>
using If = typename IfImpl<C, T, F>::type;



template <typename P> struct UniqueImpl;

template <template<typename...> typename P, typename T, typename... Ts>
struct UniqueImpl<P<T, Ts...>> {
  using type = If< packContains<P<Ts...>, T>, typename UniqueImpl<P<Ts...>>::type, PackPushBack< typename UniqueImpl<P<Ts...>>::type, T > >;
};

template <template<typename...> typename P>
struct UniqueImpl<P<>> {
  using type = P<>;
};

template <typename P>
using Unique = typename UniqueImpl<Reverse<P>>::type;

template <typename P, int N> struct PackGetImpl;

template <template <typename...> typename P, int N, typename T, typename... Ts>
struct PackGetImpl<P<T, Ts...>, N> {
  using type = typename PackGetImpl<P<Ts...>, N-1>::type;
};

template <template <typename...> typename P, typename T, typename... Ts>
struct PackGetImpl<P<T, Ts...>, 0> {
  using type = T;
};

template <typename P, int N>
using PackGet = typename PackGetImpl<P, N>::type;



template <typename T> struct RemoveCVImpl;

template<typename T>
struct RemoveCVImpl<T const> {
  using type = T;
};

template<typename T>
struct RemoveCVImpl<T volatile> {
  using type = T;
};

template<typename T>
struct RemoveCVImpl {
  using type = T;
};

template <typename T>
using RemoveCV= typename RemoveCVImpl<T>::type;



template <bool B> struct EnableIfImpl;

template<>
struct EnableIfImpl<true> {
  using type = bool;
};

template <bool B>
using EnableIf = typename EnableIfImpl<B>::type;



struct Add{
  template <typename T> 
    static T eval(T l, T r){
      return l + r;
    }
};

struct Mul{
  template <typename T> 
    static T eval(T l, T r){
      return l * r;
    }
};


template<typename T>
class Val{
  T _val;

  public:
  Val(T v) : _val(v){};
  Val() {};

  T eval() const {
    return _val;
  }
};

template<typename Op, typename L, typename R>
struct BinExpr{
  L l;
  R r;

  auto eval(){
    return Op::eval(l.eval(), r.eval());
  }

  auto operator()(L l, R r){
    return Op::eval(l.eval(), r.eval());
  }
};


template<typename L, typename R>
auto operator+(L l, R r) { 
  return BinExpr<Add, L, R>{l,r};
}

template<typename L, typename R>
auto operator*(L l, R r) { 
  return BinExpr<Mul, L, R>{l,r};
}

#endif
