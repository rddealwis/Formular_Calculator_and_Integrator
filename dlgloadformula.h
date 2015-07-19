#ifndef DLGLOADFORMULA_H
#define DLGLOADFORMULA_H
//#include "formulator.h"
#include "xmlfilehandling.h"
#include <QDialog>

namespace Ui {
class dlgLoadFormula;
}

class dlgLoadFormula : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLoadFormula(QWidget *parent = 0);
    QString text;
    ~dlgLoadFormula();

private slots:
    void on_pbBrowseFile_clicked();

    void on_pushButton_clicked();

private:
    Ui::dlgLoadFormula *ui;
};

#endif // DLGLOADFORMULA_H
