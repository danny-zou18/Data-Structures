#include <cmath>
#include <iostream>

using namespace std;

void compute_squares(unsigned int * a,unsigned int * b,unsigned n){
    for (unsigned int i = 0; i < n;i++){
        *b = *a * *a;
        b++;
        a++;
    }
}
int main(){
    unsigned int a[5] = {2,5,6,7,8};
    unsigned int b[5];

    compute_squares(a,b,5);
    for (unsigned int i = 0; i < 5; i++){
        cout << a[i] << " " << b[i] << endl;
    }
}
