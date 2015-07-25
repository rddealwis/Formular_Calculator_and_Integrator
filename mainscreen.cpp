#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "formulator.h"
#include "dlgloadformula.h"
#include "dlgsaveformula.h"
#include "dlgsavegraph.h"
#include "dlggraphviewer.h"
#include "dlgcalareaundercurve.h"
#include <qmessagebox.h>
#include <qframe.h>
#include <QInputDialog>
#include <QDir>


MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    ui->frmAboutCalculator->setVisible(false);
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

void MainScreen::on_pbMultiply_clicked()
{
    this->ButtonClickEventHandler("*", 0);
}

void MainScreen::on_pbZero_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0"){
        this->ButtonClickEventHandler("0", 0);
    }
}

void MainScreen::on_pbOne_clicked()
{
   this->ButtonClickEventHandler("1", 0);
}

void MainScreen::on_pbTwo_clicked()
{
    this->ButtonClickEventHandler("2", 0);
}

void MainScreen::on_pbThree_clicked()
{
    this->ButtonClickEventHandler("3", 0);
}

void MainScreen::on_pbFour_clicked()
{
    this->ButtonClickEventHandler("4", 0);
}

void MainScreen::on_pbFive_clicked()
{
    this->ButtonClickEventHandler("5", 0);
}

void MainScreen::on_pbSix_clicked()
{
    this->ButtonClickEventHandler("6", 0);
}

void MainScreen::on_pbSeven_clicked()
{
    this->ButtonClickEventHandler("7", 0);
}

void MainScreen::on_pbEight_clicked()
{
    this->ButtonClickEventHandler("8", 0);
}

void MainScreen::on_pbNine_clicked()
{
    this->ButtonClickEventHandler("9", 0);
}

void MainScreen::on_pbDot_clicked()
{
    this->ButtonClickEventHandler(".", 0);
}

void MainScreen::on_pbPlus_clicked()
{
    this->ButtonClickEventHandler("+", 0);
}

void MainScreen::on_pbMinus_clicked()
{
    this->ButtonClickEventHandler("-", 0);
}

void MainScreen::on_pbEqual_clicked()
{
    std::vector<variableValue*> variableValues;

    std::string input = this->ui->txtTextEditor->toPlainText().toStdString();
    std::string formulaInput(input);
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
}

void MainScreen::on_pbInverse_clicked()
{
    QTextCursor prev_cursor = ui->txtTextEditor->textCursor();
    ui->txtTextEditor->moveCursor(QTextCursor::End);

    ui->txtTextEditor->setText("1/("+ ui->txtTextEditor->toPlainText()+")");
    ui->txtTextEditor->setTextCursor(prev_cursor);
}

void MainScreen::on_pbPercentage_clicked()
{
    this->ButtonClickEventHandler("%", 0);
}

void MainScreen::on_pbDivide_clicked()
{
    this->ButtonClickEventHandler("/", 0);
}

void MainScreen::on_pbSqRoot_clicked()
{
    this->ButtonClickEventHandler("sqrt(", 0);
}

void MainScreen::on_pbOpenBrackets_clicked()
{
    this->ButtonClickEventHandler("(", 0);
}

void MainScreen::on_pbCloseBrackets_clicked()
{
    this->ButtonClickEventHandler(")", 0);
}

void MainScreen::on_pbLog_clicked()
{
    this->ButtonClickEventHandler("log(", 0);
}

void MainScreen::on_pbLn_clicked()
{
    this->ButtonClickEventHandler("ln(", 0);
}

void MainScreen::on_pbSin_clicked()
{
    this->ButtonClickEventHandler("sin(", 0);
}

void MainScreen::on_pbCos_clicked()
{
    this->ButtonClickEventHandler("cos(", 0);
}

void MainScreen::on_pbTan_clicked()
{
    this->ButtonClickEventHandler("Tan(", 0);
}

void MainScreen::on_pbFactorial_clicked()
{
    this->ButtonClickEventHandler("!", 0);
}


void MainScreen::on_pbSquare_clicked()
{
    this->ButtonClickEventHandler("^2", 0);
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
}

void MainScreen::on_pbPower_clicked()
{
    this->ButtonClickEventHandler("^", 0);
}

void MainScreen::on_pbModulus_clicked()
{
    this->ButtonClickEventHandler("mod", 0);
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
}

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
}

void MainScreen::on_pbCE_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        if(!ui->txtTextEditor->toPlainText().isEmpty())
        {
            ui->txtTextEditor->textCursor().deletePreviousChar();
        }
    }
    ui->txtResultsEditor->clear();
}

void MainScreen::on_pbC_clicked()
{
    ui->txtTextEditor->clear();
    ui->txtResultsEditor->clear();
}

void MainScreen::on_pbDel_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        if(!ui->txtTextEditor->toPlainText().isEmpty())
        {
            ui->txtTextEditor->textCursor().deletePreviousChar();
        }
    }
    ui->txtResultsEditor->clear();
}

void MainScreen::on_pbSaveFormula_clicked()
{
    dlgSaveFormula saveFormula;
    saveFormulaValue = this->ui->txtTextEditor->toPlainText().toStdString();
    saveFormula.setCurrentMemory(saveFormulaValue, formula, formulaName, formulaOnMemory, formulaNameOnMemory, this->filePath);
    saveFormula.setModal(true);
    saveFormula.exec();
    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    std::fill( std::begin( formulaOnMemory ), std::end( formulaOnMemory ), "" );
    std::fill( std::begin( formulaNameOnMemory ), std::end( formulaNameOnMemory ), "" );
    this->ui->lstScientificFromFile->clear();
    this->filePath = saveFormula.filePath;
    saveFormula.getSavedEquations(formula,formulaName, formulaOnMemory, formulaNameOnMemory);
    this->LoadToListGraphFromFile();
    this->LoadToListGraphInMemory();
    this->LoadToListGraphScientificFromFile();
    this->LoadToListGraphScientificInMemory();
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
}

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
}

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



void MainScreen::on_pbAddGraphFormula_clicked()
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(this->ui->txtEquation->toPlainText());
    int row = this->ui->lstGraphFormulas->row(this->ui->lstGraphFormulas->currentItem());
    this->ui->lstGraphFormulas->insertItem(row, newItem);
}

void MainScreen::on_pbGenerate_clicked()
{
    dlgGraphViewer graphViewer;

//    QMessageBox::critical(this,"Infinity Calculator",this->ui->lstGraphFormulas->item(0)->text(), QMessageBox::Ok);
//    for(int i = 0; i< 1/*this->ui->lstGraphInMemory->count()*/; i++)
//    {
//        formulaListTemp[i] = this->ui->lstGraphFormulas->currentItem()->text().toStdString();
//        FormulaElement* formula  = FormulaElement::parseFormula(formulaListTemp[i]);
//        formulaList.push_back(formula);// = formula;
//    }

//    FormulaElement *test = formulaList[this->ui->lstGraphFormulas->count()];


    graphViewer.intializeGraphs(graphEquations,
                                this->ui->txtXaxisName->toPlainText().toStdString(),
                                this->ui->txtYaxisName->toPlainText().toStdString(),
                                (this->ui->txtXaxisRangeFrom->toPlainText()).toDouble(),
                                (this->ui->txtXaxisRangeTo->toPlainText()).toDouble(),
                                (this->ui->txtYaxisRangeFrom->toPlainText()).toDouble(),
                                (this->ui->txtYaxisRangeTo->toPlainText()).toDouble());

    graphViewer.setModal(true);
    graphViewer.exec();
}

void MainScreen::on_tabMenu_currentChanged(int index)
{
    if((index == 0) || (index == 1) || (index == 2)){
        ui->frmAboutCalculator->setVisible(false);
    }
}


void MainScreen::on_pbRemoveFormula_clicked()
{
    this->ui->lstGraphFormulas->takeItem(this->ui->lstGraphFormulas->row(this->ui->lstGraphFormulas->currentItem()));
}

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


void MainScreen::on_pbCalAreaUndertheCurve_clicked()
{
    dlgCalAreaUnderCurve calAreaUnderCurve;

    calAreaUnderCurve.setGraphEquation(this->ui->lstGraphFormulas->currentItem()->text().toStdString());
    calAreaUnderCurve.setModal(true);
    calAreaUnderCurve.exec();
}




