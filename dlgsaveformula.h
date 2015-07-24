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
    void setCurrentMemory(std::string saveFormula, std::string p_formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[], std::string p_filePath);
    void getSavedEquations(std::string formula[], std::string p_formulaName[], std::string p_formulaOnMemory[], std::string p_formulaNameOnMemory[]);
    std::string selectFormula;
    std::string formula[1024];
    std::string formulaName[1024];
    std::string formulaOnMemory[1024];
    std::string formulaNameOnMemory[1024];
    std::string filePath;
    ~dlgSaveFormula();

private slots:
    void on_pbBrowseSaveLoc_clicked();

    void on_rdToMemory_clicked();

    void on_rdToFile_clicked();

    void on_pbSaveFormula_clicked();

    void on_pbClose_clicked();

private:
    Ui::dlgSaveFormula *ui;
};

#endif // DLGSAVEFORMULA_H
