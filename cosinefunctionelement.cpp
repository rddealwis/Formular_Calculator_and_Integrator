#include "cosinefunctionelement.h"
#include <math.h>

CosineFunctionElement::CosineFunctionElement()
{
}

CosineFunctionElement::~CosineFunctionElement()
{

}

std::string CosineFunctionElement::toQString()
{
    return "cos(" + GetArgument().at(0)->toQString() + ")";
}

void CosineFunctionElement::AddArgument(FormulaElement *argument)
{
    int temp=GetArgument().size();

    if(temp==0)
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
    return cos(this->GetArgument().at(0)->evaluate());
}
