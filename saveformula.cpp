#include "saveformula.h"
#include "ui_saveformula.h"

SaveFormula::SaveFormula(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveFormula)
{
    ui->setupUi(this);
    ui->tblCurrentFormulae->setColumnWidth(0,250);
}

SaveFormula::~SaveFormula()
{
    delete ui;
}

void SaveFormula::on_pbBrowseSaveLoc_clicked()
{
    ui->txtSaveLocation->setText(QFileDialog::getOpenFileName(this, tr("Save File"), "/desktop", tr("XML Files (*.xml)")));
}

void SaveFormula::on_pbSave_clicked()
{

}

void SaveFormula::on_pbClose_clicked()
{
    this->close();
}
