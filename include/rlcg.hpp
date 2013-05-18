#ifndef RLCG_HPP
#define RLCG_HPP

#include <cstdint>

namespace rlcg {

namespace details{

template<class T>
T mod(T a, T b) {
    a %= b;
    return a > 0 ? a : a + b;
}

void ext_euclid(int64_t a, int64_t b, int64_t *lastx, int64_t *lasty) {
    int64_t x = 0;
    int64_t y = 1;
    *lastx = 1;
    *lasty = 0;
    int64_t q, r;
    int64_t tmp;

    while (b != 0) {
        q = a / b;
        r = a % b;
        tmp = x; x = *lastx - q * x; *lastx = tmp;
        tmp = y; y = *lasty - q * y; *lasty = tmp;
        a = b; b = r;
    }
}

} // end namespace details

using namespace details;

class ReversibleLCG {
    int64_t x;
    int64_t a;
    int64_t m;
    int64_t c;
    int64_t ainverse;
public:
    ReversibleLCG(int seed) : x(seed), a(1103515245), m(1u<<31u), c(12345){
        int64_t discard;
        ext_euclid(a, m, &ainverse, &discard);
    }
    unsigned int next(){
        x = (a*x + c) % m;
        return x >> 2;
    }
    unsigned int prev(){
        x = mod(ainverse * (x - c), m);
        return x >> 2;
    }
    unsigned int max(){
        return m >> 2;
    }
};

} // end namespace rlcg


#endif // RLCG_HPP
