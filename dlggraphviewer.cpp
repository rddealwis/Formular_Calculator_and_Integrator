#include "dlggraphviewer.h"
#include "ui_dlggraphviewer.h"
#include "dlgsavegraph.h"
#include "exprtk.hpp"
#include <math.h>

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

        QVector<QVector<double>> graphPoints;

        for (int i=0; i<1440; i++)
        {
            x[i] = i;
            //currentGraph[i] = cos(i*(3.14159265) / 180);
            currentGraph[i] = i*i + 4;
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

        ui->textEdit->setText(QString::number(findAreaUnderTheCurve(graphEquations)));

        return true;
    }

    catch(...)
    {
        QMessageBox::critical(this,"Infinity Calculator","Unexpected error occurred when plotting the graph.", QMessageBox::Ok);
        return false;
    }
}

double dlgGraphViewer::findAreaUnderTheCurve(std::string graphEquations[]){

    exprtk::parser<double> parser;
    exprtk::expression<double> expression;
    exprtk::symbol_table<double> symbol_table;

    double t1 = 0;
    double t2 = 3.1415992;
    double temp = 0;

    std::string expression_string = "abs(sin(X))";
    symbol_table.add_variable("X",temp);
    symbol_table.add_variable("Y",temp);

    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string,expression);

    return exprtk::integrate(expression,"X",t1,t2);
    //return 0;
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
