//SimpleInterestLoan.h

#ifndef SIMPLE_INTEREST_LOAN_H
#define SIMPLE_INTEREST_LOAN_H

#include "LoanType.h"

class SimpleInterestLoan : public LoanType 
{
    public:
        SimpleInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate);
        double calculateInterest(double principal, int term, double rate) const override;
		double calculateIndividualPayment(double principal, int term, double rate) const override;
        double calculateTotalInterest(double principal, int term) const override;
};

#endif // SIMPLE_INTEREST_LOAN_H