#include "minusfunctionelement.h"

MinusFunctionElement::MinusFunctionElement()
{

}

MinusFunctionElement::~MinusFunctionElement()
{

}

std::string MinusFunctionElement::toQString()
{
   return GetArgument().at(0)->toQString() + " - " + GetArgument().at(1)->toQString();
}

double MinusFunctionElement::evaluate()
{
	return GetArgument().at(0)->evaluate() - GetArgument().at(1)->evaluate();
}