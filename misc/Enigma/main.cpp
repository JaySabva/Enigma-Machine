#include <bits/stdc++.h>
#include "enigma.h"

int main()
{
    // Rotor Types: I, II, III, IV, V, VI, VII, VIII
    string leftRotorType = "III";
    string middleRotorType = "II";
    string rightRotorType = "I";
    string reflectorType = "B";

    // Rotor Positions: 0-25
    int leftRotorPosition = 0;
    int middleRotorPosition = 0;
    int rightRotorPosition = 0;

    // Ring Settings: 0-25
    int leftRingSetting = 0;
    int middleRingSetting = 0;
    int rightRingSetting = 0;

    // Plugboard Connections: A-Z
    string plugboardConnections = "AQ BJ CM DX EZ FL GY HW IP KU";

    // Create an Enigma machine
    Enigma enigma(leftRotorType, middleRotorType, rightRotorType,
                  reflectorType, leftRotorPosition, middleRotorPosition, rightRotorPosition,
                  leftRingSetting, middleRingSetting, rightRingSetting, plugboardConnections);

    // Encrypt a message
    string plaintext = "JAYSABVA";
    string ciphertext = enigma.encrypt(plaintext);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
