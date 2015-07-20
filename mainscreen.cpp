#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "aboutcalculator.h"
#include "formulator.h"
#include "dlgloadformula.h"
#include "dlgsaveformula.h"
#include <qmessagebox.h>
#include <qframe.h>

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

void MainScreen::ButtonClickEventHandler(std::string txt)
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

void MainScreen::on_pbMultiply_clicked()
{
    this->ButtonClickEventHandler("*");
}

void MainScreen::on_pbZero_clicked()
{
   this->ButtonClickEventHandler("0");
}

void MainScreen::on_pbOne_clicked()
{
   this->ButtonClickEventHandler("1");
}

void MainScreen::on_pbTwo_clicked()
{
    this->ButtonClickEventHandler("2");
}

void MainScreen::on_pbThree_clicked()
{
    this->ButtonClickEventHandler("3");
}

void MainScreen::on_pbFour_clicked()
{
    this->ButtonClickEventHandler("4");
}

void MainScreen::on_pbFive_clicked()
{
    this->ButtonClickEventHandler("5");
}

void MainScreen::on_pbSix_clicked()
{
    this->ButtonClickEventHandler("6");
}

void MainScreen::on_pbSeven_clicked()
{
    this->ButtonClickEventHandler("7");
}

void MainScreen::on_pbEight_clicked()
{
    this->ButtonClickEventHandler("8");
}

void MainScreen::on_pbNine_clicked()
{
    this->ButtonClickEventHandler("9");
}

void MainScreen::on_pbDot_clicked()
{
    this->ButtonClickEventHandler(".");
}

void MainScreen::on_pbPlus_clicked()
{
    this->ButtonClickEventHandler("+");
}

void MainScreen::on_pbMinus_clicked()
{
    this->ButtonClickEventHandler("-");
}

void MainScreen::on_pbEqual_clicked()
{
    std::string input=this->ui->txtTextEditor->toPlainText().toStdString();
    std::string formulaInput(input);
    FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
    //this->ui->txtTextEditor->setText(QString::fromStdString(formula->toQString().data()));
    this->ui->txtResultsEditor->setText(QString::number(formula->evaluate()));
}

void MainScreen::on_pbInverse_clicked()
{
    this->ButtonClickEventHandler("1/");
}

void MainScreen::on_pbPercentage_clicked()
{
    this->ButtonClickEventHandler("%");
}


void MainScreen::on_pbDivide_clicked()
{
    this->ButtonClickEventHandler("/");
}

void MainScreen::on_pbSqRoot_clicked()
{
    this->ButtonClickEventHandler("sqrt(");
}

void MainScreen::on_pbOpenBrackets_clicked()
{
    this->ButtonClickEventHandler("(");
}

void MainScreen::on_pbCloseBrackets_clicked()
{
    this->ButtonClickEventHandler(")");
}

void MainScreen::on_pbLog_clicked()
{
    this->ButtonClickEventHandler("log(");
}

void MainScreen::on_pbLn_clicked()
{
    this->ButtonClickEventHandler("ln(");
}

void MainScreen::on_pbSin_clicked()
{
    this->ButtonClickEventHandler("sin(");
}

void MainScreen::on_pbCos_clicked()
{
    this->ButtonClickEventHandler("cos(");
}

void MainScreen::on_pbTan_clicked()
{
    this->ButtonClickEventHandler("Tan(");
}

void MainScreen::on_pbFactorial_clicked()
{
    this->ButtonClickEventHandler("!");
}


void MainScreen::on_pbSquare_clicked()
{
    this->ButtonClickEventHandler("^2");
}

void MainScreen::on_pbPi_clicked()
{
    if(sizeof(ui->txtTextEditor->size())>2)
    {
        this->ButtonClickEventHandler("3.1416");
    }
    else
    {
        this->ButtonClickEventHandler("3.1415926535897932384626433832795");
    }
}

void MainScreen::on_pbPower_clicked()
{
    this->ButtonClickEventHandler("^");
}

void MainScreen::on_pbOptions_clicked()
{
    ui->frmAboutCalculator->setVisible(false);
}

void MainScreen::on_pbHelp_clicked()
{
    ui->frmAboutCalculator->setVisible(false);
}

void MainScreen::on_pbAboutUs_clicked()
{
    ui->frmAboutCalculator->setVisible(true);
}

void MainScreen::on_pbExit_clicked()
{

}

void MainScreen::on_pbCE_clicked()
{
    ui->txtTextEditor->clear();
    ui->txtTextEditor->setText("0");
}

void MainScreen::on_pbC_clicked()
{
    ui->txtTextEditor->clear();
    ui->txtTextEditor->setText("0");
}

void MainScreen::on_pbDel_clicked()
{
    if(ui->txtTextEditor->toPlainText()!= "0")
    {
        while(!ui->txtTextEditor->toPlainText().isEmpty())
        {
            ui->txtTextEditor->textCursor().deletePreviousChar();
//            QTextCursor prev_cursor = ui->txtTextEditor->textCursor();
//            ui->txtTextEditor->moveCursor(QTextCursor::End);
//            //ui->txtTextEditor->insertPlainText(QString::fromStdString(txt));
//            ui->txtTextEditor->setTextCursor(prev_cursor);
        }
    }
}

void MainScreen::on_pbSaveFormula_clicked()
{
    dlgSaveFormula saveFormula;

    saveFormula.setModal(true);
    saveFormula.exec();
}

void MainScreen::on_pbLoadFormula_clicked()
{
    dlgLoadFormula loadFormula;

    loadFormula.setModal(true);
    loadFormula.exec();
}
