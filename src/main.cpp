// baruh.ifraimov@gmail.com
#include <iostream>
#include "../inc/SquareMat.hpp"

// Helper to convert static 2D array to dynamic double**
double** to_double_ptr(double arr[][2], int size) {
    double** result = new double*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            result[i][j] = arr[i][j];
        }
    }
    return result;
}

// Helper to convert static 3D array to dynamic double**
double** to_double_ptr(double arr[][3], int size) {
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
void free_SquareMat(double** mat, int size) {
    for (int i = 0; i < size; ++i)
        delete[] mat[i];
    delete[] mat;
}

int main() {
    // Static 2D arrays
    double a[2][2] = {
        {1, 2},
        {3, 4}
    };

    double b[2][2] = {
        {5, 6},
        {7, 8}
    };
    
    double c[3][3] = {
        {5, 6,2.2},
        {7, 8,3.1},
        {1, 1,0.2}
    };

    double** m1 = to_double_ptr(a, 2);
    double** m2 = to_double_ptr(b, 2);
    double** m3 = to_double_ptr(c, 3);


    mtrx::SquareMat A(m1, 2);
    mtrx::SquareMat B(m2, 2);
    mtrx::SquareMat S(m3, 3);


    std::cout << "SquareMat A:\n" << A << std::endl;
    std::cout << "SquareMat B:\n" << B << std::endl;

    mtrx::SquareMat C = A + B;
    std::cout << "A + B:\n" << C << std::endl;

    mtrx::SquareMat D = A * B;
    std::cout << "A * B:\n" << D << std::endl;

    int det = !A;
    std::cout << "Determinant of A: " << det << std::endl;

    std::cout << "A[0][1]: " << A[0][1] << std::endl;

    A *= B;
    std::cout << "SquareMat A*=B:\n" << A << std::endl;

    A[0][1] = 15;
    std::cout << "SquareMat A after change:\n" << A << std::endl;
    
    mtrx::SquareMat E(A);
    std::cout << "SquareMat E (copy of A):\n" << E << std::endl;
    
    
    mtrx::SquareMat G = A - B;
    std::cout << "A - B:\n" << G << std::endl;
    
    mtrx::SquareMat H = -A;
    std::cout << "-A:\n" << H << std::endl;
    
    mtrx::SquareMat I = A * 2;
    std::cout << "A * 2:\n" << I << std::endl;
    
    mtrx::SquareMat J = 3 * B;
    std::cout << "3 * B:\n" << J << std::endl;

	std::cout << "A:\n" << A << std::endl;

	std::cout << "++A:\n" << ++A << std::endl;

	std::cout << "A++:\n" << A++ << std::endl;

	std::cout << "A:\n" << A << std::endl;

	std::cout << "--A:\n" << --A << std::endl;

	std::cout << "A--:\n" << A-- << std::endl;

	std::cout << "A:\n" << A << std::endl;

	std::cout << "A%2:\n" << A%2 << std::endl;

	std::cout << "A%B:\n" << A%B << std::endl;
    
    std::cout << "~A:\n" << ~A << std::endl;
    
    std::cout << "A:\n" << A << std::endl;

    std::cout << "S:\n" << S << std::endl;

    std::cout << "~S:\n" << ~S << std::endl;
    
    std::cout << "A:\n" << A << std::endl;

    std::cout << "A^2:\n" << (A^2) << std::endl;

    std::cout << "A^0:\n" << (A^0) << std::endl;

    free_SquareMat(m1, 2);
    free_SquareMat(m2, 2);
    free_SquareMat(m3, 3);

    return 0;
}