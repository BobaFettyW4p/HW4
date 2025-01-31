#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>
//this library has support for static_assert, which lets us ensure that we only try to add 2 matrices of the same exact size
#include <type_traits>

#undef minor // Some compilers have a macro named minor

using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::inner_product;
using std::ostream;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::endl;
using std::max;


namespace mpcs51044 {

template<int rows, int cols = rows>
class Matrix {
public:
	Matrix() : data{} {}
	Matrix(initializer_list<initializer_list<double>> init) {
		auto dp = data.begin();
		for (auto row : init) {
			std::copy(row.begin(), row.end(), dp->begin());
			dp++;
		}
	}
	double &operator()(int x, int y) {
		return data[x][y];
	}

	double operator()(int x, int y) const {
		return data[x][y];
	}
	/**
	 * @brief operator+ overload for the Matrix class
	 * The function begins with a static assert that ensures the matrices that are being added together are the same size
	 * If they are not, the static_assert will prevent compilation
	 * Otherwise, the function proceeds to leverage the operator+= overload to add the matrices
	 */
    Matrix operator+(const Matrix& right) const {
        static_assert(rows == rows && cols == cols,
					"These matrices are of different sizes. Remember, matrix addition only works if both are exactly the same size.");
		return Matrix(*this) += right;
    }

	/**
	 * @brief operator+= overload for the Matrix class
	 * The function begins with a static assert that ensures the matrices that are being added together are the same size
	 * If they are not, the static_assert will prevent compilation
	 * Otherwise, the function will proceed to add the matrices
	 * This implementation performs operations directly on *this
	 * This is more efficient and carries no tradeoffs in the event that the original matrix will no longer be needed once the addition operation is completed
	 */
	Matrix& operator+=(const Matrix& right) {
		static_assert(rows == rows && cols == cols,
					"These matrices are of different sizes. Remember, matrix addition only works if both are exactly the same size.");
        for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				(*this)(i,j) += right(i,j);
			}
		}
		return *this;
    }

	inline friend
		ostream &
		operator<<
		(ostream &os, const Matrix<rows, cols> &m) {
		size_t width = m.longestElementSize() + 2;
		os << "[ " << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				os << setw(static_cast<streamsize>(width)) << m(i, j);
			}
			os << endl;
		}
		os << "]" << endl;
		return os;
	}

	Matrix<rows - 1, cols - 1> minor(int r, int c) const {
		Matrix<rows - 1, cols - 1> result;
		for (int i = 0; i < rows; i++) {
			if (i == r) {
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (j == c) {
					continue;
				}
				result(i < r ? i : i - 1, j < c ? j : j - 1) = data[i][j];
			}
		}
		return result;
	}

	double determinant() const {
		double val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).determinant();
		}
		return val;
	}

private:
	static size_t accumulateMax(size_t acc, double d) {
		ostringstream ostr;
		ostr << d;
		return std::max(acc, ostr.str().size());
	}
	static size_t accumulateMaxRow(size_t acc, array<double, cols> row) {
		return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
	}
	size_t longestElementSize() const {
		return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
	}
	array<array<double, cols>, rows> data;
};

template<>
double
Matrix<1, 1>::determinant() const
{
	return data[0][0];
}

template<int a, int b, int c>
inline Matrix<a, c>
operator*(Matrix<a, b> const &l, Matrix<b, c> const &r)
{
	Matrix<a, c> result;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			double total = 0;
			for (int k = 0; k < b; k++)
				total += l(i, k) * r(k, j);
			result(i, j) = total;
		}
	}
	return result;
}
}
#endif