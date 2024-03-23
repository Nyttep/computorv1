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
	this->var = rhs.var;
	return (*this);
}

Term &Term::operator=(const std::string &rhs) // HANDLE IF NO COEFF (x^2)
{
	std::string copy = rhs;
	std::erase(copy, ' ');
	if (rhs.length() > 0)
		this->coef = std::stoi(copy);
	else
		this->coef = 0;
	if (copy.find('^') != copy.npos)
	{
		this->power = std::stoi(&(copy[copy.find('^')]));
		this->var = copy[copy.find('*') + 1];
	}
	else
	{
		this->power = 0;
		this->var = -1;
	}
	return (*this);
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------

std::string Term::tostr()
{
	std::string ret;
	ret = std::to_string(this->coef);
	if (this->var != -1)
		ret += " * " + this->var + '^';
	return (ret);
}