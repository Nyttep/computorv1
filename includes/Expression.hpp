#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

class Term;

class Expression
{
private:
public:
	std::vector<Term> terms;
	Expression();
	Expression(const Expression &src);
	~Expression();
	Expression &operator=(const Expression &rhs);
	Expression &operator=(const std::string &rhs);
	std::string tostr();
	bool checkValid();
	void simplify();
	void normalize();
	uint8_t getDegree();
};

#endif