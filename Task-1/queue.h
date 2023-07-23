#pragma once
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class Queue {
private:
    int queue = 0;
    int max;

    std::thread thr_clnt;
    std::thread thr_cshr;

    void clients();

    void cashier();
public:

    Queue(int _max);

    void init();

    ~Queue();

};
