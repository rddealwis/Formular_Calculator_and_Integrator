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
    void ButtonClickEventHandler(std::string txt);

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

    void on_pbDivide_clicked();

    void on_pbSqRoot_clicked();

    void on_pbOpenBrackets_clicked();

    void on_pbCloseBrackets_clicked();

    void on_pbLog_clicked();

    void on_pbLn_clicked();

    void on_pbSin_clicked();

    void on_pbCos_clicked();

    void on_pbTan_clicked();

    void on_pbFactorial_clicked();


    void on_pbSquare_clicked();

    void on_pbPi_clicked();

    void on_pbPower_clicked();

    void on_pbOptions_clicked();

    void on_pbHelp_clicked();

    void on_pbAboutUs_clicked();

    void on_pbExit_clicked();

    void on_pbCE_clicked();

    void on_pbC_clicked();

    void on_pbDel_clicked();
    
    void on_pbSaveFormula_clicked();

    void on_pbLoadFormula_clicked();

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
