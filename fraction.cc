#include <iostream>
#include <string>
#include <cstdlib>
#include "fraction.h"
using namespace std;

Fraction :: Fraction() {}

Fraction :: Fraction(long _num, long _den) {
  this->num = _num;
  this->den = _den;
}

Fraction :: Fraction(long _num) {
  this->num = _num;
  this->den = 1;
}

Fraction :: ~Fraction() {}

long Fraction :: get_num() const {
  return this->num;
}

long Fraction :: get_den() const {
  return this->den;
}

void Fraction :: set_num(long _num) {
  this->num = _num;
}

void Fraction :: set_den(long _den) {
  this->den = _den;
}

bool Fraction :: is_zero() const { //must be a valid form
  return (this->den != 0 && this->num == 0);
}

bool Fraction :: undefined() const{
  return (this->den == 0);
}

void Fraction :: read() {
  string buf, buf_num, buf_den;
  size_t found;
  int i;

  buf_num.clear();
  buf_den.clear();
  cin >> buf;
  found = buf.find("/"); //string.npos stores the index at which the / has been found
  //if it was found, a num/den format is expected 
  if(found != string :: npos) {
    for(i = 0; i < found; i++)
      buf_num.push_back(buf[i]);
    for(i = found + 1; i < buf.length(); i++)
      buf_den.push_back(buf[i]);
    this->num = stoi(buf_num);
    this->den = stoi(buf_den);
    if(this->undefined()) {
      cerr << "Invalid denumerator, setting fraction to " << this->num << endl;
      this->den = 1;
    }
  }
  else { //otherwise only the numerator is expected
    for(i = 0; i < buf.length(); i++)
      buf_num.push_back(buf[i]);
    this->num = stoi(buf_num);
    this->den = 1;
  }
  this->simplify();
}

string Fraction :: print() const {
  string fraz;
  fraz = to_string(this->num);
  if(this->num < 10 && this->num >= 0)
    fraz.insert(0, " ");
  if(this->den != 1) {
    fraz += "/" + to_string(this->den);
    if(this->den < 10)
      fraz += " ";
  }
  else fraz += "   ";
  return fraz;
}

double Fraction :: to_double() const  {
  return (double)num/(double)den;
}

Fraction Fraction :: reciprocal() const {
  Fraction rec;
  if(this->num == 0)
    rec = *(this);
  else rec = Fraction(this->den, this->num);
  return rec;
}

//helper function for absolute value
static long my_abs(long n1) {
  return ((n1 < 0) ? -n1 : n1);
}

//helper function for MCD used in simplification
static long mcd(long n1, long n2) {
  long com;
  bool found = false;
  bool first = true; //first iteration
  bool both_neg = (n1 < 0 && n2 < 0); //true if both negative
  
  n1 = my_abs(n1);
  n2 = my_abs(n2);
  if(n2 > n1) {   //Algorithm works for n1>=n2
    int tmp = n1;
    n1 = n2;
    n2 = tmp;
  }
  com = n2;
  while(!found && com > 1) {
    if((n1 % com) == 0 && (n2 % com) == 0) {
      found = true;
    }
    else {
      if(first) {
	      com /= 2;
	      first = false;
      }
      else com--;
    }
  }
  return ((both_neg)? -com : com);
}

void Fraction :: simplify() {
  long com = mcd(this->den, this->num);
  if(com > 1) { //the fraction can be simplified
    this->num /= com;
    this->den /= com;
  }
  if(den < 0) { //negative sign moved to numerator for convenience
    this->num = -num;
    this->den = -den;
  }
  if(is_zero())
    den = 1;
}

// -- OPERATORS OVERRIDE ON FRACTIONS --
Fraction Fraction :: operator = (const Fraction& F) {
  this->num = F.num;
  this->den = F.den;
  this->simplify();
  return *this;
}

Fraction Fraction :: operator + (const Fraction& F) {
  long nden = F.den * this->den;
  long nnum = F.den * this->num + F.num * this->den;
  Fraction res = Fraction(nnum, nden);
  res.simplify();
  return res;
}

Fraction Fraction :: operator - (const Fraction& F) {
  long nden = F.den * this->den;
  long nnum = F.den * this->num - F.num * this->den;
  Fraction res = Fraction(nnum, nden);
  res.simplify();
  return res;
} 

Fraction Fraction :: operator * (const Fraction& F) {
  Fraction res = Fraction(this->num * F.num, this->den * F.den);
  res.simplify();
  return res;
}

Fraction Fraction :: operator / (const Fraction& F) {
  return (*(this) * F.reciprocal());
}

bool Fraction :: operator == (const Fraction& F) {
  return (this->num == F.num && this->den == F.den);
}

bool Fraction :: operator != (const Fraction& F) {
  return (this->num != F.num || this->den != F.den);
}

// -- OPERATOR OVERRIDE ON FRACTIONS AND INTEGERS -- 

Fraction Fraction :: operator = (long n) {
  this->num = n;
  this->den = 1;
  this->simplify();
  return *(this);
}

Fraction Fraction :: operator + (long n) {
  Fraction to_add = Fraction(n);
  to_add = to_add + *(this);
  to_add.simplify();
  return to_add;
}

Fraction Fraction :: operator - (long n) {
   Fraction to_sub = Fraction(n);
   to_sub = *(this) - to_sub;
   to_sub.simplify();
   return to_sub;
} 

Fraction Fraction :: operator * (long n) {
  Fraction f = Fraction(this->num * n, this->den);
  f.simplify();
  return f;
}

Fraction Fraction :: operator / (long n) {
  Fraction f = Fraction(this->num, this->den * n);
  f.simplify();
  return f;
}

bool Fraction :: operator == (long n) {
  this->simplify();
  return (this->num == n && this->den == 1);
}

bool Fraction :: operator != (long n) {
  this->simplify();
  return (this->num != n || this->den != 1);
}
