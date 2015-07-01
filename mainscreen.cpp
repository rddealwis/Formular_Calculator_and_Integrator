#include "mainscreen.h"
#include "ui_mainscreen.h"

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

void MainScreen::on_pbMultiply_clicked()
{
   ui->txtEditor->setText("*");
}

void MainScreen::on_pbZero_clicked()
{
   ui->txtEditor->setText("0");
}

void MainScreen::on_pbOne_clicked()
{
   ui->txtEditor->setText("1");
}

void MainScreen::on_pbTwo_clicked()
{
    ui->txtEditor->setText("2");
}

void MainScreen::on_pbThree_clicked()
{
    ui->txtEditor->setText("3");
}

void MainScreen::on_pbFour_clicked()
{
    ui->txtEditor->setText("4");
}

void MainScreen::on_pbFive_clicked()
{
    ui->txtEditor->setText("5");
}

void MainScreen::on_pbSix_clicked()
{
    ui->txtEditor->setText("6");
}

void MainScreen::on_pbSeven_clicked()
{
    ui->txtEditor->setText("7");
}

void MainScreen::on_pbEight_clicked()
{
    ui->txtEditor->setText("8");
}

void MainScreen::on_pbNine_clicked()
{
    ui->txtEditor->setText("9");
}

void MainScreen::on_pbDot_clicked()
{
    ui->txtEditor->setText(".");
}

void MainScreen::on_pbPlus_clicked()
{
    ui->txtEditor->setText("+");
}

void MainScreen::on_pbMinus_clicked()
{
    ui->txtEditor->setText("-");
}

void MainScreen::on_pbEqual_clicked()
{
    ui->txtEditor->setText("=");
}

void MainScreen::on_pbInverse_clicked()
{
    ui->txtEditor->setText("1/");
}

void MainScreen::on_pbPercentage_clicked()
{
    ui->txtEditor->setText("%");
}

void MainScreen::on_tabMenu_tabBarClicked(int index)
{

}
