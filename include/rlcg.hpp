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
constexpr bool isPowerOfTwo(T x){
    return (x & (x - 1)) == 0;
}

//template metaprogramming implementation of euclids algorithm
/* Based on this recursive definition from wikipedia:
function extended_gcd(a, b)
  if b == 0
    return (1, 0)
  else
    (q, r) := divide (a, b)
    (s, t) := extended_gcd(b, r)
    return (t, s - q * t)
This assumes a "divide" procedure exists that returns a (quotient,remainder) pair (one could alternatively put q := a div b, and then r = a − b * q).
*/
template <uint64_t A, uint64_t B>
struct ExtendedEuclid {
    enum {
        x = ExtendedEuclid<B, A - B * (A / B)>::y,
        y = ExtendedEuclid<B, A - B * (A / B)>::x - (A / B) * ExtendedEuclid<B, A - B * (A / B)>::y
    };
};
template <uint64_t T>
struct ExtendedEuclid<T, 0> {
    enum {x = 1, y = 0};
};

//modulus M, multiplicand A, increment C, least significant bits to discard D
template<uint64_t M = 1ul<<63ul, uint64_t A = 6364136223846793005, uint64_t C = 1442695040888963407, uint64_t D = 32>
class ReversibleLCG {
    static_assert(isPowerOfTwo(M), "M is not a power of two as it should be");
    uint64_t x;
public:
    ReversibleLCG(unsigned int seed) : x(seed){}
    unsigned int next() {
        //nextx = (a * x + c) % m;
        x = (A * x + C) & (M - 1);
        return x >> D;
    }
    unsigned int prev() {
        const uint64_t ainverse = ExtendedEuclid<A, M>::x;
        //prevx = (ainverse * (x - c)) mod m
        x = ainverse * (x - C) & (M - 1);
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
