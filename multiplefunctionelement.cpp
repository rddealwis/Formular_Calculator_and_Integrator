#include "multiplefunctionelement.h"

#include "multiplefunctionelement.h"
#include "constantelement.h"
#include "variableelement.h"
#include "powerfunctionelement.h"

MultipleFunctionElement::MultipleFunctionElement()
{

}

MultipleFunctionElement::~MultipleFunctionElement()
{

}

std::string MultipleFunctionElement::toQString()
{
    std::string typeLHS(typeid(*getArgOne()).name());
    std::string typeRHS(typeid(*getArgTwo()).name());

    if ((typeLHS == "class ConstantElement") && (typeRHS == "class ConstantElement")) {

        ConstantElement* tempLHS = (ConstantElement*)getArgOne();
        ConstantElement* tempRHS = (ConstantElement*)getArgTwo();
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
        return getArgOne()->toQString() + getArgTwo()->toQString();
    }

    if ((typeLHS == "class VariableElement")
            && (typeRHS == "class ConstantElement")) {
        return getArgTwo()->toQString() + getArgOne()->toQString();
    }

    if (("class VariableElement" == typeLHS)
            && ("class VariableElement" == typeRHS)) {
        return getArgOne()->toQString() + getArgTwo()->toQString();
    }

    if (("class MultipleFunctionElement" == typeLHS)
            && ("class VariableElement" == typeRHS)) {
        return getArgTwo()->toQString() + "(" + getArgOne()->toQString() + ")";
    }

    if (("class VariableElement" == typeLHS)
            && ("class MultipleFunctionElement" == typeRHS)) {
        return getArgOne()->toQString() + "(" + getArgTwo()->toQString() + ")";
    }

    if (("class ConstantElement" == typeLHS)
        && ("class CosineFunctionElement" == typeRHS || "class SineFunctionElement" == typeRHS)) {
        return getArgOne()->toQString() + getArgTwo()->toQString();
    }

    if (("class MultipleFunctionElement" == typeLHS) || ("class DivideFunctionElement" == typeLHS))
        return getArgOne()->toQString() + "(" + getArgTwo()->toQString() + ")";

    if (("class MultipleFunctionElement" == typeRHS) || ("class DivideFunctionElement" == typeRHS))
        return "(" + getArgOne()->toQString() + ")" + getArgTwo()->toQString();

    if ((("class MultipleFunctionElement" == typeRHS) || ("class DivideFunctionElement" == typeRHS))
        && (("class MultipleFunctionElement" == typeLHS) || ("class DivideFunctionElement" == typeLHS)))
        return "(" + getArgOne()->toQString() + ")" + getArgTwo()->toQString();

    return "(" + getArgOne()->toQString() + ")(" + getArgTwo()->toQString() + ")";
}

double MultipleFunctionElement::evaluate()
{
    return getArgOne()->evaluate()*getArgTwo()->evaluate();
}

FormulaElement* combineElements(MultipleFunctionElement* input)
{
    FormulaElement* LHSsimplify = input->getArgOne()->simplify();
    FormulaElement* RHSsimplify = input->getArgTwo()->simplify();

    std::string typeLHSsimplify(typeid(*(LHSsimplify)).name());
    std::string typeRHSsimplify(typeid(*(RHSsimplify)).name());

    if (("class ConstantElement" == typeLHSsimplify) && ("class ConstantElement" == typeRHSsimplify))
    {
        return new ConstantElement(input->evaluate());
    }

    if (("class ConstantElement" == typeLHSsimplify && "class VariableElement" == typeRHSsimplify) ||
        ("class VariableElement" == typeLHSsimplify && "class ConstantElement" == typeRHSsimplify) ||
        ("class VariableElement" == typeLHSsimplify && "class VariableElement" == typeRHSsimplify))
    {
        VariableElement* lhsTemp = dynamic_cast<VariableElement*>(LHSsimplify);
        VariableElement* rhsTemp = dynamic_cast<VariableElement*>(RHSsimplify);
        if (lhsTemp != 0 && rhsTemp != 0 && lhsTemp->GetVariable().compare(rhsTemp->GetVariable()) == 0)
        {
            PowerFunctionElement* temp = new PowerFunctionElement();
            temp->setArgOne(LHSsimplify);
            temp->setArgTwo(new ConstantElement(2));

            return temp;
        }
        MultipleFunctionElement* temp = new MultipleFunctionElement();
        temp->setArgOne(LHSsimplify);
        temp->setArgTwo(RHSsimplify);

        return temp;
    }
    return 0;
}

FormulaElement* MultipleFunctionElement::simplify()
{
    FormulaElement* LHSsimplify = getArgOne()->simplify();
    FormulaElement* RHSsimplify = getArgTwo()->simplify();

    std::string typeLHS(typeid(*(LHSsimplify)).name());
    std::string typeRHS(typeid(*(RHSsimplify)).name());

    if (("class ConstantElement" == typeLHS) && ("class ConstantElement" == typeRHS))
    {
        return new ConstantElement(evaluate());
    }

    std::vector<FormulaElement*> LHSvector, RHSvector, simplifyVector;
    FormulaElement::toVector(LHSsimplify, &LHSvector);
    FormulaElement::toVector(RHSsimplify, &RHSvector);

    for (int i = 0; i < LHSvector.size(); i++)
    {
        std::string typeCheck(typeid(*(LHSvector[i])).name());
        if (typeCheck != "class MinusFunctionElement" && typeCheck != "class PlusFunctionElement")
        for (int j = 0; j < RHSvector.size(); j++)
        {
            std::string typeCheck2(typeid(*(RHSvector[j])).name());
            if (typeCheck2 != "class MinusFunctionElement" && typeCheck2 != "class PlusFunctionElement")
            {
                MultipleFunctionElement* temp = new MultipleFunctionElement();
                temp->setArgOne(LHSvector[i]);
                temp->setArgTwo(RHSvector[j]);
                FormulaElement* temp_ = (combineElements(temp) != 0) ? combineElements(temp) : temp;
                simplifyVector.push_back(temp_);
            }
            else
                simplifyVector.push_back(RHSvector[j]->getNewInstance());
        }
        else
            simplifyVector.push_back(LHSvector[i]);
    }

    FunctionElement::functionElemetns(&simplifyVector);
    if (simplifyVector.size() != 1)
        throw ("Unable to simplify expression!");
    else
        return simplifyVector[0];
}
