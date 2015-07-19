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
    FormulaElement* getNewInstance() { return new CosineFunctionElement(); }
private:
    FunctionElement* argument;
};

#endif // COSINEFUNCTIONELEMENT_H
