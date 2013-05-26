Reversible Linear Congruential Generator
========================================

A header-only implementation of a random number generator which 
supports generating random numbers in two directions.

What do you mean reversible?
----------------------------

Most random number generators support only generation of numbers 
in one direction:

```c++
Rng myRng(seed)
int rnd1 = myRng.next();
int rnd2 = myRng.next();
int rnd3 = myRng.next();
```

With this implementation you can do:

```c++
rlcg::Reversible myRng(seed);
int rnd1 = myRng.next();
int rnd2 = myRng.next();
int rnd3 = myRng.prev(); // rnd3 == rnd1
int rnd4 = myRng.next(); // rnd4 == rnd2
```

Why would I want this?
----------------------

Sometimes it is useful to backtrace from a current random number to the 
previous ones without storing them along the way. This implementation 
stores only a 64-bit state internally, so memory the memory footprint is 
extremely small.


Are there other alternatives?
-----------------------------

Yes, these are the ones I'm aware of:


### Hashing

You could get the same functionality by using a hash 
function and an index.

```c++
class rrng {
    int index;
public:
    rrnd(int seed):index(seed){}
    int next(){ return hash(index++); }
    int prev(){ return hash(index--); }
};
```

where `hash(int)` is your favorite hash function


### Encryption

You could use a simple symmetric encryption algorithm to encrypt 
the previous number. I have not tested this, but in theory it should 
work.

How random are the generated numbers?
-------------------------------------

Basically the quality is the same as the as for a regular linear 
congruential generator, and it should be fine in most use cases. 
With the standard parameters, the generator has a period of 2^64.

See https://en.wikipedia.org/wiki/Linear_congruential_generator 
for more details.

There's an issue with the random number before the first number 
often being 0 or close to zero. I am not completely sure why this 
happens, but it seems to have something to do with what happens 
when an lcg wraps.

Author
------

Johan Klokkhammer Helsing (johanhelsing@gmail.com)


Thanks
------

Jakob Progsch for his initial implementation.
