#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "matrix.h"
using namespace std;

Matrix ::Matrix(){}

Matrix ::Matrix(int r, int c)
{
  this->elem.resize(r);
  for (int i = 0; i < r; i++)
  {
    this->elem[i].resize(c);
    for (int j = 0; j < c; j++)
      this->elem[i][j] = Fraction(0);
  }
  this->r = r;
  this->c = c;
}

Fraction Matrix ::get_elem(int row, int column) const
{
  return this->elem[row][column];
}

void Matrix ::set_elem(const Fraction& F, int row, int column)
{
  this->elem[row][column] = F;
}

int Matrix ::get_r() const
{
  return this->r;
}

int Matrix ::get_c() const
{
  return this->c;
}

void Matrix ::read()
{ 
  for (int i = 0; i < this->r; i++)
  {
    for (int j = 0; j < this->c; j++)
    {
      //Each element is written by the user
      Fraction n = Fraction();
      cout << "m[" << i << "][" << j << "]: ";
      n.read();
      this->set_elem(n, i, j);
    }
  }
}

void Matrix ::random()
{
  srand(time(NULL));
  for (int i = 0; i < this->r; i++)
    for (int j = 0; j < this->c; j++)
      this->elem[i][j] = Fraction(rand() % 10);
}

void Matrix ::print() const
{
  cout << endl;
  for (int i = 0; i < this->r; i++)
  {
    for (int j = 0; j < this->c; j++)
      cout << this->get_elem(i, j).print() << " ";
    cout << endl;
  }
  cout << endl;
}

void Matrix ::print_val() const
{
  cout << endl;
  for (int i = 0; i < this->r; i++)
  {
    for (int j = 0; j < this->c; j++)
      cout << setprecision(3) << setw(6) << this->get_elem(i, j).to_double() << " ";
    cout << endl;
  }
  cout << endl;
}

void Matrix ::product(const Matrix& m1, const Matrix& m2, Matrix& res)
{ 
  res = Matrix(m1.get_r(), m2.get_c());
  //this number of column must be the same as M number of rows
  if (m1.get_c() == m2.get_r())
  {
    for (int i = 0; i < res.get_r(); i++) {
      for (int j = 0; j < res.get_c(); j++) {
        Fraction new_f = Fraction(0);
        for (int k = 0; k < m1.get_c(); k++) {
          new_f = new_f + m1.get_elem(i, k) * m2.get_elem(k, j);
        }
        res.set_elem(new_f, i, j);
      }
    }
  }
  else { //Error in dimension
    cerr << "Error: left matrix has " << m1.get_c() << " columns and right matrix has " << m2.get_r() << " rows. These numbers must be equal to carry out this operation." << endl;
  }
}

bool Matrix ::is_square() const
{
  return (this->c == this->r);
}

bool Matrix ::is_invertible() const
{
  return (this->det() != 0);
}

bool Matrix ::is_identical() const
{
  bool res = true;
  if (!this->is_square())
    res = false;
  for (int i = 0; i < this->r && res; i++)
    for (int j = 0; j < this->c && res; j++)
     {
      if ((j == i) && (this->get_elem(i, j) != long(1))) {
        res = false;
      }
      if ((j != i) && (this->get_elem(i, j) != long(0))) {
        res = false;
      }
    }
  return res;
}

void Matrix ::clone(Matrix& m) const
{ //creates a clone
  m = Matrix(this->r, this->c);
  for (int i = 0; i < m.r; i++)
    for (int j = 0; j < m.c; j++) {
      Fraction f = this->get_elem(i, j);
      m.set_elem(f, i, j);
    }
}

void gauss_jordan_ric(Matrix& mat, int col, int row, int &ns)
{
  if (col < mat.get_c() && row < mat.get_r())
  {
    int i = row;
    //Looking for a non-zero element in the current column
    while (i < mat.get_r() && mat.get_elem(i, col).is_zero())
      i++;
    if (i < mat.get_r())
    { //When found, it is swapped to the first row if not already there
      if (i != row)
      { 
        mat.S(row, i); 
        ns++;
      }
      Fraction rec = mat.get_elem(row, col).reciprocal(); 
      //This value is then used to eliminate the below column
      for (i = row + 1; i < mat.get_r(); i++)
      {
        Fraction tmp = Fraction(-1, 1) * mat.get_elem(i, col) * rec;
        mat.E(i, row, tmp);
      }
      //Go to next row and column
      gauss_jordan_ric(mat, col + 1, row + 1, ns);
    }
    else //The current column is zero-valued, 
      gauss_jordan_ric(mat, col + 1, row, ns);
  }
}

void Matrix ::gauss_jordan(Matrix& red, int &n_swaps) const
{ //ns (swap numbers) is used for determinant computed with gauss method 
  this->clone(red);
  n_swaps = 0;
  gauss_jordan_ric(red, 0, 0, n_swaps);
}

static bool is_pivot(const Matrix& M, int col, int row)
{
  bool res = true;
  for (int i = row + 1; i < M.get_r() && res; i++) //the column under tht pivot must be null
    res = (M.get_elem(i, col).is_zero());
  if (res && col != 0)
    for (int i = col - 1; i >= 0 && res; i--) //the row to the left of the pivot must be null
      res = (M.get_elem(row, i).is_zero());
  return res;
}

static void rref_ric(Matrix& m, int col, int row)
{
  if (col >= 0 && row >= 0)
  {
    int i = row;
    //Check the column until a not-zero element is found
    while (i >= 0 && (m.get_elem(i, col) == 0)) 
      i--;
    if (i >= 0)
    {
      if (is_pivot(m, col, i))
      { //A pivot has been found. It is used to cancel all numbers in the column above it
        Fraction rec = m.get_elem(i, col).reciprocal();
        m.D(i, rec); 
        for (int j = i - 1; j >= 0; j--)
          m.E(j, i, (m.get_elem(j, col) * -1));
        rref_ric(m, col - 1, i - 1); //next pivot will be above it and to the left
      }
      else
        rref_ric(m, col - 1, i); //if not, next pivot will be to the left
    }
    else // The the column is zero, I need to look to the left
      rref_ric(m, col - 1, row); 
  }
}

void Matrix ::rref(Matrix& red) const
{        
  int x; 
  this->gauss_jordan(red, x);
  rref_ric(red, red.c - 1, red.r - 1);
}

void Matrix ::rref_for_inv(const Matrix& m, Matrix& red)
{
  int x; //not actually used, only needed for swap count
  m.gauss_jordan(red, x);
  //column dimension is half, because the matrix has been joined with the identical one for reduction
  rref_ric(red, red.get_c() / 2 - 1, red.get_r() - 1);
}

void Matrix ::submatrix(int ir, int ic, int nr, int nc, Matrix& red) const
{ 
  if ((ir < 0) || (ic < 0) || (nr <= 0) || (nc <= 0) || (ir >= this->r) || (ic >= this->c)) {
    cerr << "Error: indexes out of bound." << endl;
  }
  else
  {
    //Dimensions are adjusted if necessary
    if((ir + nr) > this->r)
      nr = this->r - ir;
    if((ic + nc) > this->c)
      nc = this->c - ic;

    red = Matrix(nr, nc);
    for (int i = 0; i < nr; i++)
      for (int j = 0; j < nc; j++)
        red.elem[i][j] = this->elem[i + ir][j + ic];
  }
}

void Matrix ::join(const Matrix& m1, const Matrix& m2, Matrix& res)
{ //must have same number of rows
  if (m1.get_r() != m2.get_r()) 
    cerr << "Error: the matrices must have the same number of rows." << endl;
  else
  {
    res =  Matrix(m1.get_r(), m1.get_c() + m2.get_c()); 
    for (int i = 0; i < m1.get_r(); i++)               
      for (int j = 0; j < m1.get_c(); j++)
        res.set_elem(m1.get_elem(i,j), i, j);
    for (int i = 0; i < m2.get_r(); i++) 
      for (int j = 0; j < m2.get_c(); j++)
        res.set_elem(m2.get_elem(i,j), i, j + m1.get_c());
  }
}

void Matrix ::generate_identical(int order, Matrix& m)
{
  m = Matrix(order, order);
  Fraction f = Fraction(1);
  for (int i = 0; i < order; i++)
    m.set_elem(f, i, i);
}

void Matrix ::invert(Matrix& res) const
{ 
  if (this->is_invertible())
  {
    Matrix m_clone, to_reduce, reduced, identical;
    this->clone(m_clone);
    Matrix :: generate_identical(this->c, identical);
    Matrix :: join(m_clone, identical, to_reduce);
    Matrix :: rref_for_inv(to_reduce, reduced);
    reduced.submatrix(0, m_clone.get_c(), m_clone.get_c(), m_clone.get_c(), res);
  }
}

double Matrix ::det() const
{
  int n_swap;                      //swap number
  Matrix red;
  Fraction d = Fraction(1, 1); //determinant
  this->gauss_jordan(red, n_swap); //gauss jordan method is used for matrix computation
  for (int i = 0; i < red.get_c(); i++)
    d = d * red.get_elem(i, i); //determinant is the product of elements on the diagonal
  if ((n_swap % 2) == 1)                //sign is fixed if necessary
    d.set_num(-d.get_num());
  return d.to_double();
}

void Matrix ::S(int r1, int r2)
{
  //Given two rows, the numbers are swapped one by one
  for (int i = 0; i < this->c; i++) {
    Fraction tmp = this->get_elem(r1, i);
    this->set_elem(this->get_elem(r2, i), r1, i);
    this->set_elem(tmp, r2, i);
  }
}

void Matrix ::E(int r1, int r2, Fraction lambda) 
{
  //Each element on row2 is multiplied by lambda and added to the same element in row1
  if (!lambda.is_zero() && (r1 != r2))
    for (int i = 0; i < this->c; i++) {
      Fraction tmp = this->get_elem(r1, i) + lambda * this->get_elem(r2, i);
      this->set_elem(tmp, r1, i);
    }     
}

void Matrix ::D(int r, Fraction lambda)
{
  //Each element on a given row is multiplied by lambda
  if (!lambda.is_zero())
    for (int i = 0; i < this->c; i++)
      if (!this->get_elem(r, i).is_zero()) {
        Fraction tmp = this->get_elem(r, i) * lambda;
        this->set_elem(tmp, r, i);
      }
}
