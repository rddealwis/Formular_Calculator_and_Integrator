#include "functionelement.h"

FunctionElement::FunctionElement()
{

}

FunctionElement::~FunctionElement()
{

}

void FunctionElement::AddArgument(FormulaElement *argument)
{
    this->arguments.push_back(argument);
}

std::vector<FormulaElement *> FunctionElement::GetArgument()
{
    return this->arguments;
}

std::string FunctionElement::toQString()
{
    return GetArgument().at(0)->toQString() + GetArgument().at(1)->toQString();
}

bool FunctionElement::isArgOneNull()
{
	NullElement *temp = dynamic_cast<NullElement*>(this->GetArgument().at(0));
	return (temp != 0);
	
}

bool FunctionElement::isArgTwoNull()
{
	NullElement *temp = dynamic_cast<NullElement*>(this->GetArgument().at(1));
	return (temp != 0);
	
}
