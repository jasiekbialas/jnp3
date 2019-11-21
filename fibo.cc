#include "fibo.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// Assumes (bits[size -1], bits[size-2], ... , bits[i]) has no two consecutive
// ones and bits[i] = bits[i-1] = 1.
void Fibo::correct_consecutive_bits(size_t i)
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
            bits[i] = true;
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

void Fibo::normalise()
{
    bool last = false;

    for (size_t i = bits.size(); i>0; i--) {
        if (bits[i-1] && last) {
            correct_consecutive_bits(i-1);
        }
        last = bits[i-1];
    }
}

// If bits has only zeros, then it leaves one ( 00...00 = 0 ).
void Fibo::remove_leading_zeros()
{
    while (bits.size()>1 && bits[bits.size()-1]==false) {
        bits.pop_back();
    }
}

// Returns 0;
Fibo::Fibo()
{
    bits = boost::dynamic_bitset<>{1, 0};
}

Fibo::Fibo(long long n)
{
    if (n < 0) throw runtime_error("Incorrect input");

    if (n==0) {
        bits = boost::dynamic_bitset<>{1, 0};
    }
    else {
        size_t back_id = 0;
        long long front_fibit = 2, back_fibit = 1;

        while (0<front_fibit && front_fibit<=n) {
            front_fibit = front_fibit+back_fibit;
            back_fibit = front_fibit-back_fibit;
            back_id++;
        }

        bits = boost::dynamic_bitset<>{back_id+1, false};

        while (0<n) {
            if (back_fibit<=n) {
                bits[back_id] = true;
                n -= back_fibit;
            }
            back_fibit = front_fibit-back_fibit;
            front_fibit = front_fibit-back_fibit;

            back_id--;
        }
    }
}

// Returns number corresponding to string s in Fibonacci coding.
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

void Fibo::operator+=(const Fibo& f)
{
    int last = 0;
    size_t i = bits.size();

    if (f.bits.size()>bits.size()) {
        bits.resize(f.bits.size(), false);
        i = bits.size();
    }
    else if (f.bits.size()<bits.size()) {
        i = f.bits.size();
    }
    else {
        if (f.bits[i-1]==bits[i-1]) {
            bits.push_back(false);
        }
    }

    int test;
    while (i>0) {
        test = last+bits[i-1]+f.bits[i-1];

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

void Fibo::operator<<=(int n)
{
    if (n < 0) throw runtime_error("Incorrect input");

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

size_t Fibo::length() const
{
    return bits.size();
}

const Fibo& Zero()
{
    static const Fibo zero;
    return zero;
}

const Fibo& One()
{
    static const Fibo one(1);
    return one;
}