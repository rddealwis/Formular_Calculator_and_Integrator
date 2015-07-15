#include "sinefunctionelement.h"

SineFunctionElement::SineFunctionElement()
{
}

SineFunctionElement::~SineFunctionElement()
{

}

std::string SineFunctionElement::toQString()
{
    return "sin(" + GetArgument().at(0)->toQString() + ")";
}

void SineFunctionElement::AddArgument(FormulaElement *argument)
{
    int temp=GetArgument().size();

    if(temp==0)
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
	return sin(GetArgument().at(0)->evaluate());
}
