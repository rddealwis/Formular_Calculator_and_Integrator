#ifndef PLUSFUNCTIONELEMENT_H
#define PLUSFUNCTIONELEMENT_H

#include "functionelement.h"

class PlusFunctionElement : public FunctionElement
{
public:
    PlusFunctionElement();
    ~PlusFunctionElement();
    std::string toQString();
	double evaluate();
};

#endif // PLUSFUNCTIONELEMENT_H
