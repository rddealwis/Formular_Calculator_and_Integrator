#ifndef ABOUTCALCULATOR_H
#define ABOUTCALCULATOR_H

#include <QWidget>

namespace Ui {
class aboutcalculator;
}

class aboutcalculator : public QWidget
{
    Q_OBJECT

public:
    explicit aboutcalculator(QWidget *parent = 0);
    ~aboutcalculator();

private:
    Ui::aboutcalculator *ui;
};

#endif // ABOUTCALCULATOR_H
