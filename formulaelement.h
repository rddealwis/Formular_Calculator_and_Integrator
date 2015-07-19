#ifndef FORMULAELEMENT_H
#define FORMULAELEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <typeinfo>
#include <math.h>

struct variableValue;

class FormulaElement
{
public:
    const double pi = 3.141592653589793238462643383279502884L;
    FormulaElement();
    ~FormulaElement();
    virtual std::string toQString() = 0;
    static FormulaElement* parseFormula(std::string formula);
	virtual bool setVariableValues(std::vector<variableValue*> *variableValues) = 0;
	virtual void getVariableValues(std::vector<variableValue*> *variableValues) = 0;
	virtual bool isFullyGrounded() = 0;
	virtual double evaluate() = 0;
    virtual FormulaElement* simplify() = 0;
    //static void functionElemetnsInit(std::vector<FormulaElement*> *formElements);
    static void functionElemetns(std::vector<FormulaElement*> *formElements);
    static void toVector(FormulaElement* node, std::vector<FormulaElement*> *formElements);

    virtual FormulaElement* getNewInstance() = 0;

};

struct variableValue
{
public:
	std::string variable = "";
	double value = 0;
};

struct BracketPos
{
public:
    int startPos = -1;
    int endPos   = -1;
    bool hasInnerBracket = false;
};

class NullElement :public FormulaElement
{
public:
    NullElement(){}
    void getVariableValues(std::vector<variableValue*> *variableValues){ return; }
    bool setVariableValues(std::vector<variableValue*> *variableValues){ return false; }
	bool isFullyGrounded() { return false; }
	double evaluate(){ return 0; }
    FormulaElement* simplify() { return this; }
    FormulaElement* getNewInstance() { return new NullElement(); }
    std::string toQString()
    {
        return "";
    }
    ~NullElement(){}
};

class Bracket :public FormulaElement
{
private:
    bool open;
public:
    void getVariableValues(std::vector<variableValue*> *variableValues){ return; }
    bool setVariableValues(std::vector<variableValue*> *variableValues){ return false; }
	bool isFullyGrounded() { return false; }
	double evaluate(){ return 0; }
    FormulaElement* simplify() { return this; }
    FormulaElement* getNewInstance() { return new Bracket(this->open); }
    Bracket(bool open)
    {
        this->open = open;
    }

    bool isOpen()
    {
        return open;
    }

    std::string toQString()
    {
        return "";
    }

    ~Bracket(){}
};

#endif // FORMULAELEMENT_H
