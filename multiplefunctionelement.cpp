#include "multiplefunctionelement.h"

#include "multiplefunctionelement.h"
#include "constantelement.h"
#include "variableelement.h"

MultipleFunctionElement::MultipleFunctionElement()
{

}

MultipleFunctionElement::~MultipleFunctionElement()
{

}

std::string MultipleFunctionElement::toQString()
{
    std::string typeLHS(typeid(*GetArgument().at(0)).name());
    std::string typeRHS(typeid(*GetArgument().at(1)).name());

    if ((typeLHS == "class ConstantElement")
            && (typeRHS == "class ConstantElement")) {
        ConstantElement* tempLHS = (ConstantElement*)GetArgument().at(0);
        ConstantElement* tempRHS = (ConstantElement*)GetArgument().at(1);
        double result = tempLHS->GetConstant() * tempRHS->GetConstant();
        char* buffer = new char[100];
        std::string returnVal;
        sprintf(buffer, "%g", result);
        returnVal = buffer;
        delete buffer;
        return returnVal;
    }

    if ((typeLHS == "class ConstantElement")
            && (typeRHS == "class VariableElement")) {
        return GetArgument().at(0)->toQString() + GetArgument().at(1)->toQString();
    }

    if ((typeLHS == "class VariableElement")
            && (typeRHS == "class ConstantElement")) {
        return GetArgument().at(1)->toQString() + GetArgument().at(0)->toQString();
    }

    if (("class VariableElement" == typeLHS)
            && ("class VariableElement" == typeRHS)) {
        return GetArgument().at(0)->toQString() + GetArgument().at(1)->toQString();
    }

    if (("class MultipleFunctionElement" == typeLHS)
            && ("class VariableElement" == typeRHS)) {
        return GetArgument().at(1)->toQString() + "(" + GetArgument().at(0)->toQString() + ")";
    }

    if (("class VariableElement" == typeLHS)
            && ("class MultipleFunctionElement" == typeRHS)) {
        return GetArgument().at(0)->toQString() + "(" + GetArgument().at(1)->toQString() + ")";
    }

    if (("class ConstantElement" == typeLHS)
        && ("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)) {
        return GetArgument().at(0)->toQString() + GetArgument().at(1)->toQString();
    }

    if (("class MultipleFunctionElement" == typeLHS) || ("class DivideFunctionElement" == typeLHS))
        return GetArgument().at(0)->toQString() + "(" + GetArgument().at(1)->toQString() + ")";

    if (("class MultipleFunctionElement" == typeRHS) || ("class DivideFunctionElement" == typeRHS))
        return "(" + GetArgument().at(0)->toQString() + ")" + GetArgument().at(1)->toQString();

    if ((("class MultipleFunctionElement" == typeRHS) || ("class DivideFunctionElement" == typeRHS))
        && (("class MultipleFunctionElement" == typeLHS) || ("class DivideFunctionElement" == typeLHS)))
        return "(" + GetArgument().at(0)->toQString() + ")" + GetArgument().at(1)->toQString();

    return "(" + GetArgument().at(0)->toQString() + ")(" + GetArgument().at(1)->toQString() + ")";
}

double MultipleFunctionElement::evaluate()
{
	return GetArgument().at(0)->evaluate()*GetArgument().at(1)->evaluate();
}