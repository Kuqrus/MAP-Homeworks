#pragma once
#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

class AtomicQueue {
private:
    std::atomic<int> queue{ 0 };
    int max;

    std::thread thr_clnt;
    std::thread thr_cshr;

    void clients();
    void cashier();

public:
    AtomicQueue(int _max);
    void init();
    ~AtomicQueue();
};