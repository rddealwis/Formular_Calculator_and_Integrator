#ifndef VARIABLEELEMENT_H
#define VARIABLEELEMENT_H

#include "functionelement.h"

class VariableElement : public FormulaElement
{
public:
    VariableElement(std::string variable);
    ~VariableElement();
    std::string GetVariable();
    double GetNumVal();
    void SetNumVal(double numVal);
    std::string toQString();
	void getVariableValues(std::vector<variableValue*> *variableValues);
	bool setVariableValues(std::vector<variableValue*> *variableValues);
	bool isFullyGrounded();
	double evaluate(){ return this->numVal; }
    FormulaElement* simplify() { return new VariableElement(this->variable); }
    FormulaElement* getNewInstance() { return new VariableElement(this->variable); }
private:
    std::string variable;
    double numVal;
	bool grounded = false;
};

#endif // VARIABLEELEMENT_H
