#include "loandetails.h"
#include "ui_loandetails.h"

LoanDetails::LoanDetails(QWidget *parent, double amount, double interestRate, int term, double payment, std::vector<PaymentInfo> paymentSchedule)
    : QWidget(parent)
    , ui(new Ui::LoanDetails)
{
    ui->setupUi(this);


    ui->lineEditPaymentAmount->setText(QString::number(payment));
    ui->lineEditInterestRate->setText(QString::number(interestRate));
    ui->lineEditLoanTerm->setText(QString::number(term));

    ui->tableWidget_paymentSchedule->setRowCount(paymentSchedule.size());
    int i = 0;
    double totalInterest = 0;
    QLineSeries *cumulativePrincipal = new QLineSeries();
    double principalC = 0;
    cumulativePrincipal->append(i, principalC);
    QLineSeries *cumulativeInterest = new QLineSeries();
    double interestC = 0;
    cumulativeInterest->append(i, interestC);

    std::stringstream stream;
    stream << std::fixed;
    // Set the precision to control the number of decimal places
    stream << std::setprecision(2);

    stream.str("");
    stream << amount;
    std::string am = stream.str();
    QString qAm = QString::fromStdString(am);
    ui->lineEditPrincipal->setText(qAm);

    for (const auto& paymentInfo : paymentSchedule)
    {
        principalC += paymentInfo.principalComponent;
        interestC += paymentInfo.interestComponent;

        stream.str("");
        stream << paymentInfo.principalComponent;
        std::string princ = stream.str();
        QString qPrinc= QString::fromStdString(princ);
        ui->tableWidget_paymentSchedule->setItem(i, 0, new QTableWidgetItem(QString("MDL ") + qPrinc));

        stream.str("");
        stream << paymentInfo.interestComponent;
        std::string inter = stream.str();
        QString qInter = QString::fromStdString(inter);
        ui->tableWidget_paymentSchedule->setItem(i, 1, new QTableWidgetItem(QString("MDL ") + qInter));

        stream.str("");
        stream << paymentInfo.remainingBalance;
        std::string rem = stream.str();
        QString qRem = QString::fromStdString(rem);
        if (paymentInfo.remainingBalance > 0.5){
            ui->tableWidget_paymentSchedule->setItem(i, 2, new QTableWidgetItem(QString("MDL ") + qRem));
        } else {
            ui->tableWidget_paymentSchedule->setItem(i, 2, new QTableWidgetItem(QString("MDL ") + QString::number(0)));
        }


        totalInterest += paymentInfo.interestComponent;
        i++;
        cumulativePrincipal->append(i, principalC);
        cumulativeInterest->append(i, interestC);
    }


    // Convert the double to a string
    stream.str("");
    stream << totalInterest;
    std::string totalInterestStr = stream.str();

    // Convert the string to a QString and set it to the line edit
    QString qTotalInterest = QString::fromStdString(totalInterestStr);
    ui->lineEditTotalInterest->setText(qTotalInterest);


    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(cumulativePrincipal);
    chart->createDefaultAxes();
    chart->setVisible(true);
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisX) {
        axisX->setTitleText("Number of payments");
    }
    if (axisY) {
        axisY->setTitleText("MDL");
    }
    chart->setTitle(QString("Cumulative Principal"));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);
    ui->verticalLayoutCumulativePrincipal->addWidget(chartView);

    QChart *chart1 = new QChart();
    chart1->legend()->hide();
    chart1->addSeries(cumulativeInterest);
    chart1->createDefaultAxes();
    chart1->setVisible(true);
    QValueAxis *axisX1 = qobject_cast<QValueAxis *>(chart1->axisX());
    QValueAxis *axisY1 = qobject_cast<QValueAxis *>(chart1->axisY());
    if (axisX1) {
        axisX1->setTitleText("Number of payments");
    }
    if (axisY1) {
        axisY1->setTitleText("MDL");
    }
    chart1->setTitle(QString("Cumulative Interest"));

    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setVisible(true);
    ui->verticalLayoutCumulativeInterest->addWidget(chartView1);


    stream.str("");
    stream << amount+totalInterest;
    std::string tot = stream.str();
    QString qTot = QString::fromStdString(tot);
    ui->lineEditTotal->setText(qTot);
}

LoanDetails::~LoanDetails()
{
    delete ui;
}


void LoanDetails::on_btnBackToMain_clicked()
{
    emit mainWindow();
    this->hide();

    // Show the MainWindow (i.e. the parent window)
    // QWidget *parent = this->parentWidget();
    // parent->show();


}

