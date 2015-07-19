#ifndef SINEFUNCTIONELEMENT_H
#define SINEFUNCTIONELEMENT_H

#include "functionelement.h"

class SineFunctionElement : public FunctionElement
{
public:
    SineFunctionElement();
    ~SineFunctionElement();
    std::string toQString();
    void AddArgument(FormulaElement *argument);
	bool isNull(); 
	double evaluate();

	void getVariableValues(std::vector<variableValue*> *variableValues)
	{
        getArgTwo()->getVariableValues(variableValues);
	}

	bool setVariableValues(std::vector<variableValue*> *variableValues)
	{
        return getArgTwo()->setVariableValues(variableValues);
	}

	bool isFullyGrounded()
	{
        return getArgTwo()->isFullyGrounded();
	}
    FormulaElement* simplify();
    FormulaElement* getNewInstance() { return new SineFunctionElement(); }
private:
    FunctionElement* argument;
};

#endif // SINEFUNCTIONELEMENT_H
