#pragma once

#include <string>

#include "InterestEarning.h"

#include "Account.h"

class Savings : public Account, public InterestEarning
{
public:

    Savings(float firstBalance, bool isa);
    ~Savings();
    std::string toString() override;
    float computeInterest(int years) override;
    void deposit(float value, std::string description = "Deposit") override;
    void withdraw(float value, std::string description = "Deposit") override;
private:
    bool isa;
    float interestRate;

};