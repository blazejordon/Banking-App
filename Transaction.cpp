#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>


Transaction::Transaction(float TransactionValue, std::string TransactionDescription, std::chrono::time_point<std::chrono::system_clock> TransactionTime)
{
	value = TransactionValue;
	desc = TransactionDescription;
	timestamp = TransactionTime;
}
Transaction::~Transaction() {}

std::string Transaction::toString()
{


	std::stringstream output;
	output << desc << " -- £" << std::fixed << std::setprecision(2) << value;
	std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
	output << " " << std::ctime(&time);
	return output.str();



}
