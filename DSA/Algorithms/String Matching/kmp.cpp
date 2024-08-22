#include <bits/stdc++.h>
using namespace std;

vector<long long> computeLPS(string pattern, int len)
{
    vector<long long> lps(len, 0);
    int L = 0;
    int i = 1;

    while (i < len)
    {
        if (pattern[i] == pattern[L])
        {
            lps[i] = L + 1;
            L++;
            i++;
        }
        else
        {
            if (L != 0)
            {
                L = lps[L - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void kmpStringMatch(string text, string pattern)
{
    int lenText = text.length();
    int lenPattern = pattern.size();

    vector<long long> lps(lenPattern, 0);
    lps = computeLPS(pattern, lenPattern);

    int i = 0, j = 0; // i = pointer in the text and j = pointer in the lps array

    while (i < lenText)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
        if (j == lenPattern)
        {
            cout << "Found at index : " << i - j << "\n";
            j = lps[j - 1];
        }
    }
}

int main()
{
    kmpStringMatch("onionionspl", "onions");
}