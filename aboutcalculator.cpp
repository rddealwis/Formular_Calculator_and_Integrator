#include "aboutcalculator.h"
#include "ui_aboutcalculator.h"

aboutcalculator::aboutcalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutcalculator)
{
    ui->setupUi(this);
}

aboutcalculator::~aboutcalculator()
{
    delete ui;
}
