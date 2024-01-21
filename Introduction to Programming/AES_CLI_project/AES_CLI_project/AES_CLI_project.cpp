/**
*
* Solution to course project # 10
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Теодор Голишарски
* @idnumber 6MI0600367
* @compiler VC
*
* AES CLI Project
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "matrices.h"

using namespace std;

const string INVALID_OPERATION = "Invalid operation!";

void addRoundKey(unsigned char* state, unsigned char* roundKey) {
	for (int i = 0; i < 16; i++) {
		state[i] ^= roundKey[i];
	}
}

void subBytes(unsigned char* state) {
	for (int i = 0; i < 16; i++) {
		state[i] = s_box[state[i]];
	}
}

void shiftRows(unsigned char* state) {
	unsigned char temp[16];

	temp[0] = state[0];
	temp[1] = state[5];
	temp[2] = state[10];
	temp[3] = state[15];

	temp[4] = state[4];
	temp[5] = state[9];
	temp[6] = state[14];
	temp[7] = state[3];

	temp[8] = state[8];
	temp[9] = state[13];
	temp[10] = state[2];
	temp[11] = state[7];

	temp[12] = state[12];
	temp[13] = state[1];
	temp[14] = state[6];
	temp[15] = state[11];

	for (int i = 0; i < 16; i++) {
		state[i] = temp[i];
	}
}

void mixColumns(unsigned char* state) {
	unsigned char temp[16];

	temp[0] = (unsigned char)mul2[state[0]] ^ mul3[state[1]] ^ state[2] ^ state[3];
	temp[1] = (unsigned char)state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3];
	temp[2] = (unsigned char)state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]];
	temp[3] = (unsigned char)mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]];

	temp[4] = (unsigned char)mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7];
	temp[5] = (unsigned char)state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7];
	temp[6] = (unsigned char)state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]];
	temp[7] = (unsigned char)mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]];

	temp[8] = (unsigned char)mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11];
	temp[9] = (unsigned char)state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11];
	temp[10] = (unsigned char)state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]];
	temp[11] = (unsigned char)mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]];

	temp[12] = (unsigned char)mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15];
	temp[13] = (unsigned char)state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15];
	temp[14] = (unsigned char)state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]];
	temp[15] = (unsigned char)mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]];

	for (int i = 0; i < 16; i++) {
		state[i] = temp[i];
	}
}

void round(unsigned char* state, unsigned char* key) {
	subBytes(state);
	shiftRows(state);
	mixColumns(state);
	addRoundKey(state, key);
}

void lastRound(unsigned char* state, unsigned char* key) {
	subBytes(state);
	shiftRows(state);
	addRoundKey(state, key);
}

void instructions() {
	cout << "-------------------------------------------" << endl;
	cout << "Welcome the AES_CLI_project!" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "Available codes:" << endl;
	cout << " | START - read text from file" << endl;
	cout << " | enc - encrypt text with AES" << endl;
	cout << " | dec - decrypt text" << endl;
	cout << " | save - save result in file (OPTIONAL)" << endl;
	cout << " | END - stop the application" << endl;
	cout << "-------------------------------------------" << endl;
}

void encrypt(unsigned char* plainText, unsigned char* key, unsigned char* encryptedMessage) {
	unsigned char state[16];

	for (int i = 0; i < 16; i++)
	{
		state[i] = plainText[i];
	}
	int rounds = 9;

	addRoundKey(state, key);

	for (int i = 0; i < rounds; i++)
	{
		round(state, key + (16 * (i + 1)));
	}

	lastRound(state, key + 160);

	for (int i = 0; i < 16; i++)
	{
		encryptedMessage[i] = state[i];
	}
}

void fileWrite(string fileName, string content) {
	ofstream file(fileName);

	while (true)
	{
		if (file.is_open()) {
			file << content;
			cout << "File has been created successfully!" << endl;
			break;
		}
		else {
			while (true)
			{
				cout << "Error occured :(" << endl;
				cout << "File has NOT been created. Try again!" << endl;
				cout << "File name: ";
				cin >> fileName;
				cout << endl;
				file.open(fileName);
			}
		}
	}
}

string fileRead(string filePath) {
	string readedText = "";
	string line = "";

	ifstream file;
	file.open(filePath);

	while (true)
	{
		if (file.is_open()) {
			cout << "File has been opened successfuly!" << endl;
			break;
		}
		else {
			cout << "File has NOT been opened! Try again!" << endl;
			cout << "File path: ";
			cin >> filePath;
			file.open(filePath);
		}
	}


	if (file.is_open()) {
		while (file.good()) {
			line = "";
			getline(file, line);
			readedText += line + "\n";
		}
	}
	file.close();

	return readedText;
}

int main()
{
	instructions();

	string inputCode;
	cout << "Type START!" << endl;;

	while (true) {
		getline(cin, inputCode);

		if (inputCode == "START") {
			string filePath;

			cout << "File path: ";
			cin >> filePath;

			string readedText = fileRead(filePath);

			cout << "Type \"enc\" to encrypt the text or \"dec\" to decrypt it!" << endl;
			string command;
			cin >> command;

			if (command == "enc") {
				char plainText[1024];
				for (int i = 0; i < readedText.length(); i++)
				{
					plainText[i] = readedText[i];
				}
				int len = strlen((const char*)plainText);

				int paddedLen = len;

				if ((paddedLen % 16) != 0) {
					paddedLen = (paddedLen / 16 + 1) * 16;
				}

				unsigned char* paddedText = new unsigned char[paddedLen];
				for (int i = 0; i < paddedLen; i++)
				{
					if (i >= len) {
						paddedText[i] = 0;
					}
					else {
						paddedText[i] = plainText[i];
					}
				}
				unsigned char* encryptedMessage = new unsigned char[paddedLen];

				string line;
				cout << "Type key: ";
				cin.ignore();
				getline(cin, line);

				istringstream hex_chars_stream(line);
				unsigned char key[16];
				int i = 0;
				unsigned int c;
				while (hex_chars_stream >> hex >> c)
				{
					key[i] = c;
					i++;
				}

				unsigned char expandedKey[176];

				keyExpansion(key, expandedKey);

				for (int i = 0; i < paddedLen; i++)
				{
					encrypt(paddedText + i, expandedKey, encryptedMessage + i);

				}

				cout << "Encrypted message: " << endl;
				for (int i = 0; i < paddedLen; i++)
				{
					cout << hex << (int)encryptedMessage[i] << " ";
				}
				cout << endl;
			}
			else if (command == "dec") {

			}
			else {
				cout << INVALID_OPERATION << endl;
			}

		}
		else if (inputCode == "END") {
			cout << "GoodBye!" << endl;
			return 0;
		}
		else {
			cout << INVALID_OPERATION << endl;
		}
	}

	return 0;
}

