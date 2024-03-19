#include "computorv1.hpp"

//---------------------- Constructors & Destructors ----------------------

Equation::Equation()
{
}

Equation::Equation(std::string src)
{
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

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------
