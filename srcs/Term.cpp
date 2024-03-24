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
	if (rhs.length() > 0)
		this->coef = std::stoi(copy);
	else
		this->coef = 0;
	if (copy.find('^') != copy.npos)
	{
		this->power = std::atoi(&(copy[copy.find('^') + 1]));
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
	if (this->coef != 1 && this->coef != -1)
	{
		ret += std::to_string(std::abs(this->coef));
	}
	if (this->power > 0)
	{
		if (!ret.empty())
			ret += " * ";
		ret += this->var;
		if (this->power == 2)
		{
			ret += "^";
			ret += std::to_string(this->power);
		}
	}
	return (ret);
}