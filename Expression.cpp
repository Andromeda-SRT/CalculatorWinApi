#include "Expression.h"

Expression::Expression(double lvalue, double rvalue, operation act)
{
	larg = new Argument(lvalue);
	rarg = new Argument(rvalue);
	op = act;
}

Expression::~Expression()
{
	delete larg; delete rarg;
}

Argument Expression::Calculate() const 
{
	if (op == plus) return *larg + *rarg;
	if (op == minus) return *larg - *rarg;
	if (op == mult) return (*larg) * (*rarg);
	if (op == dev) return *larg / *rarg;
};
