#include <iostream>
using namespace std;


int main(){
    int n;  
    double* a = new double[n];

    double* tmp = new double[2*n];

    for (unsigned int i = 0; i < n; i++){
        tmp[i] = a[i];
    }

    delete [] a;

    a = tmp; // Points a to tmp


    for (unsigned int k = 0; k <)

    return 0;
}
