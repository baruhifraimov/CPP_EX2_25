#pragma once
#include <iostream>

namespace mtrx {
	class Matrix{
		// Inner class for the array proxy, to implement the invalid access for the matrix
		// We will make it inline for the sake of clarity
		class HiddenArr {
			double* row;
			int size;
		public:
			HiddenArr(double* row, int size) : row(row), size(size) {}
			
			double& operator[](int index) {
				if (index < 0 || index >= size) {
					throw std::out_of_range("Index is out of bounds");
				}
				return row[index];
			}
	
			const double& operator[](int index) const {
				if (index < 0 || index >= size) {
					throw std::out_of_range("Index is out of bounds");
				}
				return row[index];
			}
		};
		private:
			double **mat_table;
			int size;
		public:
			// Constructor 1
			Matrix(int size);
			// Constructor 2
			Matrix(double** matrix, int size);
			// Copy Constructor
			Matrix(const Matrix & o);
			// Destructor
			~Matrix();
			// Operators:
			//~m1 (Transpose)
			Matrix operator~();
			// m1 = m2
			Matrix& operator=(const Matrix& o);
			// m1+m2
			Matrix operator+(const Matrix& o) const;
			// m1-m2
			Matrix operator-(const Matrix& o) const;
			// m1*m2
			Matrix operator*(const Matrix& o) const;
			// m1%m2
			Matrix operator%(const Matrix& o) const;
			// -m1
			Matrix operator-();
			// m1*<num>
			Matrix operator*(double num) const;
			// <num>*m1
			friend Matrix operator*(double num, const Matrix& o);
			// m1^<num>
			Matrix operator^(int num) const;
			// m1/<num>
			Matrix operator/(double num) const;
			// m1%<num>
			Matrix operator%(int num) const;
			// m1++
			Matrix operator++(int);
			// ++m1
			Matrix &operator++();
			// m1--
			Matrix operator--(int);
			// --m1
			Matrix &operator--();
			// m1[]
			HiddenArr operator[](int index);
			// m1 == m2
			bool operator==(const Matrix& o) const;
			// m1 != m2
			bool operator!=(const Matrix& o) const;
			// m1 < m2
			bool operator<(const Matrix& o) const;
			// m1 > m2
			bool operator>(const Matrix& o) const;
			// m1 <= m2
			bool operator<=(const Matrix& o) const;
			// m1 >= m2
			bool operator>=(const Matrix& o) const;
			// !m1 (Determinant)
			int operator!() const;
			// m1 += m2
			Matrix& operator+=(const Matrix& o);
			// m1 -= m2
			Matrix& operator-=(const Matrix& o);
			// m1 /= m2
			Matrix& operator/=(double num);
			// m1 *= m2
			Matrix& operator*=(const Matrix& o);
			// m1 %= m2
			Matrix& operator%=(const Matrix& o);
			// m1 *= num
			Matrix& operator*=(double num);
			// m1 %= num
			Matrix& operator%=(double num);
			// cout << m1 
			friend std::ostream& operator<<(std::ostream& os, const Matrix& o);
			// Determinator ezer
			int determinantHelper(double **mat, int n) const;

			
	};
}