#include "FilterGeneric.h"
#include "FilterForTwoDigitPositive.h"

using namespace std;

FilterForTwoDigitPositive::FilterForTwoDigitPositive():FilterGeneric() {
}

bool FilterForTwoDigitPositive::g(int n){
  return (9 < n and n < 100);
}