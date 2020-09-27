#include <iostream>
#include <string>
#include "matrix.h"
using namespace std;

void test_base() {
    Matrix m1 = Matrix(2,2);
    Fraction f = Fraction(3);
    m1.print();
    m1.set_elem(f, 1, 1);
    m1.print();
}

void test_product() {
    Matrix m1 = Matrix(2,2);
    Matrix m2 = Matrix(2,2);
    Matrix prod;
    m1.read();
    m2.read();
    m1.print();
    m2.print();
    Matrix::product(m1, m2, prod);
    prod.print();
}

void test_join() {
    Matrix m1 = Matrix(3,3);
    Matrix m2 = Matrix(3,6);
    Matrix merged;
    m1.random();
    m1.print();
    m2.random();
    m2.print();
    Matrix::join(m1, m2, merged);
    merged.print();
}

void test_identical() {
    Matrix m;
    Matrix::generate_identical(5, m);
    m.print();
}

void test_reduce() {
    Matrix m, red, redd;
    int x = 0;
    m = Matrix(4,4);
    m.read();
    m.gauss_jordan(red, x);
    m.rref(redd);
    cout << endl;
    red.print();
    cout << endl;
    redd.print();
    cout << endl;
}

void test_inversion() {
    int x;
    Matrix m, rid, inv, prod;
    m = Matrix(2,2);
    m.read();
    m.gauss_jordan(rid, x);
    rid.print();
    cout << "Invertible: " << m.is_invertible() << endl;    
    m.invert(inv);
    inv.print();
    Matrix::product(m,inv,prod);
    prod.print();
}

int main() {
    test_inversion();
}

