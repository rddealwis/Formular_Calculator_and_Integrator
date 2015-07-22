#include "variableelement.h"

VariableElement::VariableElement(std::string variable)
{
    this->variable=variable;
}

VariableElement::~VariableElement()
{

}

std::string VariableElement::GetVariable()
{
    return this->variable;
}

double VariableElement::GetNumVal()
{
    return this->numVal;
}

void VariableElement::SetNumVal(double numVal)
{
    this->numVal=numVal;
}

std::string VariableElement::toQString()
{
    return this->variable;
}

void VariableElement::getVariableValues(std::vector<variableValue*> *variableValues)
{
	bool found = false;
	for (size_t i = 0; i < (*variableValues).size(); i++)
	if (found = (*variableValues)[i]->variable.compare(this->variable) == 0)
		break;

	if (!found)
	{
		variableValue* varVal = new variableValue();
		varVal->value = this->numVal;
		varVal->variable = this->variable;
		(*variableValues).push_back(varVal);
	}
}

bool VariableElement::setVariableValues(std::vector<variableValue*> *variableValues)
{
	for (size_t i = 0; i < (*variableValues).size(); i++)
	{
		if ((*variableValues)[i]->variable.compare(this->variable) == 0)
		{
			this->numVal = (*variableValues)[i]->value;
			this->grounded = true;
			return true;
		}
	}
	return false;
}

bool VariableElement::isFullyGrounded()
{
	return this->grounded;
}
