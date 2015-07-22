#ifndef DLGSAVEFORMULA_H
#define DLGSAVEFORMULA_H
#include "xmlfilehandling.h"
#include <QDialog>

namespace Ui {
class dlgSaveFormula;
}

class dlgSaveFormula : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSaveFormula(QWidget *parent = 0);
    void setCurrentMemory(std::string saveFormula, std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[]);
    void getSavedEquations(std::string formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[]);
    std::string selectFormula;
    std::string formula[1024];
    std::string formulaName[1024];
    std::string formulaOnMemory[1024];
    std::string formulaNameOnMemory[1024];
    ~dlgSaveFormula();

private slots:
    void on_pbBrowseSaveLoc_clicked();

    void on_btnBoxSubmit_clicked(QAbstractButton *button);

private:
    Ui::dlgSaveFormula *ui;
};

#endif // DLGSAVEFORMULA_H
