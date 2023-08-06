#include "ParallelForEach.h"

void add(int& x) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	x += 10;
}

template <typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function func) {
	size_t total_elements = std::distance(first, last);

	if (total_elements <= 3) {
		std::for_each(first, last, func);
	}
	else {
		Iterator middle = first;
		std::advance(middle, total_elements / 3);

		//std::thread t1(parallel_for_each<Iterator, Function>, first, middle, func);
		//std::thread t2(parallel_for_each<Iterator, Function>, middle, last, func);
		//t1.join();
		//t2.join();

		auto fut = std::async(std::launch::async, parallel_for_each<Iterator, Function>, first, middle, func);
		parallel_for_each(middle, last, func);

	}
}

void InitForeach() {
	Timer time;

	std::vector<int> vvv{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	time.Start();

	parallel_for_each(vvv.begin(), vvv.end(), add);

	time.End();

	for (const auto& el : vvv) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}