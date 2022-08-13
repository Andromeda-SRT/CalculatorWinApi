#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Expression.h"

class Calculator
{
	double res;
	double prev_res;
	int exp_len;
	struct exp_stack_item {
		Expression *exp;
		exp_stack_item *next;
	};
	exp_stack_item *first;
	//static Calculator *inst = 0;
	
	public:
		Calculator(); 
		~Calculator();
		void addExpression(Expression* exp, double lvalue, operation op, double rvalue = 0.0); //add to the begining
		void deleteExpression(Expression* exp);
		void ComputingAllExp(Expression *first);
		void DisplayResult();
		double GetPrevVelue() {return prev_res;}
	protected:
};

#endif
