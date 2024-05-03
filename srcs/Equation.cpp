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
		this->lhs.terms.push_back(this->rhs.terms[0]);
		this->rhs.terms.erase(this->rhs.terms.begin());
	}
	this->rhs.terms[0].coef = 0;

	this->lhs.simplify();
}

std::string Equation::tostr()
{
	return (this->lhs.tostr() + " = " + this->rhs.tostr());
}