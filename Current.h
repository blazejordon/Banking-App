#pragma once

#include <string>

#include "Account.h"

class Current : public Account
{
private:
    int overdraft;

public:
    void deposit(float value, std::string description = "Deposit") override;
    std::string toString() override;
    void withdraw(float value, std::string description = "Withdraw") override;



    Current(float firstBalance);
    ~Current();

};