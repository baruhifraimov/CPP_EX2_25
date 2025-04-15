#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../inc/doctest.h"
#include "../inc/matrixFunc.hpp"
#include <iostream>

using namespace mtrx;

/*
================== 🧪 DOCTEST CHEAT SHEET ==================

✅ Structure:
------------------------------------------------------------
TEST_CASE("description") {
    // Arrange
    // Act
    // Assert

    SUBCASE("Addition") {
        CHECK(A + B == expected);
    }
}

✅ Basic Assertions:
------------------------------------------------------------
CHECK(expr);               // Check if true, keep going on failure
REQUIRE(expr);             // Check if true, STOP on failure

CHECK_EQ(a, b);            // a == b
REQUIRE_EQ(a, b);          // a == b, stop on failure

CHECK_NE(a, b);            // a != b
CHECK_LT(a, b);            // a < b
CHECK_GT(a, b);            // a > b
CHECK_LE(a, b);            // a <= b
CHECK_GE(a, b);            // a >= b

✅ Floating Point (with tolerance):
------------------------------------------------------------
CHECK(doctest::Approx(a) == b); // a ≈ b

✅ Exceptions:
------------------------------------------------------------
CHECK_THROWS(expr);                   // Any exception
CHECK_THROWS_AS(expr, ExcType);       // Specific exception
CHECK_NOTHROW(expr);                  // Should NOT throw

✅ Subsections (like nested tests):
------------------------------------------------------------
TEST_CASE("Matrix arithmetic") {
    SUBCASE("Addition") {
        ...
    }
    SUBCASE("Multiplication") {
        ...
    }
}

✅ Test Setup:
------------------------------------------------------------
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

=============================================================
*/

TEST_CASE("Matrix Class Tests") {
    // Initializing matrices
    Matrix m1(2), m2(2), m3(3), m4(2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m1[i][j] = i + j;
            m2[i][j] = (i+1.3) * j;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m3[i][j] = i + j % 10;
        }
    }

    // Copy constructor
    m4 = m2;

    // std::cout << "M1: "<< m1 << "\n"<< "M2: "<<m2  << "\n"<<"M3: "<< m3  << "\n"<<"M4: "<< m4 << std::endl;


    SUBCASE("Equality (==)") {
        CHECK_EQ(m4, m2);
    }

    SUBCASE("Inequality (!=)") {
        CHECK_NE(m1, m2);
        CHECK_NE(m1, m3); // Different sizes
    }

    // also here
    SUBCASE("Addition (m1 + m2)") {
        Matrix result = m1 + m2;
        CHECK(doctest::Approx(result[0][0]) == 0.0);
        CHECK(doctest::Approx(result[0][1]) == 2.3);
        CHECK(doctest::Approx(result[1][0]) == 1.0);
        CHECK(doctest::Approx(result[1][1]) == 4.3);
    }

    // something here is wrong?
    SUBCASE("Multiplication (m1 * m2)") {
        Matrix result = m1 * m2;
        CHECK(doctest::Approx(result[0][0]) == 0.0);
        CHECK(doctest::Approx(result[0][1]) == 2.3);
        CHECK(doctest::Approx(result[1][0]) == 0.0);
        CHECK(doctest::Approx(result[1][1]) == 5.9);
    }

    SUBCASE("Determinant (!m1)") {
        Matrix a(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        CHECK_EQ(!a, -2);
    }

    SUBCASE("Indexing (m1[i][j])") {
        CHECK_EQ(m1[0][0], 0);
        CHECK_EQ(m1[0][1], 1);
        CHECK_EQ(m1[1][0], 1);
        CHECK_EQ(m1[1][1], 2);
    }

    SUBCASE("Exceptions - different size addition 2x2 + 3x3") {
        CHECK_THROWS_AS(m1 + m3, std::invalid_argument);
    }

    SUBCASE("Exceptions - index out of this world [][]") {
        CHECK_THROWS(m1[12][0]);
        CHECK_THROWS(m1[0][12]);
        CHECK_THROWS(m1[12][12]);
    }

    SUBCASE("Exceptions - different size multiplication") {
        CHECK_THROWS_AS(m1 * m3, std::invalid_argument);
    }

    SUBCASE("No Throw - same size addition") {
        CHECK_NOTHROW(m1 + m2);
    }

    SUBCASE("No Throw - same size multiplication") {
        CHECK_NOTHROW(m1 * m2);
    }

    SUBCASE("Substitution (m1 - m2))"){
        Matrix result = m1 - m2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)-3/10);
        CHECK(doctest::Approx(result[1][0]) == 1);
        CHECK(doctest::Approx(result[1][1]) == (double)-3/10);
    }

    SUBCASE("Unary minus (-m1))"){
        Matrix result = -m1;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == -1);
        CHECK(doctest::Approx(result[1][0]) == -1);
        CHECK(doctest::Approx(result[1][1]) == -2);
    }

    SUBCASE("Scalar multiplication (m1*scalar))"){
        Matrix result = m1*2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 2);
        CHECK(doctest::Approx(result[1][0]) == 2);
        CHECK(doctest::Approx(result[1][1]) == 4);
    }

    SUBCASE("Scalar multiplication (scalar*m1))"){
        Matrix result = m1*2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 2);
        CHECK(doctest::Approx(result[1][0]) == 2);
        CHECK(doctest::Approx(result[1][1]) == 4);
    }

    SUBCASE("Scalar division (m1/scalar))"){
        Matrix result = m1/3;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)1/3);
        CHECK(doctest::Approx(result[1][0]) == (double)1/3);
        CHECK(doctest::Approx(result[1][1]) == (double)2/3);
    }

    // modification for m4
    m4*=13.2;
    m4[0][0] = 12;
    SUBCASE("Modulo with scalar (m1&scalar))"){
        Matrix result = m4%2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 1);
        CHECK(doctest::Approx(result[1][0]) == 0);
        CHECK(doctest::Approx(result[1][1]) == 0);
    }

    SUBCASE("Power Matrix (multiply it by num times) (m2^2))"){
        Matrix result = m2^2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)299/100);
        CHECK(doctest::Approx(result[1][0]) == 0);
        CHECK(doctest::Approx(result[1][1]) == (double)529/100);
    }

    SUBCASE("Greater than or equal (m1 >= m2)") {
        Matrix a(2);
        a[0][0] = 5; a[0][1] = 5;
        a[1][0] = 5; a[1][1] = 5; // Sum: 20
        
        Matrix b(2);
        b[0][0] = 1; b[0][1] = 2;
        b[1][0] = 3; b[1][1] = 4; // Sum: 10
        
        Matrix c(2);
        c[0][0] = 8; c[0][1] = 4;
        c[1][0] = 4; c[1][1] = 4; // Sum: 20
        
        CHECK(a >= b);
        CHECK(a >= c);
        CHECK(!(b >= a));
    }

    SUBCASE("Less than or equal (m1 <= m2)") {
        Matrix a(2);
        a[0][0] = 1; a[0][1] = 2;
        a[1][0] = 3; a[1][1] = 4; // Sum: 10
        
        Matrix b(2);
        b[0][0] = 5; b[0][1] = 5;
        b[1][0] = 5; b[1][1] = 5; // Sum: 20
        
        Matrix c(2);
        c[0][0] = 3; c[0][1] = 3;
        c[1][0] = 2; c[1][1] = 2; // Sum: 10
        
        CHECK(a <= b);
        CHECK(a <= c);
        CHECK(!(b <= a));
    }

    SUBCASE("Greater than (m1 > m2)") {
        // Create matrices with specific sums to test > operator
        Matrix a(2);
        a[0][0] = 3; a[0][1] = 3;
        a[1][0] = 3; a[1][1] = 3; // Sum: 12
        
        Matrix b(2);
        b[0][0] = 2; b[0][1] = 2;
        b[1][0] = 2; b[1][1] = 2; // Sum: 8
        
        CHECK(a > b);
        CHECK(!(b > a));
        CHECK(!(a > a));
    }

    SUBCASE("Less than (m1 < m2)") {
        Matrix a(2);
        a[0][0] = 2; a[0][1] = 2;
        a[1][0] = 2; a[1][1] = 2; // Sum: 8
        
        Matrix b(2);
        b[0][0] = 3; b[0][1] = 3;
        b[1][0] = 3; b[1][1] = 3; // Sum: 12
        
        CHECK(a < b);
        CHECK(!(b < a));
        CHECK(!(a < a));
    }

    SUBCASE("Transpose (~m1)") {
        Matrix result = ~m1;
        
        CHECK_EQ(result[0][0], m1[0][0]);
        CHECK_EQ(result[0][1], m1[1][0]);
        CHECK_EQ(result[1][0], m1[0][1]);
        CHECK_EQ(result[1][1], m1[1][1]);
    }

    SUBCASE("Post-increment (m1++)") {
        Matrix a = m1;
        Matrix before = a++;
        
        CHECK_EQ(before[0][0], m1[0][0]);
        CHECK_EQ(before[0][1], m1[0][1]);
        CHECK_EQ(before[1][0], m1[1][0]);
        CHECK_EQ(before[1][1], m1[1][1]);
        
        CHECK_EQ(a[0][0], m1[0][0] + 1);
        CHECK_EQ(a[0][1], m1[0][1] + 1);
        CHECK_EQ(a[1][0], m1[1][0] + 1);
        CHECK_EQ(a[1][1], m1[1][1] + 1);
    }

    SUBCASE("Pre-increment (++m1)") {
        Matrix a = m1;
        Matrix& result = ++a;
        
        CHECK_EQ(&result, &a);
        
        CHECK_EQ(a[0][0], m1[0][0] + 1);
        CHECK_EQ(a[0][1], m1[0][1] + 1);
        CHECK_EQ(a[1][0], m1[1][0] + 1);
        CHECK_EQ(a[1][1], m1[1][1] + 1);
    }

    SUBCASE("Post-decrement (m1--)") {
        Matrix a = m1;
        Matrix before = a--;
        
        CHECK_EQ(before[0][0], m1[0][0]);
        CHECK_EQ(before[0][1], m1[0][1]);
        CHECK_EQ(before[1][0], m1[1][0]);
        CHECK_EQ(before[1][1], m1[1][1]);
        
        CHECK_EQ(a[0][0], m1[0][0] - 1);
        CHECK_EQ(a[0][1], m1[0][1] - 1);
        CHECK_EQ(a[1][0], m1[1][0] - 1);
        CHECK_EQ(a[1][1], m1[1][1] - 1);
    }

    SUBCASE("Pre-decrement (--m1)") {
        Matrix a = m1;
        Matrix& result = --a;
        
        CHECK_EQ(&result, &a);
        
        CHECK_EQ(a[0][0], m1[0][0] - 1);
        CHECK_EQ(a[0][1], m1[0][1] - 1);
        CHECK_EQ(a[1][0], m1[1][0] - 1);
        CHECK_EQ(a[1][1], m1[1][1] - 1);
    }

    SUBCASE("Compound Addition (m1 += m2)") {
        Matrix a = m1;
        Matrix b = m2;
        
        Matrix expected = m1 + m2;
        
        a += b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE("Compound Subtraction (m1 -= m2)") {
        Matrix a = m1;
        Matrix b = m2;
        
        Matrix expected = m1 - m2;
        
        a -= b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE("Compound Multiplication (m1 *= m2)") {
        Matrix a = m1;
        Matrix b = m2;
        
        Matrix expected = m1 * m2;
        
        a *= b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE("Compound Scalar Multiplication (m1 *= num)") {
        Matrix a = m1;
        double num = 3.5;
        
        Matrix expected = m1 * num;
        
        a *= num;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE("Compound Scalar Division (m1 /= num)") {
        Matrix a = m1;
        double num = 2.5;
        
        Matrix expected = m1 / num;
        
        a /= num;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE("Compound Scalar Division - Exception (m1 /= 0)") {
        Matrix a = m1;
        
        CHECK_THROWS(a /= 0);
    }

    SUBCASE("Compound Modulo with Matrix (m1 %= m2)") {
        Matrix a(2);
        a[0][0] = 5; a[0][1] = 7;
        a[1][0] = 9; a[1][1] = 11;
        
        Matrix b(2);
        b[0][0] = 2; b[0][1] = 3;
        b[1][0] = 4; b[1][1] = 5;
        
        Matrix expected = a % b;
        
        a %= b;
        
        CHECK_EQ(a[0][0], expected[0][0]);
        CHECK_EQ(a[0][1], expected[0][1]);
        CHECK_EQ(a[1][0], expected[1][0]);
        CHECK_EQ(a[1][1], expected[1][1]);
    }

    SUBCASE("Compound Modulo with Scalar (m1 %= num)") {
        Matrix a(2);
        a[0][0] = 5; a[0][1] = 7;
        a[1][0] = 9; a[1][1] = 11;
        
        int num = 3;
        
        Matrix expected = a % num;
        
        a %= num;
        
        CHECK_EQ(a[0][0], expected[0][0]);
        CHECK_EQ(a[0][1], expected[0][1]);
        CHECK_EQ(a[1][0], expected[1][0]);
        CHECK_EQ(a[1][1], expected[1][1]);
    }
    SUBCASE("Trying to create a matrix with <=0 size")
    {
        CHECK_THROWS_AS(Matrix a(-1),std::length_error);
        CHECK_THROWS_AS(Matrix a(0),std::length_error);
    }

}