#ifndef TERM_HPP
#define TERM_HPP

class Term
{
private:
	int coef;
	int power;
	char var;

public:
	Term();
	Term(const Term &src);
	~Term();
	Term &operator=(const Term &rhs);
	Term &operator=(const std::string &rhs);
	std::string tostr();
};

#endif