#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Argument.h"
#include "operations.cpp"

class Expression
{
	Argument* larg;
	Argument* rarg;
	operation op;
	
	public:
		Expression(double lvalue, double rvalue, operation act);
		~Expression();
		Argument Calculate() const;
};

#endif
