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


    boost::dynamic_bitset<> add_this = f.bits;

    if(add_this.size() > bits.size()) {
        bits.resize(add_this.size(), false);
    } else {
        add_this.resize(bits.size(), false);
    }

    bool last = false;
    size_t i = bits.size() - 1;


    if(bits[i] && add_this[i]) {
        bits.push_back(true);
    }

    while(i > 0) {
        switch ((int)last + (int)bits[i] + (int)add_this[i]) {
            case 3:
                bits[i+2] = true;
                bits[i] = false;
                last = true;
                i--;
                i -= (bool)i;
                break;
            case 2:
                bits[i+1] = true;
                bits[i] = false;
                bits[i-1] = bits[i-1] || add_this[i-1];
                last = true;
                i--;
                i -= (bool)i;
                break;
            case 1:
                bits[i] = true;
                last = false;
                i--;
                break;
            default:
                i--;
                break;
        }
    }

    switch ((int)last + (int)bits[0] + (int)add_this[0]) {
        case 3:
            bits[1] = true;
            bits[0] = true;
            break;
        case 2:
            bits[1] = true;
            bits[0] = false;
            break;
        case 1:
            bits[0] = true;
            break;
        default:
            break;
    }

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
        cout<<i-1<<": "<<bits[i-1]<<" "<<f.bits[i-1]<<endl;
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
    return true;
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