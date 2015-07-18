#include "dlgsaveformula.h"
#include "ui_dlgsaveformula.h"
#include "QFileDialog"

dlgSaveFormula::dlgSaveFormula(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSaveFormula)
{
    ui->setupUi(this);
}

dlgSaveFormula::~dlgSaveFormula()
{
    delete ui;
}

void dlgSaveFormula::on_pbBrowseSaveLoc_clicked()
{
    ui->txtSaveLocation->setText(QFileDialog::getOpenFileName(this, tr("Save File"), "/desktop", tr("XML Files (*.xml)")));
}
