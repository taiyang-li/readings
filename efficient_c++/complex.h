#ifndef __EFFICIENT_CPP_COMPLEX_H__
#define __EFFICIENT_CPP_COMPLEX_H__

#include <cstdio>
#include <iostream>

class Complex
{
  public:
    Complex(double real=0.0, double imag=0.0) : real_(real), imag_(imag_) {
      std::cout << "constructor" << std::endl;
    }
    ~Complex() {
      std::cout << "desctructor" << std::endl;
    }

    Complex(const Complex& other) : real_(other.real_), imag_(other.imag_) {
      std::cout << "copy constuctor" << std::endl;
    }

    Complex(const Complex& left, const Complex& right) : real_(left.real_+right.real_), imag_(left.imag_+right.imag_) {}
    

    Complex& operator=(const Complex& other) 
    {
      real_ = other.real_;
      imag_ = other.imag_;
      std::cout << "copy operator" << std::endl;
      return *this;
    }

    friend Complex operator+(const Complex& left, const Complex& right);

  private:
    double real_;
    double imag_;
};

Complex operator+(const Complex& left, const Complex& right)
{
  return Complex(left.real_+right.real_, left.imag_+right.imag_);
}




#endif  /*COMPLEX_H*/
