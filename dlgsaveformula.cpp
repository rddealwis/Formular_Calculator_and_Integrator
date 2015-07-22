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

void CopyArray(std::string array1[], std::string array2[]);

void CopyArray(std::string array1[], std::string array2[])
{
    for(int i = 0; i < array1->length(); i++)
    {
        array2[i] = array1[i];
    }
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
    if(button ==this->ui->btnBoxSubmit->button(QDialogButtonBox::Save))
    {
        formulaName[formula->length()]=this->ui->txtFormulaName->toPlainText().toStdString();
        formula[formula->length()]=this->ui->txtFormula->toPlainText().toStdString();
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

void dlgSaveFormula::setCurrentMemory(std::string saveFormula, std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[])
{
    this->ui->txtFormula->setText(QString::fromStdString(saveFormula));
    CopyArray(p_formula, formula);
    CopyArray(p_formulaName, formulaName);
    CopyArray(p_formulaOnMemory, formulaOnMemory);
    CopyArray(p_formulaNameOnMemory, formulaNameOnMemory);

    for (unsigned j=0; j<formulaNameOnMemory->length();j++)
    {
    QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaNameOnMemory[j].c_str()));
    QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formulaOnMemory[j].c_str()));
    this->ui->tblCurrentFormulae->insertRow(j);
    this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
    this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);
    }

}

void dlgSaveFormula::getSavedEquations(std::string formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[])
{

}
