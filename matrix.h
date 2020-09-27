// -*- C++ -*-

#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "fraction.h"

class Matrix
{
private:
  vector<vector<Fraction>> elem; //matrix elements
  int r;                 //row dimension
  int c;                 //column dimension

  //used for verifying existence of inversion matrix
  static void rref_for_inv(const Matrix& m, Matrix& red);

public:
  Matrix();
  //default constructor with rows and columns                            
  Matrix(int row, int column);                
  //get element at given coordinates                                     
  Fraction get_elem(int row, int column) const;
  //set element at given coordinates   
  void set_elem(const Fraction& f, int row, int column);  
  //getter for dimensions
  int get_r() const;                               
  int get_c() const;                               
  //input a matrix
  void read();    
  //randomly initialize a matrix                                 
  void random();                
  //formatted print in fractions                  
  void print() const;
  //formatted print in rational numbers                                
  void print_val() const;
  //checks on matrix property                          
  bool is_square() const;                           
  bool is_invertible() const;                        
  bool is_identical() const; 
  //clone a matrix                          
  void clone(Matrix& m) const;
  //Gauss-Jordan algorithm for reduction. Number of swaps only necessary for determinant computation                           
  void gauss_jordan(Matrix& red, int& n_swaps) const;          
  //row and column reduction
  void rref(Matrix& red) const;
  //create at index (ir,ic) a submatrix of dimension(nr,nc)                            
  void submatrix(int ir, int ic, int nr, int nc, Matrix& res) const;  
  //generate inverse matrix, if it exists
  void invert(Matrix& res) const;        
  //compute determinant with gauss method                
  double det() const;                              
  
  //joins in res the given matrices
  static void join(const Matrix& m1, const Matrix& m2, Matrix& res); 
  //row column product
  static void product(const Matrix& m1, const Matrix& m2, Matrix& res);          
  //generates identical matrix of given order
  static void generate_identical(int order, Matrix& m);

  //swap, elimination and divide operations for reduction
  void S(int r1, int r2);             
  void E(int r1, int r2, Fraction lambda);
  void D(int r, Fraction lambda);        
};

#endif
