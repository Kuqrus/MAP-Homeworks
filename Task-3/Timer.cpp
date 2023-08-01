#include "Timer.h"

void Timer::Start() {
	t1 = std::chrono::high_resolution_clock::now();
}

void Timer::End() {
	t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> delta = t2 - t1;


	std::cout << "Time spent: ";
	if (delta.count() >= 100) {
		double deltaSec = delta.count() / 1000000;
		std::cout << deltaSec << " s\t";
	}
	else {
		std::cout << "0.0000" << delta.count() << " s\t";
	}
	std::cout << std::endl;
}