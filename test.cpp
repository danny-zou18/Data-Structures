#include <iostream>
using namespace std;

// Recursive function to calculate factorial
int factorial(int n) {
   if (n == 0) {
      return 1; // Base case
   } else {
      return n * factorial(n - 1); // Recursive call
   }
}
int main() {
   int n = 5;
   factorial(n);

   return 0;
}
