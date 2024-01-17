#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void instructions() {
	cout << "-------------------------------------------" << endl;
	cout << "Welcome the AES_CLI_project!" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "Available codes:" << endl;
	cout << " | 01 - read text from file" << endl;
	cout << " | 02 - crypt text with AES" << endl;
	cout << " | 03 - decrypt text" << endl;
	cout << " | 04 - save crypted text" << endl;
	cout << " | 05 - save decrypted text" << endl;
	cout << " | ++ - guide" << endl;
	cout << "-------------------------------------------" << endl;
}

int main()
{
	instructions();

	string code;
	getline(cin, code);
	
	if (code == "01") {
		string fileAddress;
		cin >> fileAddress;

		string readedText = "";

		ifstream
	}
}

