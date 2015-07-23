#include "dlgcalareaundercurve.h"
#include "ui_dlgcalareaundercurve.h"
#include "formulaelement.h"
#include "exprtk.hpp"

dlgCalAreaUnderCurve::dlgCalAreaUnderCurve(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCalAreaUnderCurve)
{
    ui->setupUi(this);
}

dlgCalAreaUnderCurve::~dlgCalAreaUnderCurve()
{
    delete ui;
}

void dlgCalAreaUnderCurve::findAreaUnderTheCurve(std::string graphEquation){

//    exprtk::parser<double> parser;
//    exprtk::expression<double> expression;
//    exprtk::symbol_table<double> symbol_table;

//    std::string minRange = this->ui->txtMinRange->toPlainText().toStdString();
//    std::string maxRange = this->ui->txtMaxRange->toPlainText().toStdString();

//    double minimumRange = std::stod(minRange);
//    double maximumRange = std::stod(maxRange);
//    double temp = 0;

//    std::string expression_string = "abs(" +graphEquation+ ")";

//    std::vector<variableValue*> variableValues;
//    std::string formulaInput(graphEquation);
//    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
//    formula->getVariableValues(&variableValues);

//    for (int i = 0; i < variableValues.size(); i++)
//    {
//        bool ok;
//        double val = 0;

//        val = QInputDialog::getDouble(this,tr("Enter variable value"),tr("Please enter a value for the variable ")+variableValues[i]->variable.data(),
//                                        0,-2147483647,2147483647,4,&ok);
//        variableValues[i]->value = val;
//    }

//    symbol_table.add_variable("X",temp);
//    symbol_table.add_variable("Y",temp);

//    expression.register_symbol_table(symbol_table);
//    parser.compile(expression_string,expression);

//    double calculatedArea = (exprtk::integrate(expression,"X",minimumRange,maximumRange));

//    this->ui->txtCalAreaUndertheCurve->setText(QString::number(calculatedArea));
}

void dlgCalAreaUnderCurve::on_pbCalculate_clicked()
{
    //findAreaUnderTheCurve(this->ui->txtFormula->toPlainText().toStdString());
}

void dlgCalAreaUnderCurve::on_pbClose_clicked()
{
    this->close();
}
