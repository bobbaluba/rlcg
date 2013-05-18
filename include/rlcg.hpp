/*
    RLCG - Reversible Linear Congruential Generator
    Copyright (c) 2013 Johan Klokkhammer Helsing

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

       1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.

       2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.

       3. This notice may not be removed or altered from any source
       distribution.

    Johan Klokkhammer Helsing
    (johanhelsing@gmail.com)
*/

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

const int moduloInverse(int64_t a, int64_t b) {
    //euclid's algorithm
    int64_t x = 0;
    int64_t y = 1;
    int64_t lastx = 1;
    int64_t lasty = 0;
    int64_t q, r;
    int64_t tmp;

    while (b != 0) {
        q = a / b;
        r = a % b;
        tmp = x; x = lastx - q * x; lastx = tmp;
        tmp = y; y = lasty - q * y; lasty = tmp;
        a = b; b = r;
    }
    return lastx;
}

template<int64_t M = 1u<<31u, int64_t A = 1103515245, int64_t C = 12345, int64_t D = 2>
class ReversibleLCG {
    int64_t x;
    const int64_t ainverse;
public:
    ReversibleLCG(int seed) : x(seed), ainverse(moduloInverse(A, M)){}
    unsigned int next() {
        x = (A * x + C) % M;
        return x >> D;
    }
    unsigned int prev() {
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
