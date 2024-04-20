// LoanType.h

#ifndef LOAN_TYPE_H
#define LOAN_TYPE_H

#include <string>
#include <vector>

using namespace std;

enum class PaymentFrequency 
{
    Monthly,
    BiWeekly,
    Weekly
};

struct PaymentInfo 
{
    double principalComponent;
    double interestComponent;
    double remainingBalance;
};

class LoanType
{
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
        int getPaymentsPerYear() const;

    //constructorul
    public:
	    LoanType(const string& name, double minimumAmount, double maximumAmount, int minimumLoanTerm, int maximumLoanTerm, double minimumInterestRate, double maximumInterestRate, PaymentFrequency freq = PaymentFrequency::Monthly);

        virtual ~LoanType();  // Virtual destructor
		
		//Getters si setters
        string getName() const;
        double getMinimumAmount() const;
        double getMaximumAmount () const;
        int getMinimumLoanTerm () const;
        int getMaximumLoanTerm () const;
        double getMinimumInterestRate() const;
        double getMaximumInterestRate () const;
        PaymentFrequency getPaymentFrequency() const;

        void setCreditScore(int score);
        void setPaymentFrequency(PaymentFrequency frequency);
        virtual double calculateInterest(double principal, int term, double rate) const = 0;
        virtual double calculateIndividualPayment(double principal, int term, double rate) const = 0;   
        double calculateRateBasedOnCreditScore() const;
        virtual double calculateTotalInterest(double principal, int term) const = 0;
		double calculateTotalAmount(double principal, int term, double rate) const;
};

#endif // LOAN_TYPE_H