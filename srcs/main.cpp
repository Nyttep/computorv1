#include "computorv1.hpp"

bool verbose = false;

void printUsage()
{
	std::cout << "Usage: ./computor [-v] <equation>" << std::endl;
}

bool parseArgs(int ac, char **av)
{
	if (ac == 3) // check if there are 2 arguments
	{
		if (av[1] == std::string("-v") || av[1] == std::string("--verbose")) // check if first argument is -v or --verbose
		{
			verbose = true; // set verbose to true
		}
		else
		{
			printUsage();
			return 1;
		}
	}
	else if (ac != 2) // check if there is a wrong number of arguments
	{
		printUsage();
		return 1;
	}
	return 0;
}

int main(int ac, char **av)
{
	try // catch bad_alloc exceptions
	{

		if (parseArgs(ac, av))
			return 1;
		else if (verbose)
			av++; // shift args when -v is present

		Equation eq;

		try
		{
			eq = std::string(av[1]); // extract equation from args
		}
		catch (const char *e)
		{
			std::cerr << e << '\n';
			return 1;
		}

		eq.simplify(); // simplify equation

		// check if equation is still valid
		try
		{
			eq.checkValid();
		}
		catch (const char *e)
		{
			std::cerr << "Error: " << e << '\n';
			return 1;
		}

		std::cout << "Reduced form : " << eq.tostr() << std::endl; // display equation

		eq.solve(); // solve equation
	}
	catch (std::bad_alloc &e)
	{
		std::cerr << "Error: bad_alloc occured, you can try rerunning this program but your RAM seems to be overloaded\n";
		return 1;
	}
}