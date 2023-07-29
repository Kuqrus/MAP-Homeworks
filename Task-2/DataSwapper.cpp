#include "DataSwapper.h"

Data::Data(int _num) : num{ _num } {};

int Data::Get() {
    return num;
}

void Data::Set(int n) {
    num = n;
}

void Swap(Data& d1, Data& d2) {

    std::lock(d1.m, d2.m);
    std::lock_guard<std::mutex> lock1(d1.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(d2.m, std::adopt_lock);

    //std::scoped_lock s_lock(d1.m, d2.m);

    //std::unique_lock<std::mutex> u_lock1(d1.m, std::defer_lock);
    //std::unique_lock<std::mutex> u_lock2(d2.m, std::defer_lock);
    //std::lock(u_lock1, u_lock2);

    int tmp = d1.Get();
    d1.Set(d2.Get());
    d2.Set(tmp);

    std::cout << "Swapped!" << std::endl;
}

void StartSwapper() {
    Data d1(3);
    Data d2(5);

    Data d3(0);

    std::cout << "D1 = " << d1.Get() << ", D2 = " << d2.Get() << ", D3 = " << d3.Get() << std::endl;

    std::cout << "\n" << "D3 <-> D1" << " | " << "D3 <-> D2" << std::endl << std::endl;

    std::thread t1(Swap, std::ref(d1), std::ref(d3));
    std::thread t2(Swap, std::ref(d3), std::ref(d2));
    t1.join();
    t2.join();

    std::cout << "\n" << "D1 = " << d1.Get() << ", D2 = " << d2.Get() << ", D3 = " << d3.Get() << std::endl;
}