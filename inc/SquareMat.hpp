// baruh.ifraimov@gmail.com
#pragma once
#include <iostream>

namespace mtrx {
	class SquareMat{
		private:
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
			double **mat_table;
			int size;

			/**
			 * @brief Sum all the elements in the array
			 * 
			 * @param o The Matrix to be calculated
			 * @return double 
			 */
			double matSum( const SquareMat& o) const;

		public:
			// Constructor 1
			/**
			 * @brief Construct a new Square Mat object
			 * 
			 * @param size  Size of the matrix
			 * @throw std::length_error if size is less than or equal to 0
			 */
			SquareMat(int size);
			// Constructor 2
			/**
			 * @brief Construct a new Square Mat object
			 * 
			 * @param matrix  Matrix to be copied
			 * @param size  Size of the matrix
			 * @throw std::length_error if size is less than or equal to 0
			 * @throw std::invalid_argument if matrix is null
			 */
			SquareMat(double** matrix, int size);
			// Copy Constructor
			/**
			 * @brief Construct a new Square Mat object
			 * 
			 * @param o  Matrix to be copied
			 */
			SquareMat(const SquareMat & o);
			// Destructor
			/**
			 * @brief Destroy the Square Mat object
			 * 
			 */
			~SquareMat();

			/**
			 * @brief Get the Size object
			 * 
			 * @return int 
			 */
			int getSize() const {
				return this->size;
			}

			/**
			 * @brief Get the Determinant of the matrix
			 * 
			 * @return double - The determinant
			 */
			double determinantHelper(double **mat, int n) const;

			/**
			 * @brief Calculates the adjoint (adjugate) of a matrix
			 * 
			 * @return SquareMat - The adjoint matrix
			 */
			SquareMat adjoint() const;

			/**
			 * @brief Calculates the determinant of a matrix
			 * 
			 * @param mat  Matrix to be calculated
			 * @param n  Size of the matrix
			 * @return double - The determinant
			 */
			void getCofactor(double** mat, double** temp, int p, int q, int n) const;

			/**
			 * @brief Calculates the determinant of a matrix
			 * 
			 * @return double - The determinant
			 */
			SquareMat inverse() const;

			
			/***************************************
			 *           Operators Overload        *
			 ***************************************/
				
			/**
			 * @brief  Transpose the matrix
			 * ~m1 (Transpose)
			 * @return SquareMat 
			 */
			SquareMat operator~() const;

			/**
			 * @brief  Assign the matrix
			 * m1 = m2
			 * @param o  Matrix to be copied
			 * @return SquareMat& 
			 */
			SquareMat& operator=(const SquareMat& o);

			/**
			 * @brief  Add two matrices
			 * m1+m2
			 * @param o  Matrix to be added
			 * @throw std::invalid_argument if matrix sizes do not match
			 * @return SquareMat 
			 */
			SquareMat operator+(const SquareMat& o) const;

			/**
			 * @brief  Subtract two matrices
			 * m1-m2
			 * @param o  Matrix to be subtracted
			 * @throw std::invalid_argument if matrix sizes do not match
			 * @return SquareMat 
			 */
			SquareMat operator-(const SquareMat& o) const;

			/**
			 * @brief  Multiply two matrices
			 * m1*m2
			 * @param o  Matrix to be multiplied
			 * @throw std::invalid_argument if matrix sizes do not match
			 * @return SquareMat 
			 */
			SquareMat operator*(const SquareMat& o) const;

			/**
			 * @brief  Multiply this matrix with 2nd matrix each element by element
			 * m1%m2
			 * @param o  Matrix to be moduloed
			 * @throw std::invalid_argument if matrix sizes do not match
			 * @return SquareMat 
			 */
			SquareMat operator%(const SquareMat& o) const;

			/**
			 * @brief  Negate the matrix
			 * -m1
			 * @return SquareMat 
			 * @throw std::invalid_argument if matrix sizes do not match
			 */
			SquareMat operator-();
			// m1*<num>
			/**
			 * @brief  Multiply the matrix with a number
			 * 
			 * @param num  Number to be multiplied
			 * @return SquareMat 
			 */
			SquareMat operator*(double num) const;

			/**
			 * @brief  Multiply the matrix with a number
			 * <num>*m1
			 * @param num  Number to be multiplied
			 * @param o  Matrix to be multiplied
			 * @return SquareMat 
			 */
			friend SquareMat operator*(double num, const SquareMat& o);

			/**
			 * @brief  Power the matrix to a number
			 * m1^<num>
			 * @param num  Number to be powered
			 * @return SquareMat  
			 */
			SquareMat operator^(int num) const;

			/**
			 * @brief  Divide the matrix with a number
			 * m1/<num>
			 * @param num  Number to be divided
			 * @throw std::invalid_argument if num is 0
			 * @return SquareMat  
			 */
			SquareMat operator/(double num) const;

			/**
			 * @brief  Modulo the matrix with a number
			 * m1%<num>
			 * @param num  Number to be moduloed
			 * @return SquareMat 
			 */
			SquareMat operator%(int num) const;

			/**
			 * @brief  Increment the matrix
			 * m1++
			 * @return SquareMat  
			 */
			SquareMat operator++(int);

			/**
			 * @brief  Increment the matrix
			 * ++m1
			 * @return SquareMat& 
			 */
			SquareMat &operator++();

			/**
			 * @brief  Decrement the matrix
			 * m1--
			 * @return SquareMat 
			 */
			SquareMat operator--(int);

			/**
			 * @brief  Decrement the matrix
			 * --m1
			 * @return SquareMat& 
			 */
			SquareMat &operator--();

			/**
			 * @brief  Access the matrix
			 * m1[]
			 * @param index  Index of the matrix
			 * @throw std::out_of_range if index is out of bounds
			 * @return HiddenArr 
			 */
			HiddenArr operator[](int index);
			HiddenArr operator[](int index) const;
			/**
			 * @brief  Compare two matrices
			 * m1 == m2
			 * @param o  Matrix to be compared
			 * @return true if equal
			 * @return false if not equal
			 * @throw std::invalid_argument if matrix sizes do not match
			 */
			bool operator==(const SquareMat& o) const;

			/**
			 * @brief  Compare two matrices
			 * m1 != m2
			 * @param o  Matrix to be compared
			 * @return true  if not equal
			 * @return false  if equal
			 */
			bool operator!=(const SquareMat& o) const;

			/**
			 * @brief  Compare two matrices sum of all elements
			 * m1 < m2
			 * @param o  Matrix to be compared
			 * @return true  if m1 < m2
			 * @return false  if m1 >= m2
			 */
			bool operator<(const SquareMat& o) const;

			/**
			 * @brief  Compare two matrices sum of all elements
			 * m1 > m2
			 * @param o  Matrix to be compared
			 * @return true  if m1 > m2
			 * @return false  if m1 <= m2
			 */
			bool operator>(const SquareMat& o) const;

			/**
			 * @brief  Compare two matrices sum of all elements
			 * m1 <= m2
			 * @param o  Matrix to be compared
			 * @return true  if m1 <= m2
			 * @return false  if m1 > m2
			 */
			bool operator<=(const SquareMat& o) const;

			/**
			 * @brief  Compare two matrices sum of all elements
			 * m1 >= m2
			 * @param o  Matrix to be compared
			 * @return true  if m1 >= m2
			 * @return false  if m1 < m2
			 */
			bool operator>=(const SquareMat& o) const;

			/**
			 * @brief  Calculate the determinant of the matrix
			 * !m1 (Determinant)
			 * @return int Determinant of the matrix
			 */
			double operator!() const;

			/**
			 * @brief  Add two matrices
			 * m1 += m2
			 * @param o  Matrix to be added
			 * @return SquareMat& 
			 */
			SquareMat& operator+=(const SquareMat& o);

			/**
			 * @brief  Subtract two matrices
			 * m1 -= m2
			 * @param o  Matrix to be subtracted
			 * @return SquareMat& 
			 */
			SquareMat& operator-=(const SquareMat& o);

			/**
			 * @brief  Divide the matrix with a number
			 * m1 /= m2
			 * @param num  Number to be divided
			 * @return SquareMat&  
			 */
			SquareMat& operator/=(double num);

			/**
			 * @brief  Multiply two matrices
			 * m1 *= m2
			 * @param o  Matrix to be multiplied
			 * @return SquareMat&  
			 */
			SquareMat& operator*=(const SquareMat& o);

			/**
			 * @brief  Multiply this matrix with 2nd matrix each element by element
			 * m1 %= m2
			 * @param o  Matrix to be moduloed
			 * @return SquareMat&  
			 */
			SquareMat& operator%=(const SquareMat& o);

			/**
			 * @brief  Multiply the matrix with a number
			 * m1 *= num
			 * @param num  Number to be multiplied
			 * @return SquareMat& 
			 */
			SquareMat& operator*=(double num);

			/**
			 * @brief  Modulo the matrix with a number
			 * m1 %= num
			 * @param num  Number to be moduloed
			 * @return SquareMat&  
			 */
			SquareMat& operator%=(double num);

			/**
			 * @brief  Print the matrix
			 * cout << m1 
			 * @param os  Output stream
			 * @param o  Matrix to be printed
			 * @return std::ostream&  
			 */
			friend std::ostream& operator<<(std::ostream& os, const SquareMat& o);

			
	};
}