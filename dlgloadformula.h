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
    void setCurrentMemory(std::string p_formula[], std::string p_formulaName[]);
    std::string getSelectedEquation(std::string formula[], std::string formulaName[]);
    std::string selectFormula;
    std::string formula[1024];
    std::string formulaName[1024];
    ~dlgLoadFormula();

private slots:
    void on_pbBrowseFile_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::dlgLoadFormula *ui;
};

#endif // DLGLOADFORMULA_H
