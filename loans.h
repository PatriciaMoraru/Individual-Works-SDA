#ifndef LOANS_H
#define LOANS_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

enum class PaymentFrequency
{
    Monthly,
    BiWeekly,
    Weekly
};

// The BASE class
class LoanType
{
    //folosim access modifier de tip private pentru encapsulare. Astfel asiguram securitatea si control sporit al datelor.
private:
    string name;
    double minimumAmount;
    double maximumAmount;
    int minimumLoanTerm;
    int maximumLoanTerm;
    double minimumInterestRate;
    double maximumInterestRate;

protected:
    int creditScore;
    PaymentFrequency paymentFrequency;
    int getPaymentsPerYear() const
    {
        switch (paymentFrequency)
        {
        case PaymentFrequency::Monthly:
            return 12;
        case PaymentFrequency::BiWeekly:
            return 26;
        case PaymentFrequency::Weekly:
            return 52;
        default:
            return 12;
        }
    }

    //constructorul
public:
    LoanType(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate, PaymentFrequency freq = PaymentFrequency::Monthly)
        : name(name), minimumAmount(minimumAmount), maximumAmount(maximumAmount), minimumLoanTerm(minimumLoanTerm), maximumLoanTerm(maximumLoanTerm), minimumInterestRate(minimumInterestRate), maximumInterestRate(maximumInterestRate), paymentFrequency(freq) {}

    virtual ~LoanType() {}  // Virtual destructor

    //Getters si setters
    string getName() const { return name; }
    double getMinimumAmount() const { return minimumAmount; }
    double getMaximumAmount () const { return maximumAmount; }
    int getMinimumLoanTerm () const { return minimumLoanTerm; }
    int getMaximumLoanTerm () const { return maximumLoanTerm; }
    double getMinimumInterestRate() const { return minimumInterestRate; }
    double getMaximumInterestRate () const { return maximumInterestRate; }
    PaymentFrequency getPaymentFrequency() const { return paymentFrequency; }

    void setCreditScore(int score)
    {
        creditScore = score;
    }

    void setPaymentFrequency(PaymentFrequency frequency)
    {
        paymentFrequency = frequency;
    }

    virtual double calculateInterest(double principal, int term, double rate) const = 0;
    virtual double calculateIndividualPayment(double principal, int term, double rate) const = 0;

    double calculateRateBasedOnCreditScore() const
    {
        //Interest Rate Formula:
        //I = Mi -  ((Mi - mi) / (Mcs - mcs)) * (CS - mcs)
        const int MinCreditScore = 580; // Minimum possible credit score
        const int MaxCreditScore = 850; // Maximum possible credit score
        double rate = maximumInterestRate - ((maximumInterestRate - minimumInterestRate) / (MaxCreditScore - MinCreditScore)) * (creditScore - MinCreditScore);
        return rate / 100.0; // Convert percentage to decimal
    }

    virtual double calculateTotalInterest(double principal, int term) const = 0;

    double calculateTotalAmount(double principal, int term, double rate) const
    {
        double totalInterest = calculateTotalInterest(principal, term);
        return principal + totalInterest;
    }
};

struct PaymentInfo
{
    double principalComponent;
    double interestComponent;
    double remainingBalance;
};

//Clasa derivata (derived class) pentru loan cu interes simplu
class SimpleInterestLoan : public LoanType
{
public:
    SimpleInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate)
        : LoanType(name, minimumAmount, maximumAmount, minimumLoanTerm, maximumLoanTerm, minimumInterestRate, maximumInterestRate) {}

    double calculateInterest(double principal, int term, double rate) const override
    {
        int paymentsPerYear = getPaymentsPerYear();
        int totalPayments = term * paymentsPerYear / 12;

        double ratePerPeriod = rate / paymentsPerYear;
        double totalInterest = principal * ratePerPeriod * totalPayments;

        return totalInterest;
    }

    double calculateIndividualPayment(double principal, int term, double rate) const override
    {
        int paymentsPerYear = getPaymentsPerYear();
        int totalPayments = term * paymentsPerYear / 12;

        double paymentAmount;
        if (rate > 0)
        {
            double ratePerPeriod = rate / paymentsPerYear;
            paymentAmount = principal * ratePerPeriod / (1 - pow(1 + ratePerPeriod, -totalPayments));
        }
        else
        {
            paymentAmount = principal / totalPayments;
        }
        return paymentAmount;
    }

    double calculateTotalInterest(double principal, int term) const override
    {
        double annualRate = calculateRateBasedOnCreditScore();
        int paymentsPerYear = getPaymentsPerYear();
        int totalPayments = term * paymentsPerYear / 12;

        double ratePerPeriod = annualRate / paymentsPerYear;
        double interestPerPeriod = principal * ratePerPeriod;
        return interestPerPeriod * totalPayments;  // Interesul total pe toata perioada
    }
};

//Clasa derivata (derived class) pentru loan cu interes amortizat
class AmortizationInterestLoan : public LoanType {
public:
    AmortizationInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate)
        : LoanType(name, minimumAmount, maximumAmount, minimumLoanTerm, maximumLoanTerm, minimumInterestRate, maximumInterestRate) {}

    double calculateInterest(double principal, int term, double rate) const override
    {
        int paymentsPerYear = getPaymentsPerYear();
        double ratePerPeriod = rate / paymentsPerYear;
        double totalInterest = 0;
        double remainingBalance = principal;

        for (int i = 0; i < term * paymentsPerYear / 12; ++i)
        {
            double interestPayment = remainingBalance * ratePerPeriod;
            totalInterest += interestPayment;
            remainingBalance -= (principal / (term * paymentsPerYear / 12)) - interestPayment;
        }

        return totalInterest;
    }

    double calculateIndividualPayment(double principal, int term, double rate) const override
    {
        int paymentsPerYear = getPaymentsPerYear();
        double ratePerPeriod = rate / paymentsPerYear;
        int totalPayments = term * paymentsPerYear / 12;

        if (ratePerPeriod == 0)
        {
            return principal / totalPayments;
        }
        else
        {
            return (principal * ratePerPeriod * pow(1 + ratePerPeriod, totalPayments)) /( pow(1 + ratePerPeriod, totalPayments) - 1);
        }
    }

    double calculateTotalInterest(double principal, int term) const override
    {
        double ratePerPeriod = calculateRateBasedOnCreditScore() / getPaymentsPerYear();
        double payment = calculateIndividualPayment(principal, term, ratePerPeriod * 12);
        return payment * term * getPaymentsPerYear() / 12 - principal;
    }

    vector<PaymentInfo> generatePaymentSchedule(double principal, int term, double paymentAmount) const
    {
        vector<PaymentInfo> schedule;
        int paymentsPerYear = getPaymentsPerYear();
        double ratePerPeriod = calculateRateBasedOnCreditScore() / paymentsPerYear;
        double remainingBalance = principal;

        double totalInterestPaid = 0;
        int totalPayments = term * paymentsPerYear / 12;

        for (int i = 0; i < totalPayments; ++i)
        {
            PaymentInfo info;
            info.interestComponent = remainingBalance * ratePerPeriod;
            info.principalComponent = paymentAmount - info.interestComponent;

            remainingBalance -= info.principalComponent;
            if (remainingBalance < 0)
            {
                info.principalComponent += remainingBalance;
                info.interestComponent = paymentAmount - info.principalComponent;
                remainingBalance = 0;
            }

            totalInterestPaid += info.interestComponent;
            info.remainingBalance = remainingBalance;
            schedule.push_back(info);

            if (remainingBalance <= 0) break;
        }

        cout << "Total Interest Paid: $" << totalInterestPaid << endl;
        return schedule;
    }
};

class BusinessLoan : public AmortizationInterestLoan
{
public:
    BusinessLoan()
        : AmortizationInterestLoan("Business", 10000, 1.5e6, 6, 60, 6.9, 38.9)
    {}
};

class MortgageLoan : public AmortizationInterestLoan
{
public:
    MortgageLoan()
        : AmortizationInterestLoan("Mortgage", 40000, 5e6, 6, 360, 7.5, 8.5)
    {}
};

class WeddingLoan : public AmortizationInterestLoan
{
public:
    WeddingLoan()
        : AmortizationInterestLoan("Wedding", 20000, 6e5, 6, 48, 7.9, 38.9)
    {}
};

class RefinancingLoan : public AmortizationInterestLoan
{
public:
    RefinancingLoan()
        : AmortizationInterestLoan("Refinancing", 20000, 4e5, 6, 48, 7.9, 38.9)
    {}
};

class MajorPurchasesLoan : public AmortizationInterestLoan
{
public:
    MajorPurchasesLoan()
        : AmortizationInterestLoan("Major Purchases", 20000, 4e5, 6, 48, 7.9, 38.9)
    {}
};

class VacationLoan : public AmortizationInterestLoan
{
public:
    VacationLoan()
        : AmortizationInterestLoan("Vacation", 20000, 4e5, 6, 48, 7.9, 38.9)
    {}
};

class MedicalTreatmentLoan : public AmortizationInterestLoan
{
public:
    MedicalTreatmentLoan()
        : AmortizationInterestLoan("Medical Treatment", 20000, 4e5, 6, 48, 7.9, 38.9)
    {}
};


class VehicleLoan : public AmortizationInterestLoan
{
public:
    VehicleLoan()
        : AmortizationInterestLoan("Vehicle", 60000, 5e5, 6, 60, 7.9, 21.32)
    {}
};

class EducationLoan : public AmortizationInterestLoan
{
public:
    EducationLoan()
        : AmortizationInterestLoan("Education", 20000, 6e5, 6, 60, 6.9, 10.1)
    {}
};

class PersonalExpensesLoan : public AmortizationInterestLoan
{
public:
    PersonalExpensesLoan()
        : AmortizationInterestLoan("Personal Expenses", 20000, 4e5, 6, 48, 7.9, 38.9)
    {}
};


#endif // LOANS_H
