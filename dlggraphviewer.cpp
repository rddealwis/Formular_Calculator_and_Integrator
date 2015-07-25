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
        double range = 1440;

        QVector<double> x(range), currentGraph(range);
        std::vector<variableValue*> variableValues;
        for(int j = 0; graphEquations[j] != ""; j++)
        {
            GraphsCordinates = "";
            double xAxis = xAxisRangeFrom;
            std::string formulaInput(graphEquations[j]);
            FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
            formula->getVariableValues(&variableValues);
            for (int i=0; i<range; i++)
            {
                x[i] = xAxis;
                variableValues[0]->value = xAxis;
                formula->setVariableValues(&variableValues);
                currentGraph[i] = (float)formula->evaluate();                

                if(x[i] < xAxisRangeTo)
                {
                    QString x1 = QString::number(xAxis);
                    QString y1 = QString::number(currentGraph[i]);
                    GraphsCordinates += x1 +  ", " + y1 + "\n ";
                }
                xAxis++;
            }
            GraphsData += QString::fromStdString(graphEquations[j]) + "\n\nX,Y\n " + GraphsCordinates + "\n\n";

            ui->customPlot->legend->setVisible(true);
            ui->customPlot->addGraph();

            switch(j)
            {
                case 0: ui->customPlot->graph(j)->setPen(QPen(Qt::red)); break;
                case 1: ui->customPlot->graph(j)->setPen(QPen(Qt::green)); break;
                case 2: ui->customPlot->graph(j)->setPen(QPen(Qt::blue));break;
                case 3: ui->customPlot->graph(j)->setPen(QPen(Qt::black));break;
                case 4: ui->customPlot->graph(j)->setPen(QPen(Qt::darkRed));break;
                case 5: ui->customPlot->graph(j)->setPen(QPen(Qt::darkGreen));break;
                case 6: ui->customPlot->graph(j)->setPen(QPen(Qt::darkBlue));break;
                case 7: ui->customPlot->graph(j)->setPen(QPen(Qt::cyan));break;
                case 8: ui->customPlot->graph(j)->setPen(QPen(Qt::magenta));break;
                case 9: ui->customPlot->graph(j)->setPen(QPen(Qt::yellow));break;
                case 10: ui->customPlot->graph(j)->setPen(QPen(Qt::gray));break;
                case 11: ui->customPlot->graph(j)->setPen(QPen(Qt::darkCyan));break;
                case 12: ui->customPlot->graph(j)->setPen(QPen(Qt::darkMagenta));break;
                case 13: ui->customPlot->graph(j)->setPen(QPen(Qt::darkYellow));break;
                case 14: ui->customPlot->graph(j)->setPen(QPen(Qt::darkGray));break;
                default: ui->customPlot->graph(j)->setPen(QPen(Qt::lightGray));
            }

           ui->customPlot->graph(j)->setData(x, currentGraph);
           ui->customPlot->graph(j)->setName(QString::fromStdString(graphEquations[j]));
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
    saveGraph.SetCurrentValues(this->GraphsData, this->ui->customPlot);
    saveGraph.setModal(true);
    saveGraph.exec();
}

void dlgGraphViewer::on_pbClose_clicked()
{
    this->close();
}
