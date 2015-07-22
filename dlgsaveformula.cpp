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
    if(obj1.Read(filePath, formula, formulaName))
    {
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
    else
    {
        QMessageBox::critical(this,"Infinity Calculator","Unexpected error occurred when accessing the specified file.", QMessageBox::Ok);
    }
}

void dlgSaveFormula::on_btnBoxSubmit_clicked(QAbstractButton *button)
{
    XMLFileHandling obj1;
    std::string filePath;
    if(button ==this->ui->btnBoxSubmit->button(QDialogButtonBox::Save))
    {
        if(this->ui->rdToFile->isChecked())
        {
            formulaName[formula->length()]=this->ui->txtFormulaName->toPlainText().toStdString();
            formula[formula->length()]=this->ui->txtFormula->toPlainText().toStdString();
            filePath=this->ui->txtSaveLocation->toPlainText().toStdString();
            if(obj1.Write(filePath, formula,formulaName))
            {
                QMessageBox::information(this, "Infinity Calculator", "Formula is successfully saved to the file.", QMessageBox::Ok);
            }
            else
            {
                QMessageBox::critical(this,"Infinity Calculator","Failed to open the file to write.", QMessageBox::Ok);
            }
        }
        else
        {
            try
            {
                formulaNameOnMemory[formulaOnMemory->length()]=this->ui->txtFormulaName->toPlainText().toStdString();
                formulaOnMemory[formulaOnMemory->length()]=this->ui->txtFormula->toPlainText().toStdString();
                QMessageBox::information(this, "Infinity Calculator", "Formula is successfully saved to the memory.", QMessageBox::Ok);
            }

            catch(...)
            {
                QMessageBox::critical(this,"Infinity Calculator","Error occured when writing to the memory", QMessageBox::Ok);
            }

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
    this->ui->txtSaveLocation->setEnabled(false);
    this->ui->pbBrowseSaveLoc->setEnabled(false);
}

void dlgSaveFormula::getSavedEquations(std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[])
{
    CopyArray(formula, p_formula);
    CopyArray(formulaName, p_formulaName);
    CopyArray(formulaOnMemory,p_formulaOnMemory);
    CopyArray(formulaNameOnMemory, p_formulaNameOnMemory);
}

void dlgSaveFormula::on_rdToMemory_clicked()
{
    for (unsigned j=0; j<formulaNameOnMemory->length();j++)
    {
        QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaNameOnMemory[j].c_str()));
        QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formulaOnMemory[j].c_str()));
        this->ui->tblCurrentFormulae->insertRow(j);
        this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
        this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);
    }
    this->ui->txtSaveLocation->setEnabled(false);
    this->ui->pbBrowseSaveLoc->setEnabled(false);
}

void dlgSaveFormula::on_rdToFile_clicked()
{
    for (unsigned j=0; j<formulaName->length();j++)
    {
        QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaName[j].c_str()));
        QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formula[j].c_str()));
        this->ui->tblCurrentFormulae->insertRow(j);
        this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
        this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);
    }
    this->ui->txtSaveLocation->setEnabled(true);
    this->ui->pbBrowseSaveLoc->setEnabled(true);
}
