#include "sinefunctionelement.h"
#include "constantelement.h"


SineFunctionElement::SineFunctionElement()
{
}

SineFunctionElement::~SineFunctionElement()
{

}

std::string SineFunctionElement::toQString()
{
    return "sin(" + getArgTwo()->toQString() + ")";
}

void SineFunctionElement::AddArgument(FormulaElement *argument)
{
    if(GetArgument().size() == 0)
    {
        FunctionElement::AddArgument(argument);
    }
    else
    {
        printf("Can't insert another argument for Sine. Previously entered argument is added.\n\n");
    }
}

bool SineFunctionElement::isNull()
{
    return false;
}

double SineFunctionElement::evaluate()
{
    return sin(getArgTwo()->evaluate()* (pi /180));
}

FormulaElement* SineFunctionElement::simplify()
{
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (typeRHS.compare("class ConstantElement") == 0)
    {
        return new ConstantElement(evaluate());
    }
    else
    {
        FormulaElement* temp = this->getArgTwo()->simplify();
        SineFunctionElement* simplifyResult = new SineFunctionElement();
        simplifyResult->setArgTwo(temp);

        return simplifyResult;
    }
}
