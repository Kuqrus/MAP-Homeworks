#pragma once
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

class Timer {
private:
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;

public:
	void Start();
	void End();
};
