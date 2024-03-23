#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

class Term;

class Expression
{
private:
	std::vector<Term> terms;

public:
	Expression();
	Expression(const Expression &src);
	~Expression();
	Expression &operator=(const Expression &rhs);
	Expression &operator=(const std::string &rhs);
	std::string tostr();
};

#endif