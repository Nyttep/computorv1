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

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------

bool Expression::checkValid()
{
	char var = -1;
	for (size_t i = 0; i < terms.size(); i++)
	{
		if (terms[i].power > 2)
		{
			throw "Invalid power: can only solve equations up to power 2";
			return (0);
		}
		if (terms[i].var != -1)
		{
			if (var == -1)
			{
				var = terms[i].var;
			}
			else if (var != terms[i].var)
			{
				throw "Invalid variable: can only solve equations with one variable";
				return (0);
			}
		}
	}
	return (1);
}

void Expression::simplify()
{
	// add all terms with the same power
	for (size_t i = 0; i < terms.size(); i++)
	{
		for (size_t j = i + 1; j < terms.size(); j++)
		{
			if (terms[i].var == terms[j].var && terms[i].power == terms[j].power)
			{
				terms[i].coef += terms[j].coef;
				terms.erase(terms.begin() + j);
				j--;
			}
		}
	}

	// remove terms with coef 0
	for (size_t i = 0; i < terms.size(); i++)
	{
		if (terms[i].coef == 0)
		{
			terms.erase(terms.begin() + i);
			i--;
		}
	}
}

void Expression::normalize()
{
	std::vector<Term> sortedTerms;

	// sort terms by power
	sortedTerms.resize(this->terms.size());
	for (size_t i = 0; i < this->terms.size(); i++)
	{
		sortedTerms[this->terms[i].power] = this->terms[i];
	}
	this->terms = sortedTerms;
}

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

uint8_t Expression::getDegree()
{
	uint8_t degree = 0;
	for (uint8_t i = 0; i < terms.size(); i++)
	{
		if (terms[i].power > degree)
		{
			degree = terms[i].power;
		}
	}
	return (degree);
}
