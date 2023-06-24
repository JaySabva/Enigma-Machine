#include <bits/stdc++.h>
using namespace std;

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