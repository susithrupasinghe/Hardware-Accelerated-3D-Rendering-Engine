#include "SimpleTimer.h"

SimpleTimer::SimpleTimer() {
	m_last_tp = std::chrono::steady_clock::now();
}

SimpleTimer::~SimpleTimer() {}

float SimpleTimer::Peek() const {
	std::chrono::steady_clock::time_point current_tp = std::chrono::steady_clock::now();
	std::chrono::duration<float> fElapsedTime = current_tp - m_last_tp;
	return fElapsedTime.count();
}

float SimpleTimer::Mark() {
	std::chrono::steady_clock::time_point current_tp = std::chrono::steady_clock::now();
	std::chrono::duration<float> fElapsedTime = current_tp - m_last_tp;
	m_last_tp = current_tp;
	return fElapsedTime.count();
}
