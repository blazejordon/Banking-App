#include "Savings.h"
#include <cmath>
#include "InterestEarning.h"
#include <chrono>
#include <iostream>


Savings::Savings(float firstBalance, bool isIsa) //adds required opening balance and registers it in history
{
	balance = firstBalance;

	if (isIsa) { interestRate = 1.15; } //define interest rate for ISA
	else { interestRate = 0.85; } //define interest rate for Savings

	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	Transaction reg = Transaction(firstBalance, "Opening Balance", currentTime);
	history.push_back(reg);
	isa = isIsa;
}

void Savings::deposit(float amount, std::string desc) //logical actions for depositing. saves in history
{

	balance += amount;
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	history.push_back(Transaction(amount, desc, currentTime));


}

void Savings::withdraw(float amount, std::string desc) //logical actions for withdrawal. saves in history
{

	if ((balance - amount) < 0) //checks if withdrawal is possible
	{
		std::cout << "withdrawal not possible, not enough funds in your account. \n";
	}

	if ((balance - amount) > 0) //proceeds if everything is fine
	{
		balance -= amount;
		std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
		Transaction reg = Transaction(amount, desc, currentTime);
		history.push_back(reg);
		std::cout << "Operation successful" << std::endl;

	}
}

float Savings::computeInterest(int years)
{

	float rate = interestRate / 100; //turns interest percentage and turns it into a decimal for further use

	float workingBalance = balance; //a copy of the account's balance
	float medium; //amount of funds when taken the percentage of interest through balance

	for (int i = 0; i < years; i++) //loops by how many years into the future the user would like to project
	{
		medium = workingBalance * rate; //medium is calculated
		workingBalance += medium; //the value is added to the copy of balance. As the loop repeats it carries out the full equation where new balance is altered through loops
	}

	return workingBalance;


}



std::string Savings::toString() //describes how output should function when history is shown
{
	std::string type;
	if (isa == true) { type = "ISA"; }
	if (isa == false) { type = "Savings"; }

	std::string output = type + " accout || Balance: " + std::to_string(balance);
	int size = history.size();
	int identify = 0;
	while (identify != (size))
	{
		output += "\n ---> " + history[identify].toString();

		identify++;

	}

	return output;

}