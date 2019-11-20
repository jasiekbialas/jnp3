#ifndef DB406645_JB385150_FIBO_H_
#define DB406645_JB385150_FIBO_H_

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
    boost::dynamic_bitset<> bits;
    void normalise();
    void move_frd(size_t i);
//    void initialize_to_n(unsigned long long n);

public:
    Fibo();
    Fibo(unsigned long long n);
    Fibo(const std::string &s);
    Fibo(const Fibo &f);
//    Fibo(boost::dynamic_bitset<> &bits);

    void show();
//
//    friend Fibo operator+(const Fibo &fst, const Fibo &snd);
//    friend Fibo operator+(const Fibo &fst, unsigned long long n);
//
//    friend Fibo operator&(const Fibo &fst, const Fibo &snd);
//    friend Fibo operator|(const Fibo &fst, const Fibo &snd);
//    friend Fibo operator^(const Fibo &fst, const Fibo &snd);
//    friend Fibo operator<<(const Fibo &fst, size_t n);
//
//    void operator=(unsigned long long n);

    void operator+=(const Fibo &f);
//    void operator+=(unsigned long long n);

    void operator^=(const Fibo &f);
    void operator&=(const Fibo &f);
    void operator|=(const Fibo &f);

    void operator<<=(unsigned int n);

    bool operator<(const Fibo &f) const;
    bool operator==(const Fibo &f) const;

    friend std::ostream& operator<<(std::ostream &os, const Fibo &f);

    size_t length();
};

const Fibo Zero();
const Fibo One();

#endif //DB406645_JB385150_FIBO_H_
