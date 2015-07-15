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
	return this->GetArgument().at(0)->evaluate() / this->GetArgument().at(1)->evaluate();
}

std::string DivideFunctionElement::toQString()
{
	std::string typeLHS(typeid(*GetArgument().at(0)).name());
	std::string typeRHS(typeid(*GetArgument().at(1)).name());

	if ((typeLHS == "class ConstantElement")
		&& (typeRHS == "class ConstantElement")) {
		ConstantElement* tempLHS = (ConstantElement*)GetArgument().at(0);
		ConstantElement* tempRHS = (ConstantElement*)GetArgument().at(1);
		double result = tempLHS->GetConstant() / tempRHS->GetConstant();

		char* buffer = new char[100];
		std::string returnVal;
		sprintf(buffer, "%g", result);
		returnVal = buffer;
		delete buffer;

		return returnVal;
	}

	if ((typeLHS == "class ConstantElement")
		&& (typeRHS == "class VariableElement")) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}

	if ((typeLHS == "class VariableElement")
		&& (typeRHS == "class ConstantElement")) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}

	if (("class VariableElement" == typeLHS)
		&& ("class VariableElement" == typeRHS)) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}

	if (("class DivideFunctionElement" == typeLHS)
		&& ("class VariableElement" == typeRHS)) {
		return "(" + GetArgument().at(0)->toQString() + ")/" + GetArgument().at(1)->toQString();
	}

	if (("class VariableElement" == typeLHS)
		&& ("class DivideFunctionElement" == typeRHS)) {
		return GetArgument().at(0)->toQString() + "/(" + GetArgument().at(1)->toQString() + ")";
	}

	if (("class ConstantElement" == typeLHS)
		&& ("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}

	if (("class ConstantElement" == typeRHS)
		&& ("class CosineFunctionElement" == typeLHS || "class SineFunctionElement" == typeLHS)) {
		return GetArgument().at(1)->toQString() + "/" + GetArgument().at(0)->toQString();
	}

	if (("class VariableElement" == typeLHS || "class ConstantElement" == typeLHS)
		|| ("class VariableElement" == typeRHS || "class ConstantElement" == typeRHS)) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}

	if (("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)
		|| ("class CosineFunctionElement" == typeLHS || "class SineFunctionElement" == typeLHS)) {
		return GetArgument().at(0)->toQString() + "/" + GetArgument().at(1)->toQString();
	}
   return "(" + GetArgument().at(0)->toQString() + ") / (" + GetArgument().at(1)->toQString() + ")";
}
