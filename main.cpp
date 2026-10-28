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


  Val<int> a, b;
  auto e = a + b;
  auto f = a * b;
  auto g = a + a * a + a;
  auto h = a + f;
  auto k = e * a;
  auto l = e + f;
  std::printf("e(5, 7) = %d\n", e(5, 7)); // 5+7= 12
  std::printf("f(5, 7) = %d\n", f(5, 7)); // 5*7= 35
  std::printf("g({1, {7, 2}}, 5) = %d\n", g({1, {7, 2}}, 5)); // (1+(7*2))+5= 20
  std::printf("h(1, {7, 5}) = %d\n", h(1, {7, 5})); // 1+(7*5)= 36
  std::printf("k({7, 5}, 2) = %d\n", k({7, 5}, 2)); // (7+5)*2= 24
  std::printf("l({7, 5}, {2, 3}) = %d\n", l({7, 5}, {2, 3})); // (7+5)+(2*3)= 18 

}
