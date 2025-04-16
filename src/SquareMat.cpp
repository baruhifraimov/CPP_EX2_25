// baruh.ifraimov@gmail.com
#include <iostream>
#include <stdexcept>
#include "../inc/SquareMat.hpp"
#include "../inc/MatrixUtils.hpp"
namespace mtrx{

	// Help function to sum any size of matrix
	double matSum( const SquareMat& o){
		int size = o.getSize();
		double result=0;
		// Loop through the matrix and sum all the elements
		for (int i = 0; i < size ; i++)
		{
			for (int j = 0; j < size; j++)
		{
			result+=(o[i][j]);
		}
		}
		return result;
	}

	SquareMat::SquareMat(int size){
		if(size <= 0){
			throw(std::length_error("Negative (or zero) value will not be tolerated!"));
		}
		this->size = size;
		mat_table = new double*[size];
		for (int i = 0; i < size; i++)
		{
			mat_table[i] = new double[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				mat_table[i][j] = 0;
			}
		}
	}

	SquareMat::SquareMat(double** matrix, int size){
		if(size <= 0){
			throw(std::length_error("Negative (or zero) value will not be tolerated!"));
		}

		if(matrix == nullptr || (*matrix) == nullptr){
			throw(std::invalid_argument("Matrix is null"));
		}

		this->size = size;
		mat_table = new double*[size];
		for (int i = 0; i < size; i++)
		{
			mat_table[i] = new double[size];
		}

		for (int i = 0; i < size; i++)
		{
			if (matrix[i] == nullptr) {
				throw std::invalid_argument("Row pointer is null at index " + std::to_string(i));
			}
			for (int j = 0; j < size; j++)
			{
				mat_table[i][j] = matrix[i][j];
			}
		}
		
	}

	SquareMat::SquareMat(const SquareMat & o){

		this->size = o.size;
		mat_table = new double*[size];
		for (int i = 0; i < size; i++)
		{
			mat_table[i] = new double[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				mat_table[i][j] = o.mat_table[i][j];
			}
			
		}
		
	}

	SquareMat::~SquareMat(){
		if(mat_table != nullptr){
		for (int i = 0; i < this->size; i++)
		{
			delete[] mat_table[i];
		}
		delete[] mat_table;
		}
	}

	// ~m1 (Transpose)
	SquareMat SquareMat::operator~() const{
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = this->mat_table[j][i]; // Transpose
		}
		}
		return m;
	}


	// m1 = m2
	SquareMat& SquareMat::operator=(const SquareMat& o) {
		if (this == &o) {
			return *this; // are we the same? then dont do nothing.
		}
		
		// Clean up existing fields (to free up unreachable memmory)
		if (mat_table != nullptr) {
			for (int i = 0; i < size; i++) {
				delete[] mat_table[i];
			}
			delete[] mat_table;
		}
		
		// Copy from other matrix
		size = o.size;
		mat_table = new double*[size];
		for (int i = 0; i < size; i++) {
			mat_table[i] = new double[size];
			for (int j = 0; j < size; j++) {
				mat_table[i][j] = o.mat_table[i][j];
			}
		}
		
		return *this;
	}

	// m1+m2
	SquareMat SquareMat::operator+(const SquareMat& o) const{
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = this->mat_table[i][j] + o.mat_table[i][j];
		}
		}
		return m;
	}

	// m1-m2
	SquareMat SquareMat::operator-(const SquareMat& o) const{
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = this->mat_table[i][j] - o.mat_table[i][j];
		}
		}
		return m;
	}

	// m1*m2
	SquareMat SquareMat::operator*(const SquareMat& o) const{
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		SquareMat m(size);
		double curr_result =0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				for (int t = 0; t < size; t++)
				{
					curr_result += this->mat_table[i][t] * o.mat_table[t][j];
				}
				// Round to 0 if close to 0 (to avoid floating point errors)
				if (curr_result < 0.0001 && curr_result > 0){
					curr_result =0;
				}
				else if(curr_result > -0.0001 && curr_result < 0){
					curr_result =0;
				}
				m.mat_table[i][j] = curr_result;
				curr_result = 0;
			}
		}
		return m;
	}

	// m1%m2
	SquareMat SquareMat::operator%(const SquareMat& o) const{
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = this->mat_table[i][j] * o.mat_table[i][j];
		}
		}
		return m;
	}

	// -m1
	SquareMat SquareMat::operator-(){
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = -(this->mat_table[i][j]);
		}
		}
		return m;
	}

	// m1*<num>
	SquareMat SquareMat::operator*(double num) const{
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = num*(this->mat_table[i][j]);
				// Round to 0 if close to 0 (to avoid floating point errors)
				if(m.mat_table[i][j] < 0.0001 && m.mat_table[i][j] > 0){
				m.mat_table[i][j] =0;
			}
			else if(m.mat_table[i][j] > -0.0001 && m.mat_table[i][j] < 0){
				m.mat_table[i][j] =0;
			}
		}
		}
		return m;
	}

	// <num>*m1
	SquareMat operator*(double num, const SquareMat& o){
		SquareMat m(o.size);
		for (int i = 0; i < o.size; i++)
		{
			for (int j = 0; j < o.size; j++)
		{
			m.mat_table[i][j] = num*(o.mat_table[i][j]);
		}
		}
		return m;
	}



	/**
	 * @brief Get cofactor of mat[p][q] in temp[][]. n is current size of mat[][]
	 */
	void SquareMat::getCofactor(double** mat, double** temp, int p, int q, int n) const {
		int i = 0, j = 0;
		
		// Looping for each element of the matrix
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				if (row != p && col != q) {
					temp[i][j++] = mat[row][col];
					// Row is filled, so increase row index and reset col index
					if (j == n - 1) {
						j = 0;
						i++;
					}
				}
			}
		}
	}

	/**
	 * @brief Calculates the adjoint (adjugate) of a matrix
	 * 
	 * @return SquareMat - The adjoint matrix
	 */
	SquareMat SquareMat::adjoint() const {
		SquareMat adj(size);
		// 1x1 matrix the adjoint is 1
		if (size == 1) {
			adj.mat_table[0][0] = 1;
			return adj;
		}
		int sign;
		// temp matrix for storing cofactors
		double** temp = new double*[size-1];
		for (int i = 0; i < size-1; i++) {
			temp[i] = new double[size-1];
		}
		// Calculate the adjoint matrix
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				getCofactor(mat_table, temp, i, j, size);
				sign = ((i + j) % 2 == 0) ? 1 : -1;
				adj.mat_table[j][i] = sign * determinantHelper(temp, size-1);
			}
		}
		for (int i = 0; i < size-1; i++) {
			delete[] temp[i];
		}
		delete[] temp;
		return adj;
	}

		/**
	 * @brief Calculates the inverse of a matrix
	 * 
	 * @return SquareMat - The inverse matrix
	 */
	SquareMat SquareMat::inverse() const {
		// compute determinant (operator! now returns double)
		double det = !(*this);
		if (det == 0.0) {
			throw std::invalid_argument("Matrix is not invertible (determinant is zero)");
		}
	
		// get adjugate (you already have adjoint())
		SquareMat adj = this->adjoint();
	
		// scale each element by 1/det
		double invDet = 1.0 / det;
		adj *= invDet;
	
		return adj;
	}

	// m1^<num>
	SquareMat SquareMat::operator^(int num) const{
		SquareMat m(size);
		m = *this;

		if(num <0){
			m = m.inverse();
			SquareMat copyM = m;
			for (int i = 1; i < -num; i++)
			{
				m*=copyM;
			}
		}

		else if(num == 0){
			for (int i = 0; i < size; i++)
			{
					for (int j = 0; j < size; j++)
				{
					if(i == j)
					{
						m.mat_table[i][j] = 1;
					}
					else
					{
					m.mat_table[i][j] = 0;
					}
				}
			}
		}

		else{
		for (int i = 1; i < num; i++)
		{
			m*=(*this);
		}
	}

		return m;
	}

	// m1/<num>
	SquareMat SquareMat::operator/(double num) const{
		if(num == 0){
			throw std::invalid_argument("Can't divide by zero!");
		}
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = (this->mat_table[i][j])/num;
		}
		}
		return m;
	}

	// m1%<num>
	SquareMat SquareMat::operator%(int num) const{
		SquareMat m(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			m.mat_table[i][j] = (int)(this->mat_table[i][j])%num;
		}
		}
		return m;
	}

	// m1++
	SquareMat SquareMat::operator++(int){
		SquareMat m = *this;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			this->mat_table[i][j]++;
		}
		}
		return m;
	}

	// ++m1
	SquareMat& SquareMat::operator++(){
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			++(this->mat_table[i][j]);
		}
		}
		return *this;
	}

	// m1--
	SquareMat SquareMat::operator--(int){
		SquareMat m = *this;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			(this->mat_table[i][j])--;
		}
		}
		return m;
	}

	// --m1
	SquareMat& SquareMat::operator--(){
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
		{
			--(this->mat_table[i][j]);
		}
		}
		return *this;
	}


	// m1[] const
	SquareMat::HiddenArr SquareMat::operator[](int index) const{
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of bounds");
		}
		return HiddenArr(mat_table[index], size);
	}

	// m1[]
	SquareMat::HiddenArr SquareMat::operator[](int index){
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of bounds");
		}
		return HiddenArr(mat_table[index], size);
	}

	// m1 == m2
	bool SquareMat::operator==(const SquareMat& o) const{
		double result1=0,result2=0;
		result1 = mtrx::matSum(*this);
		result2 = mtrx::matSum(o);
		return result1==result2;
	}

	// m1 != m2
	bool SquareMat::operator!=(const SquareMat& o) const{
		if (this->size != o.size){
			return true;
		}
		return !(*this == o);
	}

	// m1 < m2
	bool SquareMat::operator<(const SquareMat& o) const{
		double result1=0,result2=0;
		result1 = mtrx::matSum(*this);
		result2 = mtrx::matSum(o);
		return result1 < result2;
	}

	// m1 > m2
	bool SquareMat::operator>(const SquareMat& o) const{
		double result1=0,result2=0;
		result1 = mtrx::matSum(*this);
		result2 = mtrx::matSum(o);
		return result1 > result2;
	}

	// m1 <= m2
	bool SquareMat::operator<=(const SquareMat& o) const{
		double result1=0,result2=0;
		result1 = mtrx::matSum(*this);
		result2 = mtrx::matSum(o);
		return result1 <= result2;
	}

	// m1 >= m2
	bool SquareMat::operator>=(const SquareMat& o) const{
		double result1=0,result2=0;
		result1 = mtrx::matSum(*this);
		result2 = mtrx::matSum(o);
		return result1 >= result2;
	}

	double SquareMat::determinantHelper(double** mat, int n) const {
		if (n == 1) // base case
			return mat[0][0];
		if (n == 2) // base case
			return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
	  
		double det = 0, sign = 1;
		double** temp = new double*[n-1];
		for(int i=0;i<n-1;i++) temp[i] = new double[n-1];
	  
		for(int col=0; col<n; col++){
		  // build submatrix
		  int subi = 0;
		  for(int i=1;i<n;i++){
			int subj=0;
			for(int j=0;j<n;j++){
			  if(j==col) continue;
			  temp[subi][subj++] = mat[i][j];
			}
			subi++;
		  }
		  det += sign * mat[0][col] * determinantHelper(temp, n-1);
		  sign = -sign;
		}
	  
		for(int i=0;i<n-1;i++) delete[] temp[i];
		delete[] temp;
		return det;
	  }
	  

	// !m1 (Determinant)
	double SquareMat::operator!() const {
		return determinantHelper(mat_table, size);
	  }

	// m1 += m2
	SquareMat& SquareMat::operator+=(const SquareMat& o){
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		*this = *this + o;

		return *this;
	}

	// m1 -= m2
	SquareMat& SquareMat::operator-=(const SquareMat& o){
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		*this = *this - o;

		return *this;
	}

	// m1 /= num
	SquareMat& SquareMat::operator/=(double num){
		*this = (*this)/num;

		return *this;
	}

	// m1 *= m2
	SquareMat& SquareMat::operator*=(const SquareMat& o){
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		*this = *this * o;

		return *this;
	}

	// m1 %= m2
	SquareMat& SquareMat::operator%=(const SquareMat& o){
		if (this->size != o.size){
			throw std::invalid_argument("Matrix sizes do not match");
		}
		*this = *this % o;

		return *this;
	}
	
	// m1 *= num
	SquareMat& SquareMat::operator*=(double num){
		
		*this = *this * num;

		return *this;
	}

	// m1 %= num
	SquareMat& SquareMat::operator%=(double num){
		*this = *this % num;

		return *this;
	}

	// cout << m1 
	std::ostream& operator<<(std::ostream& os, const SquareMat& o){
		int size = o.size;
		for (int i = 0; i < size; i++)
		{
			os << "[";
			for (int j = 0; j < size-1; j++)
			{
				os << o.mat_table[i][j] << ","; 
			}
			os << o.mat_table[i][size-1]; 
			os << "]\n";
		}
		return os;
	}
}