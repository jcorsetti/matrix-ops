// -*- C++ -*-

#ifndef FRACTION_H
#define FRACTION_H
#include <string>
using namespace std;

class Fraction
{

private:
  long num; // numerator
  long den; // denominator

public:
  //default constructor
  Fraction();          
  //constructor with numerator and denominator           
  Fraction(long _num, long _den); 
  //constructor from integer number
  Fraction(long _num);            
  //destructor
  ~Fraction();
  //simplifies the fraction if possible                    
  void simplify();                
  //getter and setters for attributes
  long get_num() const;           
  long get_den() const;        
  void set_num(long _num);     
  void set_den(long _den);         
  //true if fraction is 0/1
  bool is_zero() const;    
  //true if fraction is 0/0       
  bool undefined() const;  
  //input from user       
  void read();     
  //converts to string for input               
  string print() const;         
  //converts to decimal number  
  double to_double() const;   
  //returns the fraction reciprocal    
  Fraction reciprocal() const;    

  //defines operator between fractions. Result is simplified when possible
  Fraction operator=(const Fraction &); 
  Fraction operator+(const Fraction &); 
  Fraction operator-(const Fraction &); 
  Fraction operator*(const Fraction &); 
  Fraction operator/(const Fraction &); 
  bool operator==(const Fraction &);     
  bool operator!=(const Fraction &);
  
  //defines operators between fractions and integer number. Result is simplified when possible
  Fraction operator=(long); 
  Fraction operator+(long); 
  Fraction operator-(long); 
  Fraction operator*(long); 
  Fraction operator/(long); 
  bool operator==(long);
  bool operator!=(long);     
};

#endif
