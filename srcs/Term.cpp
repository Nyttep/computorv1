#include "computorv1.hpp"

//---------------------- Constructors & Destructors ----------------------

Term::Term() : coef(0), power(0), var(-1)
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
	{
		if ((std::isdigit(rhs[0]) || std::isdigit(rhs[1])))
		{
			if (strToDoubleOverflow(copy))
				throw "Error: Overflow on coefficient";
			try
			{
				this->coef = std::stod(copy);
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error: the coefficient of the term \"" << rhs << "\" is too precise" << '\n';
				exit(1);
			}
		}
		else if (rhs[0] == '-')
			this->coef = -1;
		else
			this->coef = 1;
	}
	else
		this->coef = 0;

	// find var and power, var can be any letter, power is always an int, if no power, power = 1, if no var, var = -1 and power = 0
	if (copy.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != copy.npos)
	{
		this->var = toupper(copy[copy.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")]);
		if (copy.find('^') != copy.npos)
		{
			if (strToIntOverflow(&(copy[copy.find('^') + 1])))
				throw "Error: Overflow on power";
			this->power = std::atoi(&(copy[copy.find('^') + 1]));
		}
		else
		{
			this->power = 1;
		}
	}
	else
	{
		this->var = -1;
		this->power = 0;
	}
	return (*this);
}

// ------------- Setters & Getters ---------------------

//------------------------- Other Functions -----------------------------

std::string Term::tostr()
{
	std::string ret;
	std::ostringstream ss;

	if (this->coef == 0)
		return ("");

	if ((this->coef != 1 && this->coef != -1) || this->power == 0)
	{
		ss << std::abs(this->coef);
		ret += ss.str();
	}

	if (this->power > 0 && this->coef != 0)
	{
		if (!ret.empty())
			ret += " * ";
		ret += this->var;
		if (this->power >= 2)
		{
			ret += "^";
			ret += std::to_string(this->power);
		}
	}
	return (ret);
}