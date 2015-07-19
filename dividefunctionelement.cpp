#include "dividefunctionelement.h"
#include "constantelement.h"
#include "variableelement.h"

DivideFunctionElement::DivideFunctionElement()
{

}

DivideFunctionElement::~DivideFunctionElement()
{

}

double DivideFunctionElement::evaluate()
{
    return this->getArgOne()->evaluate() / this->getArgTwo()->evaluate();
}

std::string DivideFunctionElement::toQString()
{
    std::string typeLHS(typeid(*getArgOne()).name());
    std::string typeRHS(typeid(*getArgTwo()).name());

	if ((typeLHS == "class ConstantElement")
		&& (typeRHS == "class ConstantElement")) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
        /*ConstantElement* tempLHS = (ConstantElement*)getArgOne();
        ConstantElement* tempRHS = (ConstantElement*)getArgTwo();
		double result = tempLHS->GetConstant() / tempRHS->GetConstant();

		char* buffer = new char[100];
		std::string returnVal;
		sprintf(buffer, "%g", result);
		returnVal = buffer;
		delete buffer;

        return returnVal;*/
	}

	if ((typeLHS == "class ConstantElement")
		&& (typeRHS == "class VariableElement")) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}

	if ((typeLHS == "class VariableElement")
		&& (typeRHS == "class ConstantElement")) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}

	if (("class VariableElement" == typeLHS)
		&& ("class VariableElement" == typeRHS)) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}

	if (("class DivideFunctionElement" == typeLHS)
		&& ("class VariableElement" == typeRHS)) {
        return "(" + getArgOne()->toQString() + ")/" + getArgTwo()->toQString();
	}

	if (("class VariableElement" == typeLHS)
		&& ("class DivideFunctionElement" == typeRHS)) {
        return getArgOne()->toQString() + "/(" + getArgTwo()->toQString() + ")";
	}

	if (("class ConstantElement" == typeLHS)
		&& ("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}

	if (("class ConstantElement" == typeRHS)
		&& ("class CosineFunctionElement" == typeLHS || "class SineFunctionElement" == typeLHS)) {
        return getArgTwo()->toQString() + "/" + getArgOne()->toQString();
	}

	if (("class VariableElement" == typeLHS || "class ConstantElement" == typeLHS)
		|| ("class VariableElement" == typeRHS || "class ConstantElement" == typeRHS)) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}

	if (("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)
		|| ("class CosineFunctionElement" == typeLHS || "class SineFunctionElement" == typeLHS)) {
        return getArgOne()->toQString() + "/" + getArgTwo()->toQString();
	}
   return "(" + getArgOne()->toQString() + ") / (" + getArgTwo()->toQString() + ")";
}

FormulaElement* DivideFunctionElement::simplify()
{
    std::string typeLHS(typeid(*(getArgOne()->simplify())).name());
    std::string typeRHS(typeid(*(getArgTwo()->simplify())).name());

    if (("class ConstantElement" == typeLHS)
        && ("class ConstantElement" == typeRHS)) {
        return new ConstantElement(evaluate());
    }
    else
    {
        DivideFunctionElement* temp = new DivideFunctionElement();
        temp->setArgOne(getArgOne()->simplify());
        temp->setArgTwo(getArgTwo()->simplify());
        return temp;
    }
}
