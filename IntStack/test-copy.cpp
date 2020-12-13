#include "IntStack.h"

int main () {
  IntStack st1 (100);
  IntStack st2 = st1;
  st1.push (10);
  st2.push (20);
  st1.print (); // ? [10 [
  st2.print (); // ? [20 [
  return 0;
}