#include "queue.h"

Queue::Queue(int _max) {
    max = _max;
}

void Queue::clients() {
    while (true) {
        std::this_thread::sleep_for(1s);
        queue += 1;
        system("cls");
        std::cout << "Current queue: ";
        if (queue >= max) {
            std::cout << "The queue is full";
            continue;
        }
        std::cout << queue << " ";
    }
}

void Queue::cashier() {
    while (true) {
        std::this_thread::sleep_for(2s);
        queue -= 1;
        system("cls");
        std::cout << "Current queue: ";
        if (queue < 0) {
            std::cout << "The queue is empty! ";
            continue;
        }
        std::cout << queue << " ";
    }
}


void Queue::init() {
    thr_clnt = std::thread(&Queue::clients, this);
    thr_cshr = std::thread(&Queue::cashier, this);
}

Queue::~Queue() {
    thr_clnt.join();
    thr_cshr.join();
}