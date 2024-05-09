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

// bool resIsPositive(double lhs, double rhs)
// {
// 	if (lhs > 0 && rhs > 0) // both positive
// 	{
// 		std::cout << "both positive" << std::endl;
// 		return (true);
// 	}
// 	else if (lhs < 0 && rhs < 0) // both negative
// 	{
// 		std::cout << "both negative" << std::endl;
// 		return (true);
// 	}
// 	return (false);
// }

bool doubleOperationOverflow(double lhs, double rhs, char op)
{
	if (op == '+')
	{
		if (rhs > 0 && lhs > std::numeric_limits<double>::max() - rhs)
			return (1);
		if (rhs < 0 && lhs < -std::numeric_limits<double>::max() - rhs)
			return (1);
	}
	else if (op == '-')
	{
		if (rhs > 0 && lhs < -std::numeric_limits<double>::max() + rhs)
			return (1);
		if (rhs < 0 && lhs > std::numeric_limits<double>::max() + rhs)
			return (1);
	}
	else if (op == '*')
	{
		if (rhs == 0)
			return (0);
		if (lhs > 0)
		{
			if (rhs > 0 && lhs > std::numeric_limits<double>::max() / rhs)
				return (1);
			if (rhs < 0 && lhs > -std::numeric_limits<double>::max() / rhs)
				return (1);
		}
		else if (lhs < 0)
		{
			if (rhs > 0 && lhs < -std::numeric_limits<double>::max() / rhs)
				return (1);
			if (rhs < 0 && lhs < std::numeric_limits<double>::max() / rhs)
				return (1);
		}
	}
	else if (op == '/')
	{
		if (rhs > -1 && rhs < 0)
		{
			if (lhs > 0)
			{
				if (rhs > 0 && lhs > std::numeric_limits<double>::max() * rhs)
					return (1);
				if (rhs < 0 && lhs > -std::numeric_limits<double>::max() * rhs)
					return (1);
			}
			else if (lhs < 0)
			{
				if (rhs > 0 && lhs < -std::numeric_limits<double>::max() * rhs)
					return (1);
				if (rhs < 0 && lhs < std::numeric_limits<double>::max() * rhs)
					return (1);
			}
		}
	}
	return (0);
}
