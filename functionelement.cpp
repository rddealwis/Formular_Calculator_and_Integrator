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
    return getArgOne()->toQString() + getArgTwo()->toQString();
}

bool FunctionElement::isArgOneNull()
{
    NullElement *temp = dynamic_cast<NullElement*>(this->getArgOne());
	return (temp != 0);
	
}

bool FunctionElement::isArgTwoNull()
{
    NullElement *temp = dynamic_cast<NullElement*>(this->getArgTwo());
	return (temp != 0);
	
}

FormulaElement* FunctionElement::getArgOne()
{
    return this->ArgOne;
}

FormulaElement* FunctionElement::getArgTwo()
{
    return this->ArgTwo;
}

void FunctionElement::setArgOne(FormulaElement* e)
{
    this->ArgOne = e;
}

void FunctionElement::setArgTwo(FormulaElement* e)
{
    this->ArgTwo = e;
}
