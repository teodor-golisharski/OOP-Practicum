#pragma once
#include "BankingSystem.h"
#include "MyString.hpp"
#include "Controller.h"

void run() {
	Controller controller;
	
	MyString command;
	while (true)
	{
		std::cin >> command;
		if (command == "create_bank") {
			MyString bank_name;
			std::cin >> bank_name;
			controller.create_bank(bank_name);
		}
		else if (command == "check_avl") {

		}
		else if (command == "open") {

		}
		else if (command == "close") {

		}
		else if (command == "redeem") {

		}
		else if (command == "change") {

		}
		else if (command == "list") {

		}
		else if (command == "messages") {

		}
		else if (command == "login") {

		}
		else if (command == "signup") {

		}
		else if (command == "whoami") {

		}
		else if (command == "help") {

		}
		else if (command == "send_check") {

		}
		else if (command == "tasks") {

		}
		else if (command == "view") {

		}
		else if (command == "approve") {

		}
		else if (command == "validate") {

		}
		else if (command == "disapprove") {

		}
		else if (command == "exit") {

		}
		else {
			std::cout << "Unrecognized command! Try again!" << std::endl;
		}
	}
}