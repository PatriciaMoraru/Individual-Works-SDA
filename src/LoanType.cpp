// LoanType.cpp

#include "../include/LoanType.h"
#include <cmath>

LoanType::LoanType(const std::string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate, PaymentFrequency freq)
    : name(name), minimumAmount(minimumAmount), maximumAmount(maximumAmount), minimumLoanTerm(minimumLoanTerm), maximumLoanTerm(maximumLoanTerm), minimumInterestRate(minimumInterestRate), maximumInterestRate(maximumInterestRate), paymentFrequency(freq) {}
    
LoanType::~LoanType() {}

int LoanType::getPaymentsPerYear() const 
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

string LoanType::getName() const { return name; }
double LoanType::getMinimumAmount() const { return minimumAmount; }
double LoanType::getMaximumAmount () const { return maximumAmount; }
int LoanType::getMinimumLoanTerm () const { return minimumLoanTerm; }
int LoanType::getMaximumLoanTerm () const { return maximumLoanTerm; }
double LoanType::getMinimumInterestRate() const { return minimumInterestRate; }
double LoanType::getMaximumInterestRate () const { return maximumInterestRate; }
PaymentFrequency LoanType::getPaymentFrequency() const { return paymentFrequency; }

void LoanType::setCreditScore(int score) 
{
    creditScore = score;
}
        
void LoanType::setPaymentFrequency(PaymentFrequency frequency) 
{
    paymentFrequency = frequency;
}

double LoanType::calculateRateBasedOnCreditScore() const 
{
	//Interest Rate Formula:
    //I = Mi -  ((Mi - mi) / (Mcs - mcs)) * (CS - mcs)
	const int MinCreditScore = 580; // Minimum possible credit score
	const int MaxCreditScore = 850; // Maximum possible credit score
	double rate = maximumInterestRate - ((maximumInterestRate - minimumInterestRate) / (MaxCreditScore - MinCreditScore)) * (creditScore - MinCreditScore);
	return rate / 100.0; // Convert percentage to decimal
}

double LoanType::calculateTotalAmount(double principal, int term, double rate) const 
{
    double totalInterest = calculateTotalInterest(principal, term);
    return principal + totalInterest;
}

//LoanType.cpp