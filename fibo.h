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
        public boost::left_shiftable<Fibo, int> {
private:
    boost::dynamic_bitset<> bits;

    void correct_consecutive_bits(size_t i);

    void normalise();

    void remove_leading_zeros();

public:
    Fibo();

    Fibo(long long n);

    explicit Fibo(const std::string& s);

    void operator+=(const Fibo& f);

    void operator^=(const Fibo& f);

    void operator&=(const Fibo& f);

    void operator|=(const Fibo& f);

    void operator<<=(int n);

    bool operator<(const Fibo& f) const;

    bool operator==(const Fibo& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Fibo& f);

    size_t length() const;
};

const Fibo& Zero();

const Fibo& One();

#endif //DB406645_JB385150_FIBO_H
