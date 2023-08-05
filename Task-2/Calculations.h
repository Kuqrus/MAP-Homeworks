#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>

#include "Timer.h"

using namespace std::chrono_literals;

// Class that contains and print IDs of "corrupted" threads
class Corrupted {
private:
	std::vector<std::thread::id> v;
public:
	void Add(std::thread::id id);
	void Print();
};


// Function returns random number from 5000 to 20000
int RandNumLarge();

// Random chance to simulate error in "calculations"
bool RussianRoulette();

void VerySlowSort_in_parallel(int num);
void StartCalculation_in_parallel();

//void VerySlowSort(int num);
//void StartCalculation();