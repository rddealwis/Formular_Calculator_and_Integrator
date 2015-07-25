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

void CopyArrayL(std::string array1[], std::string array2[]);

void CopyArrayL(std::string array1[], std::string array2[])
{
    //QMessageBox::information(0, "Infinity Calculator", QString::number(array1->length()), QMessageBox::Ok);
    /*for(int i = 0; i <= array1->length(); i++)
    {
        array2[i] = array1[i];
    }*/
    for(int i = 0; array1[i]!=""; i++)
    {
        array2[i] = array1[i];
    }
}

void dlgLoadFormula::setCurrentMemory(std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[], std::string p_filePath)
{
    
    CopyArrayL(p_formula, formula);
    CopyArrayL(p_formulaName, formulaName);
    CopyArrayL(p_formulaOnMemory, formulaOnMemory);
    CopyArrayL(p_formulaNameOnMemory, formulaNameOnMemory);
    this->filePath = p_filePath;

    //Formulae in the RuntimeMemory will be populated to the table by default
    for (int j=0; formulaNameOnMemory[j] != "";j++)
    {
        QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaNameOnMemory[j].c_str()));
        QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formulaOnMemory[j].c_str()));

        this->ui->tblCurrentFormulae->insertRow(j);
        this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
        this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);

        formulaNameItem->setFlags(formulaNameItem->flags() ^ Qt::ItemIsEditable);
        formulaItem->setFlags(formulaItem->flags() ^ Qt::ItemIsEditable);
    }

    this->ui->txtFileLocation->setEnabled(false);
    this->ui->pbBrowseFile->setEnabled(false);

}

std::string dlgLoadFormula::getSelectedEquation(std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[])
{
    CopyArrayL(formula, p_formula);
    CopyArrayL(formulaName, p_formulaName);
    CopyArrayL(formulaOnMemory, p_formulaOnMemory);
    CopyArrayL(formulaNameOnMemory, p_formulaNameOnMemory);

    return selectFormula;
}

void dlgLoadFormula::on_pbBrowseFile_clicked()
{
    XMLFileHandling obj1;
    filePath=QFileDialog::getOpenFileName(this, tr("Open File"), "/desktop", tr("XML Files (*.xml)")).toUtf8().constData();
    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    if(obj1.Read(filePath, formula, formulaName))
    {
        this->ui->tblCurrentFormulae->setRowCount(0);

        for (unsigned j=0; formulaName[j]!="";j++)
        {
            QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaName[j].c_str()));
            QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formula[j].c_str()));

            this->ui->tblCurrentFormulae->insertRow(j);
            this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
            this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);

            formulaNameItem->setFlags(formulaNameItem->flags() ^ Qt::ItemIsEditable);
            formulaItem->setFlags(formulaItem->flags() ^ Qt::ItemIsEditable);
        }
        ui->txtFileLocation->setText(QString::fromStdString(filePath));
    }
    else
    {
        QMessageBox::critical(this,"Infinity Calculator","Unexpected error occurred when accessing the specified file.", QMessageBox::Ok);
    }
}

void dlgLoadFormula::on_rdFromMemory_clicked()
{
    this->ui->txtFileLocation->setText("");
    this->ui->tblCurrentFormulae->model()->removeRows(0, this->ui->tblCurrentFormulae->rowCount());
    for (int j=0; formulaNameOnMemory[j] != "";j++)
    {
        QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaNameOnMemory[j].c_str()));
        QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formulaOnMemory[j].c_str()));

        this->ui->tblCurrentFormulae->insertRow(j);
        this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
        this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);

        formulaNameItem->setFlags(formulaNameItem->flags() ^ Qt::ItemIsEditable);
        formulaItem->setFlags(formulaItem->flags() ^ Qt::ItemIsEditable);
    }

    this->ui->txtFileLocation->setEnabled(false);
    this->ui->pbBrowseFile->setEnabled(false);
}

void dlgLoadFormula::on_rdFromFile_clicked()
{
    this->ui->txtFileLocation->setText(QString::fromStdString(this->filePath));
    this->ui->tblCurrentFormulae->model()->removeRows(0, this->ui->tblCurrentFormulae->rowCount());
    if( this->ui->tblCurrentFormulae->rowCount()<=0)
    {
        for (int j=0; formulaName[j] !="";j++)
        {
            QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaName[j].c_str()));
            QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formula[j].c_str()));

            this->ui->tblCurrentFormulae->insertRow(j);
            this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
            this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);

            formulaNameItem->setFlags(formulaNameItem->flags() ^ Qt::ItemIsEditable);
            formulaItem->setFlags(formulaItem->flags() ^ Qt::ItemIsEditable);
        }
    }

    this->ui->txtFileLocation->setEnabled(true);
    this->ui->pbBrowseFile->setEnabled(true);
}

void dlgLoadFormula::on_pbLoadFormula_clicked()
{
    QModelIndexList selectedList = this->ui->tblCurrentFormulae->selectionModel()->selectedRows();

    if((this->ui->rdFromFile->isChecked())&&(this->ui->txtFileLocation->toPlainText() == ""))
    {
        QMessageBox::critical(this,"Infinity Calculator","Please specify the file location.", QMessageBox::Ok);
    }
    else if (selectedList.size() > 0) {

        selectFormula=this->ui->tblCurrentFormulae->item(selectedList.at(0).row(), 1)->text().toStdString();
        this->close();
    }
    else
    {
        QMessageBox::critical(this,"Infinity Calculator","Please select a formula to load.", QMessageBox::Ok);
    }
}

void dlgLoadFormula::on_pbClose_clicked()
{
    this->close();
}
