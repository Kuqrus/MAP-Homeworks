#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>

#include "Timer.h"

using namespace std::chrono_literals;

std::mutex m;
std::once_flag flag;
std::exception_ptr GlobalException = nullptr;
HANDLE h;

// Class that contains and print IDs of "corrupted" threads
class Corrupted {
private:
	std::vector<std::thread::id> v;
public:
	void Add(std::thread::id id);
	void Print();
};
Corrupted c;

// Function returns random number from 5000 to 20000
int RandNumLarge();

// Random chance to simulate error in "calculations"
bool RussianRoulette();

void VerySlowSort(int num);

void StartCalculation();