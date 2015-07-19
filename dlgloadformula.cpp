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

void dlgLoadFormula::on_pbBrowseFile_clicked()
{
    XMLFileHandling obj1;
    std::string formula[1024];
    std::string formulaName[1024];
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

void dlgLoadFormula::on_pushButton_clicked()
{
    QModelIndexList selectedList = this->ui->tblCurrentFormulae->selectionModel()->selectedRows();
    text=this->ui->tblCurrentFormulae->item(selectedList.at(0).row(), 1)->text();
    QMessageBox::information(this,"", text);


}
