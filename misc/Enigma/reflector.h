#include <bits/stdc++.h>
using namespace std;
class Reflector
{
    vector<int> forwardWiring;

public:
    Reflector(const string &encoding)
        : forwardWiring(decodeWiring(encoding)) {}

    static Reflector Create(const string &name)
    {
        if (name == "B")
            return Reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");
        else if (name == "C")
            return Reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL");
        else
            return Reflector("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    int forward(int c) const
    {
        return forwardWiring[c];
    }

private:
    static vector<int> decodeWiring(const string &encoding)
    {
        vector<int> wiring;
        for (char c : encoding)
        {
            int value = c - 'A';
            wiring.push_back(value);
        }
        return wiring;
    }
};