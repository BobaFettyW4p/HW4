#include "Matrix.h"
#include <iostream>
#include <chrono>
using namespace mpcs51044;
using namespace std;

int main()
{
	auto start = chrono::system_clock::now();
	Matrix<3, 3> m = { 
			{ 1, 2, 3, }, 
			{ 4, 5, 6, },
			{7, 8, 9, } 
	};
	static double total;
	for (int i = 0; i < 100'000'000; i++) {
		m(1, 1) = i;
		total += m.determinant();
	}
	cout << chrono::duration<double>(chrono::system_clock::now() - start).count() << " seconds\n";
}

//elapsed time with my direct implentation of determinant() for 2x2 matrices in Matrix.h
//29.5539 seconds

//elapsed time with my direct implemntation of determinant() for 2x2 matrices commented out
//41.7557 seconds