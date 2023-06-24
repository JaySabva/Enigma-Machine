#include "rotor..h"
#include "reflector.h"
#include "plugboard.h"

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
          plugboard(Plugboard(plugboardConnections)) {}

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
            if (std::isalpha(c))
            {
                c = 'A' + encrypt(std::toupper(c) - 'A');
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
        else if (rightRotor.isAtNotch())
        {
            middleRotor.turnover();
        }

        rightRotor.turnover();
    }
};