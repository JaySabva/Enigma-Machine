#include <bits/stdc++.h>
#include "enigma.h"
using namespace std;

int main()
{
	cout << "Enigma Machine" << endl;
	cout << "--------------" << endl;
	cout << "Sabva Jay Dilipbhai" << endl;
	cout << "--------------" << endl;
	string leftRotorType;
	string middleRotorType;
	string rightRotorType;
	string reflectorType;
	int leftRotorPosition;
	int middleRotorPosition;
	int rightRotorPosition;
	int leftRingSetting;
	int middleRingSetting;
	int rightRingSetting;
	string plugboardConnections;

	cout << "Enigma Machine Configuration" << endl;
	cout << "---------------------------" << endl;

	cout << "Enter the left rotor type (I-VIII): ";
	cin >> leftRotorType;

	cout << "Enter the middle rotor type (I-VIII): ";
	cin >> middleRotorType;

	cout << "Enter the right rotor type (I-VIII): ";
	cin >> rightRotorType;

	cout << "Enter the reflector type (B or C): ";
	cin >> reflectorType;

	cout << "Enter the left rotor position (0-25): ";
	cin >> leftRotorPosition;

	cout << "Enter the middle rotor position (0-25): ";
	cin >> middleRotorPosition;

	cout << "Enter the right rotor position (0-25): ";
	cin >> rightRotorPosition;

	cout << "Enter the left rotor ring setting (0-25): ";
	cin >> leftRingSetting;

	cout << "Enter the middle rotor ring setting (0-25): ";
	cin >> middleRingSetting;

	cout << "Enter the right rotor ring setting (0-25): ";
	cin >> rightRingSetting;

	cout << "Enter the plugboard connections (e.g., AQ BJ CM): ";
	cin.ignore(); // Ignore the newline character from previous input
	getline(cin, plugboardConnections);

	Enigma enigma(leftRotorType, middleRotorType, rightRotorType, reflectorType, leftRotorPosition,
				  middleRotorPosition, rightRotorPosition, leftRingSetting, middleRingSetting,
				  rightRingSetting, plugboardConnections);

	while (true)
	{
		cout << endl;
		cout << "Enigma Machine" << endl;
		cout << "--------------" << endl;

		cout << "Left Rotor: " << enigma.getLeftRotorPosition() << " Middle Rotor: " << enigma.getMiddleRotorPosition() << " Right Rotor: " << enigma.getRightRotorPosition() << endl;
		cout << "--------------" << endl;
		cout << "Enter a plaintext message (or 'quit' to exit): ";
		string plaintext;
		getline(cin, plaintext);

		// Convert to uppercase
		transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

		if (plaintext == "QUIT")
		{
			break;
		}

		string ciphertext = enigma.encrypt(plaintext);
		cout << "Ciphertext: " << ciphertext << endl;
		cout << "--------------" << endl;
	}

	return 0;
}