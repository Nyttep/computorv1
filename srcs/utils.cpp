#include "computorv1.hpp"

int check_args(int ac)
{
	if (ac != 2)
	{
		return (0);
	}
	return (1);
}

bool strToDoubleOverflow(std::string str)
{
	std::istringstream ss(str);
	double d;
	ss >> d;
	if (ss.fail())
		return (1);
	return (0);
}

bool strToIntOverflow(std::string str)
{
	std::istringstream ss(str);
	int i;
	ss >> i;
	if (ss.fail())
		return (1);
	return (0);
}
