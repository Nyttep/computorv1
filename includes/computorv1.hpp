#ifndef COMPUTORV1_HPP
#define COMPUTORV1_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <utility>
#include <cmath>
#include "Term.hpp"
#include "Expression.hpp"
#include "Equation.hpp"

int check_args(int ac);

bool strToDoubleOverflow(std::string str);
bool strToIntOverflow(std::string str);

bool doubleOperationOverflow(double lhs, double rhs, char op);

#endif