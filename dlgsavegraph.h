#ifndef DLGSAVEGRAPH_H
#define DLGSAVEGRAPH_H

#include <QDialog>

namespace Ui {
class dlgSaveGraph;
}

class dlgSaveGraph : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSaveGraph(QWidget *parent = 0);
    ~dlgSaveGraph();

private slots:
    void on_pbBrowseGraphSaveLoc_clicked();

    void on_pbSaveGraph_clicked();

    void on_pbClose_clicked();

private:
    Ui::dlgSaveGraph *ui;
};

#endif // DLGSAVEGRAPH_H
