#include "dlgloadformula.h"
#include "ui_dlgloadformula.h"
#include "QFileDialog"

dlgLoadFormula::dlgLoadFormula(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLoadFormula)
{
    ui->setupUi(this);
}

dlgLoadFormula::~dlgLoadFormula()
{
    delete ui;
}

void dlgLoadFormula::on_pbBrowseFile_clicked()
{
    ui->txtFileLocation->setText(QFileDialog::getOpenFileName(this, tr("Open File"), "/desktop", tr("XML Files (*.xml)")));
}
