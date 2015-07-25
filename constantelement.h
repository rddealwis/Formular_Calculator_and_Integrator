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
    void getVariableValues(std::vector<variableValue*>*){ return; }
    bool setVariableValues(std::vector<variableValue*>*) { return true; }
	bool isFullyGrounded() { return true; }
    double evaluate(){ return this->constant; }
    FormulaElement* simplify() { return this; }
    FormulaElement* getNewInstance() { return new ConstantElement(this->constant); }
private:
    double constant;
};

#endif // CONSTANTELEMENT_H
