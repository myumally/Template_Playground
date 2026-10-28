#include "pack.hpp"

int main(){
  using P0=Pack<char>;
  bool boo = packContains<P0, char>;
  if(boo) printTypes<PackPushBack<P0, int>>(5);

  using P1 = Pack<int, char, char, int, int, void, float, long, int, float, int, int>;
  printTypes<P1>();
  printTypes<Reverse<P1>>();
  printTypes<Unique<P1>>(); 
}
