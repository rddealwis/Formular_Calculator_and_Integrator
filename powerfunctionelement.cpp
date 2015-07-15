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
	std::string typeLHS(typeid(*GetArgument().at(0)).name());
	std::string typeRHS(typeid(*GetArgument().at(1)).name());

	if ((typeLHS == "class ConstantElement")
		&& (typeRHS == "class ConstantElement")) {
		ConstantElement* tempLHS = (ConstantElement*)GetArgument().at(0);
		ConstantElement* tempRHS = (ConstantElement*)GetArgument().at(1);
		double result = pow(tempLHS->GetConstant(), tempRHS->GetConstant());

		char* buffer = new char[100];
		std::string returnVal;
		sprintf(buffer, "%g", result);
		returnVal = buffer;
		delete buffer;

		return returnVal;
	}

	if ((typeRHS == "class ConstantElement" || typeRHS == "class VariableElement")
		&& (typeLHS == "class CosineFunctionElement" || typeLHS == "class SineFunctionElement")) {
		return GetArgument().at(0)->toQString() + "^" + GetArgument().at(1)->toQString();
	}

	if ((typeLHS == "class ConstantElement" || typeLHS == "class VariableElement")
		&& (typeRHS == "class VariableElement" || typeRHS == "class ConstantElement")) {
		return GetArgument().at(0)->toQString() + "^" + GetArgument().at(1)->toQString();
	}

	if (typeLHS == "class ConstantElement" || typeLHS == "class VariableElement"){
		return GetArgument().at(0)->toQString() + "^(" + GetArgument().at(1)->toQString() + ")";
	}

	if (typeRHS == "class ConstantElement" || typeRHS == "class VariableElement"){
		return "(" + GetArgument().at(0)->toQString() + ")^" + GetArgument().at(1)->toQString();
	}

	return GetArgument().at(0)->toQString() + "^(" + GetArgument().at(1)->toQString() + ")";
}

double PowerFunctionElement::evaluate()
{
	return pow(GetArgument().at(0)->evaluate(), GetArgument().at(1)->evaluate());
}