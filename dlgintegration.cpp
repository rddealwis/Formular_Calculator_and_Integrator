#include "dlgintegration.h"
#include "ui_dlgintegration.h"
#include "formulaelement.h"
#include "exprtk.hpp"
#include <qmessagebox.h>
#include <QInputDialog>

dlgIntegration::dlgIntegration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgIntegration)
{
    ui->setupUi(this);
}

dlgIntegration::~dlgIntegration()
{
    delete ui;
}

void dlgIntegration::setGraphEquation(std::string graphEquation)
{
    this->ui->txtFormula->setText(QString::fromStdString(graphEquation));
    addIntegrationVariables(this->ui->txtFormula->toPlainText().toStdString());
}

void dlgIntegration::addIntegrationVariables(std::string graphEquation)
{
    std::vector<variableValue*> variableValues;
    std::string formulaInput(graphEquation);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    formula->getVariableValues(&variableValues);

    this->ui->cmbIntegrationVar->clear();
    this->ui->cmbIntegrationVar->addItem("-Select-");
    for (int i = 0; i < variableValues.size(); i++)
    {
        this->ui->cmbIntegrationVar->addItem(variableValues[i]->variable.data());
    }
}

double dlgIntegration::findAreaUnderTheCurve(std::string graphEquation){

    exprtk::parser<double> parser;
    exprtk::expression<double> expression;
    exprtk::symbol_table<double> symbol_table;

    std::string minRange = this->ui->txtMinRange->toPlainText().toStdString();
    std::string maxRange = this->ui->txtMaxRange->toPlainText().toStdString();
    std::string integrationVar = this->ui->cmbIntegrationVar->currentText().toStdString();

    double minimumRange = std::stod(minRange);
    double maximumRange = std::stod(maxRange);

    std::string expression_string = graphEquation;

    std::vector<variableValue*> variableValues;
    std::string formulaInput(graphEquation);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    formula->getVariableValues(&variableValues);

    for (int i = 0; i < variableValues.size(); i++)
    {
        bool ok;
        double val = 0;

        if(variableValues[i]->variable.data() != this->ui->cmbIntegrationVar->currentText())
        {

            val = QInputDialog::getDouble(this,tr("Enter variable value"),tr("Please enter a value for the variable ")+variableValues[i]->variable.data(),
                                            0,-2147483647,2147483647,4,&ok);
            variableValues[i]->value = val;

            symbol_table.add_variable(variableValues[i]->variable.data(),variableValues[i]->value);
        }
        else
        {
            variableValues[i]->value = 0;
            symbol_table.add_variable(variableValues[i]->variable.data(),variableValues[i]->value);
        }
    }

    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string,expression);

    return (exprtk::integrate(expression,integrationVar,minimumRange,maximumRange));
}

void dlgIntegration::on_pbOk_clicked()
{
    if((this->ui->txtMinRange->toPlainText() == "")|| (this->ui->txtMaxRange->toPlainText() == ""))
    {
        QMessageBox::critical(this,"Infinity Calculator","Please provide both minimum & maximum ranges.", QMessageBox::Ok);
    }
    else if(this->ui->cmbIntegrationVar->currentText().toStdString()== "-Select-")
    {
        QMessageBox::critical(this,"Infinity Calculator","Please select the integration variable", QMessageBox::Ok);
    }
    else
    {
        calculatedArea = findAreaUnderTheCurve(this->ui->txtFormula->toPlainText().toStdString());
        this->close();
    }    
}

void dlgIntegration::on_pbClose_clicked()
{
    this->close();
}
