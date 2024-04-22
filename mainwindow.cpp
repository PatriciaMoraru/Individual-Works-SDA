#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loandetails.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString selectedLoanName = ui->loanType->currentText();

    BusinessLoan businessLoan;
    MortgageLoan mortgageLoan;
    WeddingLoan weddingLoan;
    RefinancingLoan refinancingLoan;
    MajorPurchasesLoan majorPurchasesLoan;
    VacationLoan vacationLoan;
    MedicalTreatmentLoan medicalTreatmentLoan;
    VehicleLoan vehicleLoan;
    EducationLoan educationLoan;
    PersonalExpensesLoan personalExpensesLoan;

    vector<LoanType*> loans = {&businessLoan, &mortgageLoan, &weddingLoan, &refinancingLoan, &majorPurchasesLoan, &vacationLoan, &medicalTreatmentLoan, &vehicleLoan, &educationLoan, &personalExpensesLoan};

    LoanType* selectedLoan = nullptr;

    for (auto loan : loans)
    {
        if (loan->getName() == selectedLoanName.toStdString())
        {
            selectedLoan = loan;
            break;
        }
    }

    // loanDetailsWindow = new LoanDetails();
    // connect(loanDetailsWindow, &LoanDetails::mainWindow, this, &MainWindow::show);

    ui->creditScoreSlider->setMinimum(500);
    ui->creditScoreSlider->setMaximum(850);

    ui->loanAmountSlider->setMinimum(selectedLoan->getMinimumAmount());
    ui->loanAmountSlider->setMaximum(selectedLoan->getMaximumAmount());

    ui->loanTermSlider->setMinimum(selectedLoan->getMinimumLoanTerm());
    ui->loanTermSlider->setMaximum(selectedLoan->getMaximumLoanTerm());

    ui->creditScoreValue->setText(QString::number(ui->creditScoreSlider->value()));
    ui->loanTermValue->setText(QString::number(ui->loanTermSlider->value()));
    ui->loanAmountValue->setText(QString::number(ui->loanAmountSlider->value()));

    ui->minCreditScoreValue->setText(QString::number(ui->creditScoreSlider->minimum()));
    ui->minLoanTermValue->setText(QString::number(ui->loanTermSlider->minimum()));
    ui->minLoanAmountValue->setText(QString::number(ui->loanAmountSlider->minimum()));

    ui->maxCreditScoreValue->setText(QString::number(ui->creditScoreSlider->maximum()));
    ui->maxLoanTermValue->setText(QString::number(ui->loanTermSlider->maximum()));
    ui->maxLoanAmountValue->setText(QString::number(ui->loanAmountSlider->maximum()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_loanType_currentIndexChanged(int index)
{
    QString selectedLoanName = ui->loanType->currentText();

    BusinessLoan businessLoan;
    MortgageLoan mortgageLoan;
    WeddingLoan weddingLoan;
    RefinancingLoan refinancingLoan;
    MajorPurchasesLoan majorPurchasesLoan;
    VacationLoan vacationLoan;
    MedicalTreatmentLoan medicalTreatmentLoan;
    VehicleLoan vehicleLoan;
    EducationLoan educationLoan;
    PersonalExpensesLoan personalExpensesLoan;

    vector<LoanType*> loans = {&businessLoan, &mortgageLoan, &weddingLoan, &refinancingLoan, &majorPurchasesLoan, &vacationLoan, &medicalTreatmentLoan, &vehicleLoan, &educationLoan, &personalExpensesLoan};

    LoanType* selectedLoan = nullptr;

    for (auto loan : loans)
    {
        if (loan->getName() == selectedLoanName.toStdString())
        {
            selectedLoan = loan;
            break;
        }
    }
    ui->creditScoreSlider->setMinimum(500);
    ui->creditScoreSlider->setMaximum(850);

    ui->loanAmountSlider->setMinimum(selectedLoan->getMinimumAmount());
    ui->loanAmountSlider->setMaximum(selectedLoan->getMaximumAmount());
    ui->loanAmountSlider->setSingleStep(1000);

    ui->loanTermSlider->setMinimum(selectedLoan->getMinimumLoanTerm());
    ui->loanTermSlider->setMaximum(selectedLoan->getMaximumLoanTerm());

    ui->creditScoreValue->setText(QString::number(ui->creditScoreSlider->value()));
    ui->loanTermValue->setText(QString::number(ui->loanTermSlider->value()));
    ui->loanAmountValue->setText(QString::number(ui->loanAmountSlider->value()));

    ui->minCreditScoreValue->setText(QString::number(ui->creditScoreSlider->minimum()));
    ui->minLoanTermValue->setText(QString::number(ui->loanTermSlider->minimum()));
    ui->minLoanAmountValue->setText(QString::number(ui->loanAmountSlider->minimum()));

    ui->maxCreditScoreValue->setText(QString::number(ui->creditScoreSlider->maximum()));
    ui->maxLoanTermValue->setText(QString::number(ui->loanTermSlider->maximum()));
    ui->maxLoanAmountValue->setText(QString::number(ui->loanAmountSlider->maximum()));

}


void MainWindow::on_paymentFrequency_currentIndexChanged(int index)
{
    QString selectedText = ui->paymentFrequency->currentText();
    qDebug() << "Selected option: " << selectedText;
}


void MainWindow::on_btnGetLoan_clicked()
{
    QString selectedLoanName = ui->loanType->currentText();

    BusinessLoan businessLoan;
    MortgageLoan mortgageLoan;
    WeddingLoan weddingLoan;
    RefinancingLoan refinancingLoan;
    MajorPurchasesLoan majorPurchasesLoan;
    VacationLoan vacationLoan;
    MedicalTreatmentLoan medicalTreatmentLoan;
    VehicleLoan vehicleLoan;
    EducationLoan educationLoan;
    PersonalExpensesLoan personalExpensesLoan;

    vector<LoanType*> loans = {&businessLoan, &mortgageLoan, &weddingLoan, &refinancingLoan, &majorPurchasesLoan, &vacationLoan, &medicalTreatmentLoan, &vehicleLoan, &educationLoan, &personalExpensesLoan};

    LoanType* selectedLoan = nullptr;

    for (auto loan : loans)
    {
        if (loan->getName() == selectedLoanName.toStdString())
        {
            selectedLoan = loan;
            break;
        }
    }

    selectedLoan->setCreditScore(ui->creditScoreValue->text().toInt());

    PaymentFrequency frequency = PaymentFrequency::Monthly;
    QString frequencyChoice = ui->paymentFrequency->currentText();

    if (frequencyChoice.toStdString() == "Biweekly"){
        frequency = PaymentFrequency::BiWeekly;
    } else if (frequencyChoice.toStdString() == "Weekly"){
        frequency = PaymentFrequency::Weekly;
    }

    selectedLoan->setPaymentFrequency(frequency);

    double amount;
    int term;
    int creditScore;

    amount = ui->loanAmountValue->text().toDouble();
    term = ui->loanTermValue->text().toInt();
    creditScore = ui->creditScoreValue->text().toInt();
    double rate = selectedLoan->calculateRateBasedOnCreditScore();
    double payment = selectedLoan->calculateIndividualPayment(amount, term, rate);


    AmortizationInterestLoan* amortizedLoan = dynamic_cast<AmortizationInterestLoan*>(selectedLoan);
    std::vector<PaymentInfo> schedule = amortizedLoan->generatePaymentSchedule(amount, term, payment);
    double totalInterest = 0;
    for (const auto& paymentInfo : schedule)
    {
        totalInterest += paymentInfo.interestComponent;
    }

    LoanDetails *loanDetailsWindow = new LoanDetails(nullptr, amount, rate*100, term, payment, schedule);
    connect(loanDetailsWindow, &LoanDetails::mainWindow, this, &MainWindow::show);
    loanDetailsWindow->show();
    this->hide();
}

void MainWindow::showMainWindow()
{
    // Show the main window
    this->show();
}


void MainWindow::on_creditScoreSlider_valueChanged(int value)
{
    ui->creditScoreValue->setText(QString::number(value));
}


void MainWindow::on_loanTermSlider_valueChanged(int value)
{
    ui->loanTermValue->setText(QString::number(value));
}


void MainWindow::on_loanAmountSlider_valueChanged(int value)
{
    ui->loanAmountValue->setText(QString::number(value));
}

