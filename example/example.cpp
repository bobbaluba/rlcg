#include <rlcg.hpp>

#include <iostream>
#include <cassert>
#include <vector>

int main() {
	rlcg::ReversibleLCG rng(42);
	const int numtests = 10000;

	std::vector<unsigned int> forward;
	std::cout << "\nForward:\n";
	for(int i = 0; i<numtests; ++i){
		forward.push_back(rng.next());
		std::cout << forward.back() << std::endl;
		assert(forward.back() <= rng.max());
	}
	std::cout << "\nBackwards:\n";
	for(int i = numtests - 2; i>=0; --i){
		unsigned int val = rng.prev();
		std::cout << val << std::endl;
		assert(val == forward[static_cast<unsigned int>(i)]);
	}

	std::vector<unsigned int> backward;
	std::cout << "\nBackwards:\n";
	for(int i = 0; i<numtests; ++i){
		backward.push_back(rng.prev());
		std::cout << backward.back() << std::endl;
	}
	std::cout << "\nForwards:\n";
	for(int i = numtests - 2; i>=0; --i){
		unsigned int val = rng.next();
		std::cout << val << std::endl;
		assert(val == backward[static_cast<unsigned int>(i)]);
	}
	return 0;
}
