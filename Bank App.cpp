
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Savings.h"
#include "Current.h"
#include "Account.h"
#include <iomanip>




Savings* openSavings(std::string type, float amount)
{
	if (type == "isa")
	{



		return new Savings(amount, true);

	}

	if (type == "savings")
	{
		return new Savings(amount, false);

	}


}

Current* openCurrent(float amount)
{
	return new Current(amount);
}









int main()
{
	std::vector <Account*> Accounts; //allows to store all active accounts for manipulation
	std::vector <Savings*> SavingsAccount; //seperate vector to allow computeInterest 
	std::vector <std::string> parameters;
	std::string userCommand;
	int ISAlimit = 0; //helps to only allow one ISA account to be opened


	std::cout << "~~~ Welcome to BankApp! ~~~" << std::endl;
	std::cout << "Type 'options' to get help" << std::endl;

	while (userCommand != "exit") //commands
	{
		parameters.clear(); // clear ready for next command
		std::cout << std::endl << ">>> ";

		std::getline(std::cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];//saves the length of user command into a c style array
		strcpy(cstr, userCommand.c_str());//copies the user command into cstr, the .c_str defines c string

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}


		std::string command = parameters[0];

		if (command.compare("options") == 0)
		{

			std::cout << "open" << "\n - (opens a new account) as in: open 1 200 (opens corrent account with 200) \n" << std::endl;
			std::cout << "view" << "\n - (view your accounts) \n" << std::endl;
			std::cout << "withdraw" << "\n - (withdraws defined amount from defined account) \n" << std::endl;
			std::cout << "deposit" << "\n - (deposits defined amount to defined account) \n" << std::endl;
			std::cout << "transfer" << "\n - (transfers funds from one account to another) \n" << std::endl;
			std::cout << "project" << "\n - (show compound interest of an account in defined years) \n" << std::endl;




		}
		else if (command.compare("open") == 0)
		{

			std::string type;
			float amount = 0;


			if (stoi(parameters[1]) == 1)
			{


				float input = std::stof(parameters[2]);
				amount = input;

				if (amount <= 0) { std::cout << "...minimum £0.01" << std::endl; } //doesn't allow if input is invalid
				else
				{
					std::cout << "Current account created!";
					Accounts.push_back(openCurrent(amount)); //adds data to accounts vector
				}


			}

			if (stoi(parameters[1]) == 2)
			{


				float input = std::stof(parameters[2]);
				amount = input;

				if (amount < 1000) { std::cout << "...minimum £1000" << std::endl; }
				else
				{
					std::cout << "Savings account created!";
					Savings* s = openSavings("savings", amount);
					Accounts.push_back(s);
					SavingsAccount.push_back(s); //adds same data to a savings vector



				}

			}

			if (stoi(parameters[1]) == 3)
			{




				float input = std::stof(parameters[2]);
				amount = input;
				if (amount < 1000) { std::cout << "...minimum £1000" << std::endl; }

				else
				{
					if (ISAlimit == 1) { std::cout << "\n You can only have one ISA account! \n"; }


					if (ISAlimit == 0)
					{
						std::cout << "ISA account created!";
						Savings* s = openSavings("isa", amount);
						Accounts.push_back(s);
						SavingsAccount.push_back(s);
						ISAlimit++;
					}

				}



			}



		}
		else if (command.compare("view") == 0)
		{


			if (parameters.size() != 2)
			{
				int size = Accounts.size();
				int identify = 0;
				while (identify != size) //takes all data and loops seperately to output individual information
				{
					std::cout << "\n ---> " + Accounts[identify]->toString();

					identify++;

				}

			}


			if (parameters.size() > 1) //same thing but only for one, selected account
			{
				std::cout << Accounts[std::stoi(parameters[1])]->toString();

			}


		}
		else if (command.compare("withdraw") == 0)
		{


			int acc = std::stoi(parameters[1]);
			int amount = std::stoi(parameters[2]);

			Accounts[acc]->withdraw(amount); //sends user input to withdraw function



		}
		else if (command.compare("deposit") == 0)
		{

			int acc = std::stoi(parameters[1]);
			int amount = std::stoi(parameters[2]);

			Accounts[acc]->deposit(amount);

			std::cout << "Deposit successful" << std::endl;



		}
		else if (command.compare("transfer") == 0)
		{




			std::string out = "Transfer out " + parameters[2]; //needed for viewing actions when prompted
			std::string in = "transfer in " + parameters[1];

			Accounts[std::stoi(parameters[1])]->withdraw(std::stof(parameters[3]), out); //takes funds away from from one account
			Accounts[std::stoi(parameters[2])]->deposit(std::stof(parameters[3]), in); //adds same funds to another




		}
		else if (command.compare("project") == 0)
		{

			std::stringstream s; //needed to round output to 2 decimal places
			s << "Projected balance: " << std::fixed << std::setprecision(2) << SavingsAccount[std::stoi(parameters[2])]->computeInterest(std::stoi(parameters[1])); //sends info to desired functions
			std::cout << s.str(); //output processed data

		}
		else
		{
			std::cout << "unrecognised command! try again: " << std::endl;
		}

	}

	std::cout << "Press any key to quit...";
	std::getchar();
}

