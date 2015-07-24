#include "dlggraphviewer.h"
#include "ui_dlggraphviewer.h"
#include "dlgsavegraph.h"
#include "exprtk.hpp"
#include <math.h>
#include "formulator.h"

dlgGraphViewer::dlgGraphViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgGraphViewer)
{
    ui->setupUi(this);


}

dlgGraphViewer::~dlgGraphViewer()
{
    delete ui;
}

bool dlgGraphViewer::intializeGraphs(std::string graphEquations[],FormulaElement* formulaList, std::string xAxisLabel,std::string yAxisLabel,
                                     double xAxisRangeFrom, double xAxisRangeTo, double yAxisRangeFrom, double yAxisRangeTo)
{
    try
    {
        QVector<double> x(1440), currentGraph(1440);
        std::vector<variableValue*> variableValues;
        formulaList->getVariableValues(&variableValues);
        float temp = 0;
        //QVector<QVector<double>> graphPoints;

        for (int i=0; i<1440; i++)
        {
            x[i] = i;

            currentGraph[i] = formulaList->evaluate();










            //currentGraph[i] = cos(i*(3.14159265) / 180);
            //currentGraph[i] = i*i + 4;
        }

        ui->customPlot->legend->setVisible(true);

        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
        ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
        ui->customPlot->graph(0)->setData(x, currentGraph);
        ui->customPlot->graph(0)->setName(QString::fromStdString(graphEquations[0]));

        ui->customPlot->xAxis->setRange(xAxisRangeFrom, xAxisRangeTo);
        ui->customPlot->yAxis->setRange(yAxisRangeFrom, yAxisRangeTo);
        ui->customPlot->xAxis->setLabel(QString::fromStdString(xAxisLabel));
        ui->customPlot->yAxis->setLabel(QString::fromStdString(yAxisLabel));
        ui->customPlot->replot();



        return true;
    }

    catch(...)
    {
        QMessageBox::critical(this,"Infinity Calculator","Unexpected error occurred when plotting the graph.", QMessageBox::Ok);
        return false;
    }
}

void dlgGraphViewer::on_pbSaveGraph_clicked()
{
    dlgSaveGraph saveGraph;

    saveGraph.setModal(true);
    saveGraph.exec();
}

void dlgGraphViewer::on_pbClose_clicked()
{
    this->close();
}
