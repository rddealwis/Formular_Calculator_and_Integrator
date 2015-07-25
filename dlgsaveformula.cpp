#include "dlgsaveformula.h"
#include "ui_dlgsaveformula.h"
#include "QFileDialog"
#include <sstream>
#include "QFile"
#include "QTextStream"

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
    for(int i = 0; array1[i] != ""; i++)
    {
        array2[i] = array1[i];
    }

}

void dlgSaveFormula::on_pbBrowseSaveLoc_clicked()
{
    XMLFileHandling obj1;
    QString temp = "<temp></temp>";
    filePath=QFileDialog::getSaveFileName(this, tr("Save File"), "/desktop", tr("XML Files (*.xml)"), new QString("XML Files (*.xml)")).toUtf8().constData();

    QFile file(QString::fromStdString(filePath));
    if(!file.exists())
    {
        if(file.open(QFile::WriteOnly |QFile::Truncate))
        {
            QTextStream stream(&file);
            stream <<temp;
        }
    }
    std::fill( std::begin( formulaName ), std::end( formulaName ), "" );
    std::fill( std::begin( formula ), std::end( formula ), "" );
    if(file.exists())
    {
        file.close();
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

            ui->txtSaveLocation->setText(QString::fromStdString(filePath));
        }
        else
        {
            QMessageBox::critical(this,"Infinity Calculator","Unexpected error occurred when accessing the specified file." + QString::fromStdString(filePath), QMessageBox::Ok);
        }
    }
    file.close();
}

void dlgSaveFormula::setCurrentMemory(std::string saveFormula, std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[], std::string p_filePath)
{
    this->ui->txtFormula->setText(QString::fromStdString(saveFormula));
    CopyArray(p_formula, formula);
    CopyArray(p_formulaName, formulaName);
    CopyArray(p_formulaOnMemory, formulaOnMemory);
    CopyArray(p_formulaNameOnMemory, formulaNameOnMemory);
    this->filePath = p_filePath;

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
    this->ui->txtSaveLocation->setText("");
    this->ui->tblCurrentFormulae->model()->removeRows(0, this->ui->tblCurrentFormulae->rowCount());
    for (int j=0; formulaNameOnMemory[j] != ""; j++)
    {
        QTableWidgetItem *formulaNameItem=new QTableWidgetItem(tr(formulaNameOnMemory[j].c_str()));
        QTableWidgetItem *formulaItem=new QTableWidgetItem(tr(formulaOnMemory[j].c_str()));

        this->ui->tblCurrentFormulae->insertRow(j);
        this->ui->tblCurrentFormulae->setItem(j,0,formulaNameItem);
        this->ui->tblCurrentFormulae->setItem(j,1,formulaItem);

        formulaNameItem->setFlags(formulaNameItem->flags() ^ Qt::ItemIsEditable);
        formulaItem->setFlags(formulaItem->flags() ^ Qt::ItemIsEditable);
    }

    this->ui->txtSaveLocation->setEnabled(false);
    this->ui->pbBrowseSaveLoc->setEnabled(false);
}

void dlgSaveFormula::on_rdToFile_clicked()
{
    this->ui->txtSaveLocation->setText(QString::fromStdString(this->filePath));
    this->ui->tblCurrentFormulae->model()->removeRows(0, this->ui->tblCurrentFormulae->rowCount());
    if( this->ui->tblCurrentFormulae->rowCount()<=0)
    {
        for (int j=0; formulaName[j] != "";j++)
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

    this->ui->txtSaveLocation->setEnabled(true);
    this->ui->pbBrowseSaveLoc->setEnabled(true);
}

int GetArraySize(std::string arr[]);
int GetArraySize(std::string arr[])
{
    int size = 0;
    for(size = 0; arr[size] != ""; size++)
    {}
    return size;

}

void dlgSaveFormula::on_pbSaveFormula_clicked()
{
    XMLFileHandling obj1;

    if((this->ui->txtFormulaName->toPlainText() == ""))
    {
        QMessageBox::critical(this,"Infinity Calculator","Please enter a formula name.", QMessageBox::Ok);
    }
    else if((this->ui->txtFormula->toPlainText() == ""))
    {
        QMessageBox::critical(this,"Infinity Calculator","Please enter a formula.", QMessageBox::Ok);
    }
    else
    {
        if(this->ui->rdToFile->isChecked())
        {
            if((this->ui->txtSaveLocation->toPlainText() == ""))
            {
                QMessageBox::critical(this,"Infinity Calculator","Please specify the save location.", QMessageBox::Ok);
            }
            else
            {
                location = GetArraySize(formula);
                this->formulaTemp = this->ui->txtFormula->toPlainText().toStdString();
                this->formulaNameTemp = this->ui->txtFormulaName->toPlainText().toStdString();

                if(this->ValidateFormulaName(formulaName))
                {

                    formulaName[location]= this->formulaNameTemp;
                    formula[location]= this->formulaTemp;

                    filePath=this->ui->txtSaveLocation->toPlainText().toStdString();

                    if(obj1.Write(filePath, formula,formulaName))
                    {
                        QMessageBox::information(this, "Infinity Calculator", "Formula is successfully saved to the file.", QMessageBox::Ok);
                        this->close();
                    }
                    else
                    {
                        QMessageBox::critical(this,"Infinity Calculator","Failed to open the file to write.", QMessageBox::Ok);
                    }
                }
            }
        }
        else
        {
            try
            {
                location = 0;
                while(true)
                {
                    if(formulaOnMemory[location] == "")
                    {
                        break;
                    }
                    location++;
                }

                location = GetArraySize(formulaNameOnMemory);
                this->formulaTemp = this->ui->txtFormula->toPlainText().toStdString();
                this->formulaNameTemp = this->ui->txtFormulaName->toPlainText().toStdString();

                if(this->ValidateFormulaName(formulaNameOnMemory))
                {
                    formulaNameOnMemory[location] = this->formulaNameTemp;
                    formulaOnMemory[location] = this->formulaTemp;
                    QMessageBox::information(this, "Infinity Calculator", "Formula is successfully saved to the memory.", QMessageBox::Ok);
                    this->close();
                }
            }
            catch(...)
            {
                QMessageBox::critical(this,"Infinity Calculator","Error occured when writing to the memory", QMessageBox::Ok);
            }
        }
    }
}

bool dlgSaveFormula::ValidateFormulaName(std::string arr[])
{
    for(int i = 0; arr[i] !=""; i++)
    {
        if(arr[i] == this->formulaNameTemp)
        {
            QMessageBox::StandardButton overideInfo = QMessageBox::question(this,"Infinity Calculator","Formula Name Exists. Overide the existing formula?", QMessageBox::Yes|QMessageBox::No);

            if(overideInfo == QMessageBox::Yes)
            {
                this->location = i;
                return true;
            }
            else
            {
                QMessageBox::information(this,"Infinity Calculator","Please specify a diffrent name for the formula.", QMessageBox::Ok);
                return false;
            }
        }
    }
    return true;
}

void dlgSaveFormula::on_pbClose_clicked()
{
    this->close();
}
