#pragma once
#include <iostream>
#include <mutex>
#include <thread>

class Data {
private:
    int num;

public:
    std::mutex m;

    Data(int _num);

    int Get();

    void Set(int n);
};

void Swap(Data& d1, Data& d2);

void StartSwapper();