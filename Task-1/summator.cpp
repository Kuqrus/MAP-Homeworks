#include "summator.h"

std::once_flag flag;

void VectorSummator::FillVectors() {
    for (int i = 0; i < v1.size(); i++) {
        v1[i] = std::rand() % 1000 + 1;
        v2[i] = std::rand() % 1000 + 1;
    }
}

VectorSummator::VectorSummator(int _size) {
    size = _size;
    v1.resize(size);
    v2.resize(size);
    v3.resize(size);
    FillVectors();
}

void VectorSummator::operator()() {
    std::call_once(flag, []() {
        std::cout << "Numbers of hardware concurrency: " << std::thread::hardware_concurrency() << std::endl << std::endl;
        std::cout << "Elements \t1000\t\t10000\t\t100000\t\t1000000\n";
        });

    for (int i = 0; i < size; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

void Start() {
    int VectorSize = 1000;
    int ThreadAmount = 1;

    bool FirstGen = true;

    while (ThreadAmount <= 18) {
        VectorSummator vs(VectorSize);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> vt;

        for (int i = 0; i < ThreadAmount; i++) {
            vt.push_back(std::thread(vs));
        }

        for (auto& v : vt) {
            v.join();
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> delta = t2 - t1;
        if (FirstGen) {
            std::cout << ThreadAmount << " threads\t";
        }
        FirstGen = false;
        if (delta.count() >= 100) {
            double deltaSec = delta.count() / 1000000;
            std::cout << deltaSec << " s\t";
        }
        else {
            std::cout << "0.0000" << delta.count() << " s\t";
        }

        VectorSize *= 10;
        if (VectorSize > 1000000) {
            ThreadAmount *= 2;
            std::cout << std::endl;
            VectorSize = 1000;
            FirstGen = true;
        }
    }
}