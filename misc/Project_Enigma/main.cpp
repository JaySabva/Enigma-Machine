#include <bits/stdc++.h>
#include "enigma.h"

using namespace std;

int main()
{
	string leftRotorType = "III";
	string middleRotorType = "II";
	string rightRotorType = "I";
	string reflectorType = "B";
	int leftRotorPosition = 0;
	int middleRotorPosition = 0;
	int rightRotorPosition = 0;
	int leftRingSetting = 0;
	int middleRingSetting = 0;
	int rightRingSetting = 0;
	string plugboardConnections = "AQ BJ CM DX EZ FL GY HW IP KU";

	Enigma enigma(leftRotorType, middleRotorType, rightRotorType, reflectorType, leftRotorPosition,
				  middleRotorPosition, rightRotorPosition, leftRingSetting, middleRingSetting,
				  rightRingSetting, plugboardConnections);

	string plaintext;
	cout << "Enter the : ";
	getline(cin, plaintext);
	// convert to uppercase
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
	string ciphertext = enigma.encrypt(plaintext);
	cout << "Ciphertext: " << ciphertext << endl;

	// while (true) {
	// string input;
	// cout << "Enter a key (A-Z) or 'quit' to exit: ";
	// getline(cin, input);

	// // Convert to uppercase
	// transform(input.begin(), input.end(), input.begin(), ::toupper);

	// if (input == "QUIT") {
	//     break;
	// }

	// string output = enigma.encrypt(input);
	// cout << "Encoded/Decoded key: " << output << endl;

	return 0;
}