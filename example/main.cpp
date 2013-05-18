#include <rlcg.hpp>

#include <iostream>
#include <cassert>
#include <vector>

int main() {
	rlcg::ReversibleLCG rng(42);

	std::vector<unsigned int> forward;
	std::cout << "\nForward:\n";
	for(int i = 0; i<10; ++i){
		forward.push_back(rng.next());
		std::cout << forward.back() << std::endl;
	}
	std::cout << "\nBackwards:\n";
	for(int i = 8; i>=0; --i){
		unsigned int val = rng.prev();
		std::cout << val << std::endl;
		assert(val == forward[i]);
	}

	std::vector<unsigned int> backward;
	std::cout << "\nBackwards:\n";
	for(int i = 0; i<10; ++i){
		backward.push_back(rng.prev());
		std::cout << backward.back() << std::endl;
	}
	std::cout << "\nForwards:\n";
	for(int i = 8; i>=0; --i){
		unsigned int val = rng.next();
		std::cout << val << std::endl;
		assert(val == backward[i]);
	}
	return 0;
}
