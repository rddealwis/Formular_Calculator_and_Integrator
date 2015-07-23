#include "dlgcalareaundercurve.h"
#include "ui_dlgcalareaundercurve.h"

dlgCalAreaUnderCurve::dlgCalAreaUnderCurve(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCalAreaUnderCurve)
{
    ui->setupUi(this);
}

dlgCalAreaUnderCurve::~dlgCalAreaUnderCurve()
{
    delete ui;
}
