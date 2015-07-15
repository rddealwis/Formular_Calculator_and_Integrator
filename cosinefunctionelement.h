#ifndef COSINEFUNCTIONELEMENT_H
#define COSINEFUNCTIONELEMENT_H

#include "functionelement.h"
class CosineFunctionElement : public FunctionElement
{
public:
    CosineFunctionElement();
    ~CosineFunctionElement();
    std::string toQString();
    bool isNull();
    void AddArgument(FormulaElement *argument);
	double evaluate();
	void getVariableValues(std::vector<variableValue*> *variableValues)
	{
        GetArgument().at(0)->getVariableValues(variableValues);
	}

	bool setVariableValues(std::vector<variableValue*> *variableValues)
	{
        return GetArgument().at(0)->setVariableValues(variableValues);
	}

	bool isFullyGrounded()
	{
        return GetArgument().at(0)->isFullyGrounded();
	}
private:
    FunctionElement* argument;
};

#endif // COSINEFUNCTIONELEMENT_H
