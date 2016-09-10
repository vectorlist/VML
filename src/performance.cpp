#include "performance.h"

//performance* performance::globalPerformace = nullptr;

//performance::performance()
//{
//	/*globalPerformace = this;*/
//};

void performance::chronoStart()
{
	cStart = std::chrono::system_clock::now();
}

void performance::chronoEnd()
{
	cEnd = std::chrono::system_clock::now();
	std::chrono::seconds cSec;
	cSec = std::chrono::duration_cast<std::chrono::seconds>(cEnd - cStart);
	seconds = cSec.count();
}

QString performance::chronoElapseTime()
{
	int hour = seconds / 3600;
	int min = (seconds / 60) % 60;
	int sec = seconds % 60;

	return QString("hour : %1 min : %2 sec : %3 ").arg(hour).arg(min).arg(sec);
}