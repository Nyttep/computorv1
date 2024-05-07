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
	// move everything to the left side
	while (this->rhs.terms.size() > 0)
	{
		this->rhs.terms[0].coef *= -1;
		this->lhs.terms.push_back(this->rhs.terms[0]);
		this->rhs.terms.erase(this->rhs.terms.begin());
	}
	this->rhs.terms[0].coef = 0;

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
		if (this->lhs.terms[0].coef == 0)
			std::cout << "This equation is a constant polynomial, it is always true" << std::endl;
		else
			std::cout << "This equation is always false" << std::endl;
		break;
	}

	case 1:
	{
		std::cout << "Polynomial degree: 1" << std::endl;
		std::cout << "The solution is:" << std::endl;

		double ret = this->solveDegree1();

		if (ret == (int)ret) // check if the result of the division is a whole number
			std::cout << ret << std::endl;
		else // if not, also display the result as a fraction
			std::cout << -(this->lhs.terms[0].coef) << "/" << this->lhs.terms[1].coef << " (" << ret << ")" << std::endl;
		break;
	}

	case 2:
	{
		std::cout << "Polynomial degree: 2" << std::endl;
		double delta = this->getDelta();
		std::pair<double, double> ret = this->solveDegree2(delta);
		if (delta > 0)
		{
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			if (ret.first == (int)ret.first)
				std::cout << ret.first << std::endl;
			else
				std::cout << -(this->lhs.terms[1].coef) + sqrt(delta) << "/" << 2 * this->lhs.terms[0].coef << " (" << ret.first << ")" << std::endl;
			if (ret.second == (int)ret.second)
				std::cout << ret.second << std::endl;
			else
				std::cout << -(this->lhs.terms[1].coef) - sqrt(delta) << "/" << 2 * this->lhs.terms[0].coef << " (" << ret.second << ")" << std::endl;
		}
		else if (delta == 0)
		{
			std::cout << "Discriminant is equal to zero, the solution is:" << std::endl;
			if (ret.first == (int)ret.first)
				std::cout << ret.first << std::endl;
			else
				std::cout << -(this->lhs.terms[1].coef) << "/" << 2 * this->lhs.terms[0].coef << " (" << ret.first << ")" << std::endl;
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
	double a = this->lhs.terms[0].coef;
	double b = this->lhs.terms[1].coef;
	return (-a / b);
}

double Equation::getDelta()
{
	double a = this->lhs.terms[2].coef;
	double b = this->lhs.terms[1].coef;
	double c = this->lhs.terms[0].coef;
	return (b * b - 4 * a * c);
}

std::pair<double, double> Equation::solveDegree2(double delta)
{
	double a = this->lhs.terms[2].coef;
	double b = this->lhs.terms[1].coef;
	if (delta > 0)
	{
		double x1 = (-b + sqrt(delta)) / (2 * a);
		double x2 = (-b - sqrt(delta)) / (2 * a);
		return (std::make_pair(x1, x2));
	}
	else if (delta == 0)
	{
		double x = -b / (2 * a);
		return (std::make_pair(x, x));
	}
	else
	{
		return (std::make_pair(0, 0));
	}
}
