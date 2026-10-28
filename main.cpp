#include "pack.hpp"

int main(){
  using P0=Pack<char>;
  bool boo = packContains<P0, char>;
  if(boo) printTypes<PackPushBack<P0, int>>(5);
}
