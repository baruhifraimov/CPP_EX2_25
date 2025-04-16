// baruh.ifraimov@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../inc/doctest.h"
#include "../inc/SquareMat.hpp"
#include <iostream>

using namespace mtrx;


TEST_CASE("SquareMat Class Tests") {
    // Initializing matrices
    SquareMat m1(2), m2(2), m3(3), m4(2);

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

    m4 = m2;

    SUBCASE("Creating SquareMat with null array") {
        double** null_arr = nullptr;
        CHECK_THROWS_AS(SquareMat a(null_arr, 2), std::invalid_argument);
    }

    SUBCASE("Equality (==)") {
        CHECK_EQ(m4, m2);
    }

    SUBCASE("Equality (==)") {
        CHECK_EQ(m4, m2);
    }

    SUBCASE("Inequality (!=)") {
        CHECK_NE(m1, m2);
        CHECK_NE(m1, m3); // Different sizes
    }

    // also here
    SUBCASE("Addition (m1 + m2)") {
        SquareMat result = m1 + m2;
        CHECK(doctest::Approx(result[0][0]) == 0.0);
        CHECK(doctest::Approx(result[0][1]) == 2.3);
        CHECK(doctest::Approx(result[1][0]) == 1.0);
        CHECK(doctest::Approx(result[1][1]) == 4.3);
    }

    // something here is wrong?
    SUBCASE("Multiplication (m1 * m2)") {
        SquareMat result = m1 * m2;
        CHECK(doctest::Approx(result[0][0]) == 0.0);
        CHECK(doctest::Approx(result[0][1]) == 2.3);
        CHECK(doctest::Approx(result[1][0]) == 0.0);
        CHECK(doctest::Approx(result[1][1]) == 5.9);
    }

    SUBCASE("Determinant (!m1)") {
        SquareMat a(2);
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
        SquareMat result = m1 - m2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)-3/10);
        CHECK(doctest::Approx(result[1][0]) == 1);
        CHECK(doctest::Approx(result[1][1]) == (double)-3/10);
    }

    SUBCASE("Unary minus (-m1))"){
        SquareMat result = -m1;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == -1);
        CHECK(doctest::Approx(result[1][0]) == -1);
        CHECK(doctest::Approx(result[1][1]) == -2);
    }

    SUBCASE("Scalar multiplication (m1*scalar))"){
        SquareMat result = m1*2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 2);
        CHECK(doctest::Approx(result[1][0]) == 2);
        CHECK(doctest::Approx(result[1][1]) == 4);
    }

    SUBCASE("Scalar multiplication (scalar*m1))"){
        SquareMat result = m1*2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 2);
        CHECK(doctest::Approx(result[1][0]) == 2);
        CHECK(doctest::Approx(result[1][1]) == 4);
    }

    SUBCASE("Scalar division (m1/scalar))"){
        SquareMat result = m1/3;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)1/3);
        CHECK(doctest::Approx(result[1][0]) == (double)1/3);
        CHECK(doctest::Approx(result[1][1]) == (double)2/3);
    }

    // modification for m4
    m4*=13.2;
    m4[0][0] = 12;
    SUBCASE("Modulo with scalar (m1&scalar))"){
        SquareMat result = m4%2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == 1);
        CHECK(doctest::Approx(result[1][0]) == 0);
        CHECK(doctest::Approx(result[1][1]) == 0);
    }

    SUBCASE("Power SquareMat (multiply it by num times) (m2^2))"){
        SquareMat result = m2^2;
        CHECK(doctest::Approx(result[0][0]) == 0);
        CHECK(doctest::Approx(result[0][1]) == (double)299/100);
        CHECK(doctest::Approx(result[1][0]) == 0);
        CHECK(doctest::Approx(result[1][1]) == (double)529/100);
    }

    SUBCASE("Power SquareMat (multiply it by num times) (m2^0))"){
        SquareMat result1 = m2^0;
        // should be matrix YEHIDA
        SquareMat result2 = m3^0;
        CHECK(doctest::Approx(result1[0][0]) == 1);
        CHECK(doctest::Approx(result1[0][1]) == 0);
        CHECK(doctest::Approx(result1[1][0]) == 0);
        CHECK(doctest::Approx(result1[1][1]) == 1);
        CHECK(doctest::Approx(result2[0][0]) == 1);
        CHECK(doctest::Approx(result2[0][1]) == 0);
        CHECK(doctest::Approx(result2[0][2]) == 0);
        CHECK(doctest::Approx(result2[1][0]) == 0);
        CHECK(doctest::Approx(result2[1][1]) == 1);
        CHECK(doctest::Approx(result2[1][2]) == 0);
        CHECK(doctest::Approx(result2[2][0]) == 0);
        CHECK(doctest::Approx(result2[2][1]) == 0);
        CHECK(doctest::Approx(result2[2][2]) == 1);
    }

    SUBCASE("Greater than or equal (m1 >= m2)") {
        SquareMat a(2);
        a[0][0] = 5; a[0][1] = 5;
        a[1][0] = 5; a[1][1] = 5; // Sum: 20
        
        SquareMat b(2);
        b[0][0] = 1; b[0][1] = 2;
        b[1][0] = 3; b[1][1] = 4; // Sum: 10
        
        SquareMat c(2);
        c[0][0] = 8; c[0][1] = 4;
        c[1][0] = 4; c[1][1] = 4; // Sum: 20
        
        CHECK(a >= b);
        CHECK(a >= c);
        CHECK(!(b >= a));
    }

    SUBCASE("Less than or equal (m1 <= m2)") {
        SquareMat a(2);
        a[0][0] = 1; a[0][1] = 2;
        a[1][0] = 3; a[1][1] = 4; // Sum: 10
        
        SquareMat b(2);
        b[0][0] = 5; b[0][1] = 5;
        b[1][0] = 5; b[1][1] = 5; // Sum: 20
        
        SquareMat c(2);
        c[0][0] = 3; c[0][1] = 3;
        c[1][0] = 2; c[1][1] = 2; // Sum: 10
        
        CHECK(a <= b);
        CHECK(a <= c);
        CHECK(!(b <= a));
    }

    SUBCASE("Greater than (m1 > m2)") {
        // Create matrices with specific sums to test > operator
        SquareMat a(2);
        a[0][0] = 3; a[0][1] = 3;
        a[1][0] = 3; a[1][1] = 3; // Sum: 12
        
        SquareMat b(2);
        b[0][0] = 2; b[0][1] = 2;
        b[1][0] = 2; b[1][1] = 2; // Sum: 8
        
        CHECK(a > b);
        CHECK(!(b > a));
        CHECK(!(a > a));
    }

    SUBCASE("Less than (m1 < m2)") {
        SquareMat a(2);
        a[0][0] = 2; a[0][1] = 2;
        a[1][0] = 2; a[1][1] = 2; // Sum: 8
        
        SquareMat b(2);
        b[0][0] = 3; b[0][1] = 3;
        b[1][0] = 3; b[1][1] = 3; // Sum: 12
        
        CHECK(a < b);
        CHECK(!(b < a));
        CHECK(!(a < a));
    }

    SUBCASE("Transpose (~m1)") {
        SquareMat result = ~m1;
        
        CHECK_EQ(result[0][0], m1[0][0]);
        CHECK_EQ(result[0][1], m1[1][0]);
        CHECK_EQ(result[1][0], m1[0][1]);
        CHECK_EQ(result[1][1], m1[1][1]);
    }

    SUBCASE("Post-increment (m1++)") {
        SquareMat a = m1;
        SquareMat before = a++;
        
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
        SquareMat a = m1;
        SquareMat& result = ++a;
        
        CHECK_EQ(&result, &a);
        
        CHECK_EQ(a[0][0], m1[0][0] + 1);
        CHECK_EQ(a[0][1], m1[0][1] + 1);
        CHECK_EQ(a[1][0], m1[1][0] + 1);
        CHECK_EQ(a[1][1], m1[1][1] + 1);
    }

    SUBCASE("Post-decrement (m1--)") {
        SquareMat a = m1;
        SquareMat before = a--;
        
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
        SquareMat a = m1;
        SquareMat& result = --a;
        
        CHECK_EQ(&result, &a);
        
        CHECK_EQ(a[0][0], m1[0][0] - 1);
        CHECK_EQ(a[0][1], m1[0][1] - 1);
        CHECK_EQ(a[1][0], m1[1][0] - 1);
        CHECK_EQ(a[1][1], m1[1][1] - 1);
    }

    SUBCASE(" Addition (m1 += m2)") {
        SquareMat a = m1;
        SquareMat b = m2;
        
        SquareMat expected = m1 + m2;
        
        a += b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE(" Subtraction (m1 -= m2)") {
        SquareMat a = m1;
        SquareMat b = m2;
        
        SquareMat expected = m1 - m2;
        
        a -= b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE(" Multiplication (m1 *= m2)") {
        SquareMat a = m1;
        SquareMat b = m2;
        
        SquareMat expected = m1 * m2;
        
        a *= b;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE(" Scalar Multiplication (m1 *= num)") {
        SquareMat a = m1;
        double num = 3.5;
        
        SquareMat expected = m1 * num;
        
        a *= num;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE(" Scalar Division (m1 /= num)") {
        SquareMat a = m1;
        double num = 2.5;
        
        SquareMat expected = m1 / num;
        
        a /= num;
        
        CHECK(doctest::Approx(a[0][0]) == expected[0][0]);
        CHECK(doctest::Approx(a[0][1]) == expected[0][1]);
        CHECK(doctest::Approx(a[1][0]) == expected[1][0]);
        CHECK(doctest::Approx(a[1][1]) == expected[1][1]);
    }

    SUBCASE(" Scalar Division - Exception (m1 /= 0)") {
        SquareMat a = m1;
        
        CHECK_THROWS(a /= 0);
    }

    SUBCASE(" Modulo with SquareMat (m1 %= m2)") {
        SquareMat a(2);
        a[0][0] = 5; a[0][1] = 7;
        a[1][0] = 9; a[1][1] = 11;
        
        SquareMat b(2);
        b[0][0] = 2; b[0][1] = 3;
        b[1][0] = 4; b[1][1] = 5;
        
        SquareMat expected = a % b;
        
        a %= b;
        
        CHECK_EQ(a[0][0], expected[0][0]);
        CHECK_EQ(a[0][1], expected[0][1]);
        CHECK_EQ(a[1][0], expected[1][0]);
        CHECK_EQ(a[1][1], expected[1][1]);
    }

    SUBCASE(" Modulo with Scalar (m1 %= num)") {
        SquareMat a(2);
        a[0][0] = 5; a[0][1] = 7;
        a[1][0] = 9; a[1][1] = 11;
        
        int num = 3;
        
        SquareMat expected = a % num;
        
        a %= num;
        
        CHECK_EQ(a[0][0], expected[0][0]);
        CHECK_EQ(a[0][1], expected[0][1]);
        CHECK_EQ(a[1][0], expected[1][0]);
        CHECK_EQ(a[1][1], expected[1][1]);
    }
    SUBCASE("Trying to create a SquareMat with <=0 size")
    {
        CHECK_THROWS_AS(SquareMat a(-1),std::length_error);
        CHECK_THROWS_AS(SquareMat a(0),std::length_error);
    }

}