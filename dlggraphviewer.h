#ifndef DLGGRAPHVIEWER_H
#define DLGGRAPHVIEWER_H

#include <QDialog>

namespace Ui {
class dlgGraphViewer;
}

class dlgGraphViewer : public QDialog
{
    Q_OBJECT

public:
    explicit dlgGraphViewer(QWidget *parent = 0);
    ~dlgGraphViewer();

private slots:
    void on_pbSaveGraph_clicked();

    void on_pbClose_clicked();

private:
    Ui::dlgGraphViewer *ui;
};

#endif // DLGGRAPHVIEWER_H
