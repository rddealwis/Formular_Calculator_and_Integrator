#ifndef CONSTANTELEMENT_H
#define CONSTANTELEMENT_H

#include "formulaelement.h"

class ConstantElement : public FormulaElement
{
public:
    ConstantElement(double constant);
    ~ConstantElement();
    double GetConstant();
    std::string toQString();
	void getVariableValues(std::vector<variableValue*> *variableValues){ return; }
	bool setVariableValues(std::vector<variableValue*> *variableValues) { return true; }
	bool isFullyGrounded() { return true; }
	double evaluate(){ return this->constant; }
private:
    double constant;
};

#endif // CONSTANTELEMENT_H
