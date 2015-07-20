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
    ui->txtSaveLocation->setText(QFileDialog::getOpenFileName(this, tr("Save Graph"), "/desktop", tr("Image Files (*.png *.jpg *.bmp)")));
}
