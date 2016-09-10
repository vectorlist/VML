#include <Random.h>

double Random::haltonSeq(const unsigned int index, const unsigned int base)
{
	/*FUNCTION(index, base)
		BEGIN
		result = 0;
	f = 1;
	i = index;
	WHILE(i > 0)
		BEGIN
		f = f / base;
	result = result + f * (i % base);
	i = FLOOR(i / base);
	END
		RETURN result;
	END*/
	double ret = 0;
	double fraction = 1.0 / (double)base;
	unsigned int acc = index;

	while (acc != 0)
	{
		unsigned int mod = acc % base;
		ret = ret + mod * fraction;
		acc = (acc - mod) / base;
		fraction = fraction / (double)base;
	}

	return ret;
}

