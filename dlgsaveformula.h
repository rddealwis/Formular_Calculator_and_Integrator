#ifndef DLGSAVEFORMULA_H
#define DLGSAVEFORMULA_H

#include <QDialog>

namespace Ui {
class dlgSaveFormula;
}

class dlgSaveFormula : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSaveFormula(QWidget *parent = 0);
    ~dlgSaveFormula();

private slots:
    void on_pbBrowseSaveLoc_clicked();

private:
    Ui::dlgSaveFormula *ui;
};

#endif // DLGSAVEFORMULA_H
