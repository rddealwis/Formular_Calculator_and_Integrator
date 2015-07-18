#ifndef DLGLOADFORMULA_H
#define DLGLOADFORMULA_H

#include <QDialog>

namespace Ui {
class dlgLoadFormula;
}

class dlgLoadFormula : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLoadFormula(QWidget *parent = 0);
    ~dlgLoadFormula();

private slots:
    void on_pbBrowseFile_clicked();

private:
    Ui::dlgLoadFormula *ui;
};

#endif // DLGLOADFORMULA_H
