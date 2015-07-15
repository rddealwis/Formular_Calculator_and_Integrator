#ifndef MULTIPLEFUNCTIONELEMENT_H
#define MULTIPLEFUNCTIONELEMENT_H

#include "functionelement.h"

class MultipleFunctionElement : public FunctionElement
{
public:
    MultipleFunctionElement();
    ~MultipleFunctionElement();
    std::string toQString();
	double evaluate();
};

#endif // MULTIPLEFUNCTIONELEMENT_H
