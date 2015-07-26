#ifndef DLGINTEGRATION_H
#define DLGINTEGRATION_H

#include <QDialog>

namespace Ui {
class dlgIntegration;
}

class dlgIntegration : public QDialog
{
    Q_OBJECT

public:
    explicit dlgIntegration(QWidget *parent = 0);
    double calculatedArea =0;
    ~dlgIntegration();
    void addIntegrationVariables(std::string graphEquation);
    void setIntegrationEquation(std::string graphEquation);
    double findAreaUnderTheCurve(std::string graphEquation);

private slots:
    void on_pbOk_clicked();

    void on_pbClose_clicked();

private:
    Ui::dlgIntegration *ui;
};

#endif // DLGINTEGRATION_H
