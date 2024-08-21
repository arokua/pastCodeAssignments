#include "FilterGeneric.h"
#include "FilterNonPositive.h"

using namespace std;

FilterNonPositive::FilterNonPositive():FilterGeneric() {
}

bool FilterNonPositive::g(int n){
  return n < 1;
}