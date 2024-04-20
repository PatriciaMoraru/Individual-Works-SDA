// AmortizationInterestLoan.h

#ifndef AMORTIZATION_INTEREST_LOAN_H
#define AMORTIZATION_INTEREST_LOAN_H

#include "LoanType.h"
#include <vector>
#include <cmath>

class AmortizationInterestLoan : public LoanType 
{
	public:
	    AmortizationInterestLoan(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate);

    double calculateInterest(double principal, int term, double rate) const override;
    double calculateIndividualPayment(double principal, int term, double rate) const override;
	double calculateTotalInterest(double principal, int term) const override;

    vector<PaymentInfo> generatePaymentSchedule(double principal, int term, double paymentAmount) const;
};

#endif // AMORTIZATION_INTEREST_LOAN_H