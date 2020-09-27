using namespace std;
#include <iostream>
#include <cstring>
#include "matrix.h"

char menu();
void input_matrix(Matrix&);
void random_matrix(Matrix&);

int main() {
  int r1,r2;
  char c; //choice
  Fraction lambda;
  Matrix m;
 
  input_matrix(m);
  m.print();
  do {
    c = menu();
    switch(c) {
    //New input matrix
      case 'N': {
        input_matrix(m);
      }
        break;
    //New random matrix
      case 'R': {
        random_matrix(m);
      }
        break;
    //Row swap operation
      case 'S': {
        cin >> r1 >> r2;
        m.S(r1 - 1, r2 - 1);
      }
        break;
    //Multiplication operation
      case 'D': {
        cin >> r1;
        lambda.read();
        m.D(r1 - 1, lambda);
      }
        break;
    //Elimination operation
      case 'E': {
        cin >> r1 >> r2;
        lambda.read();
        m.E(r1 - 1, r2 - 1, lambda);
      }
        break;
    //To floating point values
      case 'V' : {
        m.print_val();
      }
        break;
      case 'H' : {
        cout << "Elimination (r1, r2, k): each element in row r1 is added the corresponding element in row r2, multiplied by lambda (integer or fraction)." << endl;
        cout << "Row swap (r1, r2): each element in row r1 is swapped with the respective element in row r2." << endl;
        cout << "Multiplication (r1, lambda): each element in row r1 is multiplied by lambda (integer or fraction)." << endl;
        cout << "To double: prints the matrix in floating point values." << endl;
      }
    }
    m.print();
  } while(c != 'X');
  return 0;
}

void input_matrix(Matrix &m) {
  int r,c;
  do {
    cout << "Column number (>0):";
    cin >> c;
  } while(c <= 0);
  
  do {
    cout << "Row number (>0):";
    cin >> r;
  } while(r <= 0);
  m = Matrix(r,c);
  m.read();
}

void random_matrix(Matrix &m) {
  int r,c;
  do {
    cout << "Column number (>0):";
    cin >> c;
  } while(c <= 0);
  
  do {
    cout << "Row number (>0):";
    cin >> r;
  } while(r <= 0);
  m = Matrix(r,c);
  m.random(); 
}

char menu()
{
  char s;
  cout << "---OPTIONS---" << endl;
  cout << "Input new matrix (N)" << endl;
  cout << "Generate random matrix (R)" << endl;
  cout << "Elimination (E)" << endl;
  cout << "Row swap (S)" << endl;
  cout << "Multiplication (D)" << endl;
  cout << "To double (T)" << endl;
  cout << "Help (H)" << endl;
  cout << "Exit (X)" << endl;
  cout << endl << "Choose an option: ";
  cin >> s;
  return toupper(s);
}
