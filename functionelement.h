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
    FormulaElement* getArgOne();
    FormulaElement* getArgTwo();
    void setArgOne(FormulaElement* e);
    void setArgTwo(FormulaElement* e);
    bool isArgOneNull();
    bool isArgTwoNull();
	void getVariableValues(std::vector<variableValue*> *variableValues)
    {
        getArgOne()->getVariableValues(variableValues);
        getArgTwo()->getVariableValues(variableValues);
	}

	bool setVariableValues(std::vector<variableValue*> *variableValues)
	{
        return (getArgOne()->setVariableValues(variableValues) && getArgTwo()->setVariableValues(variableValues));
	}

	bool isFullyGrounded()
	{
        return(getArgOne()->isFullyGrounded() && getArgTwo()->isFullyGrounded());
	}
private:
	std::vector<FormulaElement*> arguments;
    FormulaElement* ArgOne = new NullElement();
    FormulaElement* ArgTwo = new NullElement();
};

#endif // FUNCTIONELEMENT_H

