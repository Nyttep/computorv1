#include "computorv1.hpp"

//---------------------- Constructors & Destructors ----------------------

Term::Term()
{
}

Term::Term(const Term &toCopy)
{
	*this = toCopy;
}

Term::~Term()
{
}

//----------------------- Operators Overloads ---------------------------

Term &Term::operator=(const Term &rhs)
{
	this->coef = rhs.coef;
	this->power = rhs.power;
	return (*this);
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------
