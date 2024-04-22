#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loandetails.h"
#include "loans.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loanType_currentIndexChanged(int index);

    void on_paymentFrequency_currentIndexChanged(int index);

    void on_btnGetLoan_clicked();

    void on_creditScoreSlider_valueChanged(int value);

    void on_loanTermSlider_valueChanged(int value);

    void on_loanAmountSlider_valueChanged(int value);

    void showMainWindow();

private:
    Ui::MainWindow *ui;
    LoanDetails *loanDetailsWindow;
};
#endif // MAINWINDOW_H
