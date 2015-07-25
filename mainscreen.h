#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include "formulator.h"
#include <QMainWindow>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    int testVariable;
    std::string formula[1024];
    std::string formulaName[1024];
    std::string formulaOnMemory[1024];
    std::string formulaNameOnMemory[1024];
    std::string graphEquations[1024];
    std::string saveFormulaValue;    
    void LoadToListGraphFromFile();
    void LoadToListGraphInMemory();
    void LoadToListGraphScientificFromFile();
    void LoadToListGraphScientificInMemory();
    std::string formulaListTemp[1024];
    std::vector<FormulaElement*> formulaList;
    std::string filePath;
    ~MainScreen();

private slots:
    void ButtonClickEventHandler(std::string txt, int txtField);

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

    void on_pbAboutUs_clicked();

    void on_pbCE_clicked();

    void on_pbC_clicked();

    void on_pbDel_clicked();
    
    void on_pbSaveFormula_clicked();

    void on_pbLoadFormula_clicked();

    void on_pbLoadGraphFormula_clicked();

    void on_pbGenerate_clicked();

    void on_tabMenu_currentChanged(int index);

    void on_pbAddGraphFormula_clicked();

    void on_pbRemoveFormula_clicked();

    void on_lstScientificInMemory_doubleClicked(const QModelIndex &index);

    void on_lstScientificFromFile_doubleClicked(const QModelIndex &index);

    void on_lstGraphInMemory_doubleClicked(const QModelIndex &index);

    void on_lstGraphFromFile_doubleClicked(const QModelIndex &index);

    void on_pbCalAreaUndertheCurve_clicked();

    void on_pbModulus_clicked();

    void on_pbPlusOrMinus_clicked();

    void on_pbIntegration_clicked();

    void on_lstGraphFormulas_clicked(const QModelIndex &index);

    void on_txtEquation_textChanged();

    void on_pbPoweOfTen_clicked();

    void on_pbNthPower_clicked();

    double iter_factorial(double n);

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
