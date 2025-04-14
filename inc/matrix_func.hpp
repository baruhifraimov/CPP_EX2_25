#pragma once
#include <iostream>

namespace mtrx {
	class Matrix{
		private:
			double **mat_table;
			int size;
			Matrix(int size);
		public:
			// Constructor
			Matrix(double** matrix, int size);
			// Copy Constructor
			Matrix(const Matrix & o);
			// Destructor
			~Matrix();
			// Operators:

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
			Matrix operator^(double num) const;
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
			double* operator[](int index);
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