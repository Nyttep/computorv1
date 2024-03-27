#include "computorv1.hpp"

int check_args(int ac)
{
	if (ac != 2)
	{
		std::cout << "usage: ./computorv1 <equation>" << std::endl;
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	(void)av;
	if (!check_args(ac))
		return (1);

	Equation eq = std::string(av[1]);
	std::cout << std::defaultfloat << "equation : " << eq.tostr() << std::endl;
}