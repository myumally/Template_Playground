#include "pack.hpp"

template<typename T, EnableIf<(sizeof(T) > 2)>* = nullptr>
void f(T const&) {
  std::puts("> 2");
}

template<typename T, EnableIf<(sizeof(T) <= 2)>* = nullptr>
void f(T const&) {
  std::puts("≤ 2");
}

int main(){
  using P0=Pack<char>;
  bool boo = packContains<P0, char>;
  if(boo) printTypes<PackPushBack<P0, int>>(5);

  using P1 = Pack<int, char, char, int, int, void, float, long, int, float, int, int>;
  printTypes<P1>();
  printTypes<Reverse<P1>>();
  printTypes<Unique<P1>>();

  using P2 = Pack<int, char, float, bool, char, void>;
  using V0 = PackGet<P2, 0>;
  using V2 = PackGet<P2, 2>;
  using V5 = PackGet<P2, 5>;
  printTypes<V0, V2, V5>();

  using A = RemoveCV<int const>; // int
  using B = RemoveCV<int>; // int
  using C = RemoveCV<int* volatile>; // int*
  using D = RemoveCV<int const&>; // int const&
  using E = RemoveCV<int* const** const>; // int* const**
  printTypes<A, B, C, D, E>();

  f('a'); // ≤ 2
  f(0);   // > 2
}
