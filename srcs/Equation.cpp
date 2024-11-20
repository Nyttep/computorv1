#include "computorv1.hpp"

//---------------------- Constructors & Destructors ----------------------

Equation::Equation()
{
}

Equation::Equation(std::string src)
{
	*this = src;
}

Equation::Equation(const Equation &toCopy)
{
	*this = toCopy;
}

Equation::~Equation()
{
}

//----------------------- Operators Overloads ---------------------------

Equation &Equation::operator=(const Equation &rhs)
{
	this->lhs = rhs.lhs;
	this->rhs = rhs.rhs;
	return (*this);
}

Equation &Equation::operator=(const std::string &rhs)
{
	// std::erase(rhs, ' ');
	std::string tmp = rhs.substr(0, rhs.find('='));
	this->lhs = tmp;
	if (rhs.find('=') != rhs.npos)
		tmp = rhs.substr(rhs.find('=') + 1, rhs.length() - rhs.find('=') + 1);
	else
		tmp = "";
	this->rhs = tmp;
	return (*this);
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------

bool Equation::checkValid()
{
	if (this->lhs.checkValid() && this->rhs.checkValid())
		return (1);
	return (0);
}

void Equation::simplify()
{
	// Term tmp;

	// move everything to the left side
	while (this->rhs.terms.size() > 0)
	{
		this->rhs.terms[0].coef *= -1;
		this->lhs.terms.push_back(this->rhs.terms[0]);
		// tmp = this->rhs.terms[0];
		this->rhs.terms.erase(this->rhs.terms.begin());
	}
	// this->rhs.terms.push_back(tmp);
	// this->rhs.terms.push_back(Term());

	this->lhs.simplify();
	this->lhs.normalize();
}

std::string Equation::tostr()
{
	return (this->lhs.tostr() + " = " + this->rhs.tostr());
}

uint8_t Equation::getDegree()
{
	return (this->lhs.getDegree());
}

void Equation::solve()
{
	switch (this->getDegree())
	{
	case 0:
	{
		std::cout << "Polynomial degree: 0" << std::endl;
		if (this->lhs.getCoef(0) == 0)
			std::cout << "This equation is a constant polynomial, it is always true" << std::endl;
		else
			std::cout << "This equation is always false" << std::endl;
		break;
	}

	case 1:
	{
		std::cout << "Polynomial degree: 1" << std::endl;

		double ret = this->solveDegree1();

		std::cout << "The solution is:" << std::endl;

		// commented parts are for separation of whole number/decimal number

		// if (ret == (int)ret) // check if the result of the division is a whole number
		if (ret == 0) // honestly idk why but it prints -0 if i dont do that
			std::cout << "0" << std::endl;
		else
			std::cout << ret << std::endl;
		// else // if not, also display the result as a fraction
		// 	std::cout << -(this->lhs.getCoef(0)) << "/" << this->lhs.getCoef(1) << " (" << ret << ")" << std::endl;
		break;
	}

	case 2:
	{
		std::cout << "Polynomial degree: 2" << std::endl;
		double delta = this->getDelta();
		// commented parts are for separation of whole number/decimal number
		if (delta > 0)
		{
			std::cout << "Discriminant is strictly positive";

			std::pair<double, double> ret = this->solveDegree2(delta);

			if (!verbose)
				std::cout << ", the two solutions are:" << std::endl;
			else
				std::cout << "The two solutions are: " << std::endl;

			// if (ret.first == (int)ret.first) // if the result of the equation is a whole number
			if (ret.first == 0) // honestly idk why it prints -0 if i dont do that
				std::cout << "0" << std::endl;
			else
				std::cout << ret.first << std::endl;
			// else
			// 	std::cout << -(this->lhs.getCoef(1)) + sqrt(delta) << "/" << 2 * this->lhs.getCoef(0) << " (" << ret.first << ")" << std::endl;

			// if (ret.second == (int)ret.second) // if the result of the equation is a whole number
			if (ret.second == 0) // honestly idk why it prints -0 if i dont do that
				std::cout << "0" << std::endl;
			else
				std::cout << ret.second << std::endl;
			// else
			// 	std::cout << -(this->lhs.getCoef(1)) - sqrt(delta) << "/" << 2 * this->lhs.getCoef(0) << " (" << ret.second << ")" << std::endl;
		}
		else if (delta == 0)
		{
			std::cout << "Discriminant is equal to zero";

			std::pair<double, double> ret = this->solveDegree2(delta);

			if (!verbose)
				std::cout << ", the solution is: " << std::endl;
			else
				std::cout << "The solution is: " << std::endl;

			// if (ret.first == (int)ret.first) // if the result of the equation is a whole number
			if (ret.first == 0) // honestly idk why it prints -0 if i dont do that
				std::cout << "0" << std::endl;
			else
				std::cout << ret.first << std::endl;
			// else
			// 	std::cout << -(this->lhs.getCoef(1)) << "/" << 2 * this->lhs.getCoef(0) << " (" << ret.first << ")" << std::endl;
		}
		else
		{
			std::cout << "Discriminant is strictly negative, there is no real solution" << std::endl;
		}
		break;
	}

	default:
		break;
	}
}

double Equation::solveDegree1()
{
	double a = this->lhs.getCoef(0);
	double b = this->lhs.getCoef(1);

	if (doubleOperationOverflow(-a, b, '/'))
	{
		std::cout << "Error: Division overflow when doing " << -a << " / " << b << std::endl;
		exit(1);
	}

	if (b == 0) // it should never be the case but still just in case
	{
		std::cout << "Error: Division by zero" << std::endl;
		exit(1);
	}

	if (verbose)
		std::cout << "Calculating solution: " << -a << " / " << b << std::endl;

	return (-a / b);
}

double Equation::getDelta()
{
	double a = this->lhs.getCoef(2);
	double b = this->lhs.getCoef(1);
	double c = this->lhs.getCoef(0);

	if (doubleOperationOverflow(b, b, '*'))
	{
		std::cout << "Error: Multiplication overflow when doing " << b << " * " << b << std::endl;
		exit(1);
	}
	if (doubleOperationOverflow(4, a, '*'))
	{
		std::cout << "Error: Multiplication overflow when doing " << 4 << " * " << a << std::endl;
		exit(1);
	}
	if (doubleOperationOverflow(4 * a, c, '*'))
	{
		std::cout << "Error: Multiplication overflow when doing " << 4 * a << " * " << c << std::endl;
		exit(1);
	}
	if (doubleOperationOverflow(b * b, 4 * a * c, '-'))
	{
		std::cout << "Error: Substraction overflow when doing " << b * b << " - " << 4 * a * c << std::endl;
		exit(1);
	}

	if (verbose)
		std::cout << "Calculating discriminant: " << b * b - 4 * a * c << " = " << b << "^2" << " - " << 4 << " * " << a << " * " << c << std::endl;

	return (b * b - 4 * a * c);
}

std::pair<double, double> Equation::solveDegree2(double delta)
{
	double a = this->lhs.getCoef(2);
	double b = this->lhs.getCoef(1);

	if (delta > 0)
	{
		if (doubleOperationOverflow(-b, sqrt(delta), '+'))
		{
			std::cout << "Error: Addition overflow when doing " << -b << " + " << sqrt(delta) << std::endl;
			exit(1);
		}
		if (doubleOperationOverflow(2, a, '*'))
		{
			std::cout << "Error: Multiplication overflow when doing " << 2 << " * " << a << std::endl;
			exit(1);
		}
		if (doubleOperationOverflow(-b + sqrt(delta), 2 * a, '/'))
		{
			std::cout << "Error: Division overflow when doing " << -b + sqrt(delta) << " / " << 2 * a << std::endl;
			exit(1);
		}

		if (verbose)
			std::cout << "\nCalculating first solution: (" << -b << " + " << "√Δ" << ") / (" << 2 * a << ")" << std::endl;

		double x1 = (-b + std::sqrt(delta)) / (2 * a);

		if (doubleOperationOverflow(-b, sqrt(delta), '-'))
		{
			std::cout << "Error: Substraction overflow when doing " << -b << " - " << sqrt(delta) << std::endl;
			exit(1);
		}
		if (doubleOperationOverflow(-b - sqrt(delta), 2 * a, '/'))
		{
			std::cout << "Error: Division overflow when doing " << -b - sqrt(delta) << " / " << 2 * a << std::endl;
			exit(1);
		}

		if (verbose)
			std::cout << "Calculating second solution: (" << -b << " - " << "√Δ" << ") / (" << 2 * a << ")" << std::endl;

		double x2 = (-b - std::sqrt(delta)) / (2 * a);

		return (std::make_pair(x1, x2));
	}
	else if (delta == 0)
	{
		if (doubleOperationOverflow(2, a, '*'))
		{
			std::cout << "Error: Multiplication overflow when doing " << 2 << " * " << a << std::endl;
			exit(1);
		}
		if (doubleOperationOverflow(-b, 2 * a, '/'))
		{
			std::cout << "Error: Division overflow when doing " << -b << " / " << 2 * a << std::endl;
			exit(1);
		}

		if (verbose)
			std::cout << "\nCalculating solution: " << -b << " / (" << 2 * a << ")" << std::endl;

		double x = -b / (2 * a);
		return (std::make_pair(x, x));
	}
	else
	{
		return (std::make_pair(0, 0));
	}
}
