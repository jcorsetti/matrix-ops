#include <iostream>
#include <string>
#include "fraction.h"
using namespace std;

int main() {
  Fraction f1 = Fraction(1, 2);
  Fraction f2 = Fraction(2);
  Fraction f3 = Fraction(2, 5);
  Fraction np = Fraction(2, 5);
  Fraction f4, f5, f6, f7, f8, f9;

  cout << "f1: " << f1.print() << endl;
  cout << "f2: " << f2.print() << endl;
  cout << "f3: " << f3.print() << endl << endl;
  f4 = f1*(-2);
  f5 = f2/3;
  f6 = f3 - 4;
  f7 = f3 + 12;
  f8 = f3 + np;
  cout << "f4 = f1 * -2: " << f4.print() << endl;
  cout << "f5 = f2 / 3: " << f5.print() << endl;
  cout << "f6 = f3 - 4: " << f6.print() << endl;
  cout << "f7 = f3 + 12: " << f7.print() << endl << endl;
  
  cout << "f2 == 2?: " << (f2 == 2) << endl;
  cout << "f2 == 3?: " << (f2 == 3) << endl;
  cout << "f3 == np?: " << (f3 == np) << endl;
  cout << "f3 == f1?: " << (f3 == f1) << endl << endl;

  cout << "f1: " << f1.print() << endl;
  cout << "f2: " << f2.print() << endl;
  cout << "f3: " << f3.print() << endl;
  cout << "Input f9: " << endl;
  f9.read();
  cout << f9.print() << endl;
 }

