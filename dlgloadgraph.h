#ifndef DLGLOADGRAPH_H
#define DLGLOADGRAPH_H

#include <QDialog>

namespace Ui {
class dlgLoadGraph;
}

class dlgLoadGraph : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLoadGraph(QWidget *parent = 0);
    ~dlgLoadGraph();

private:
    Ui::dlgLoadGraph *ui;
};

#endif // DLGLOADGRAPH_H
