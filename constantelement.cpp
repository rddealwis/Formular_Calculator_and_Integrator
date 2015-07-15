#include "constantelement.h"

ConstantElement::ConstantElement(double constant)
{
    this->constant=constant;
}

ConstantElement::~ConstantElement()
{

}

double ConstantElement::GetConstant()
{
    return this->constant;
}

std::string ConstantElement::toQString()
{
    char* buffer = new char[100];
    std::string returnVal;
    sprintf_s(buffer, 100, "%g", this->GetConstant());
    returnVal = buffer;
    return returnVal;
}
