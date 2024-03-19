#ifndef EQUATION_HPP
#define EQUATION_HPP

class Expression;

class Equation
{
private:
	Expression lhs;
	Expression rhs;

public:
	Equation();
	Equation(std::string src);
	Equation(const Equation &src);
	~Equation();
	Equation &operator=(const Equation &rhs);
};

#endif