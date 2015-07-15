#include "plusfunctionelement.h"

PlusFunctionElement::PlusFunctionElement()
{

}

PlusFunctionElement::~PlusFunctionElement()
{

}

std::string PlusFunctionElement::toQString()
{
    return GetArgument().at(0)->toQString() + " + " + GetArgument().at(1)->toQString();
}

double PlusFunctionElement::evaluate()
{
    return GetArgument().at(0)->evaluate() + GetArgument().at(1)->evaluate();
}
