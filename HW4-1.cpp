#include "HW4-1.h"
#include <iostream>

int main() {
    // Create two 3x3 matrices
    mpcs51044::Matrix<3, 3> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    mpcs51044::Matrix<3, 3> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

	//This matrix will be used to test the static_asserts
	    mpcs51044::Matrix<2,2> matrix3 = {
        {9, 8},
        {6, 5},
    };

    // Print the original matrices
    std::cout << "Matrix 1:" << std::endl;
    std::cout << matrix1 << std::endl;

    std::cout << "Matrix 2:" << std::endl;
    std::cout << matrix2 << std::endl;

    // Add the matrices using the overloaded + operator
    mpcs51044::Matrix<3, 3> matrixSum = matrix1 + matrix2;
	// Add the matrices using the overloaded += operator
	mpcs51044::Matrix<3, 3> matrixSum2 = matrix1 += matrix2;



    // Print the result
    std::cout << "Matrix Sum (Matrix1 + Matrix2) using operator+:" << std::endl;
    std::cout << matrixSum << std::endl;
	std::cout << "Matrix Sum (Matrix1 + Matrix2) using operator+=:" << std::endl;
    std::cout << matrixSum2 << std::endl;

	/**
	 * This block is designed to test my static_assert statements in the header file
	 * They ensure that any operator+ or operator+= overloads only attempt to add
	 * matrices that are the same size. If you try to run this code as it, it will compile and run correctly
	 * If you uncomment the below lines and try to run it, you will receive a compile error
	 * This is how we know our static_asserts in the header file are working correctly
	 */
	// auto matrixError1 = matrix1 + matrix3;
	// auto matrixError2 = matrix1 += matrix3;
	// std::cout << "Testing static_assert on operator+ (output should be an error message):\n";
	// std::cout << matrixError1 << "\n";
	// std::cout << "Testing static_assert on operator+= (output should be an error message):\n";
	// std::cout << matrixError2 << "\n";

    return 0;
}