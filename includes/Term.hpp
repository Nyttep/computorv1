#ifndef TERM_HPP
#define TERM_HPP

class Term
{
private:
	int coef;
	int power;

public:
	Term();
	Term(const Term &src);
	~Term();
	Term &operator=(const Term &rhs);
};

#endif