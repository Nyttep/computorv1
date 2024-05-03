#ifndef EQUATION_HPP
#define EQUATION_HPP

class Expression;

class Equation
{
private:
public:
	Expression lhs;
	Expression rhs;
	Equation();
	Equation(std::string src);
	Equation(const Equation &src);
	~Equation();
	Equation &operator=(const Equation &rhs);
	Equation &operator=(const std::string &rhs);
	std::string tostr();
	bool checkValid();
	void simplify();
};

#endif