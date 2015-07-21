#include "dlgloadformula.h"
#include "ui_dlgloadformula.h"
#include "QFileDialog"
#include "xmlfilehandling.h"
#include <qmessagebox.h>

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

void CopyArray(std::string array1[], std::string array2[]);

void CopyArray(std::string array1[], std::string array2[])
{
    for(int i = 0; i < array1->length(); i++)
    {
        array2[i] = array1[i];
    }
}

void dlgLoadFormula::setCurrentMemory(std::string p_formula[], std::string p_formulaName[])
{
    /*int a1[] = {1,2,3};
    int a2[3];
    std::copy(std::begin(a1), std::end(a1), std::begin(a2));
    formula = p_Formula;
    formulaName = p_FormulaName;
    */
    //std::copy(std::begin(p_Formula), std::end(p_Formula), std::begin(formula));
    CopyArray(p_formula, formula);
    CopyArray(p_formulaName, formulaName);
    for (unsigned j=0; j<formulaName->length();j++)
    {
    QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaName[j].c_str()));
    QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formula[j].c_str()));
    this->ui->tblCurrentFormulae->insertRow(j);
    this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
    this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);
    }

}

std::string dlgLoadFormula::getSelectedEquation(std::string formula[], std::string formulaName[])
{
    //p_Formula = formula;
    //p_FormulaName = formulaName;
    return selectFormula;
}

void dlgLoadFormula::on_pbBrowseFile_clicked()
{
    XMLFileHandling obj1;
    std::string filePath=QFileDialog::getOpenFileName(this, tr("Open File"), "/desktop", tr("XML Files (*.xml)")).toUtf8().constData();
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


    ui->txtFileLocation->setText(QString::fromStdString(filePath));


}

void dlgLoadFormula::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == this->ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        QModelIndexList selectedList = this->ui->tblCurrentFormulae->selectionModel()->selectedRows();
        selectFormula=this->ui->tblCurrentFormulae->item(selectedList.at(0).row(), 1)->text().toStdString();
    }
}
