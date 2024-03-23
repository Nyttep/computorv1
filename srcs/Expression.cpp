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
	while (true)
	{
		if (copy.find('+', 1) != copy.npos)
		{
			tmp = copy.substr(0, copy.find('+', 1));
			copy.erase(0, copy.find('+', 1));
		}
		else if (copy.find('-', 1) != copy.npos)
		{
			tmp = copy.substr(0, copy.find('-', 1));
			copy.erase(0, copy.find('-', 1));
		}
		else
			break;
		ins = tmp;
		this->terms.push_back(ins);
		tmp.clear();
	}
	ins = copy;
	this->terms.push_back(ins);
	return (*this);
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