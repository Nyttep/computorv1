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
	Equation &operator=(const std::string &rhs);
	std::string tostr();
	bool checkValid();
	void simplify();
	uint8_t getDegree();
	void solve();
	double solveDegree1();
};

#endif