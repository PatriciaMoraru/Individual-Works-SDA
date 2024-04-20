// SimpleInterestLoan.cpp

#include "../include/SimpleInterestLoan.h"
#include <cmath>

SimpleInterestLoan::SimpleInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate)
    : LoanType(name, minimumAmount, maximumAmount, minimumLoanTerm, maximumLoanTerm, minimumInterestRate, maximumInterestRate) {}

double SimpleInterestLoan::calculateInterest(double principal, int term, double rate) const
{
	int paymentsPerYear = getPaymentsPerYear();  
	int totalPayments = term * paymentsPerYear / 12;  
		    
	double ratePerPeriod = rate / paymentsPerYear;  
	double totalInterest = principal * ratePerPeriod * totalPayments;  
		    
	return totalInterest;
}
		
double SimpleInterestLoan::calculateIndividualPayment(double principal, int term, double rate) const 
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

double SimpleInterestLoan::calculateTotalInterest(double principal, int term) const
{
	double annualRate = calculateRateBasedOnCreditScore();
	int paymentsPerYear = getPaymentsPerYear();  
	int totalPayments = term * paymentsPerYear / 12;  
		    
	double ratePerPeriod = annualRate / paymentsPerYear;
	double interestPerPeriod = principal * ratePerPeriod;
	return interestPerPeriod * totalPayments;  // Interesul total pe toata perioada
}

// SimpleInterestLoan.cpp
