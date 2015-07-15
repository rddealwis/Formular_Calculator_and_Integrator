#ifndef VARIABLEELEMENT_H
#define VARIABLEELEMENT_H

#include "functionelement.h"

class VariableElement : public FormulaElement
{
public:
    VariableElement(std::string variable);
    ~VariableElement();
    std::string GetVariable();
    int GetNumVal();
    void SetNumVal(int numVal);
    std::string toQString();
	void getVariableValues(std::vector<variableValue*> *variableValues);
	bool setVariableValues(std::vector<variableValue*> *variableValues);
	bool isFullyGrounded();
	double evaluate(){ return this->numVal; }
private:
    std::string variable;
    int numVal;
	bool grounded = false;
};

#endif // VARIABLEELEMENT_H
