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

#endif // SINEFUNCTIONELEMENT_H
