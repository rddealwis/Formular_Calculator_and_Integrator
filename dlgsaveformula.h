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
    std::string formula[1024];
    std::string formulaName[1024];
    ~dlgSaveFormula();

private slots:
    void on_pbBrowseSaveLoc_clicked();

    void on_btnBoxSubmit_clicked(QAbstractButton *button);

private:
    Ui::dlgSaveFormula *ui;
};

#endif // DLGSAVEFORMULA_H
