#ifndef LOANDETAILS_H
#define LOANDETAILS_H

#include <QWidget>
#include <QTableWidget>
#include <QtCore>
#include <QtGui>
#include <QtCharts>
#include "loans.h"

namespace Ui {
class LoanDetails;
}

class LoanDetails : public QWidget
{
    Q_OBJECT

public:
    explicit LoanDetails(QWidget *parent = nullptr, double amount = 0.0, double interestRate = 0, int term = 0, double payment = 0, std::vector<PaymentInfo> paymentSchedule = std::vector<PaymentInfo>());
    ~LoanDetails();
    // void setLoanDetails(double amount, int term, int creditScore);

signals:
    void mainWindow();

private slots:
    void on_btnBackToMain_clicked();

private:
    Ui::LoanDetails *ui;
    // QTableWidget *tableWidget;


};

#endif // LOANDETAILS_H
