#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7, m = 1e9 + 7;
int p = 31;

vector<long long> calculate_power(vector<long long> power)
{
    power[0] = 1;
    for (int i = 1; i < N; i++)
    {
        power[i] = (power[i - 1] * p) % m;
    }
    return power;
}

void stringMatchRabinCarp(string text, string pattern)
{
    int lenText = text.size();
    vector<long long> power(N);
    power = calculate_power(power);
    vector<long long> hashText(lenText + 1, 0);

    for (int i = 0; i < lenText; i++)
    {
        hashText[i + 1] = (hashText[i] + (text[i] - 'a' + 1) * power[i]) % m;
    }

    long long hashPattern = 0;
    int lenPattern = pattern.size();

    for (int i = 0; i < lenPattern; i++)
    {
        hashPattern = (hashPattern + (pattern[i] - 'a' + 1) * power[i]) % m;
    }

    for (int i = 0; i + lenPattern - 1 < lenText; i++)
    {
        long long curr_hash = (hashText[i + lenPattern] - hashText[i] + m) % m;
        if (curr_hash == (hashPattern * power[i]) % m)
        {
            cout << "Found at index : " << i << "\n";
        }
    }
}

int main()
{
    stringMatchRabinCarp("collegeapna", "apna");
}
