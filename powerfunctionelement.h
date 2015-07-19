#ifndef POWERFUNCTIONELEMENT_H
#define POWERFUNCTIONELEMENT_H

#include "functionelement.h"
class PowerFunctionElement : public FunctionElement
{
public:
    PowerFunctionElement();
    ~PowerFunctionElement();
    std::string toQString();
	double evaluate();
    FormulaElement* simplify();
    FormulaElement* getNewInstance() { return new PowerFunctionElement(); }
};



#endif // POWERFUNCTIONELEMENT_H
