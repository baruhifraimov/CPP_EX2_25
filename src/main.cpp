#include <iostream>
#include "../inc/matrix_func.hpp"

using namespace std;
using namespace mtrx;

// Helper to convert static 2D array to dynamic double**
double** to_double_ptr(double arr[2][2], int size) {
    double** result = new double*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            result[i][j] = arr[i][j];
        }
    }
    return result;
}

// Helper to free dynamic double**
void free_matrix(double** mat, int size) {
    for (int i = 0; i < size; ++i)
        delete[] mat[i];
    delete[] mat;
}

int main() {
    int n_size = 2;

    // Static 2D arrays
    double a[2][2] = {
        {1, 2},
        {3, 4}
    };

    double b[2][2] = {
        {5, 6},
        {7, 8}
    };

    // Convert to double**
    double** m1 = to_double_ptr(a, n_size);
    double** m2 = to_double_ptr(b, n_size);

    // Create Matrix objects
    Matrix A(m1, n_size);
    Matrix B(m2, n_size);

    // Test and print
    cout << "Matrix A:\n" << A << endl;
    cout << "Matrix B:\n" << B << endl;

    // Test addition
    Matrix C = A + B;
    cout << "A + B:\n" << C << endl;

    // Test multiplication
    Matrix D = A * B;
    cout << "A * B:\n" << D << endl;

    // Test determinant
    int det = !A;
    cout << "Determinant of A: " << det << endl;

    // Test indexing
    cout << "A[0][1]: " << A[0][1] << endl;

    // Test multiplication assignment
    A *= B;
    cout << "Matrix A*=B:\n" << A << endl;

    // Test assignment through indexing
    A[0][1] = 15;
    cout << "Matrix A after change:\n" << A << endl;
    
    // Test copy constructor
    Matrix E(A);
    cout << "Matrix E (copy of A):\n" << E << endl;
    
    
    // Test subtraction
    Matrix G = A - B;
    cout << "A - B:\n" << G << endl;
    
    // Test unary minus
    Matrix H = -A;
    cout << "-A:\n" << H << endl;
    
    // Test scalar multiplication
    Matrix I = A * 2;
    cout << "A * 2:\n" << I << endl;
    
    // Test scalar multiplication (other direction)
    Matrix J = 3 * B;
    cout << "3 * B:\n" << J << endl;

	cout << "A:\n" << A << endl;

	cout << "++A:\n" << ++A << endl;

	cout << "A++:\n" << A++ << endl;

	cout << "A:\n" << A << endl;

	cout << "--A:\n" << --A << endl;

	cout << "A--:\n" << A-- << endl;

	cout << "A:\n" << A << endl;

	cout << "A%2:\n" << A%2 << endl;

	cout << "A%B:\n" << A%B << endl;

    // Clean up
    free_matrix(m1, n_size);
    free_matrix(m2, n_size);

    return 0;
}