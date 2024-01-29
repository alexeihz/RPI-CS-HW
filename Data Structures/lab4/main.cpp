#include <cmath>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

void compute_squares(uintptr_t n, uintptr_t* a, uintptr_t* b){
	for(uintptr_t i = 0; i< n; i++){
		*(b+i) = *(a+i) * *(a+i);
	}
}

int main() {
	uintptr_t n = 1;
	uintptr_t* a = new uintptr_t[n];
	uintptr_t* b = new uintptr_t[n];
	*a = 6;
	compute_squares(n,a,b);
	
	cout << *b << endl;
	
	delete [] a;
	delete [] b;
	
	return 0;
}