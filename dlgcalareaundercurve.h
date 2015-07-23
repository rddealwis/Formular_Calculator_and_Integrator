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
    ~dlgCalAreaUnderCurve();

private:
    Ui::dlgCalAreaUnderCurve *ui;
};

#endif // DLGCALAREAUNDERCURVE_H
