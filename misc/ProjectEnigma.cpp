#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Plugboard
{
	vector<int> wiring;

public:
	Plugboard(const string &connections)
	{
		wiring = decodePlugboard(connections);
	}

	int forward(int c)
	{
		return wiring[c];
	}

private:
	vector<int> decodePlugboard(const string &plugboard)
	{
		vector<int> mapping(26);
		iota(mapping.begin(), mapping.end(), 0);

		string temp;
		for (char c : plugboard)
		{
			if (isalpha(c))
			{
				temp += c;
			}
		}

		for (auto i = 0; i < temp.size(); i += 2)
		{
			int c1 = temp[i] - 'A';
			int c2 = temp[i + 1] - 'A';

			swap(mapping[c1], mapping[c2]);
		}

		return mapping;
	}
};

class Rotor
{
	string name;
	vector<int> forwardWiring;
	vector<int> backwardWiring;
	int rotorPosition;
	int notchPosition;
	int ringSetting;

public:
	Rotor(const string &name, const string &encoding, int rotorPosition, int notchPosition, int ringSetting)
	{
		this->name = name;
		this->forwardWiring = decodeWiring(encoding);
		this->backwardWiring = inverseWiring(forwardWiring);
		this->rotorPosition = rotorPosition;
		this->notchPosition = notchPosition;
		this->ringSetting = ringSetting;
	}

	static Rotor Create(const string &name, int rotorPosition, int ringSetting)
	{
		if (name == "I")
			return Rotor("I", "EKMFLGDQVZNTOWYHXUSPAIBRCJ", rotorPosition, 16, ringSetting);
		else if (name == "II")
			return Rotor("II", "AJDKSIRUXBLHWTMCQGZNPYFVOE", rotorPosition, 4, ringSetting);
		else if (name == "III")
			return Rotor("III", "BDFHJLCPRTXVZNYEIWGAKMUSQO", rotorPosition, 21, ringSetting);
		else if (name == "IV")
			return Rotor("IV", "ESOVPZJAYQUIRHXLNFTGKDCMWB", rotorPosition, 9, ringSetting);
		else if (name == "V")
			return Rotor("V", "VZBRGITYUPSDNHLXAWMJQOFECK", rotorPosition, 25, ringSetting);
		else if (name == "VI")
			return Rotor("VI", "JPGVOUMFYQBENHZRDKASXLICTW", rotorPosition, 0, ringSetting);
		else if (name == "VII")
			return Rotor("VII", "NZJHGRCXMYSWBOUFAIVLPEKQDT", rotorPosition, 0, ringSetting);
		else if (name == "VIII")
			return Rotor("VIII", "FKQHTLXOCBJSPDZRAMEWNIUYGV", rotorPosition, 0, ringSetting);
		else
			return Rotor("Identity", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", rotorPosition, 0, ringSetting);
	}

	string getName()
	{
		return name;
	}

	int getPosition()
	{
		return rotorPosition;
	}

	int forward(int c)
	{
		return encipher(c, rotorPosition, ringSetting, forwardWiring);
	}

	int backward(int c)
	{
		return encipher(c, rotorPosition, ringSetting, backwardWiring);
	}

	bool isAtNotch()
	{
		return notchPosition == rotorPosition;
	}

	void turnover()
	{
		rotorPosition = (rotorPosition + 1) % 26;
	}

private:
	vector<int> decodeWiring(const string &encoding)
	{
		vector<int> wiring;
		for (char c : encoding)
		{
			wiring.push_back(c - 'A');
		}
		return wiring;
	}

	vector<int> inverseWiring(const vector<int> &wiring)
	{
		vector<int> inverse(wiring.size());
		for (int i = 0; i < wiring.size(); i++)
		{
			inverse[wiring[i]] = i;
		}
		return inverse;
	}

	int encipher(int c, int rotorPos, int ringPos, const vector<int> &wiring)
	{
		int offset = c + (rotorPos - ringPos);
		int normalized = (offset + 26) % 26;
		int enciphered = wiring[normalized];
		int unoffset = (enciphered - rotorPos + ringPos + 26) % 26;
		return unoffset;
	}
};

class Reflector
{
	vector<int> forwardWiring;

public:
	Reflector(const string &encoding)
	{
		forwardWiring = decodeWiring(encoding);
	}

	static Reflector Create(const string &name)
	{
		if (name == "B")
			return Reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");
		else if (name == "C")
			return Reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL");
		else
			return Reflector("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	}

	int forward(int c)
	{
		return forwardWiring[c];
	}

private:
	vector<int> decodeWiring(const string &encoding)
	{
		vector<int> wiring;
		for (char c : encoding)
		{
			wiring.push_back(c - 'A');
		}
		return wiring;
	}
};

class Enigma
{
	Rotor leftRotor;
	Rotor middleRotor;
	Rotor rightRotor;

	Reflector reflector;

	Plugboard plugboard;

public:
	Enigma(const string &leftRotorType, const string &middleRotorType, const string &rightRotorType,
		   const string &reflectorType, int leftRotorPosition, int middleRotorPosition, int rightRotorPosition,
		   int leftRingSetting, int middleRingSetting, int rightRingSetting, const string &plugboardConnections)
		: leftRotor(Rotor::Create(leftRotorType, leftRotorPosition, leftRingSetting)),
		  middleRotor(Rotor::Create(middleRotorType, middleRotorPosition, middleRingSetting)),
		  rightRotor(Rotor::Create(rightRotorType, rightRotorPosition, rightRingSetting)),
		  reflector(Reflector::Create(reflectorType)),
		  plugboard(plugboardConnections) {}

	int encrypt(int c)
	{
		rotate();

		c = plugboard.forward(c);

		int c1 = rightRotor.forward(c);
		int c2 = middleRotor.forward(c1);
		int c3 = leftRotor.forward(c2);

		int c4 = reflector.forward(c3);

		int c5 = leftRotor.backward(c4);
		int c6 = middleRotor.backward(c5);
		int c7 = rightRotor.backward(c6);

		c7 = plugboard.forward(c7);

		return c7;
	}

	string encrypt(const string &input)
	{
		string output = input;
		for (char &c : output)
		{
			if (isalpha(c))
			{
				c = 'A' + encrypt(c - 'A');
			}
		}
		return output;
	}

private:
	void rotate()
	{
		if (middleRotor.isAtNotch())
		{
			middleRotor.turnover();
			leftRotor.turnover();
		}
		if (rightRotor.isAtNotch())
		{
			middleRotor.turnover();
		}
		rightRotor.turnover();
	}
};

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
	cout << "Enter the plaintext: ";
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
