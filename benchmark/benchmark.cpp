#include <rlcg.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
	const unsigned long numbers{1000000000};
	volatile unsigned int temp{}; //used to trick the compiler into thinking we are doing something useful with the number
	volatile int temp2{};
	{
		std::cout << "next() " << numbers << " times...\t"; std::cout.flush();

		rlcg::ReversibleLCG rng(42);
		clock_t start, end;
		start = clock();
		for(unsigned long i = 0; i<numbers; ++i){
			temp = rng.next();
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
		for(unsigned long i = 0; i<numbers; ++i){
			temp = rng.prev();
		}
		end = clock();
		double cpuTime = double(end - start) / double(CLOCKS_PER_SEC);

		std::cout << cpuTime << " seconds\n";
	}
	{
		std::cout << "cstdlib rand() " << numbers << " times...\t"; std::cout.flush();

		clock_t start, end;
		start = clock();
		for(unsigned long i = 0; i<numbers; ++i){
			temp2 = rand();
		}
		end = clock();
		double cpuTime = double(end - start) / double(CLOCKS_PER_SEC);

		std::cout << cpuTime << " seconds\n";
	}
	return 0;
}
