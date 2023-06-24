#include <bits/stdc++.h>
using namespace std;


// Plugboard Class
class Plugboard
{
    vector<int> wiring;

public:
    Plugboard(const string &connections)
    {
        wiring = decodePlugboard(connections);
    }

    int forward(int ch)
    {
        return wiring[ch];
    }

private:
    vector<int> decodePlugboard(const string &plugboard)
    {
        vector<int> mapping(26);
        // it assign 0 to 25 to mapping[0] to mapping[25]
        iota(mapping.begin(), mapping.end(), 0);

        string tmp;
        for (char c: plugboard)
        {
            if (isalpha(c))
                tmp += c;
        }
        
        for (int i = 0; i < tmp.size(); i += 2)
        {
            int c1 = tmp[i] - 'A';
            int c2 = tmp[i + 1] - 'A';

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
		this->forwardWiring = decodewiring(encoding);
		this->backwardWiring = inverseWiring(forwardWiring);
		this->rotorPosition = rotorPosition;
		this->notchPosition = notchPosition;
		this->ringSetting = ringSetting;
	}

	static Rotor Create(const string &name, int rotorPosition, int ringSetting)
	{
        // This function is used to create a rotor
        // It takes name, rotorPosition, ringSetting as input
        // It returns a Rotor object
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
			return Rotor("JaySabva", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", rotorPosition, 0, ringSetting);
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
        return encode(c, rotorPosition, ringSetting, forwardWiring);
    }

    int backward(int c)
    {
        return encode(c, rotorPosition, ringSetting, backwardWiring);
    }

    bool isNotch()
    {
        return rotorPosition == notchPosition;
    }

    void turnover()
    {
        rotorPosition = (rotorPosition + 1) % 26;
    }

private:
    vector<int> decodewiring(const string &encoding)
    {
        vector<int> wiring(26);
        for (int i = 0; i < 26; i++)
        {
            wiring[i] = encoding[i] - 'A';
        }
        return wiring;
    }

    vector<int> inverseWiring(const vector<int> &wiring)
    {
        vector<int> inverse(26);
        for (int i = 0; i < 26; i++)
        {
            inverse[wiring[i]] = i;
        }
        return inverse;
    }

    int encode(int c, int rotorPosition, int ringSetting, const vector<int> &wiring)
    {
        c = (c + rotorPosition - ringSetting + 26) % 26;
        c = wiring[c];
        c = (c - rotorPosition + ringSetting + 26) % 26;
        return c;
    }
};

class Reflector
{
    vector<int> wiring;

public:
    Reflector(const string &encoding)
    {
        wiring = decodeWiring(encoding);
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
        return wiring[c];
    }

private:
    vector<int> decodeWiring(const string &encoding)
    {
        vector<int> wiring(26);
        for (int i = 0; i < 26; i++)
        {
            wiring[i] = encoding[i] - 'A';
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

        c = plugboard.forward(c7);

        return c;
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

    int getLeftRotorPosition()
    {
        return leftRotor.getPosition();
    }

    int getMiddleRotorPosition()
    {
        return middleRotor.getPosition();
    }

    int getRightRotorPosition()
    {
        return rightRotor.getPosition();
    }

private:
    void rotate()
    {
        if (middleRotor.isNotch())
        {
            middleRotor.turnover();
            leftRotor.turnover();
        }
        else if (rightRotor.isNotch())
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
    //print the rotor position
    cout << "Rotor Positions:" << endl;
    cout << "Left Rotor: " << enigma.getLeftRotorPosition() << endl;
    cout << "Middle Rotor: " << enigma.getMiddleRotorPosition() << endl;
    cout << "Right Rotor: " << enigma.getRightRotorPosition() << endl;

	return 0;
}
