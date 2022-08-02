#include "Current.h"

#include <iostream>

#include "Account.h"

#include "Transaction.h"

#include <string>

#include <chrono>


Current::Current(float firstBalance) //adds required opening balance and registers it in history
{
	balance = firstBalance;
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	Transaction reg = Transaction(firstBalance, "Opening Balance", currentTime);
	history.push_back(reg);

	overdraft = 500;
}

void Current::deposit(float amount, std::string description) //logical actions for depositing. saves in history
{
	balance += amount;
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	Transaction reg = Transaction(amount, "Deposit", currentTime);
	history.push_back(reg);
}

void Current::withdraw(float amount, std::string description) //logical actions for withdrawal. saves in history
{

	if ((balance - amount) < -500) //checks if withdrawal is possible
	{
		std::cout << "withdrawal not possible, not enough funds in your account. \n";
	}

	if ((balance - amount) > -500) //proceeds if everything is fine
	{
		balance -= amount;
		std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
		Transaction reg = Transaction(amount, "Withdraw", currentTime);
		history.push_back(reg);
		std::cout << "Operation successful" << std::endl;

	}


}

std::string Current::toString() //describes how output should function when history is shown
{
	std::string output = "Current accout || Balance: " + std::to_string(balance);
	int size = history.size();
	int identify = 0;
	while (identify != (size))
	{
		output += "\n ---> " + history[identify].toString();

		identify++;

	}

	return output;

}


