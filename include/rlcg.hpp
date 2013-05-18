#ifndef RLCG_HPP
#define RLCG_HPP

#include <cstdint>

namespace rlcg {

namespace details {

template<class T>
T mod(T a, T b) {
    a %= b;
    return a > 0 ? a : a + b;
}

void extendedEuclid(int64_t a, int64_t b, int64_t *lastx, int64_t *lasty) {
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

int64_t moduloInverse(int64_t a, int64_t m){
    int64_t inverse, discard;
    extendedEuclid(a, m, &inverse, &discard);
    return inverse;
}

template<int64_t M = 1u<<31u, int64_t A = 1103515245, int64_t C = 12345, int64_t D = 2>
class ReversibleLCG {
    int64_t x;
public:
    ReversibleLCG(int seed) : x(seed) {}
    unsigned int next() {
        x = (A * x + C) % M;
        return x >> D;
    }
    unsigned int prev() {
        const int64_t ainverse = moduloInverse(A, M);
        x = mod(ainverse * (x - C), M);
        return x >> D;
    }
    unsigned int max() const {
        return M >> D;
    }
};

} // end namespace details

using ReversibleLCG = details::ReversibleLCG<>;

} // end namespace rlcg


#endif // RLCG_HPP
