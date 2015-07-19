#ifndef DIVIDEFUNCTIONELEMENT_H
#define DIVIDEFUNCTIONELEMENT_H

#include "functionelement.h"

class DivideFunctionElement : public FunctionElement
{
public:
    DivideFunctionElement();
    ~DivideFunctionElement();
	double evaluate();
    std::string toQString();
    FormulaElement* simplify();
    FormulaElement* getNewInstance(){ return new DivideFunctionElement(); }
};

#endif // DIVIDEFUNCTIONELEMENT_H
