#include "loadformula.h"
#include "ui_loadformula.h"
#include <QFileDialog>

LoadFormula::LoadFormula(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadFormula)
{
    ui->setupUi(this);
    ui->tblCurrentFormulae->setColumnWidth(0,250);
}

LoadFormula::~LoadFormula()
{
    delete ui;
}

void LoadFormula::on_pbBrowseFile_clicked()
{
    ui->txtFileLocation->setText(QFileDialog::getOpenFileName(this, tr("Open File"), "/desktop", tr("XML Files (*.xml)")));
}

void LoadFormula::on_pbSave_clicked()
{

}

void LoadFormula::on_pbClose_clicked()
{
    this->close();
}
