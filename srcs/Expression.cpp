#include "computorv1.hpp"

//---------------------- Constructors & Destructors ----------------------

Expression::Expression()
{
}

Expression::Expression(const Expression &toCopy)
{
	*this = toCopy;
}

Expression::~Expression()
{
}

//----------------------- Operators Overloads ---------------------------

Expression &Expression::operator=(const Expression &rhs)
{
	this->terms = rhs.terms;
	return (*this);
}

Expression &Expression::operator=(const std::string &rhs)
{
	(void)rhs;
	return (*this);
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------
