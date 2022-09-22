#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


/**
 * An object to represent a large natural number (unsigned)
 */
class DigitString {
  public:
  // ** // Public methods
  int at(int i) {
    if (i<A.length() && i>-1) {
      return (A[i]-'0');
    }
    throw "out of range";
  }
  void set(int x, int i) {
    if (x >= this->base) {
      throw "num larger than base";
    }
    if (x < 0){
      throw "cant add negatives!";
    }
    A[i] = (char)(x+'0');
  }

  int get_base(){return base;}

  void set_base(int r){base=r;}

  std::string* str() {return &A;}

  std::string cpy() {return A;}

  int length() {
    return A.length();
  }

  void append(int x) {
    A += (char)(x+'0');
  }
  void prepend(int x) {
    A = (char)(x+'0') + A;
  }

  int count() {
    std::string Ac = A;
    int i=0;
    while (Ac[i] == '0') {
      Ac.erase(0,1);
    }
    return Ac.length();
  }

  void clean() {
    while (A[0] == '0') {
      A.erase(0,1);
    }
    if (A == ""){
      A="0";
    }
  }

  DigitString s_mult(DigitString* A, DigitString* B) {
    validate_len(A->str(),B->str());

    int n = A->length();
    if (n == 1) {
      int t = A->at(0) * B->at(0);
      DigitString out (t,base);
      return out;
    }
    int k = n/2;
    int upper = n-k;

    int offset=0;
    if (n%2 == 1){
      offset++;
    }

    DigitString
    a0(A->str()->substr(k+offset,upper),base),
    a1(A->str()->substr(0,k+offset),base),
    b0(B->str()->substr(k+offset,upper),base),
    b1(B->str()->substr(0,k+offset),base),

    p0(s_mult(&a1,&b1),base),
    p1( s_mult(&a1,&b0) + s_mult(&a0,&b1) ,base),
    p2(s_mult(&a0,&b0),base);

    p0 = p0<<(2*k);
    p1 = p1<<k;

    return p0 + p1 + p2;
  }

  // ** //

  // ** // Operators
  int operator [] (int i) {return at(i);}

  DigitString operator << (int n) {
    DigitString out = *this;
    for (int i=0; i<n; i++) {
      out.append(0);
    }
    out.clean();
    return out;
  }

  // mimics dropping n LSBs
  DigitString operator >> (int n){
    DigitString out = *this;
    for (int i=0; i<n; i++) {
      out.str()->pop_back();
    }
    out.clean();
    return out;
  }

  DigitString operator + (DigitString other) {
    if (this->get_base() != other.get_base()) {
      throw "base mismatch";
    }

    DigitString Ac (A);

    // pad strings as necessary
    validate_len(Ac.str(), other.str());

    int n = Ac.length(),
    carry = 0, t = 0;
    
    DigitString sum(n,"0");
    sum.set_base(this->base);
    for (int i=n-1; i>-1; i--) {

      // temporary calculation of current r^i
      t = carry + Ac[i] + other[i];

      // update the carry
      carry = t / base; // c++ int division rounds toward 0 (functioning as floor for +ve ints)

      t = t%base; // keep t bounded to radix

      sum.set(t,i);
    }
    if (carry) {
      sum.prepend(carry);
    }

    sum.clean();
    return sum;
  }

  DigitString operator - (DigitString other) {
    if (this->get_base() != other.get_base()) {
      throw "base mismatch";
    }
    DigitString Ac (A);

    // pad strings as necessary
    validate_len(this->str(),other.str());
    
    int n = Ac.length(),
    carry = 0;
    int t = 0;

    DigitString res;
    res.set_base(this->base);
    for (int i=n-1; i>-1; i--) {

      // temporary calculation of current digit r^i
      t = Ac[i] - other[i] - carry;

      if (t < 0){
        t += base;
        carry = 1;
      } else {
        carry = 0;
      }

      res.prepend(t);
    }

    res.clean();
    return res;
  }

  DigitString operator * (DigitString other) {
    DigitString *A = this, *B = &other;
    validate_len(A->str(), B->str());

    int n = A->length();
    if (n==0) return "0";

    if (n<4) {
      return s_mult(this,&other);
    }
    int r = A->get_base();
    int k = n/2; // floor(n/2)
    int upper = n-k; // ceil(n/2)

    int offset = 0;
    if(n%2==1){
      offset = 1;
    }

    DigitString 
    a0 (A->str()->substr(0,k+offset),r),
    a1 (A->str()->substr(k+offset,upper),r),
    b0 (B->str()->substr(0,k+offset),r),
    b1 (B->str()->substr(k+offset,upper),r),
    a0sa1 = a0+a1,
    b0sb1 = b0+b1,

    p0 = a0 * b0,
    p1 = a1 * b1,
    p2 = a0sa1 * b0sb1,
    p3 = p2 - (p0+p1);

    p0 = p0<<(2*k);
    p3 = p3<<k;
    
    DigitString out = p0+p1+p3;

    return out;
  }
  // ** //

  // ** // Constructors
  DigitString() {A="";}
  DigitString(int x) {
    base = x;
  }
  DigitString(std::string X){A=X;}
  DigitString(const char* X){A=X;}

  DigitString(int x, int r) {
    base = r;

    A="";
    while (x>0) {
      this->prepend(x%r);
      x /= r;
    }

  }
  
  DigitString(std::string X, int r){
    A = X;
    base = r;
  }

  DigitString(int n, std::string X){
    A = "";
    for (int i=0; i<n; i++)
      A += X;
  }

  DigitString(DigitString X, int r){
    A=*(X.str());
    base=r;
  }

  ~DigitString(){}
  // ** //

  friend std::ostream& operator<< ( std::ostream& os, const DigitString& S ){
    return os << (S.A);
  }

  

  private:
  void validate_len(std::string* A, std::string* B) {
    
    A->erase(0, std::min(A->find_first_not_of('0'), A->size()-1));
    B->erase(0, std::min(B->find_first_not_of('0'), B->size()-1));

    // pad strings as necessary
    for (int i=A->length(); i<B->length(); i++) {
      A->insert(0,"0");
    }
    for (int i=B->length(); i<A->length(); i++){
      B->insert(0,"0");
    }
  }

  std::string A;
  int base;
};