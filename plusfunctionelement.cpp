#include "plusfunctionelement.h"
#include "constantelement.h"

PlusFunctionElement::PlusFunctionElement()
{

}

PlusFunctionElement::~PlusFunctionElement()
{

}

std::string PlusFunctionElement::toQString()
{
    return getArgOne()->toQString() + " + " + getArgTwo()->toQString();
}

double PlusFunctionElement::evaluate()
{
    return getArgOne()->evaluate() + getArgTwo()->evaluate();
}

FormulaElement* PlusFunctionElement::simplify()
{
    std::string typeLHS(typeid(*(getArgOne()->simplify())).name());
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (("class ConstantElement" == typeLHS) && ("class ConstantElement" == typeRHS)) {

        return new ConstantElement(evaluate());
    }
    else
    {
        PlusFunctionElement* temp = new PlusFunctionElement();
        temp->setArgOne(getArgOne()->simplify());
        temp->setArgTwo(getArgTwo()->simplify());

        return temp;
    }
}
