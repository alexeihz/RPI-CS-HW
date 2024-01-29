#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function

int main() {
	std::cout << "Enter length of array" << std::endl;
    int len;
    std::cin >> len;
	float array[len],num,sum = 0;
	std::cout << "Enter some values" << std::endl;
	for (int i=0; i<len;i++){
		std::cin >> num;
		array[i] = num;
		sum = sum + num;
	}
	float avg = sum/len;
	std::cout << "Average = " << avg << std::endl;
	for (int j=0;j<len;j++){
		if (array[j] < avg){
			std::cout << array[j] << std::endl;
		}
	}
 }