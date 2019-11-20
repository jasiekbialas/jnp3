#include "fibo.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

//void Fibo::initialize_to_n(unsigned long long n) {
//  if(n == 0) {
//    Fibo();
//  } else {
//    unsigned long long i = 0, one = 1, two, current = 1;
//
//    while(current <= n) {
//      i++;
//      current += one;
//      two = one;
//      one = current - one;
//    }
//
//    bits = boost::dynamic_bitset<>{i, 0};
//
//    while(n > 0) {
//      i--;
//      if(n >= one) {
//        n -= one;
//        bits[i].flip();
//      }
//
//      current = two;
//      two =  one - two;
//      one = current;
//    }
//  }
//}

Fibo::Fibo(unsigned long long n) {
    if(n == 0) {
        Fibo();
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

//Fibo::Fibo(boost::dynamic_bitset<> &bits) : bits(bits) {};

Fibo::Fibo(const Fibo &f) {
//  TODO test
  bits = f.bits;
}

//Fibo operator+(const Fibo &fst, const Fibo &snd) {
//  Fibo r{fst};
//  r+=snd;
//  return r;
//}
//
//Fibo operator+(const Fibo &fst, const unsigned long long n) {
//  Fibo r{n};
//  r += fst;
//  return r;
//}
//
//Fibo operator&(const Fibo &fst, const Fibo &snd) {
//
//  if(fst.bits.size() != snd.bits.size()) {
//    throw runtime_exception("Incorrect arguments");
//  }
//
//  Fibo r{fst};
//
//  r.bits &= snd.bits;
//
//  return r;
//}
//
//Fibo operator|(const Fibo &fst, const Fibo &snd) {
//  if(fst.bits.size() != snd.bits.size()) {
//    throw "Incorrect arguments";
//  }
//
//  Fibo r{fst};
//
//  r.bits |= snd.bits;
//
//  return r;
//}
//
//Fibo operator^(const Fibo &fst, const Fibo &snd) {
//  if(fst.bits.size() != snd.bits.size()) {
//    throw "Incorrect arguments";
//  }
//
//  Fibo r{fst};
//
//  r.bits ^= snd.bits;
//
//  return r;
//}
//
//Fibo operator<<(const Fibo &fst, const size_t n) {
//  Fibo r{fst};
//  r <<= n;
//  return r;
//}
//
//void Fibo::operator=(unsigned long long n) {
//  bits = boost::dynamic_bitset<>{1,0};
//  initialize_to_n(n);
//}

void Fibo::operator+=(const Fibo &f) {
  if(f.bits.size() > bits.size()) {
    bits.resize(f.bits.size(), false);
  }

  if(bits[0] && f.bits[0]) {
    if(bits.size() == 1) bits.push_back(true);
    bits[1] = true;
    bits[0] = false;
  } else if(bits[0] || f.bits[0]) {
    bits[0] = true;
  }

  for(size_t i = 1; i < f.bits.size(); i++) {
    if(bits[i] && f.bits[i]) {
      bits[i] = false;
      if(i+1 < bits.size()) {
        bits[i+1] = true;
      } else {
        bits.push_back(true);
      }
      if(bits[i-1]) {
        size_t j = i - 1;
        while(bits[j]) {
          bits[j+1] = true;
          bits[j] = false;
          j--;
        }
      } else {
        bits[i-1] = true;
      }
    } else {
      bits[i] = bits[i] || f.bits[i];
    }
  }

  normalise();
}
//
//void Fibo::operator+=(const unsigned long long n) {
//  Fibo f{n};
//  if(f.bits.size() > bits.size()) {
//    bits.resize(f.bits.size(), false);
//  }
//
//  if(bits[0] && f.bits[0]) {
//    if(bits.size() == 1) bits.push_back(true);
//    bits[1] = true;
//    bits[0] = false;
//  } else if(bits[0] || f.bits[0]) {
//    bits[0] = true;
//  }
//
//  for(size_t i = 1; i < f.bits.size(); i++) {
//    if(bits[i] && f.bits[i]) {
//      bits[i] = false;
//      if(i+1 < bits.size()) {
//        bits[i+1] = true;
//      } else {
//        bits.push_back(true);
//      }
//      if(bits[i-1]) {
//        size_t j = i - 1;
//        while(bits[j]) {
//          bits[j+1] = true;
//          bits[j] = false;
//          j--;
//        }
//      } else {
//        bits[i-1] = true;
//      }
//    } else {
//      bits[i] = bits[i] || f.bits[i];
//    }
//  }
//
//  normalise();
//}

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
//  if (bits_.size() != f.bits_.size()) return bits_.size() < f.bits_.size();
//  size_t id = bits_.size() - 1;
//  do {
//    if (bits_[id] < f.bits_[id]) return true;
//    if (bits_[id] > f.bits_[id]) return false;
//    id--;
//  }
//  while (id != 0);

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
    bits[i-1] = true;
    bits[i] = true;
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