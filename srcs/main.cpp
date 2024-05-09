#include "computorv1.hpp"

int main(int ac, char **av)
{
	try // catch bad_alloc exceptions
	{
		if (!check_args(ac)) // check if there is only one argument
		{
			std::cout << "usage: ./computorv1 <equation>" << std::endl;
			return (1);
		}

		Equation eq;

		try
		{
			eq = std::string(av[1]); // extract equation from args
		}
		catch (const char *e)
		{
			std::cerr << e << '\n';
			return (1);
		}

		// check if equation is valid
		try
		{
			eq.checkValid();
		}
		catch (const char *e)
		{
			std::cerr << e << '\n';
			return (1);
		}

		eq.simplify(); // simplify equation

		// check if equation is still valid
		try
		{
			eq.checkValid();
		}
		catch (const char *e)
		{
			std::cerr << "AFTER SIMPLIFICATION " << e << '\n';
			return (1);
		}

		std::cout << "Reduced form : " << eq.tostr() << std::endl; // display equation

		eq.solve(); // solve equation
	}
	catch (std::bad_alloc &e)
	{
		std::cerr << "Error: bad_alloc occured, you can try rerunning this program but your RAM seems to be overloaded" << '\n';
		return (1);
	}
}