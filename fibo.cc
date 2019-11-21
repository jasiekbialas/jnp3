#include "fibo.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

void Fibo::move_frd(size_t i) const
{
    i++;
    while (i<bits.size()) {
        bits[i-1] = false;
        bits[i] = false;
        i++;
        if (i==bits.size()) {
            bits.push_back(true);
            break;
        }
        else {
            bits[i].flip();
            i++;

            if (i==bits.size()) {
                break;
            }
            else if (!bits[i]) {
                break;
            }
        }
    }
}

void Fibo::normalise() const
{
    bool last = false;

    for (size_t i = bits.size(); i>0; i--) {
        if (bits[i-1]) {
            if (last) {
                move_frd(i-1);
                last = false;
            }
            else {
                last = true;
            }
        }
        else {
            last = false;
        }
    }
}

void Fibo::remove_leading_zeros() const
{
    while (bits.size()>1 && bits[bits.size()-1]==false) {
        bits.pop_back();
    }
}

Fibo::Fibo(unsigned long long n)
{
    if (n==0) {
        bits = boost::dynamic_bitset<>{1, 0};
    }
    else {
        size_t back_id = 0;
        unsigned long long front_fib = 2, back_fib = 1;

        while (0<front_fib && front_fib<=n) {
            front_fib = front_fib+back_fib;
            back_fib = front_fib-back_fib;
            back_id++;
        }

        bits = boost::dynamic_bitset<>{back_id+1, false};

        while (0<n) {
            if (back_fib<=n) {
                bits[back_id] = true;
                n -= back_fib;
            }
            back_fib = front_fib-back_fib;
            front_fib = front_fib-back_fib;

            back_id--;
        }
    }
}

Fibo::Fibo(const std::string& s)
{
    size_t n = s.length();
    if (n==0) {
        throw runtime_error("Incorrect input");
    }
    if (s[0]=='0' && n>1) {
        throw runtime_error("Incorrect input");
    }

    bits = boost::dynamic_bitset<>{n, false};
    for (size_t i = 0; i<n; i++) {
        if (s[i]<'0' || '1'<s[i]) {
            throw runtime_error("Incorrect input");
        }
        bits[n-1-i] = s[i]-'0';
    }

    normalise();
}

Fibo::Fibo()
{
    bits = boost::dynamic_bitset<>{1, 0};
}

Fibo::Fibo(const Fibo& f)
{
    bits = f.bits;
}

void Fibo::operator+=(const Fibo& f)
{
    int last = 0;
    size_t i = bits.size();

    if (f.bits.size()>bits.size()) {
        bits.resize(f.bits.size(), false);
        i = bits.size();
    }
    else if (f.bits.size()<bits.size()) {
        while (i!=f.bits.size()) i--;
    }
    else {
        if (f.bits[i-1]==bits[i-1]) {
            bits.push_back(false);
        }
    }

    int test;
    while (i>0) {
        test = last+(int) bits[i-1]+(int) f.bits[i-1];

        switch (test) {

        case 3:
            bits[i+1] = true;
            bits[i-1] = false;
            last = 1;
            i--;
            if (i>1) i--;
            break;
        case 2:
            if (bits[i]) {
                bits[i+1] = true;
                bits[i] = false;
                bits[i-1] = true;
                last = 0;
            }
            else {
                bits[i] = true;
                bits[i-1] = false;
                last = 1;
            }

            if (i>2) {
                if (bits[i-2] || f.bits[i-2]) {
                    bits[i] = true;
                    bits[i-1] = true;
                    bits[i-2] = false;
                    last = 0;
                }
            }

            i--;
            if (i>1) i--;
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
    if (test==1) bits[0];

    normalise();
}

void Fibo::operator^=(const Fibo& f)
{
    if (bits.size()<=f.bits.size()) {
        bits.resize(f.bits.size());
        bits ^= f.bits;
    }
    else {
        for (size_t i = 0; i<f.bits.size(); i++) {
            bits[i] ^= f.bits[i];
        }
    }

    this->remove_leading_zeros();
    this->normalise();
}

void Fibo::operator&=(const Fibo& f)
{
    if (bits.size()>=f.bits.size()) {
        bits.resize(f.bits.size());
        bits &= f.bits;
    }
    else {
        for (size_t i = 0; i<bits.size(); i++) {
            bits[i] &= f.bits[i];
        }
    }

    this->remove_leading_zeros();
}

void Fibo::operator|=(const Fibo& f)
{
    if (bits.size()<=f.bits.size()) {
        bits.resize(f.bits.size());
        bits |= f.bits;
    }
    else {
        for (size_t i = 0; i<f.bits.size(); i++) {
            bits[i] |= f.bits[i];
        }
    }
    this->normalise();
}

void Fibo::operator<<=(unsigned int n)
{
    if (bits[bits.size()-1]==false) return; // This is true iff bits == {0}
    bits.resize(bits.size()+n);
    bits <<= n;
}

bool Fibo::operator<(const Fibo& f) const
{

    if (bits.size()<f.bits.size()) return true;
    if (bits.size()>f.bits.size()) return false;

    return bits<f.bits;
}

bool Fibo::operator==(const Fibo& f) const
{
    return bits==f.bits;
}

std::ostream& operator<<(std::ostream& os, const Fibo& f)
{
    for (size_t i = f.bits.size(); i>0; i--) {
        os << f.bits[i-1];
    }
    return os;
}

size_t Fibo::length()
{
    return bits.size();
}

const Fibo Zero()
{
    return Fibo();
}

const Fibo One()
{
    return Fibo(1);
}