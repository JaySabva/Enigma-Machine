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
        : name(name), forwardWiring(decodeWiring(encoding)), backwardWiring(inverseWiring(forwardWiring)),
          rotorPosition(rotorPosition), notchPosition(notchPosition), ringSetting(ringSetting) {}

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

    string getName() const
    {
        return name;
    }

    int getPosition() const
    {
        return rotorPosition;
    }

    int forward(int c) const
    {
        return encipher(c, rotorPosition, ringSetting, forwardWiring);
    }

    int backward(int c) const
    {
        return encipher(c, rotorPosition, ringSetting, backwardWiring);
    }

    bool isAtNotch() const
    {
        return notchPosition == rotorPosition;
    }

    void turnover()
    {
        rotorPosition = (rotorPosition + 1) % 26;
    }

private:
    static vector<int> decodeWiring(const string &encoding)
    {
        vector<int> wiring;
        for (char c : encoding)
        {
            wiring.push_back(c - 'A');
        }
        return wiring;
    }

    static vector<int> inverseWiring(const vector<int> &wiring)
    {
        vector<int> inverse(wiring.size());
        for (int i = 0; i < wiring.size(); i++)
        {
            int value = wiring[i];
            inverse[value] = i;
        }
        return inverse;
    }

    static int encipher(int c, int rotorPos, int ringPos, const vector<int> &wiring)
    {
        int offset = c + rotorPos - ringPos;
        int normalized = (offset + 26) % 26;
        int enciphered = wiring[normalized];
        int unoffset = (enciphered - rotorPos + ringPos + 26) % 26;
        return unoffset;
    }
};