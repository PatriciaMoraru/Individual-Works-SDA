#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include "../include/LoanType.h"
#include "../include/SimpleInterestLoan.h"
#include "../include/AmortizationInterestLoan.h"
#include "LoanType.cpp"
#include "SimpleInterestLoan.cpp"
#include "AmortizationInterestLoan.cpp"

using namespace std;

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
        : AmortizationInterestLoan("MajorPurchases", 20000, 4e5, 6, 48, 7.9, 38.9) 
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
        : AmortizationInterestLoan("MedicalTreatment", 20000, 4e5, 6, 48, 7.9, 38.9) 
        {}
};


class VehicleLoan : public SimpleInterestLoan 
{
    public:
        VehicleLoan() 
        : SimpleInterestLoan("Vehicle", 60000, 5e5, 6, 60, 7.9, 21.32) 
        {}
};

class EducationLoan : public SimpleInterestLoan 
{
    public:
        EducationLoan() 
        : SimpleInterestLoan("Education", 20000, 6e5, 6, 60, 6.9, 10.1) 
        {}
};

class PersonalExpensesLoan : public SimpleInterestLoan 
{
	public:
	    PersonalExpensesLoan()
	    : SimpleInterestLoan("PersonalExpenses", 20000, 4e5, 6, 48, 7.9, 38.9)
	    {}
};

LoanType* selectLoanType(const vector<LoanType*>& loans)
{
	string selectedLoanName;
	cout << "Enter the loan type (Business, Mortgage, Wedding, Refinancing, MajorPurchases, Vacation, MedicalTreatment, Vehicle, Education, PersonalExpenses): ";
    getline(cin, selectedLoanName);

   for (auto loan : loans) 
   {
        if (loan->getName() == selectedLoanName) 
		{
            return loan;
        }
    }
    cout << "Invalid loan type selected.\n";
    return nullptr; 
}

int inputCreditScore() 
{
    int creditScore;
    cout << "Enter your credit score: ";
    cin >> creditScore;
    if (creditScore < 300 || creditScore > 850) 
	{
        throw range_error("Credit score is out of acceptable range (300-850).");
    }
    if (creditScore < 580) 
	{
        throw domain_error("Loan declined due to poor credit score.");
    }
    return creditScore;
}

PaymentFrequency inputPaymentFrequency() 
{
    cout << "Select payment frequency (1: Monthly, 2: BiWeekly, 3: Weekly): ";
    int frequencyChoice;
    cin >> frequencyChoice;

    switch (frequencyChoice) 
	{
        case 2: return PaymentFrequency::BiWeekly;
        case 3: return PaymentFrequency::Weekly;
        default: return PaymentFrequency::Monthly;
    }
}

double inputLoanAmount(const LoanType* selectedLoan) 
{
    double amount;
    cout << "Enter the loan amount: ";
    while (!(cin >> amount) || amount < selectedLoan->getMinimumAmount() || amount > selectedLoan->getMaximumAmount()) 
	{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid loan amount. It must be between $" << selectedLoan->getMinimumAmount()
             << " and $" << selectedLoan->getMaximumAmount() << ". Please enter a valid amount: ";
    }
    return amount;
}

int inputLoanTerm(const LoanType* selectedLoan) 
{
    int term;
    cout << "Enter the loan term (in months): ";
    while (!(cin >> term) || term < selectedLoan->getMinimumLoanTerm() || term > selectedLoan->getMaximumLoanTerm()) 
	{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid loan term. It must be between " << selectedLoan->getMinimumLoanTerm()
             << " and " << selectedLoan->getMaximumLoanTerm() << " months. Please enter a valid term: ";
    }
    return term;
}

int main() 
{
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

    vector<LoanType*> loans = 
	{
		&businessLoan, &mortgageLoan, &weddingLoan, &refinancingLoan,
        &majorPurchasesLoan, &vacationLoan, &medicalTreatmentLoan,
        &vehicleLoan, &educationLoan, &personalExpensesLoan
    };

    try 
	{
        LoanType* selectedLoan = selectLoanType(loans);
        if (!selectedLoan) 
		{
            return 1;
        }

        int creditScore = inputCreditScore();
        selectedLoan->setCreditScore(creditScore);

        PaymentFrequency frequency = inputPaymentFrequency();
        selectedLoan->setPaymentFrequency(frequency);

        double amount = inputLoanAmount(selectedLoan);
        int term = inputLoanTerm(selectedLoan);

        // Calculate the rate based on credit score
        double rate = selectedLoan->calculateRateBasedOnCreditScore();
        cout << "Calculated annual interest rate: " << rate * 100 << "%" << endl;

        // Calculate the interest and individual payment
        double interest = selectedLoan->calculateInterest(amount, term, rate);
        double payment = selectedLoan->calculateIndividualPayment(amount, term, rate);

        // Check if the selected loan supports amortization
        if (AmortizationInterestLoan* amortizedLoan = dynamic_cast<AmortizationInterestLoan*>(selectedLoan)) 
		{
            vector<PaymentInfo> schedule = amortizedLoan->generatePaymentSchedule(amount, term, payment);
            double totalInterest = 0;

            cout << "Amortization Schedule:" << endl;
            for (const auto& paymentInfo : schedule) 
			{
                cout << "Payment " << (&paymentInfo - &schedule[0] + 1) << ": "
                     << "Principal: $" << paymentInfo.principalComponent
                     << ", Interest: $" << paymentInfo.interestComponent
                     << ", Remaining Balance: $" << paymentInfo.remainingBalance << endl;
                totalInterest += paymentInfo.interestComponent;
            }
            cout << "Total Interest Paid: $" << totalInterest << endl;
        } 
		else 
		{
            cout << "Note: No amortization schedule as this is a simple interest loan.\n";
        }

        // Display loan summary
        cout << "Loan Type: " << selectedLoan->getName() << "\n";
        cout << "Loan Amount: $" << amount << "\n";
        cout << "Loan Term: " << term << " months\n";
        cout << "Estimated Interest: $" << interest << "\n";
        cout << "Monthly Payment: $" << payment << "\n";

    } 
	catch (const exception& e) 
	{
        cout << "An error occurred: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

