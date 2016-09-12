#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>
#include <QString>

//#define PF() performance::global()

class performance
{
public:
	performance(){};
	~performance(){};

	void chronoStart();
	void chronoEnd();
	QString chronoElapseTime();

protected:
	std::chrono::system_clock::time_point cStart;
	std::chrono::system_clock::time_point cEnd;
	long long seconds;
	
};

#endif // PERFORMANCE_H
