#pragma once

class ScopedTimer {
	std::chrono::high_resolution_clock::time_point t0;
	std::string _message;
	float* deltaTime = nullptr;
	bool log = false;
public:
	ScopedTimer() : t0(std::chrono::high_resolution_clock::now()), _message("duration: "), log(true) {}
	ScopedTimer(float* dt) : t0(std::chrono::high_resolution_clock::now()), deltaTime(dt) {}
	ScopedTimer(std::string message) : t0(std::chrono::high_resolution_clock::now()), _message(message) {}
	~ScopedTimer() {
		auto  t1 = std::chrono::high_resolution_clock::now();
		auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
		if (log)
			std::cout << _message << nanos << " nanoseconds\n";
		*deltaTime = (float)nanos / 1000000000;
	}
};