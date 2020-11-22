#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#include <chrono>

class SimpleTimer {
public:
	SimpleTimer();
	~SimpleTimer();

	float Peek() const;

	float Mark();

private:
	std::chrono::steady_clock::time_point m_last_tp;
};

#endif // !TIMER_H
