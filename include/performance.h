#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>
#include <string>

using std::string;

enum PerformanceType
{
	None,
	NanoSeconds,
	MicroSeconds,
	MilliSeconds
};

class performance
{
public:
	performance(PerformanceType type = None) : m_type(type){};
	~performance(){};

	void chronoStart();
	void chronoEnd();
	string chronoElapseTime();

protected:
	std::chrono::system_clock::time_point cStart;
	std::chrono::system_clock::time_point cEnd;
	//for none
	//long long seconds;
	std::chrono::seconds sec;

	std::chrono::nanoseconds Nano;
	std::chrono::microseconds Micro;
	std::chrono::milliseconds Milli;

	PerformanceType m_type;

private:
	string none_output();
	string nano_output();
	string micro_output();
	string milli_output();
	
};

#endif // PERFORMANCE_H
