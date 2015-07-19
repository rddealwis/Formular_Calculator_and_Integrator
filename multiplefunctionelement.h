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
    FormulaElement* simplify();
    FormulaElement* getNewInstance(){ return new MultipleFunctionElement(); }
};

#endif // MULTIPLEFUNCTIONELEMENT_H
