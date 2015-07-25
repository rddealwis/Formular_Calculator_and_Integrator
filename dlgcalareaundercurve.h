#ifndef DLGCALAREAUNDERCURVE_H
#define DLGCALAREAUNDERCURVE_H

#include <QDialog>

namespace Ui {
class dlgCalAreaUnderCurve;
}

class dlgCalAreaUnderCurve : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCalAreaUnderCurve(QWidget *parent = 0);
    void addIntegrationVariables(std::string graphEquation);
    void setGraphEquation(std::string graphEquation);
    void findAreaUnderTheCurve(std::string graphEquation);

    ~dlgCalAreaUnderCurve();

private slots:
    void on_pbCalculate_clicked();

    void on_pbClose_clicked();

private:
    Ui::dlgCalAreaUnderCurve *ui;
};

#endif // DLGCALAREAUNDERCURVE_H
