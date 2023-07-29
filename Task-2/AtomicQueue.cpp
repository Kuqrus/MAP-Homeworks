#include "AtomicQueue.h"

void AtomicQueue::clients() {
    while (true) {
        std::this_thread::sleep_for(1s);
        //queue.store(queue.load() + 1);
        //queue.store(queue.load() + 1, std::memory_order_consume); // Error
        queue.store(queue.load() + 1, std::memory_order_relaxed);
        system("cls");
        std::cout << "Current queue: ";
        if (queue >= max) {
            std::cout << "The queue is full";
            continue;
        }
        std::cout << queue.load() << " ";
    }
}

void AtomicQueue::cashier() {
    while (true) {
        std::this_thread::sleep_for(2s);
        //queue.store(queue.load() - 1);
        //queue.store(queue.load() - 1, std::memory_order_consume); // Error
        queue.store(queue.load() - 1, std::memory_order_relaxed);
        system("cls");
        std::cout << "Current queue: ";
        if (queue < 0) {
            std::cout << "The queue is empty! ";
            continue;
        }
        std::cout << queue.load() << " ";
    }
}

AtomicQueue::AtomicQueue(int _max) {
    max = _max;
}
void AtomicQueue::init() {
    thr_clnt = std::thread(&AtomicQueue::clients, this);
    thr_cshr = std::thread(&AtomicQueue::cashier, this);
}
AtomicQueue::~AtomicQueue() {
    thr_clnt.join();
    thr_cshr.join();
}