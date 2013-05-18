Reversible Linear Congruential Generator
========================================

A header-only implementation of a random number generator which 
supports generating random numbers in two directions.

What do you mean reversible?
----------------------------

Most random number generators support only generation of numbers 
in one direction:

    Rng myRng(seed)
    int rnd1 = myRng.next();
    int rnd2 = myRng.next();
    int rnd3 = myRng.next();

With this implementation you can do:

    rlcg::Reversible myRng(seed);
    int rnd1 = myRng.next();
    int rnd2 = myRng.next();
    int rnd3 = myRng.prev(); // rnd3 == rnd1
    int rnd4 = myRng.next(); // rnd4 == rnd2


Why would i want this?
----------------------

Sometimes it is useful to backtrace from a current random number to the 
previous ones without storing them along the way. This implementation 
stores only a 64-bit state internally, so memory the memory footprint is 
extremely small.


How random are the generated numbers?
-------------------------------------

Basically the quality is not suitable for cryptographic applications, but
it should be fine in most use cases. With the standard parameters, the 
generator has a period of 2^64.

See https://en.wikipedia.org/wiki/Linear_congruential_generator 
for more details.


Author
------

Johan Klokkhammer Helsing (johanhelsing@gmail.com)


Thanks
------

Jakob Progsch for his initial implementation.
