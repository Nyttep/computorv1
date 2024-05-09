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

bool doubleOperationOvervlow(double lhs, double rhs, char op)
{
	if (op == '+')
	{
		if (rhs > 0 && lhs > std::numeric_limits<double>::max() - rhs)
			return (1);
		if (rhs < 0 && lhs < std::numeric_limits<double>::min() - rhs)
			return (1);
	}
	else if (op == '-')
	{
		if (rhs > 0 && lhs < std::numeric_limits<double>::min() + rhs)
			return (1);
		if (rhs < 0 && lhs > std::numeric_limits<double>::max() + rhs)
			return (1);
	}
	else if (op == '*')
	{
		if (lhs == -1 && rhs == std::numeric_limits<double>::min())
			return (1);
		if (rhs == -1 && lhs == std::numeric_limits<double>::min())
			return (1);
		if (rhs != 0 && lhs > std::numeric_limits<double>::max() / rhs)
			return (1);
		if (rhs != 0 && lhs < std::numeric_limits<double>::min() / rhs)
			return (1);
	}
	else if (op == '/')
	{
		if (lhs == -1 && rhs == std::numeric_limits<double>::min())
			return (1);
		if (rhs == -1 && lhs == std::numeric_limits<double>::min())
			return (1);
		if (rhs < 1 && rhs > 0 && lhs > std::numeric_limits<double>::max() * rhs)
			return (1);
		if (rhs < 1 && rhs > 0 && lhs < std::numeric_limits<double>::min() * rhs)
			return (1);
	}
	return (0);
}
