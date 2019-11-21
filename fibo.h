#ifndef DB406645_JB385150_FIBO_H
#define DB406645_JB385150_FIBO_H

#include <vector>
#include <string>

#include <boost/dynamic_bitset.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>

class Fibo :
        public boost::totally_ordered<Fibo>,
        public boost::addable<Fibo>,
        public boost::bitwise<Fibo>,
        public boost::left_shiftable<Fibo, unsigned int> {
private:
    mutable boost::dynamic_bitset<> bits;

    void move_frd(size_t i) const;

    void normalise() const;

    void remove_leading_zeros() const;

public:
    Fibo();

    Fibo(unsigned long long n);

    Fibo(const std::string& s);

    Fibo(const Fibo& f);

    void operator+=(const Fibo& f);

    void operator^=(const Fibo& f);

    void operator&=(const Fibo& f);

    void operator|=(const Fibo& f);

    void operator<<=(unsigned int n);

    bool operator<(const Fibo& f) const;

    bool operator==(const Fibo& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Fibo& f);

    size_t length();
};

const Fibo Zero();

const Fibo One();

#endif //DB406645_JB385150_FIBO_H
