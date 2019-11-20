#include "fibo.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

Fibo::Fibo(unsigned long long n) {
    if(n == 0) {
        bits = boost::dynamic_bitset<> {1, 0};
    } else {
        unsigned long long i = 0, one = 1, two, current = 1;

        while(current <= n) {
            i++;
            current += one;
            two = one;
            one = current - one;
        }

        bits = boost::dynamic_bitset<>{i, 0};

        while(n > 0) {
            i--;
            if(n >= one) {
                n -= one;
                bits[i].flip();
            }

            current = two;
            two =  one - two;
            one = current;
        }
    }
}

Fibo::Fibo(const std::string &s) {
  size_t n = s.length();
  if(n == 0) {
    throw "Incorrect input";
  }
  if(s[0] == '0' && n > 1) {
    throw "Incorrect input";
  }
  bits = boost::dynamic_bitset<>{n, 0};
  for(size_t i = 0; i < n; i++) {
    if(s[i] == '1') {
      bits[n-1-i].flip();
    }
    else if (s[i] != '0') {
      throw "Incorrect input";
    }
  }
  normalise();
}

Fibo::Fibo() {
  bits = boost::dynamic_bitset<> {1, 0};
}

Fibo::Fibo(const Fibo &f) {
//  TODO test
  bits = f.bits;
}

void Fibo::operator+=(const Fibo &f) {

    int last = 0;
    size_t i = bits.size();

    if(f.bits.size() > bits.size()) {
        bits.resize(f.bits.size(), false);
        i = bits.size();
    } else if (f.bits.size() < bits.size()) {
        while(i != f.bits.size()) i--;
    } else {
        if(f.bits[i-1] == bits[i-1]) {
            bits.push_back(false);
        }
    }

    int test;
    while(i > 0) {
        test = last + (int)bits[i-1] + (int)f.bits[i-1];

        switch (test) {

            case 3:
                bits[i+1] = true;
                bits[i-1] = false;
                last = 1;
                i --;
                if(i > 1) i --;
                break;
            case 2:
                if(bits[i]) {
                    bits[i+1] = true;
                    bits[i] = false;
                    bits[i-1] = true;
                    last = 0;
                } else {
                    bits[i] = true;
                    bits[i-1] = false;
                    last = 1;
                }

                if(i > 2) {
                    if(bits[i-2] || f.bits[i-2]) {
                        bits[i] = true;
                        bits[i-1] = true;
                        bits[i-2] = false;
                        last = 0;
                    }
                }

                i --;
                if(i > 1) i --;
                break;
            case 1:
                bits[i-1] = true;
                last = 0;
                i--;
                break;
            default:
                i--;
                break;
        }
    }
    if(test == 1) bits[0];

    normalise();
}

void Fibo::operator^=(const Fibo &f) {
  bits ^= f.bits;
}

void Fibo::operator&=(const Fibo &f) {
  bits &= f.bits;
}

void Fibo::operator|=(const Fibo &f) {
  bits |= f.bits;
}

void Fibo::operator<<=(unsigned int n) {
  bits<<=n;
}

bool Fibo::operator<(const Fibo &f) const {

    if(bits.size() < f.bits.size()) return true;
    if(bits.size() > f.bits.size()) return false;

    for(size_t i = bits.size(); i > 0; i--) {
        if(bits[i-1]) {
            if(!f.bits[i-1]) {
                return false;
            }
        } else {
            if(f.bits[i-1]) {
                return true;
            }
        }
    }
    return false;
}

bool Fibo::operator==(const Fibo &f) const {
  return bits == f.bits;
}

std::ostream &operator<<(std::ostream &os, const Fibo &f) {
//  size_t id = f.bits_.size() - 1;
//  do {
//    os << f.bits_[id];
//    id--;
//  }
//  while (id != 0);

  return os;
}

size_t Fibo::length() {
  return bits.size();
}


const Fibo Zero() {
  return Fibo();
}

const Fibo One() {
  return Fibo(1);
}

void Fibo::show() {
  cout<<bits<<endl;
}

int Fibo::eval() {
    int big = 1;
    int small = 1;
    int sum = 0;

    for(size_t i = 0; i < bits.size(); i++) {
        if(bits[i]) sum += big;
        big += small;
        small = big - small;
    }

    return sum;
}

void Fibo::move_frd(size_t i) {
  i++;
  while(i < bits.size()) {
    bits[i-1] = false;
    bits[i] = false;
    i++;
    if(i == bits.size()) {
      bits.push_back(true);
      break;
    } else {
      bits[i].flip();
      i++;

      if(i == bits.size()) {
        break;
      } else if(!bits[i]) {
        break;
      }
    }
  }
}

void Fibo::normalise() {
  bool last = false;

  for(size_t i = bits.size(); i > 0; i--) {
    if(bits[i-1]) {
      if(last) {
        move_frd(i-1);
        last = false;
      } else {
        last = true;
      }
    } else {
      last = false;
    }
  }
}