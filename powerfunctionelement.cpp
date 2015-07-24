#include "powerfunctionelement.h"
#include <math.h>
#include "constantelement.h"
#include "variableelement.h"

PowerFunctionElement::PowerFunctionElement()
{

}

PowerFunctionElement::~PowerFunctionElement()
{

}


std::string PowerFunctionElement::toQString()
{
    std::string typeLHS(typeid(*getArgOne()).name());
    std::string typeRHS(typeid(*getArgTwo()).name());

    if ((typeLHS == "class ConstantElement") && (typeRHS == "class ConstantElement")) {

        ConstantElement* tempLHS = (ConstantElement*)getArgOne();
        ConstantElement* tempRHS = (ConstantElement*)getArgTwo();
		double result = pow(tempLHS->GetConstant(), tempRHS->GetConstant());

		char* buffer = new char[100];
		std::string returnVal;
        printf(buffer, "%g", result);
		returnVal = buffer;
		delete buffer;

		return returnVal;
	}

	if ((typeRHS == "class ConstantElement" || typeRHS == "class VariableElement")
		&& (typeLHS == "class CosineFunctionElement" || typeLHS == "class SineFunctionElement")) {
        return getArgOne()->toQString() + "^" + getArgTwo()->toQString();
	}

	if ((typeLHS == "class ConstantElement" || typeLHS == "class VariableElement")
		&& (typeRHS == "class VariableElement" || typeRHS == "class ConstantElement")) {
        return getArgOne()->toQString() + "^" + getArgTwo()->toQString();
	}

	if (typeLHS == "class ConstantElement" || typeLHS == "class VariableElement"){
        return getArgOne()->toQString() + "^(" + getArgTwo()->toQString() + ")";
	}

	if (typeRHS == "class ConstantElement" || typeRHS == "class VariableElement"){
        return "(" + getArgOne()->toQString() + ")^" + getArgTwo()->toQString();
	}

    return getArgOne()->toQString() + "^(" + getArgTwo()->toQString() + ")";
}

double PowerFunctionElement::evaluate()
{
    return pow(getArgOne()->evaluate(), getArgTwo()->evaluate());
}

FormulaElement* PowerFunctionElement::simplify()
{
    std::string typeLHS(typeid(*(getArgOne()->simplify())).name());
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (("class ConstantElement" == typeLHS) && ("class ConstantElement" == typeRHS)) {

        return new ConstantElement(evaluate());
    }
    else
    {
        PowerFunctionElement* temp = new PowerFunctionElement();
        temp->setArgOne(getArgOne()->simplify());
        temp->setArgTwo(getArgTwo()->simplify());

        return temp;
    }
}
