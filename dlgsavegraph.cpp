#include "dlgsavegraph.h"
#include "ui_dlgsavegraph.h"
#include "QFileDialog"

dlgSaveGraph::dlgSaveGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSaveGraph)
{
    ui->setupUi(this);
}

dlgSaveGraph::~dlgSaveGraph()
{
    delete ui;
}

void dlgSaveGraph::on_pbBrowseGraphSaveLoc_clicked()
{
    filePath=QFileDialog::getSaveFileName(0,"Save file",QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"), new QString("Image files (*.png)"));
    ui->txtSaveLocation->setText(filePath);
}



void dlgSaveGraph::on_pbSaveGraph_clicked()
{
    this->GraphDetails->savePng(filePath,this->GraphDetails->geometry().width(),this->GraphDetails->geometry().height());
    filePath = QString::fromStdString(filePath.toStdString().substr(0, filePath.toStdString().find_last_of(".")));
    filePath +=".csv";
    QFile file(filePath);
    if(file.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream stream(&file);
        stream << this->GraphsData;
    }
    QMessageBox::information(this,"Infinity Calculator","Image file and a .csv file of the graph is saved successfully", QMessageBox::Ok);
    this->close();
}

void dlgSaveGraph::on_pbClose_clicked()
{
    this->close();
}


void dlgSaveGraph::SetCurrentValues(QString p_GraphsData, QCustomPlot *p_GraphDetails)
{
    this->GraphsData = p_GraphsData;
    this->GraphDetails = p_GraphDetails;
}
