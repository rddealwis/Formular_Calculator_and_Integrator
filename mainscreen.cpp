#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "help.h"
#include <qmessagebox.h>

MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::ButtonClickEventHandler(std::string txt)
{
    if(ui->txtResultsEditor->toPlainText()!= "0")
    {
        QTextCursor prev_cursor = ui->txtResultsEditor->textCursor();
        ui->txtResultsEditor->moveCursor(QTextCursor::End);
        ui->txtResultsEditor->insertPlainText(QString::fromStdString(txt));
        ui->txtResultsEditor->setTextCursor(prev_cursor);
    }
    else
    {
        ui->txtResultsEditor->clear();
        QTextCursor prev_cursor = ui->txtResultsEditor->textCursor();
        ui->txtResultsEditor->moveCursor(QTextCursor::End);
        ui->txtResultsEditor->insertPlainText(QString::fromStdString(txt));
        ui->txtResultsEditor->setTextCursor(prev_cursor);
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
    this->ButtonClickEventHandler("=");
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
    this->ButtonClickEventHandler("Sin(");
}

void MainScreen::on_pbCos_clicked()
{
    this->ButtonClickEventHandler("Cos(");
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
    if(sizeof(ui->txtResultsEditor->size())>2)
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

}

void MainScreen::on_pbHelp_clicked()
{
    helpForm = new help(this);
    helpForm->show();
}

void MainScreen::on_pbAboutUs_clicked()
{

}

void MainScreen::on_pbExit_clicked()
{

}

void MainScreen::on_pbCE_clicked()
{
    ui->txtResultsEditor->clear();
    ui->txtResultsEditor->setText("0");
}

void MainScreen::on_pbC_clicked()
{
    ui->txtResultsEditor->clear();
    ui->txtResultsEditor->setText("0");
}

void MainScreen::on_pbDel_clicked()
{
    if(ui->txtResultsEditor->toPlainText()!= "0")
    {
        while(!ui->txtResultsEditor->toPlainText().isEmpty())
        {
            ui->txtResultsEditor->textCursor().deletePreviousChar();
//            QTextCursor prev_cursor = ui->txtResultsEditor->textCursor();
//            ui->txtResultsEditor->moveCursor(QTextCursor::End);
//            //ui->txtResultsEditor->insertPlainText(QString::fromStdString(txt));
//            ui->txtResultsEditor->setTextCursor(prev_cursor);
        }
    }
}
