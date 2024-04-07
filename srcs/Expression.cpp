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
	std::string copy = rhs;
	std::string tmp;
	Term ins;
	std::erase(copy, ' ');
	std::size_t posPlus = copy.find('+', 1);
	std::size_t posMinus = copy.find('-', 1);
	while (posPlus != copy.npos || posMinus != copy.npos)
	{
		if (posPlus != copy.npos)
		{
			if (posMinus != copy.npos)
			{
				if (posMinus < posPlus)
				{
					tmp = copy.substr(0, posMinus);
					copy.erase(0, posMinus);
				}
				else
				{
					tmp = copy.substr(0, posPlus);
					copy.erase(0, posPlus);
				}
			}
			else
			{
				tmp = copy.substr(0, posPlus);
				copy.erase(0, posPlus);
			}
		}
		else
		{
			tmp = copy.substr(0, posMinus);
			copy.erase(0, posMinus);
		}
		ins = tmp;
		this->terms.push_back(ins);
		tmp.clear();
		posPlus = copy.find('+', 1);
		posMinus = copy.find('-', 1);
	}
	ins = copy;
	this->terms.push_back(ins);
	return (*this);
}

Expression &Expression::operator-(const Term &rhs)
{
	for (size_t i = 0; i < terms.size() ; i++)
	{
		if (rhs.power == terms[i].power)
		{
			terms[i].coef -= rhs.coef;
		}
	}
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------

std::string Expression::tostr()
{
	std::string ret;
	ret += terms[0].tostr();
	for (size_t i = 1; i < terms.size(); i++)
	{
		if (terms[i].coef >= 0)
		{
			ret += " + ";
		}
		else
		{
			ret += " - ";
		}
		ret += terms[i].tostr();
	}
	return (ret);
}
 
void	Expression::reduce()
{
}
