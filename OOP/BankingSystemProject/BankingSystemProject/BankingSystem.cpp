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
		try
		{
			if (command == "exit") {
				if (controller.exit()) {
					break;
				}
			}
			else if (command == "whoami") {
				controller.who_am_i();
			}
			else if (command == "help") {
				controller.help();
			}
			else if (controller.has_role(UserRole::client)) {

				if (command == "check_avl") {
					MyString bank_name, account_number;
					std::cin >> bank_name >> account_number;

					controller.check_avl(bank_name, account_number);
				}
				else if (command == "open") {
					MyString bank_name;
					std::cin >> bank_name;

					controller.open(bank_name);
				}
				else if (command == "close") {
					MyString bank_name, account_number;
					std::cin >> bank_name >> account_number;

					controller.close(bank_name, account_number);
				}
				else if (command == "redeem") {
					MyString bank_name, account_number, code;
					std::cin >> bank_name >> account_number >> code;

					controller.redeem(bank_name, account_number, code.c_str());
				}
				else if (command == "change") {
					MyString new_bank_name, current_bank_name, account_number;
					std::cin >> new_bank_name >> current_bank_name >> account_number;

					controller.redeem(new_bank_name, current_bank_name, account_number.c_str());
				}
				else if (command == "list") {
					MyString bank_name;
					std::cin >> bank_name;

					controller.list(bank_name);
				}
				else if (command == "messages") {
					controller.messages();
				}
				else std::cout << COMMAND_NOT_RECOGNIZED << std::endl;
			}
			else if (controller.has_role(UserRole::thirdPartyEmployee)) {
				if (command == "send_check") {
					double sum;
					MyString bank_name, egn;
					std::cin >> sum >> bank_name >> egn;

					controller.send_check(sum, bank_name, egn);
				}
				else std::cout << COMMAND_NOT_RECOGNIZED << std::endl;
			}
			else if (controller.has_role(UserRole::employee)) {
				if (command == "tasks") {
					controller.tasks();
				}
				else if (command == "view") {
					unsigned id;
					std::cin >> id;

					controller.view(id);
				}
				else if (command == "approve") {

				}
				else if (command == "validate") {

				}
				else if (command == "disapprove") {
					unsigned id;
					MyString message;

					std::cin >> id >> message;

					controller.disapprove(id, message);
				}
				else std::cout << COMMAND_NOT_RECOGNIZED << std::endl;
			}
			else {
				if (command == "create_bank") {
					MyString bank_name;
					std::cin >> bank_name;
					controller.create_bank(bank_name);
				}
				else if (command == "login") {
					MyString name, password;
					std::cout << "Name: ";
					std::cin >> name;
					std::cout << "Password: ";
					std::cin >> password;

					controller.login(name, password);
				}
				else if (command == "signup") {

					MyString name, egn, role, password;
					unsigned age;
					std::cout << "Name: ";
					std::cin >> name;

					std::cout << "Egn: ";
					std::cin >> egn;

					std::cout << "Age: ";
					std::cin >> age;

					std::cout << "Role: ";
					std::cin >> role;

					std::cout << "Password: ";
					std::cin >> password;

					controller.signup(name, egn, role, password, age);
				}
				else std::cout << COMMAND_NOT_RECOGNIZED << std::endl;
			}
		}
		catch (const std::invalid_argument& er) {
			std::cout << er.what()<<std::endl;
		}
		catch (const std::runtime_error& er) {
			std::cout << er.what() << std::endl;
		}
		catch (const std::exception& er)
		{
			std::cout << er.what() << std::endl;
		}
		std::cout << std::endl;
	}
}