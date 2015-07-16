#ifndef SAVEFORMULA_H
#define SAVEFORMULA_H

#include <QWidget>

namespace Ui {
class SaveFormula;
}

class SaveFormula : public QWidget
{
    Q_OBJECT

public:
    explicit SaveFormula(QWidget *parent = 0);
    ~SaveFormula();

private slots:
    void on_pbBrowseSaveLoc_clicked();

    void on_pbSave_clicked();

    void on_pbClose_clicked();

private:
    Ui::SaveFormula *ui;
};

#endif // SAVEFORMULA_H
