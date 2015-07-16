#ifndef LOADFORMULA_H
#define LOADFORMULA_H

#include <QWidget>

namespace Ui {
class LoadFormula;
}

class LoadFormula : public QWidget
{
    Q_OBJECT

public:
    explicit LoadFormula(QWidget *parent = 0);
    ~LoadFormula();

private slots:
    void on_pbBrowseFile_clicked();

    void on_pbSave_clicked();

    void on_pbClose_clicked();

private:
    Ui::LoadFormula *ui;
};

#endif // LOADFORMULA_H
