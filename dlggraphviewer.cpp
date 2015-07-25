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

bool dlgGraphViewer::intializeGraphs(std::string graphEquations[], std::string xAxisLabel,std::string yAxisLabel,
                                     double xAxisRangeFrom, double xAxisRangeTo, double yAxisRangeFrom, double yAxisRangeTo)
{
    try
    {
        QVector<double> x(1440), currentGraph(1440);
        std::vector<variableValue*> variableValues;
        std::string input[] = {"x", "x+1", "x+2","-x", "x-1"};//, "-x+2","x^2", "x^2+1", "2x+2"};
        for(int j = 0; j < 5; j++)
        {
            //QMessageBox::critical(this,"Infinity Calculator","Graph: " + QString::fromStdString(input[j]), QMessageBox::Ok);
            std::string formulaInput(input[j]);
            FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
            formula->getVariableValues(&variableValues);
            for (int i=0; i<1440; i++)
            {
                x[i] = i;
                variableValues[0]->value = i;
                formula->setVariableValues(&variableValues);
                currentGraph[i] = formula->evaluate();
            }

            ui->customPlot->legend->setVisible(true);
            ui->customPlot->addGraph();
            ui->customPlot->graph(j)->setPen(QPen(Qt::blue));
            ui->customPlot->graph(j)->setBrush(QBrush(QColor(0, 0, 255, 20)));
            ui->customPlot->graph(j)->setData(x, currentGraph);
            ui->customPlot->graph(j)->setName(QString::fromStdString(input[j]));
        }

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
