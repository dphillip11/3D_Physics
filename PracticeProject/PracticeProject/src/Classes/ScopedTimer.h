#pragma once
# include <chrono>
# include <string>
# include <iostream>
using namespace std;

class ScopedTimer {
    chrono::high_resolution_clock::time_point t0;
    string _message;
    float* deltaTime = nullptr;
    bool log = false;
public:
    ScopedTimer() : t0(chrono::high_resolution_clock::now()), _message("duration: "), log(true) {}
    ScopedTimer(float* dt) : t0(chrono::high_resolution_clock::now()), deltaTime(dt) {}
    ScopedTimer(string message) : t0(chrono::high_resolution_clock::now()), _message(message) {}
    ~ScopedTimer() {
        auto  t1 = chrono::high_resolution_clock::now();
        auto nanos = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
        if (log)
            cout << _message << nanos << " nanoseconds\n";
        *deltaTime = (float)nanos/1000000000;
    }
};