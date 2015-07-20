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
    //ui->txtSaveLocation->setText(QFileDialog::getOpenFileName(this, tr("Save File"), "/desktop", tr("XML Files (*.xml)")));
    XMLFileHandling obj1;
    std::string filePath=QFileDialog::getOpenFileName(this, tr("Save File"), "/desktop", tr("XML Files (*.xml)")).toUtf8().constData();
    obj1.Read(filePath, formula, formulaName);

    this->ui->tblCurrentFormulae->setRowCount(0);
    for (unsigned j=0; j<formulaName->length();j++)
    {
    QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaName[j].c_str()));
    QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formula[j].c_str()));
    this->ui->tblCurrentFormulae->insertRow(j);
    this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
    this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);
    }


    ui->txtSaveLocation->setText(QString::fromStdString(filePath));

}

void dlgSaveFormula::on_btnBoxSubmit_clicked(QAbstractButton *button)
{
    XMLFileHandling obj1;
    std::string filePath;
    if(button ==this->ui->btnBoxSubmit->button(QDialogButtonBox::Ok))
    {
        formulaName[formula->length()+1]=this->ui->txtFormulaName->toPlainText().toStdString();
        formula[formula->length()+1]=this->ui->txtFormula->toPlainText().toStdString();
        filePath=this->ui->txtSaveLocation->toPlainText().toStdString();
        if(obj1.Write(filePath, formula,formulaName))
        {
            QMessageBox saveSuccess;
            saveSuccess.setText("Successfully Saved.");
            saveSuccess.setInformativeText("Formula is successfully saved to the file.");
            saveSuccess.setStandardButtons(QMessageBox::Ok);
            saveSuccess.setDefaultButton(QMessageBox::Ok);
            int ret = saveSuccess.exec();
        }
    }


}
