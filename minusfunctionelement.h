#ifndef MINUSFUNCTIONELEMENT_H
#define MINUSFUNCTIONELEMENT_H

#include "functionelement.h"

class MinusFunctionElement : public FunctionElement
{
public:
    MinusFunctionElement();
    ~MinusFunctionElement();
    std::string toQString();
	double evaluate();
};

#endif // MINUSFUNCTIONELEMENT_H
