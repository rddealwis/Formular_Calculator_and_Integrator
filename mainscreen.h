#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();

private slots:
    void on_pbMultiply_clicked();

    void on_pbZero_clicked();

    void on_pbOne_clicked();

    void on_pbTwo_clicked();

    void on_pbThree_clicked();

    void on_pbFour_clicked();

    void on_pbFive_clicked();

    void on_pbSix_clicked();

    void on_pbSeven_clicked();

    void on_pbEight_clicked();

    void on_pbNine_clicked();

    void on_pbDot_clicked();

    void on_pbPlus_clicked();

    void on_pbMinus_clicked();

    void on_pbEqual_clicked();

    void on_pbInverse_clicked();

    void on_pbPercentage_clicked();

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
