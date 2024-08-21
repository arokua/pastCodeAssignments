#include "FilterGeneric.h"
#include "FilterOdd.h"

using namespace std;

FilterOdd::FilterOdd():FilterGeneric() {
}

bool FilterOdd::g(int n){
  return n % 2 == 1;
}