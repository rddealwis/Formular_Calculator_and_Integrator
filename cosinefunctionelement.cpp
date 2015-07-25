#include "cosinefunctionelement.h"
#include "constantelement.h"

CosineFunctionElement::CosineFunctionElement()
{
}

CosineFunctionElement::~CosineFunctionElement()
{

}

std::string CosineFunctionElement::toQString()
{
    return "cos(" + getArgTwo()->toQString() + ")";
}

void CosineFunctionElement::AddArgument(FormulaElement *argument)
{
    if(GetArgument().size() == 0)
    {
        FunctionElement::AddArgument(argument);
    }
    else
    {
        printf("Can't insert another argument for Cosine. Previously entered argument is added.\n\n");
    }
}

bool CosineFunctionElement::isNull()
{
    return false;
}

double CosineFunctionElement::evaluate()
{
    return cos(this->getArgTwo()->evaluate() * (pi /180));
}

FormulaElement* CosineFunctionElement::simplify()
{
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (typeRHS.compare("class ConstantElement") == 0)
    {
        return new ConstantElement(this->evaluate());
    }
    else
    {
        FormulaElement* temp = this->getArgTwo()->simplify();
        CosineFunctionElement* simplifyResult = new CosineFunctionElement();
        simplifyResult->setArgTwo(temp);

        return simplifyResult;
    }
}
