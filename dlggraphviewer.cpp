#include "dlggraphviewer.h"
#include "ui_dlggraphviewer.h"
#include "dlgsavegraph.h"
#include <math.h>

dlgGraphViewer::dlgGraphViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgGraphViewer)
{
    ui->setupUi(this);

    QVector<double> x(1440), y(1440),z(1440), p(1440);
            for (int i=0; i<1440; i++)
            {
              x[i] = i;
              y[i] = cos(i*(3.14159265) / 180);
              z[i] = sin(i*(3.14159265) / 180);
              p[i] = i^3+i^2-2*i+5;
            }



            ui->customPlot->legend->setVisible(true);

            /*ui->customPlot->addGraph();
            ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
            ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
            ui->customPlot->graph(0)->setData(x, y);
            ui->customPlot->graph(0)->setName("cos(X)");*/

            ui->customPlot->addGraph();
            ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
            ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
            ui->customPlot->graph(0)->setData(x, p);
            ui->customPlot->graph(0)->setName("x+1");


           /* ui->customPlot->addGraph();
            ui->customPlot->graph(1)->setPen(QPen(Qt::red));
            ui->customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
            ui->customPlot->graph(1)->setData(x, z);
            ui->customPlot->graph(1)->setName("sin(X)");*/

            ui->customPlot->xAxis->setRange(-1, 10);
            ui->customPlot->yAxis->setRange(-1, 10);
            ui->customPlot->xAxis->setLabel("Angle in degrees");
            ui->customPlot->yAxis->setLabel("Value");
            ui->customPlot->replot();
}

dlgGraphViewer::~dlgGraphViewer()
{
    delete ui;
}

void dlgGraphViewer::on_pbSaveGraph_clicked()
{
    dlgSaveGraph saveGraph;

    saveGraph.setModal(true);
    saveGraph.exec();
}

void dlgGraphViewer::on_pbClose_clicked()
{

}
