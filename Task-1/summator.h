#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <condition_variable>



class VectorSummator {
private:
    int size = 0;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> v3;
    
    void FillVectors();

public:
    VectorSummator(int _size);

    void operator()();

};


void Start();
