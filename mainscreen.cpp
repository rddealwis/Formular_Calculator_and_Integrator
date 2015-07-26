#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "formulator.h"
#include "dlgloadformula.h"
#include "dlgsaveformula.h"
#include "dlgsavegraph.h"
#include "dlggraphviewer.h"
#include "dlgcalareaundercurve.h"
#include "dlgintegration.h"
#include <qmessagebox.h>
#include <qframe.h>
#include <cmath>
#include <QInputDialog>
#include <QDir>

#define PI 3.14159265

MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    ui->txtXaxisRangeFrom->setEnabled(false);
    ui->txtXaxisRangeTo->setEnabled(false);
    ui->txtYaxisRangeFrom->setEnabled(false);
    ui->txtYaxisRangeTo->setEnabled(false);

    ui->txtXaxisName->setEnabled(false);
    ui->txtYaxisName->setEnabled(false);

    ui->pbPercentage->setEnabled(false);
    ui->frmAboutCalculator->setVisible(false);
    ui->pbIntegration->setEnabled(false);
    ui->pbAddGraphFormula->setEnabled(false);
    ui->pbRemoveFormula->setEnabled(false);
    ui->pbCalAreaUndertheCurve->setEnabled(false);
    ui->pbGenerate->setEnabled(false);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::ButtonClickEventHandler(std::string txt, int txtField)
{
    if(txtField == 0)
    {
        if(ui->txtTextEditor->toPlainText()!= "0")
        {
            QTextCursor prev_cursor = ui->txtTextEditor->textCursor();
            ui->txtTextEditor->moveCursor(QTextCursor::End);
            ui->txtTextEditor->insertPlainText(QString::fromStdString(txt));
            ui->txtTextEditor->setTextCursor(prev_cursor);
        }
        else
        {
            ui->txtTextEditor->clear();
            QTextCursor prev_cursor = ui->txtTextEditor->textCursor();
            ui->txtTextEditor->moveCursor(QTextCursor::End);
            ui->txtTextEditor->insertPlainText(QString::fromStdString(txt));
            ui->txtTextEditor->setTextCursor(prev_cursor);
        }
    }
    else
    {
        if(ui->txtEquation->toPlainText()!= "0")
        {
            QTextCursor prev_cursor = ui->txtEquation->textCursor();
            ui->txtEquation->moveCursor(QTextCursor::End);
            ui->txtEquation->insertPlainText(QString::fromStdString(txt));
            ui->txtEquation->setTextCursor(prev_cursor);
        }
        else
        {
            ui->txtEquation->clear();
            QTextCursor prev_cursor = ui->txtEquation->textCursor();
            ui->txtEquation->moveCursor(QTextCursor::End);
            ui->txtEquation->insertPlainText(QString::fromStdString(txt));
            ui->txtEquation->setTextCursor(prev_cursor);
        }
    }
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbZero_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        this->ButtonClickEventHandler("0", 0);
    }
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbOne_clicked()
{
    this->ButtonClickEventHandler("1", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbTwo_clicked()
{
    this->ButtonClickEventHandler("2", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbThree_clicked()
{
    this->ButtonClickEventHandler("3", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbFour_clicked()
{
    this->ButtonClickEventHandler("4", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbFive_clicked()
{
    this->ButtonClickEventHandler("5", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbSix_clicked()
{
    this->ButtonClickEventHandler("6", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbSeven_clicked()
{
    this->ButtonClickEventHandler("7", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbEight_clicked()
{
    this->ButtonClickEventHandler("8", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbNine_clicked()
{
    this->ButtonClickEventHandler("9", 0);
    ui->pbPercentage->setEnabled(true);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbDot_clicked()
{
    this->ButtonClickEventHandler(".", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbPlus_clicked()
{
    this->ButtonClickEventHandler("+", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbMinus_clicked()
{
    this->ButtonClickEventHandler("-", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbMultiply_clicked()
{
    this->ButtonClickEventHandler("*", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbDivide_clicked()
{
    this->ButtonClickEventHandler("/", 0);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbPlusOrMinus_clicked()
{
    if(ui->txtResultsEditor->toPlainText().toDouble(0) < 0)
    {
        std::size_t posOfMinusSign =(ui->txtResultsEditor->toPlainText().toStdString()).find("-");
        std::string plusValue = (ui->txtResultsEditor->toPlainText().toStdString()).substr (posOfMinusSign+1);
        ui->txtResultsEditor->setText(QString::fromStdString(plusValue));

        ui->txtTextEditor->clear();
        ui->txtTextEditor->setText(QString::fromStdString(plusValue));
    }
    else
    {
        ui->txtResultsEditor->setText("-"+ ui->txtResultsEditor->toPlainText());

        ui->txtTextEditor->clear();
        ui->txtTextEditor->setText(ui->txtResultsEditor->toPlainText());
    }
    ui->pbPercentage->setEnabled(true);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbEqual_clicked()
{
    try
    {
    std::vector<variableValue*> variableValues;

    std::string input = this->ui->txtTextEditor->toPlainText().toStdString();
    std::string formulaInput(input);

    //QMessageBox::critical(this,"Infinity Calculator", QString::number(std::count(formulaInput.begin(), formulaInput.end()) +" "+, QMessageBox::Ok);
    if(std::count(formulaInput.begin(), formulaInput.end(), '(') != std::count(formulaInput.begin(), formulaInput.end(), ')'))
    {
        QMessageBox::critical(this,"Infinity Calculator", "Number of opening and closing brackets are not equal.", QMessageBox::Ok);
        return;
    }

    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    formula->getVariableValues(&variableValues);

    for (int i = 0; i < variableValues.size(); i++)
    {
        bool ok;
        double val = 0;

        val = QInputDialog::getDouble(this,tr("Enter variable value"),tr("Please enter a value for the variable ")+variableValues[i]->variable.data(),
                                      0,-2147483647,2147483647,4,&ok);
        variableValues[i]->value = val;
    }

    formula->setVariableValues(&variableValues);

    //this->ui->txtTextEditor->setText(QString::fromStdString(formula->toQString().data()));

    this->ui->txtResultsEditor->setText(QString::number(formula->evaluate()));
    ui->pbPercentage->setEnabled(false);
    }

    catch(...)
    {
        QMessageBox::critical(this,"Infinity Calculator", "Error occured when solving the equation", QMessageBox::Ok);
    }
}

void MainScreen::on_pbInverse_clicked()
{
    QTextCursor prev_cursor = ui->txtTextEditor->textCursor();
    ui->txtTextEditor->moveCursor(QTextCursor::End);

    ui->txtTextEditor->setText("1/("+ ui->txtTextEditor->toPlainText()+")");
    ui->txtTextEditor->setTextCursor(prev_cursor);
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbPercentage_clicked()
{
    double val = ui->txtTextEditor->toPlainText().toDouble(0);

    double prcntgValue = val/100;
    ui->txtResultsEditor->setText(QString::number(prcntgValue));
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbSqRoot_clicked()
{
    double val = ui->txtTextEditor->toPlainText().toDouble(0);

    double result = sqrt (val);
    ui->txtResultsEditor->setText(QString::number(result));
    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbCE_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        if(!ui->txtTextEditor->toPlainText().isEmpty())
        {
            ui->txtTextEditor->moveCursor(QTextCursor::End);
            ui->txtTextEditor->textCursor().deletePreviousChar();
        }
    }
    ui->txtResultsEditor->clear();
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbC_clicked()
{
    ui->txtTextEditor->clear();
    ui->txtResultsEditor->clear();
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbDel_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        if(!ui->txtTextEditor->toPlainText().isEmpty())
        {
            ui->txtTextEditor->moveCursor(QTextCursor::End);
            ui->txtTextEditor->textCursor().deletePreviousChar();
        }
    }
    ui->txtResultsEditor->clear();
    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbMC_clicked()
{
    this->tempMemory = 0;
    this->ui->txtTextEditor->setText("");
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbMR_clicked()
{
    this->ui->txtTextEditor->setText(QString::number(this->tempMemory, 'f', 2));
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbMS_clicked()
{
    this->tempMemory = this->ui->txtTextEditor->toPlainText().toDouble();
    this->ui->txtResultsEditor->setText(QString::number(this->tempMemory, 'f', 2));
    this->ui->txtTextEditor->setText("");
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbMPlus_clicked()
{
    this->tempMemory += this->ui->txtTextEditor->toPlainText().toDouble();
    this->ui->txtResultsEditor->setText(QString::number(this->tempMemory, 'f', 2));
    this->ui->txtTextEditor->setText("");
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbMMinus_clicked()
{
    this->tempMemory -= this->ui->txtTextEditor->toPlainText().toDouble();
    this->ui->txtResultsEditor->setText(QString::number(this->tempMemory, 'f', 2));
    this->ui->txtTextEditor->setText("");
    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbOpenBrackets_clicked()
{
    this->ButtonClickEventHandler("(", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbCloseBrackets_clicked()
{
    this->ButtonClickEventHandler(")", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbLog_clicked()
{
    this->ButtonClickEventHandler("log(", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbLn_clicked()
{
    this->ButtonClickEventHandler("ln(", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbSin_clicked()
{
    this->ButtonClickEventHandler("sin(", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbCos_clicked()
{
    this->ButtonClickEventHandler("cos(", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbTan_clicked()
{
    //this->ButtonClickEventHandler("Tan(", 0);
    double val = ui->txtTextEditor->toPlainText().toDouble(0);
    double result = tan ( val * PI / 180.0 );

    ui->txtResultsEditor->setText(QString::number(result));
    ui->txtTextEditor->setText(ui->txtResultsEditor->toPlainText());


    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbFactorial_clicked()
{

    std::string input = this->ui->txtTextEditor->toPlainText().toStdString();

    std::string formulaInput(input);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    double a = formula->evaluate();

    ui->txtResultsEditor->setText(QString::number(iter_factorial(a)));
    ui->txtTextEditor->setText(ui->txtResultsEditor->toPlainText());
    ui->pbPercentage->setEnabled(false);
}

double MainScreen::iter_factorial(double n)
{
    double ret = 1;
    for(double i = 1; i <= n; ++i)
    {
        ret = ret* i;
    }
    return ret;
}

void MainScreen::on_pbSquare_clicked()
{
    std::string input = this->ui->txtTextEditor->toPlainText().toStdString()+ "^2";

    std::string formulaInput(input);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    this->ui->txtResultsEditor->setText(QString::number(formula->evaluate()));

    this->ui->txtTextEditor->setText(QString::fromStdString(input));
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbNthPower_clicked()
{
    std::string input = this->ui->txtTextEditor->toPlainText().toStdString();
    this->ui->txtTextEditor->setText(QString::fromStdString(input)+"^");
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbPoweOfTen_clicked()
{
    std::string input = "10^"+this->ui->txtTextEditor->toPlainText().toStdString();

    std::string formulaInput(input);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    this->ui->txtResultsEditor->setText(QString::number(formula->evaluate()));

    this->ui->txtTextEditor->setText(QString::fromStdString(input));
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbNthSqRoot_clicked()
{
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbPi_clicked()
{
    if(sizeof(ui->txtTextEditor->size())>2)
    {
        this->ButtonClickEventHandler("3.1416", 0);
    }
    else
    {
        this->ButtonClickEventHandler("3.1415926535897932384626433832795", 0);
    }
    ui->pbPercentage->setEnabled(true);
}

void MainScreen::on_pbPower_clicked()
{
    this->ButtonClickEventHandler("^", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbDifferentiation_clicked()
{
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbStoD_clicked()
{
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbModulus_clicked()
{
    this->ButtonClickEventHandler("mod", 0);
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbIntegration_clicked()
{
    dlgIntegration formualIntegration;

    formualIntegration.setGraphEquation(this->ui->txtTextEditor->toPlainText().toStdString());
    formualIntegration.setModal(true);
    formualIntegration.exec();

    this->ui->txtResultsEditor->setText(QString::number(formualIntegration.calculatedArea));
    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbSaveFormula_clicked()
{
    dlgSaveFormula saveFormula;

    saveFormulaValue = this->ui->txtTextEditor->toPlainText().toStdString();

    saveFormula.setCurrentMemory(saveFormulaValue, formula, formulaName, formulaOnMemory, formulaNameOnMemory, this->filePath);
    saveFormula.setModal(true);
    saveFormula.exec();

    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    std::fill( std::begin( formulaOnMemory ), std::end( formulaOnMemory ), "" );    std::fill( std::begin( formulaNameOnMemory ), std::end( formulaNameOnMemory ), "" );
    this->ui->lstScientificFromFile->clear();

    this->filePath = saveFormula.filePath;

    saveFormula.getSavedEquations(formula,formulaName, formulaOnMemory, formulaNameOnMemory);

    this->LoadToListGraphFromFile();
    this->LoadToListGraphInMemory();
    this->LoadToListGraphScientificFromFile();
    this->LoadToListGraphScientificInMemory();

    ui->pbPercentage->setEnabled(false);
}

void ClearArray(std::string arr[]);
void ClearArray(std::string arr[])
{
    for(int i = 0; arr[i] !=""; i++)
    {
        arr[i] = "";
    }
}

void MainScreen::on_pbLoadFormula_clicked()
{
    dlgLoadFormula loadFormula;

    loadFormula.setCurrentMemory(formula, formulaName, formulaOnMemory, formulaNameOnMemory, filePath);
    loadFormula.setModal(true);
    loadFormula.exec();

    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    std::fill( std::begin( formulaOnMemory ), std::end( formulaOnMemory ), "" );
    std::fill( std::begin( formulaNameOnMemory ), std::end( formulaNameOnMemory ), "" );

    this->ui->txtTextEditor->setText(QString::fromStdString(loadFormula.getSelectedEquation(formula, formulaName, formulaOnMemory, formulaNameOnMemory)));
    this->ui->lstScientificFromFile->clear();
    this->filePath = loadFormula.filePath;

    this->LoadToListGraphFromFile();
    this->LoadToListGraphInMemory();
    this->LoadToListGraphScientificFromFile();
    this->LoadToListGraphScientificInMemory();

    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbLoadGraphFormula_clicked()
{
    dlgLoadFormula loadFormula;
    loadFormula.setCurrentMemory(formula, formulaName, formulaOnMemory, formulaNameOnMemory, filePath);
    loadFormula.setModal(true);
    loadFormula.exec();

    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    std::fill( std::begin( formulaOnMemory ), std::end( formulaOnMemory ), "" );
    std::fill( std::begin( formulaNameOnMemory ), std::end( formulaNameOnMemory ), "" );

    this->ui->txtEquation->setText(QString::fromStdString(loadFormula.getSelectedEquation(formula, formulaName, formulaOnMemory, formulaNameOnMemory)));
    this->ui->lstScientificFromFile->clear();
    this->filePath = loadFormula.filePath;

    this->LoadToListGraphFromFile();
    this->LoadToListGraphInMemory();
    this->LoadToListGraphScientificFromFile();
    this->LoadToListGraphScientificInMemory();

    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::LoadToListGraphFromFile()
{
    QListWidgetItem *newItem;
    QString ListVal = "";
    this->ui->lstGraphFromFile->clear();
    for(int i = 0; formulaName[i] != ""; i++)
    {
        // if(formulaName[i] != "")
        {
            newItem = new QListWidgetItem;
            //ListVal = QString::fromStdString(formulaName[i] + " - " + formula[i]);
            ListVal = QString::fromStdString(formula[i]);
            newItem->setText(ListVal);
            int row = this->ui->lstGraphFromFile->row(this->ui->lstGraphFromFile->currentItem());
            this->ui->lstGraphFromFile->insertItem(row, newItem);
        }
    }
}

void MainScreen::LoadToListGraphInMemory()
{
    QListWidgetItem *newItem;
    QString ListVal = "";
    this->ui->lstGraphInMemory->clear();

    for(int i = 0; formulaNameOnMemory[i] != ""; i++)
    {
        if(formulaNameOnMemory[i] != "")
        {
            newItem = new QListWidgetItem;
            //ListVal = QString::fromStdString(formulaNameOnMemory[i] + " - " + formulaOnMemory[i]);
            ListVal = QString::fromStdString(formulaOnMemory[i]);
            newItem->setText(ListVal);
            int row = this->ui->lstGraphInMemory->row(this->ui->lstGraphInMemory->currentItem());
            this->ui->lstGraphInMemory->insertItem(row, newItem);
        }
    }
}

void MainScreen::LoadToListGraphScientificFromFile()
{
    QListWidgetItem *newItem;
    QString ListVal = "";
    this->ui->lstScientificFromFile->clear();

    for(int i = 0; formulaName[i] != ""; i++)
    {
        // if(formulaName[i] != "")
        {
            newItem = new QListWidgetItem;
            //ListVal = QString::fromStdString(formulaName[i] + " - " + formula[i]);
            ListVal = QString::fromStdString(formula[i]);
            newItem->setText(ListVal);
            int row = this->ui->lstScientificFromFile->row(this->ui->lstScientificFromFile->currentItem());
            this->ui->lstScientificFromFile->insertItem(row, newItem);
        }
    }
}

void MainScreen::LoadToListGraphScientificInMemory()
{
    QListWidgetItem *newItem;
    QString ListVal = "";
    this->ui->lstScientificInMemory->clear();

    for(int i = 0; formulaNameOnMemory[i] != ""; i++)
    {
        // if(formulaNameOnMemory[i] != "")
        {
            newItem = new QListWidgetItem;
            //ListVal = QString::fromStdString(formulaNameOnMemory[i] + " - " + formulaOnMemory[i]);
            ListVal = QString::fromStdString(formulaOnMemory[i]);
            newItem->setText(ListVal);
            int row = this->ui->lstScientificInMemory->row(this->ui->lstScientificInMemory->currentItem());
            this->ui->lstScientificInMemory->insertItem(row, newItem);
        }
    }
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbAddGraphFormula_clicked()
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(this->ui->txtEquation->toPlainText());
    int row = this->ui->lstGraphFormulas->row(this->ui->lstGraphFormulas->currentItem());
    this->ui->lstGraphFormulas->insertItem(row, newItem);

    ui->txtEquation->clear();
    ui->pbGenerate->setEnabled(true);

    ui->txtXaxisRangeFrom->setEnabled(true);
    ui->txtXaxisRangeTo->setEnabled(true);
    ui->txtYaxisRangeFrom->setEnabled(true);
    ui->txtYaxisRangeTo->setEnabled(true);

    ui->txtXaxisName->setEnabled(true);
    ui->txtYaxisName->setEnabled(true);

    if(ui->txtXaxisRangeFrom->toPlainText() == "")
    {
        ui->txtXaxisRangeFrom->setText("-5");
    }
    if(ui->txtXaxisRangeTo->toPlainText() == "")
    {
        ui->txtXaxisRangeTo->setText("10");
    }
    if(ui->txtYaxisRangeFrom->toPlainText() == "")
    {
        ui->txtYaxisRangeFrom->setText("-5");
    }
    if(ui->txtYaxisRangeTo->toPlainText() == "")
    {
        ui->txtYaxisRangeTo->setText("10");
    }

    ui->txtXaxisName->setText("X-Axis");
    ui->txtYaxisName->setText("Y-Axis");

    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbRemoveFormula_clicked()
{
    this->ui->lstGraphFormulas->takeItem(this->ui->lstGraphFormulas->row(this->ui->lstGraphFormulas->currentItem()));

    if(this->ui->lstGraphFormulas->count() == 0)
    {
        ui->txtXaxisRangeFrom->setEnabled(false);
        ui->txtXaxisRangeTo->setEnabled(false);
        ui->txtYaxisRangeFrom->setEnabled(false);
        ui->txtYaxisRangeTo->setEnabled(false);

        ui->txtXaxisName->setEnabled(false);
        ui->txtYaxisName->setEnabled(false);

        ui->pbCalAreaUndertheCurve->setEnabled(false);
        ui->pbRemoveFormula->setEnabled(false);
        ui->pbGenerate->setEnabled(false);

        ui->txtXaxisRangeFrom->clear();
        ui->txtXaxisRangeTo->clear();
        ui->txtYaxisRangeFrom->clear();
        ui->txtYaxisRangeTo->clear();

        ui->txtXaxisName->clear();
        ui->txtYaxisName->clear();

        ui->pbPercentage->setEnabled(false);
    }
}

void MainScreen::on_pbGenerate_clicked()
{
    dlgGraphViewer graphViewer;
    QString InfoMessage = "You have not specified values for the following. Default value will be taken.\n";
    bool ShowMsg = false;
    std::fill( std::begin( graphEquations ), std::end( graphEquations ), "" );

    for(int i = 0; i< this->ui->lstGraphFormulas->count(); i++)
    {
        graphEquations[i] = this->ui->lstGraphFormulas->item(i)->text().toStdString();
    }

    std::string txtXaxisName    = this->ui->txtXaxisName->toPlainText().toStdString();
    std::string txtYaxisName    = this->ui->txtYaxisName->toPlainText().toStdString();
    double txtXaxisRangeFrom    = this->ui->txtXaxisRangeFrom->toPlainText().toDouble();
    double txtXaxisRangeTo      = this->ui->txtXaxisRangeTo->toPlainText().toDouble();
    double txtYaxisRangeFrom    = this->ui->txtYaxisRangeFrom->toPlainText().toDouble();
    double txtYaxisRangeTo      = this->ui->txtYaxisRangeTo->toPlainText().toDouble();

    if(graphEquations[0] == "")
    {
        QMessageBox::critical(this,"Infinity Calculator", "Insert the a graph to be plotted to the list box.", QMessageBox::Ok);
        return;
    }

    if(graphEquations[16] != "")
    {
        QMessageBox::information(this,"Infinity Calculator", "Only 15 graphs will be shown in diffrent colors. Others will be in same color.", QMessageBox::Ok);
    }

    if(txtXaxisName == "")
    {
        txtXaxisName = "X Axis";
        InfoMessage +="\t> X Axis Name, Default 'X Axis'\n";
        ShowMsg = true;
    }

    if(txtYaxisName == "")
    {
        txtYaxisName = "Y Axis";
        InfoMessage +="\t> Y Axis Name, Default 'Y Axis'\n";
        ShowMsg = true;
    }

    if(this->ui->txtXaxisRangeFrom->toPlainText() == "")
    {
        txtXaxisRangeFrom = -10;
        InfoMessage +="\t> X Axis Start point, Default Value -10\n";
        ShowMsg = true;
    }

    if(this->ui->txtXaxisRangeTo->toPlainText() == "")
    {
        txtXaxisRangeTo = 20;
        InfoMessage +="\t> X Axis End point, Default Value 20\n";
        ShowMsg = true;
    }

    if(this->ui->txtYaxisRangeFrom->toPlainText() == "")
    {
        txtYaxisRangeFrom = -10;
        InfoMessage +="\t> Y Axis Start point, Default Value -10\n";
        ShowMsg = true;
    }

    if(this->ui->txtYaxisRangeTo->toPlainText() == "")
    {
        txtYaxisRangeTo = 20;
        InfoMessage +="\t> Y Axis End point, Default Value 20\n";
        ShowMsg = true;
    }

    if(txtXaxisRangeFrom > txtXaxisRangeTo)
    {
        QMessageBox::critical(this,"Infinity Calculator", "X axis starting point must be less than its ending point.", QMessageBox::Ok);
        return;
    }
    if(txtYaxisRangeFrom > txtYaxisRangeTo)
    {
        QMessageBox::critical(this,"Infinity Calculator", "Y axis starting point must be less than its ending point.", QMessageBox::Ok);
        return;
    }

    if(ShowMsg)
    {
        QMessageBox::information(this,"Infinity Calculator", InfoMessage, QMessageBox::Ok);
    }


    bool temp = graphViewer.intializeGraphs(graphEquations,
                                            txtXaxisName,
                                            txtYaxisName,
                                            txtXaxisRangeFrom,
                                            txtXaxisRangeTo,
                                            txtYaxisRangeFrom,
                                            txtYaxisRangeTo);
    if(temp)
    {
        graphViewer.setModal(true);
        graphViewer.exec();
    }

    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_pbCalAreaUndertheCurve_clicked()
{
    QModelIndexList selectedList = this->ui->lstGraphFormulas->selectionModel()->selectedRows();
    if (selectedList.size() > 0) {

        dlgCalAreaUnderCurve calAreaUnderCurve;

        calAreaUnderCurve.setGraphEquation(this->ui->lstGraphFormulas->currentItem()->text().toStdString());
        calAreaUnderCurve.setModal(true);
        calAreaUnderCurve.exec();
    }
    else
    {
        QMessageBox::critical(this,"Infinity Calculator","Please select a formula to load.", QMessageBox::Ok);
    }
    ui->pbPercentage->setEnabled(false);
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_lstScientificInMemory_doubleClicked(const QModelIndex &index)
{
    this->ButtonClickEventHandler(this->ui->lstScientificInMemory->currentItem()->text().toStdString(), 0);
}

void MainScreen::on_lstScientificFromFile_doubleClicked(const QModelIndex &index)
{
    this->ButtonClickEventHandler(this->ui->lstScientificFromFile->currentItem()->text().toStdString(), 0);
}

void MainScreen::on_lstGraphInMemory_doubleClicked(const QModelIndex &index)
{
    this->ButtonClickEventHandler(this->ui->lstGraphInMemory->currentItem()->text().toStdString(), 1);
}

void MainScreen::on_lstGraphFromFile_doubleClicked(const QModelIndex &index)
{
    this->ButtonClickEventHandler(this->ui->lstGraphFromFile->currentItem()->text().toStdString(), 1);
}

void MainScreen::on_lstGraphFormulas_clicked(const QModelIndex &index)
{
    ui->pbRemoveFormula->setEnabled(true);
    ui->pbCalAreaUndertheCurve->setEnabled(true);
}

void MainScreen::on_txtEquation_textChanged()
{
    if(ui->txtEquation->toPlainText()== "")
    {
        ui->pbAddGraphFormula->setEnabled(false);
    }
    else
    {
        ui->pbAddGraphFormula->setEnabled(true);
    }
}

// ----------------------------------------------------------------------------------------

void MainScreen::on_pbAboutUs_clicked()
{
    if(ui->frmAboutCalculator->isVisible())
    {
        ui->frmAboutCalculator->setVisible(false);
    }
    else
    {
        ui->frmAboutCalculator->setVisible(true);
    }
    ui->pbPercentage->setEnabled(false);
}

void MainScreen::on_tabMenu_currentChanged(int index)
{
    if((index == 0) || (index == 1) || (index == 2)){
        ui->frmAboutCalculator->setVisible(false);
    }
}



void MainScreen::on_txtTextEditor_textChanged()
{
    if(ui->txtTextEditor->toPlainText()== "")
    {
        ui->pbIntegration->setEnabled(false);
    }
    else
    {
        ui->pbIntegration->setEnabled(true);
    }
}
