#include "formulator.h"
#include "formulaelement.h"

FormulaElement::FormulaElement()
{

}

FormulaElement::~FormulaElement()
{

}


const char *multiply = "*";

std::vector<std::string> splitString(std::string formulaInput);
std::vector<std::string> getTokens(std::string formulaInput);

void simplifyBrackets(std::vector<FormulaElement*> *formElements);
void formatString(std::string *text, std::string source, std::string target);
void splitTrigFunction(std::string inToken, std::vector<std::string> *outTokens);
void splitMultiplication(std::string inToken, std::vector<std::string> *outTokens);
void splitVariables(std::string inToken, std::vector<std::string> *outTokens);
bool isVariable(std::string Text);
bool isOnlyNumber(std::string Text, double *value);
bool containNumber(std::string Text);

void getConstantElements(std::vector<std::string> *tokens,
    std::vector<ConstantElement*> *constElementsOut);
void getVariableElements(std::vector<std::string> *tokens,
    std::vector<VariableElement*> *varElementsOut);
void getFormulaElements(std::vector<std::string> *tokens,
    std::vector<FormulaElement*> *formElements,
    std::vector<VariableElement*> *varElements,
    std::vector<ConstantElement*> *constElements);

bool constElementExist(std::vector<ConstantElement*> *constElements, double value, int *index);
bool constElementExist(std::vector<ConstantElement*> *constElements, double value);
bool variableElementExist(std::vector<VariableElement*> *varElements, std::string value, int *index);
bool variableElementExist(std::vector<VariableElement*> *varElements, std::string value);

bool hasBrackets(std::vector<FormulaElement*> *formElements);
int hasInnerBrackets(std::vector<FormulaElement*> *formElements, int startPos);
int findClosingBracket(std::vector<FormulaElement*> *formElements, int startPos);

void sineElemetnsInit(std::vector<FormulaElement*> *formElements);
void cosElemetnsInit(std::vector<FormulaElement*> *formElements);
void divideElemetnsInit(std::vector<FormulaElement*> *formElements);
void powerElemetnsInit(std::vector<FormulaElement*> *formElements);
void multiplyElemetnsInit(std::vector<FormulaElement*> *formElements);
void plusElemetnsInit(std::vector<FormulaElement*> *formElements);
void minusElemetnsInit(std::vector<FormulaElement*> *formElements);

void sineElemetns(std::vector<FormulaElement*> *formElements);
void cosElemetns(std::vector<FormulaElement*> *formElements);
void powerElemetns(std::vector<FormulaElement*> *formElements);
void divideElemetns(std::vector<FormulaElement*> *formElements);
void multiplyElemetns(std::vector<FormulaElement*> *formElements);
void plusElemetns(std::vector<FormulaElement*> *formElements);
void minusElemetns(std::vector<FormulaElement*> *formElements);

void functionElemetnsInit(std::vector<FormulaElement*> *formElements);
void functionElemetns(std::vector<FormulaElement*> *formElements);
FormulaElement* FormulaElement::parseFormula(std::string formula)
{
    std::vector<std::string> tokens;

    std::vector<ConstantElement*> constElements;
    std::vector<VariableElement*> varElements;
    std::vector<FormulaElement*> formElements;

    try
    {
        tokens = getTokens(formula);
        getConstantElements(&tokens, &constElements);
        getVariableElements(&tokens, &varElements);
        getFormulaElements(&tokens, &formElements, &varElements, &constElements);

        simplifyBrackets(&formElements);
		functionElemetnsInit(&formElements);

        if (formElements.size() == 1)
        {
            return formElements[0];
        }

		functionElemetns(&formElements);


        if (formElements.size() == 1)
        {
            return formElements[0];
        }
        else
            throw new std::exception("Error Parsing!");
    }
    catch (std::exception* e)
    {
        printf("%s\n", e->what());
    }
    return NULL;
}

void functionElemetnsInit(std::vector<FormulaElement*> *formElements)
{
	sineElemetnsInit(formElements);
	cosElemetnsInit(formElements);
	powerElemetnsInit(formElements);
	divideElemetnsInit(formElements);
	multiplyElemetnsInit(formElements);
	plusElemetnsInit(formElements);
	minusElemetnsInit(formElements);
}

void functionElemetns(std::vector<FormulaElement*> *formElements)
{
	sineElemetns(formElements);
	cosElemetns(formElements);
	powerElemetns(formElements);
	divideElemetns(formElements);
	multiplyElemetns(formElements);
	plusElemetns(formElements);
	minusElemetns(formElements);
}

void sineElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        SineFunctionElement *FuncEle = dynamic_cast<SineFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            if (i + 1 < (*formElements).size())
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void cosElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        CosineFunctionElement *FuncEle = dynamic_cast<CosineFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            if (i + 1 < (*formElements).size())
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void divideElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        DivideFunctionElement *FuncEle = dynamic_cast<DivideFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            std::string typeLHS = "";
            std::string typeRHS = "";
            if (i > 0)
                typeLHS = typeid(*((*formElements)[i - 1])).name();
            if (i + 1 < (*formElements).size())
                typeRHS = typeid(*((*formElements)[i + 1])).name();

            if (typeLHS.compare("class ConstantElement") == 0 || typeLHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i - 1]);
                (*formElements).erase((*formElements).begin() + (--i));
                temp.pop_back();
            }
            if (typeRHS.compare("class ConstantElement") == 0 || typeRHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void powerElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        PowerFunctionElement *FuncEle = dynamic_cast<PowerFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            std::string typeLHS = "";
            std::string typeRHS = "";
            if (i > 0)
                typeLHS = typeid(*((*formElements)[i - 1])).name();
            if (i + 1 < (*formElements).size())
                typeRHS = typeid(*((*formElements)[i + 1])).name();

            if (typeLHS.compare("class ConstantElement") == 0 || typeLHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i - 1]);
                (*formElements).erase((*formElements).begin() + (--i));
                temp.pop_back();
            }
            if (typeRHS.compare("class ConstantElement") == 0 || typeRHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void multiplyElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        MultipleFunctionElement *FuncEle = dynamic_cast<MultipleFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            std::string typeLHS = "";
            std::string typeRHS = "";
            if (i > 0)
                typeLHS = typeid(*((*formElements)[i - 1])).name();
            if (i + 1 < (*formElements).size())
                typeRHS = typeid(*((*formElements)[i + 1])).name();

            if (typeLHS.compare("class ConstantElement") == 0 || typeLHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i - 1]);
                (*formElements).erase((*formElements).begin() + (--i));
                temp.pop_back();
            }
            if (typeRHS.compare("class ConstantElement") == 0 || typeRHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void plusElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        PlusFunctionElement *FuncEle = dynamic_cast<PlusFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            std::string typeLHS = "";
            std::string typeRHS = "";
            if (i > 0)
                typeLHS = typeid(*((*formElements)[i - 1])).name();
            if (i + 1 < (*formElements).size())
                typeRHS = typeid(*((*formElements)[i + 1])).name();

            if (typeLHS.compare("class ConstantElement") == 0 || typeLHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i - 1]);
                (*formElements).erase((*formElements).begin() + (--i));
                temp.pop_back();
            }
            if (typeRHS.compare("class ConstantElement") == 0 || typeRHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void minusElemetnsInit(std::vector<FormulaElement*> *formElements)
{
    std::vector<FormulaElement*> temp;
    for (int i = 0; i < (*formElements).size(); i++)
    {
        MinusFunctionElement *FuncEle = dynamic_cast<MinusFunctionElement*>((*formElements)[i]);
        if (FuncEle != 0)
        {
            std::string typeLHS = "";
            std::string typeRHS = "";
            if (i > 0)
                typeLHS = typeid(*((*formElements)[i - 1])).name();
            if (i + 1 < (*formElements).size())
                typeRHS = typeid(*((*formElements)[i + 1])).name();

            if (typeLHS.compare("class ConstantElement") == 0 || typeLHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i - 1]);
                (*formElements).erase((*formElements).begin() + (--i));
                temp.pop_back();
            }
            if (typeRHS.compare("class ConstantElement") == 0 || typeRHS.compare("class VariableElement") == 0)
            {
                FuncEle->AddArgument((*formElements)[i + 1]);
                (*formElements).erase((*formElements).begin() + (i + 1));
            }
            temp.push_back(FuncEle);
            (*formElements).erase((*formElements).begin() + (i--));
        }
        else
        {
            temp.push_back((*formElements)[i]);
        }
    }
    (*formElements).clear();
    for (size_t i = 0; i < temp.size(); i++)
        (*formElements).push_back(temp[i]);
}

void simplifyBrackets(std::vector<FormulaElement*> *formElements)
{
    int openCount = 0;
    std::vector<BracketPos*> brakStartEnd;
    for (size_t i = 0; i < (*formElements).size(); i++)
    {
        Bracket *brak = dynamic_cast<Bracket*>((*formElements)[i]);
        if (brak != 0 && brak->isOpen())
        {
            BracketPos* brakPos = new BracketPos();
            brakPos->startPos = i;
            brakPos->endPos   = findClosingBracket(formElements, i);
            brakPos->hasInnerBracket = (hasInnerBrackets(formElements, brakPos->startPos) != -1);
            brakStartEnd.push_back(brakPos);
        }
    }

    while (hasBrackets(formElements))
    {
        if (!brakStartEnd[0]->hasInnerBracket)
        {
            std::vector<FormulaElement*> temp;
            for (size_t j = (brakStartEnd[0]->startPos + 1); j < brakStartEnd[0]->endPos; j++)
            {
                temp.push_back((*formElements)[j]);
            }

            sineElemetnsInit(&temp);
            cosElemetnsInit(&temp);
            divideElemetnsInit(&temp);
            powerElemetnsInit(&temp);
            multiplyElemetnsInit(&temp);
            plusElemetnsInit(&temp);
            minusElemetnsInit(&temp);

            if (temp.size() != 1)
                functionElemetnsInit(&temp);
            if (temp.size() != 1)
                throw new std::exception("Error Simplifying Bracket");

            (*formElements).erase((*formElements).begin() + brakStartEnd[0]->startPos, (*formElements).begin() + brakStartEnd[0]->endPos + 1);
            (*formElements).insert((*formElements).begin() + brakStartEnd[0]->startPos, temp[0]);

            if (hasBrackets(formElements))
            {
                brakStartEnd.clear();
                for (size_t k = 0; k < (*formElements).size(); k++)
                {
                    Bracket *brak = dynamic_cast<Bracket*>((*formElements)[k]);
                    if (brak != 0 && brak->isOpen())
                    {
                        BracketPos* brakPos = new BracketPos();
                        brakPos->startPos = k;
                        brakPos->endPos = findClosingBracket(formElements, k);
                        brakPos->hasInnerBracket = (hasInnerBrackets(formElements, brakPos->startPos) != -1);
                        brakStartEnd.push_back(brakPos);
                    }
                }
            }
        }
        else
        {
            std::vector<FormulaElement*> temp;
            for (size_t i = brakStartEnd[0]->startPos + 1; i < brakStartEnd[0]->endPos; i++)
            {
                temp.push_back((*formElements)[i]);
            }
            simplifyBrackets(&temp);
            divideElemetnsInit(&temp);
            powerElemetnsInit(&temp);
            multiplyElemetnsInit(&temp);
            plusElemetnsInit(&temp);
            minusElemetnsInit(&temp);

            if (temp.size() != 1)
                functionElemetnsInit(&temp);
            if (temp.size() != 1)
                throw new std::exception("Error Simplifying Bracket");

            (*formElements).erase((*formElements).begin() + brakStartEnd[0]->startPos, (*formElements).begin() + brakStartEnd[0]->endPos + 1);
            (*formElements).insert((*formElements).begin() + brakStartEnd[0]->startPos, temp[0]);

            if (hasBrackets(formElements))
            {
                brakStartEnd.clear();
                for (size_t k = 0; k < (*formElements).size(); k++)
                {
                    Bracket *brak = dynamic_cast<Bracket*>((*formElements)[k]);
                    if (brak != 0 && brak->isOpen())
                    {
                        BracketPos* brakPos = new BracketPos();
                        brakPos->startPos = k;
                        brakPos->endPos = findClosingBracket(formElements, k);
                        brakPos->hasInnerBracket = (hasInnerBrackets(formElements, brakPos->startPos) != -1);
                        brakStartEnd.push_back(brakPos);
                    }
                }
            }
        }
    }
}

int hasInnerBrackets(std::vector<FormulaElement*> *formElements, int startPos)
{
    int count = 0;
    Bracket *brakOpen = dynamic_cast<Bracket*>((*formElements)[startPos]);

    if (brakOpen != 0 && brakOpen->isOpen())
    for (size_t i = startPos; i < (*formElements).size(); i++)
    {
        Bracket *brakClose = dynamic_cast<Bracket*>((*formElements)[i]);
        if (brakClose != 0)
        {
            if (brakClose->isOpen()) count++;
            else count--;

            if (count == 0) return -1;
            if (count > 1) return i;
        }
    }
    return -1;
}

bool hasBrackets(std::vector<FormulaElement*> *formElements)
{
    for (size_t i = 0; i < (*formElements).size(); i++)
    {
        Bracket *brakOpen = dynamic_cast<Bracket*>((*formElements)[i]);
        if (brakOpen != 0)
            return true;
    }
    return false;
}

int findClosingBracket(std::vector<FormulaElement*> *formElements, int startPos)
{
    int count = 0;
    Bracket *brakOpen = dynamic_cast<Bracket*>((*formElements)[startPos]);

    if (brakOpen != 0 && brakOpen->isOpen())
    for (size_t i = startPos; i < (*formElements).size(); i++)
    {
        Bracket *brakClose = dynamic_cast<Bracket*>((*formElements)[i]);
        if (brakClose != 0)
        {
            if (brakClose->isOpen()) count++;
            else count--;

            if (count == 0) return i;
        }
    }
    return -1;
}

std::vector<std::string> splitString(std::string formulaInput)
{
    std::vector<std::string > tokens;
    std::stringstream strStream;
    std::string chkStr;
    size_t pos = 0;
    while (formulaInput.length() > 0)
    {
        strStream.clear();
        chkStr.clear();
        strStream << formulaInput.at(pos);
        strStream >> chkStr;
        if (chkStr.compare("+") == 0 || chkStr.compare("-") == 0 || chkStr.compare("*") == 0 || chkStr.compare("/") == 0 ||
            chkStr.compare("^") == 0 || chkStr.compare("(") == 0 || chkStr.compare(")") == 0)
        {
            if (pos != 0) tokens.push_back(formulaInput.substr(0, pos));
            tokens.push_back(formulaInput.substr(pos, 1));
            formulaInput = formulaInput.substr(pos + 1, formulaInput.length());
            pos = 0;
        }
        else
        {
            pos++;
            if (formulaInput.length() <= pos)
            {
                tokens.push_back(formulaInput);
                formulaInput.clear();
                break;
            }
        }
    }
    return tokens;
}

std::vector<std::string> getTokens(std::string formulaInput)
{
    formatString(&formulaInput, " ", "");
    formatString(&formulaInput, "\t", "");

    std::vector<std::string> tokens = splitString(formulaInput);
    for (size_t i = 0; i < tokens.size(); i++)
    {
        size_t sinPos = tokens[i].find("sin", 0);
        size_t cosPos = tokens[i].find("cos", 0);
        if (sinPos == std::string::npos && cosPos == std::string::npos)
        {
            if (tokens[i].length() > 2)
            {
                tokens.insert(tokens.begin() + i, "(");
                tokens.insert(tokens.begin() + (i++) + 2, ")");
            }
        }
    }
    std::vector<std::string> finalTokenVector;
    for (int i = 0; i < tokens.size(); i++)
    {
        size_t sinPos = tokens[i].find("sin", 0);
        size_t cosPos = tokens[i].find("cos", 0);

        if (sinPos == std::string::npos && cosPos == std::string::npos)
        {
            splitMultiplication(tokens[i], &finalTokenVector);
        }
        else if (sinPos != std::string::npos || cosPos != std::string::npos)
        {
            splitTrigFunction(tokens[i], &finalTokenVector);
        }
        if (tokens[i].compare(")") == 0 && (i + 1) < tokens.size() &&
            (tokens[i + 1].find("cos") != std::string::npos || tokens[i + 1].find("sin") != std::string::npos))
        {
            finalTokenVector.push_back(multiply);
        }

        if (tokens[i].compare(")") == 0 && (i + 1) < tokens.size() && tokens[i + 1].compare("(") == 0)
        {
            finalTokenVector.push_back(multiply);
        }

        if ((isVariable(tokens[i]) || containNumber(tokens[i])) && ((i + 1) < tokens.size()) && (tokens[i + 1].compare("(") == 0) &&
            (sinPos == std::string::npos) && (cosPos == std::string::npos))
        {
            finalTokenVector.push_back(multiply);
        }
    }
    finalTokenVector.shrink_to_fit();
    return finalTokenVector;
}

void formatString(std::string *text, std::string source, std::string target)
{
    size_t start_pos = 0;
    while ((start_pos = (*text).find(source, start_pos)) != std::string::npos) {
        (*text).replace(start_pos, source.length(), target);
        start_pos += target.length();
    }
}

void splitTrigFunction(std::string inToken, std::vector<std::string> *outTokens)
{

    size_t sinPos = inToken.find("sin", 0);
    size_t cosPos = inToken.find("cos", 0);
    size_t finalPos = (sinPos == std::string::npos) ? cosPos : sinPos;
    if (finalPos == 0)
    {
        (*outTokens).push_back(inToken);
        return;
    }
    else
    {
        splitMultiplication(inToken.substr(0, finalPos), outTokens);
        (*outTokens).push_back(multiply);
        (*outTokens).push_back(inToken.substr(finalPos, inToken.length()));
    }
}

void splitMultiplication(std::string inToken, std::vector<std::string> *outTokens)
{
    double chkValue = 0;
    if (containNumber(inToken) && !isOnlyNumber(inToken, &chkValue))
    {
        size_t numEndPos;
        chkValue = std::stod(inToken, &numEndPos);
        (*outTokens).push_back((new ConstantElement(chkValue))->toQString());
        (*outTokens).push_back(multiply);
        splitVariables(inToken.substr(numEndPos, inToken.length()), outTokens);
    }
    else
    {
        if (isOnlyNumber(inToken, &chkValue))
            (*outTokens).push_back(inToken);
        else
            splitVariables(inToken, outTokens);
    }
}

void splitVariables(std::string inToken, std::vector<std::string> *outTokens)
{
    for (size_t i = 0; i < inToken.length(); i++)
    {
        std::stringstream ss;
        std::string s;
        ss << inToken.at(i);
        ss >> s;
        (*outTokens).push_back(s);
        if (i < inToken.length() - 1)
            (*outTokens).push_back(multiply);
    }
}

void getConstantElements(std::vector<std::string> *tokens, std::vector<ConstantElement*> *constElementsOut)
{
    for (size_t i = 0; i < (*tokens).size(); i++)
    {
        double value = 0;
        if (isOnlyNumber((*tokens)[i], &value) && !constElementExist(constElementsOut, value))
        {
            ConstantElement* temp = new ConstantElement(value);
            (*constElementsOut).push_back(temp);
        }
    }
}

void getVariableElements(std::vector<std::string> *tokens, std::vector<VariableElement*> *varElementsOut)
{
    for (size_t i = 0; i < (*tokens).size(); i++)
    {
        if (isVariable((*tokens)[i]) && !variableElementExist(varElementsOut, (*tokens)[i]))
        {
            VariableElement* temp = new VariableElement((*tokens)[i]);
            (*varElementsOut).push_back(temp);
        }
    }
}

void getFormulaElements(std::vector<std::string> *tokens,
    std::vector<FormulaElement*> *formElements,
    std::vector<VariableElement*> *varElements,
    std::vector<ConstantElement*> *constElements)
{
    for (size_t i = 0; i < (*tokens).size(); i++)
    {
        int index = -1;
        double constVal = 0;
        if (isVariable((*tokens)[i]) && variableElementExist(varElements, (*tokens)[i], &index))
        {
            (*formElements).push_back((*varElements)[index]);
            continue;
        }
        if (isOnlyNumber((*tokens)[i], &constVal) && constElementExist(constElements, constVal, &index))
        {
            (*formElements).push_back((*constElements)[index]);
            continue;
        }
        if ((*tokens)[i] == "(")
        {
            (*formElements).push_back(new Bracket(true));
            continue;
        }
        if ((*tokens)[i] == ")")
        {
            (*formElements).push_back(new Bracket(false));
            continue;
        }
        if ((*tokens)[i] == "+")
        {
            (*formElements).push_back(new PlusFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "-")
        {
            (*formElements).push_back(new MinusFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "*")
        {
            (*formElements).push_back(new MultipleFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "^")
        {
            (*formElements).push_back(new PowerFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "/")
        {
            (*formElements).push_back(new DivideFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "sin")
        {
            (*formElements).push_back(new SineFunctionElement());
            continue;
        }
        if ((*tokens)[i] == "cos")
        {
            (*formElements).push_back(new CosineFunctionElement());
            continue;
        }
    }
}

bool variableElementExist(std::vector<VariableElement*> *varElements, std::string value)
{
    int index = 0;
    return variableElementExist(varElements, value, &index);
}

bool variableElementExist(std::vector<VariableElement*> *varElements, std::string value, int *index)
{
    for (size_t i = 0; i < (*varElements).size(); i++)
    {
        if ((*varElements)[i]->GetVariable() == value)
        {
            (*index) = i;
            return true;
        }
    }
    (*index) = -1;
    return false;
}

bool constElementExist(std::vector<ConstantElement*> *constElements, double value)
{
    int index = 0;
    return constElementExist(constElements, value, &index);
}

bool constElementExist(std::vector<ConstantElement*> *constElements, double value, int *index)
{
    for (size_t i = 0; i < (*constElements).size(); i++)
    {
        if ((*constElements)[i]->GetConstant() == value)
        {
            (*index) = i;
            return true;
        }
    }
    (*index) = -1;
    return false;
}

bool isVariable(std::string Text)
{
    return (!containNumber(Text) && Text.compare("sin") != 0 && Text.compare("cos") != 0 && Text.compare("+") != 0 && Text.compare("-") != 0 &&
        Text.compare("*") != 0 && Text.compare("/") != 0 && Text.compare("(") != 0 && Text.compare(")") != 0 && Text.compare("^") != 0 && Text.compare("") != 0);
}

bool isOnlyNumber(std::string Text, double *value)
{
    try
    {
        size_t numEndPos;
        *value = std::stod(Text, &numEndPos);
        return (Text.length() == numEndPos);
    }
    catch (...)
    {
        return false;
    }
}

bool containNumber(std::string Text)
{
    try
    {
        std::string::size_type sz;
        double chkDouble = std::stod(Text, &sz);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


void sineElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		SineFunctionElement *FuncEle = dynamic_cast<SineFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
			}
			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void cosElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		CosineFunctionElement *FuncEle = dynamic_cast<CosineFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
			}
			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void powerElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		PowerFunctionElement *FuncEle = dynamic_cast<PowerFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{
			bool LHSchg = false;
			bool RHSchg = false;
			if (FuncEle->isArgOneNull())
			{
				if (temp.size() > 0)
				{
					FuncEle->AddArgument(temp[temp.size() - 1]);
					temp.pop_back();
				}
				else
				{
					FuncEle->AddArgument((*formElements)[i - 1]);
					(*formElements).erase((*formElements).begin() + (--i));
				}
				LHSchg = true;
			}

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
				RHSchg = true;
			}

			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void divideElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		DivideFunctionElement *FuncEle = dynamic_cast<DivideFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{
			bool LHSchg = false;
			bool RHSchg = false;
			if (FuncEle->isArgOneNull())
			{
				if (temp.size() > 0)
				{
					FuncEle->AddArgument(temp[temp.size() - 1]);
					temp.pop_back();
				}
				else
				{
					FuncEle->AddArgument((*formElements)[i - 1]);
					(*formElements).erase((*formElements).begin() + (--i));
				}
				LHSchg = true;
			}

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
				RHSchg = true;
			}

			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void multiplyElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		MultipleFunctionElement *FuncEle = dynamic_cast<MultipleFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{
			bool LHSchg = false;
			bool RHSchg = false;
			if (FuncEle->isArgOneNull())
			{
				if (temp.size() > 0)
				{
					FuncEle->AddArgument(temp[temp.size() - 1]);
					temp.pop_back();
				}
				else
				{
					FuncEle->AddArgument((*formElements)[i - 1]);
					(*formElements).erase((*formElements).begin() + (--i));
				}
				LHSchg = true;
			}

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
				RHSchg = true;
			}

			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void plusElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		PlusFunctionElement *FuncEle = dynamic_cast<PlusFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{
			bool LHSchg = false;
			bool RHSchg = false;
				if (FuncEle->isArgOneNull())
			{
				if (temp.size() > 0)
				{
					FuncEle->AddArgument(temp[temp.size() - 1]);
					temp.pop_back();
				}
				else
				{
					FuncEle->AddArgument((*formElements)[i - 1]);
					(*formElements).erase((*formElements).begin() + (--i));
				}
				LHSchg = true;
			}

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
				RHSchg = true;
			}

			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

void minusElemetns(std::vector<FormulaElement*> *formElements)
{
	std::vector<FormulaElement*> temp;
	for (int i = 0; i < (*formElements).size(); i++)
	{
		MinusFunctionElement *FuncEle = dynamic_cast<MinusFunctionElement*>((*formElements)[i]);
		if (FuncEle != 0)
		{
			bool LHSchg = false;
			bool RHSchg = false;
			if (FuncEle->isArgOneNull())
			{
				if (temp.size() > 0)
				{
					FuncEle->AddArgument(temp[temp.size() - 1]);
					temp.pop_back();
				}
				else
				{
					FuncEle->AddArgument((*formElements)[i - 1]);
					(*formElements).erase((*formElements).begin() + (--i));
				}
				LHSchg = true;
			}

			if (FuncEle->isArgTwoNull())
			{
				FuncEle->AddArgument((*formElements)[i + 1]);
				(*formElements).erase((*formElements).begin() + (i + 1));
				RHSchg = true;
			}

			temp.push_back(FuncEle);
			(*formElements).erase((*formElements).begin() + (i--));
		}
		else
		{
			temp.push_back((*formElements)[i]);
		}
	}
	(*formElements).clear();
	for (size_t i = 0; i < temp.size(); i++)
		(*formElements).push_back(temp[i]);
}

