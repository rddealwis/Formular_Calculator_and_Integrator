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
        bool temp = false;
        QVector<double> x(range), currentGraph(range);
        for(int j = 0; graphEquations[j] != ""; j++)
        {
            GraphsCordinates = "";
            std::string formulaInput(graphEquations[j]);
            std::vector<variableValue*> variableValues;
            FormulaElement* formula = FormulaElement::parseFormula(formulaInput);
            formula->getVariableValues(&variableValues);

            if(variableValues.size() > 1)
            {
                QString msg ="Following types of graphs are not possible:\n\t> 3D graphs.\n\t> Log and ln graphs.\n\t> Complex graphs.";
                QMessageBox::critical(this,"Infinity Calculator", msg, QMessageBox::Ok);
                return false;
            }

            if(!temp)
            {
                std::string trig = "sin";
                temp = strstr(formulaInput.c_str(), trig.c_str());

                if(!temp)
                {
                    trig = "cos";
                    temp = strstr(formulaInput.c_str(), trig.c_str());
                }

                trig = "tan";
                if(strstr(formulaInput.c_str(), trig.c_str()))
                {
                    QMessageBox::critical(this,"Infinity Calculator","Trignometric graphs are supported only for Sine and Cosine.", QMessageBox::Ok);
                    return false;
                }

                if(temp)
                {
                    QMessageBox::StandardButton overideInfo = QMessageBox::question(this,"Infinity Calculator","One or more graph contains trignometric functions. Do you need to replace the range values with default values?", QMessageBox::Yes|QMessageBox::No);
                    if(overideInfo == QMessageBox::Yes)
                    {
                        xAxisRangeFrom = -360;
                        xAxisRangeTo   = 360;
                        yAxisRangeFrom = -1.2;
                        yAxisRangeTo   = 1.2;
                        QMessageBox::information(this,"Infinity Calculator","Default range values will were taken. Non Trignometric grpahs will be out of scale.", QMessageBox::Ok);
                    }
                    else
                    {
                        QMessageBox::information(this,"Infinity Calculator","Trignometric grpahs will be out of scale.", QMessageBox::Ok);
                    }
                }
            }
            double xAxis = xAxisRangeFrom;
            for (int i=0; i<range; i++)
            {
                x[i] = xAxis;
                if(variableValues.size() == 1)
                {
                    variableValues[0]->value = xAxis;
                    formula->setVariableValues(&variableValues);
                }
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
