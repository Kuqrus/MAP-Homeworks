#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <future>

void Lowest(std::vector<int> vec, size_t i, size_t min, std::promise<int> prom) {

	for (size_t j = i + 1; j < vec.size(); j++) {
		if (vec[j] < vec[min]) {
			min = j;
		}
	}

	prom.set_value(min);
}

void Sorting(std::vector<int>& vec) {
	size_t min = 0;

	for (size_t i = 0; i < vec.size(); i++) {
		min = i;

		std::promise<int> prom;
		std::future<int> ft_pr = prom.get_future();
		auto ft = std::async(Lowest, vec, i, min, std::move(prom));

		ft.wait();

		min = ft_pr.get();

		if (i != min) {
			std::swap(vec[min], vec[i]);
		}
	}

}

void InitSorting() {
	std::vector<int> vec{ 5, 2, 6, 1, 0, 8 };

	Sorting(vec);

	for (const auto& el : vec) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}
