#pragma once

#include <string>

#include <vector>

#include "Transaction.h"

class Account
{
public:

    virtual void withdraw(float value, std::string description = "withdraw") = 0;
    virtual void deposit(float value, std::string description = "deposit") = 0;
    virtual std::string toString() = 0;


protected:
    int balance;
    std::vector<Transaction> history;
};