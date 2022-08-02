#pragma once

#include <string>

#include<chrono>

class Transaction
{
private:
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::string desc;
    float value;
public:
    std::string toString();
    Transaction(float TransactionValue, std::string TransactionDescription, std::chrono::time_point<std::chrono::system_clock> TransactionTime);
    ~Transaction();
};