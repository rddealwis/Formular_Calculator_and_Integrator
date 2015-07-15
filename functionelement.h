#ifndef FUNCTIONELEMENT_H
#define FUNCTIONELEMENT_H

#include "formulaelement.h"

class FunctionElement : public FormulaElement
{
public:
    FunctionElement();
    ~FunctionElement();
    void AddArgument(FormulaElement *argument);
    std::vector<FormulaElement*> GetArgument();
    std::string toQString();
    bool isArgOneNull();
    bool isArgTwoNull();
	void getVariableValues(std::vector<variableValue*> *variableValues)
	{
		GetArgument().at(0)->getVariableValues(variableValues);
		GetArgument().at(1)->getVariableValues(variableValues);
	}

	bool setVariableValues(std::vector<variableValue*> *variableValues)
	{
		return (GetArgument().at(0)->setVariableValues(variableValues) && GetArgument().at(1)->setVariableValues(variableValues));
	}

	bool isFullyGrounded()
	{
		return(GetArgument().at(0)->isFullyGrounded() && GetArgument().at(1)->isFullyGrounded());
	}
private:
	std::vector<FormulaElement*> arguments;
	//FormulaElement* LHS = new NullElement();
    //FormulaElement* RHS = new NullElement();
};

#endif // FUNCTIONELEMENT_H

