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