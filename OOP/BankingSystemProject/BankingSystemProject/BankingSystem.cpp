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
		else if (command == "check_avl" && controller.has_role(UserRole::client)) {
			MyString bank_name, account_number;
			std::cin >> bank_name >> account_number;

			controller.check_avl(bank_name, account_number);
		}
		else if (command == "open" && controller.has_role(UserRole::client)) {
			MyString bank_name;
			std::cin >> bank_name;

			//controller.
		}
		else if (command == "close" && controller.has_role(UserRole::client)) {

		}
		else if (command == "redeem" && controller.has_role(UserRole::client)) {

		}
		else if (command == "change" && controller.has_role(UserRole::client)) {

		}
		else if (command == "list" && controller.has_role(UserRole::client)) {

		}
		else if (command == "messages" && controller.has_role(UserRole::client)) {

		}
		else if (command == "login") {
			MyString name, password;
			std::cout << "Name: ";
			std::cin >> name;
			std::cout << "\nPassword: ";
			std::cin >> password;

			controller.login(name, password);
		}
		else if (command == "signup") {

			MyString name, egn, role, password;
			unsigned age;
			std::cout << "Name: ";
			std::cin >> name;

			std::cout << "\nEgn: ";
			std::cin >> egn;

			std::cout << "\nAge: ";
			std::cin >> age;

			std::cout << "\Role: ";
			std::cin >> role;

			std::cout << "\nPassword: ";
			std::cin >> password;

			controller.signup(name, egn, role, password, age);
		}
		else if (command == "whoami" && controller.is_logged_in()) {
			controller.who_am_i();
		}
		else if (command == "help" && controller.is_logged_in()) {
			controller.help();
		}
		else if (command == "send_check" && controller.has_role(UserRole::thirdPartyEmployee)) {

		}
		else if (command == "tasks" && controller.has_role(UserRole::employee)) {

		}
		else if (command == "view" && controller.has_role(UserRole::employee)) {

		}
		else if (command == "approve" && controller.has_role(UserRole::employee)) {

		}
		else if (command == "validate" && controller.has_role(UserRole::employee)) {

		}
		else if (command == "disapprove" && controller.has_role(UserRole::employee)) {

		}
		else if (command == "exit") {
			if (controller.exit()) {
				break;
			}
		}
		else {
			std::cout << "Unrecognized command! Try again!" << std::endl;
		}
	}
}