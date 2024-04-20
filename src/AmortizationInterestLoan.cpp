// AmortizationInterestLoan.cpp

#include "../include/AmortizationInterestLoan.h"
#include <cmath>
#include <iostream>

AmortizationInterestLoan::AmortizationInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate)
    : LoanType(name, minimumAmount, maximumAmount, minimumLoanTerm, maximumLoanTerm, minimumInterestRate, maximumInterestRate) {}

double AmortizationInterestLoan::calculateInterest(double principal, int term, double rate) const
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

double AmortizationInterestLoan::calculateIndividualPayment(double principal, int term, double rate) const
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

double AmortizationInterestLoan::calculateTotalInterest(double principal, int term) const
{
    double ratePerPeriod = calculateRateBasedOnCreditScore() / getPaymentsPerYear();
    double payment = calculateIndividualPayment(principal, term, ratePerPeriod * 12);  
    return payment * term * getPaymentsPerYear() / 12 - principal;  
}

vector<PaymentInfo> AmortizationInterestLoan::generatePaymentSchedule(double principal, int term, double paymentAmount) const 
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

// AmortizationInterestLoan.cpp