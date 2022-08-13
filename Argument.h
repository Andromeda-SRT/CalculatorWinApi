#ifndef ARGUMENT_H
#define ARGUMENT_H

class Argument
{
	double value;
	
	public:
		Argument(double val) : value(val) {};
		~Argument();
		Argument operator+(Argument op2);
		Argument operator-(Argument op2);
		Argument operator*(Argument op2);
		Argument operator/(Argument op2);
};

#endif
