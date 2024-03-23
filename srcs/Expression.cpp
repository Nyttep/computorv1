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
	while (true)
	{
		if (copy.find('+') != copy.npos)
		{
			tmp = copy.substr(0, copy.length() - copy.find('+') - 1);
			copy.erase(0, copy.length() - copy.find('+') - 1);
		}
		else if (copy.find('-') != copy.npos)
		{
			tmp = copy.substr(0, copy.length() - copy.find('-') - 1);
			copy.erase(0, copy.length() - copy.find('-') - 1);
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
	for (size_t i = 0; i < terms.size(); i++)
	{
		ret += terms[i].tostr();
	}
	return (ret);
}