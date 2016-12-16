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
	switch (m_type)
	{
	case None :
		//std::chrono::seconds cSec;
		sec = std::chrono::duration_cast<std::chrono::seconds>(cEnd - cStart);
		//seconds = cSec.count();
		break;

	case NanoSeconds:
		Nano = std::chrono::duration_cast<std::chrono::nanoseconds>(cEnd - cStart);
		break;

	case MicroSeconds:
		Micro = std::chrono::duration_cast<std::chrono::microseconds>(cEnd - cStart);
		break;

	case MilliSeconds:
		Milli = std::chrono::duration_cast<std::chrono::milliseconds>(cEnd - cStart);
		break;
	default:
		break;
	}
	
}

string performance::chronoElapseTime()
{
	string output;
	switch (m_type)
	{
	case None:
		output = none_output();
		break;

	case NanoSeconds:
		output = nano_output();
		break;

	case MicroSeconds:
		output = micro_output();
		break;

	case MilliSeconds:
		output = milli_output();
		break;
	default :
		break;
	}
	return output;
}

string performance::none_output()
{
	long long seconds = sec.count();
	int hour = seconds / 3600;
	int min = (seconds / 60) % 60;
	int sec = seconds % 60;

	//return QString("hour : %1 min : %2 sec : %3 ").arg(hour).arg(min).arg(sec);
	string output;
	output.append("hour : ").append(std::to_string(hour) + ' ').
		append("min : ").append(std::to_string(min) + ' ').
		append("sec : ").append(std::to_string(sec) + ' ');
	return output;
}

string performance::nano_output()
{
	return string("nanoseconds : ").append(std::to_string(Nano.count()));
}

string performance::micro_output()
{
	return string("microseconds : ").append(std::to_string(Micro.count()));
}

string performance::milli_output()
{
	return string("milliseconds : ").append(std::to_string(Milli.count()));
}