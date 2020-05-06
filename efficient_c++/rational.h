#ifndef __EFFICIENT_CPP_RATIONAL_H__
#define __EFFICIENT_CPP_RATIONAL_H__

#include <cstdio>
#include <iostream>

class Rational
{
  public:
   Rational(int m=0, int n=0) : m_(m), n_(n) {
     // std::cout << "Rational constructor" << std::endl;
   }

   ~Rational () {
     // std::cout << "Rational destructor" << std::endl;
   }
   
   Rational(const Rational& other) : m_(other.m_), n_(other.n_) {
     // std::cout << "Rational copy destructor" << std::endl;
   }
   
   int m() const {return m_;}
   int n() const {return n_;}

  private:
    int m_;
    int n_;
};


#endif  /*RATIONAL_H*/
