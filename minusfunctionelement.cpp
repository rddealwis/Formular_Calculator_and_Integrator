#include "minusfunctionelement.h"
#include "constantelement.h"

MinusFunctionElement::MinusFunctionElement()
{

}

MinusFunctionElement::~MinusFunctionElement()
{

}

std::string MinusFunctionElement::toQString()
{
   return getArgOne()->toQString() + " - " + getArgTwo()->toQString();
}

double MinusFunctionElement::evaluate()
{
    return getArgOne()->evaluate() - getArgTwo()->evaluate();
}

FormulaElement* MinusFunctionElement::simplify()
{
    std::string typeLHS(typeid(*(getArgOne()->simplify())).name());
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (("class ConstantElement" == typeLHS)
        && ("class ConstantElement" == typeRHS)) {
        return new ConstantElement(evaluate());
    }
    else
    {
        MinusFunctionElement* temp = new MinusFunctionElement();
        temp->setArgOne(getArgOne()->simplify());
        temp->setArgTwo(getArgTwo()->simplify());
        return temp;
    }
}
