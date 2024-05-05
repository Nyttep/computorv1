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

		if (this->solveDegree1() == (int)this->solveDegree1()) // check if the result of the division is a whole number
			std::cout << ret << std::endl;
		else // if not, also display the result as a fraction
			std::cout << -(this->lhs.terms[0].coef) << "/" << this->lhs.terms[1].coef << " (" << ret << ")" << std::endl;
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
