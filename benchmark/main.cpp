#include <rlcg.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
	const unsigned int numbers = 10000000;
	{
		std::cout << "next() " << numbers << " times...\t"; std::cout.flush();

		rlcg::ReversibleLCG rng(42);
		clock_t start, end;
		start = clock();
		for(unsigned int i = 0; i<numbers; ++i){
			rng.next();
		}
		end = clock();
		double cpuTime = double(end - start) / double(CLOCKS_PER_SEC);

		std::cout << cpuTime << " seconds\n";
	}
	{
		std::cout << "prev() " << numbers << " times...\t"; std::cout.flush();

		rlcg::ReversibleLCG rng(42);
		clock_t start, end;
		start = clock();
		for(unsigned int i = 0; i<numbers; ++i){
			rng.prev();
		}
		end = clock();
		double cpuTime = double(end - start) / double(CLOCKS_PER_SEC);

		std::cout << cpuTime << " seconds\n";
	}
	{
		std::cout << "cstdlib rand() " << numbers << " times...\t"; std::cout.flush();

		clock_t start, end;
		start = clock();
		for(unsigned int i = 0; i<numbers; ++i){
			rand();
		}
		end = clock();
		double cpuTime = double(end - start) / double(CLOCKS_PER_SEC);

		std::cout << cpuTime << " seconds\n";
	}

	return 0;
}
