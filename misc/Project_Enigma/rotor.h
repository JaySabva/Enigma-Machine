#include <bits/stdc++.h>
using namespace std;

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