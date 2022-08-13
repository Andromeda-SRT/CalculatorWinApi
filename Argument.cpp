#include "Argument.h"

Argument::~Argument()
{
}

Argument Argument::operator+(Argument op2){
	Argument res(value+op2.value); 
	return res;  
};

Argument Argument::operator-(Argument op2){
	Argument res(value-op2.value); 
	return res;  
};

Argument Argument::operator*(Argument op2){
	Argument res(value*op2.value); 
	return res;  
};

Argument Argument::operator/(Argument op2){
	Argument res(value/op2.value); 
	return res;  
};
