#pragma once
#include <vector>
#include <iterator>
#include <thread>
#include <algorithm>
#include <future>

#include "Timer.h"

void add(int& x);

template <typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function func);

void InitForeach();
