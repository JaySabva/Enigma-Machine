class Plugboard
{
    vector<int> wiring;

public:
    /// Plugboard constructor
    Plugboard(const string &connections)
        : wiring(decodePlugboard(connections)) {}
    
    // Message is passed through the plugboard
    int forward(int c) const
    {
        return wiring[c];
    }
    
    // Message is passed through the plugboard
    static unordered_set<int> getUnpluggedCharacters(const string &plugboard)
    {
        unordered_set<int> unpluggedCharacters;
        for (int i = 0; i < 26; i++)
        {
            unpluggedCharacters.insert(i);
        }

        if (plugboard.empty())
        {
            return unpluggedCharacters;
        }

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
            unpluggedCharacters.erase(c1);
            unpluggedCharacters.erase(c2);
        }

        return unpluggedCharacters;
    }

private:
    static vector<int> decodePlugboard(const string &plugboard)
    {
        if (plugboard.empty())
        {
            return identityPlugboard();
        }

        string temp;
        for (char c : plugboard)
        {
            if (isalpha(c))
            {
                temp += c;
            }
        }

        unordered_set<int> pluggedCharacters;
        vector<int> mapping(26);
        iota(mapping.begin(), mapping.end(), 0);

        for (auto i = 0; i < temp.size(); i += 2)
        {
            if (temp[i] == temp[i + 1])
            {
                return identityPlugboard();
            }

            int c1 = temp[i] - 'A';
            int c2 = temp[i + 1] - 'A';

            if (pluggedCharacters.count(c1) || pluggedCharacters.count(c2))
            {
                return identityPlugboard();
            }

            pluggedCharacters.insert(c1);
            pluggedCharacters.insert(c2);

            mapping[c1] = c2;
            mapping[c2] = c1;
        }

        return mapping;
    }

    static vector<int> identityPlugboard()
    {
        vector<int> mapping(26);
        iota(mapping.begin(), mapping.end(), 0);
        return mapping;
    }
};