#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool you_are_an_angel()
{
    string respo;
    cout << "Are you an angel? Please enter \"YES\" or \"NO\" " << endl;
    cin >> respo;
    if (respo == "YES")
        return true;
    return false;
}

void mention_three_of_your_flaws()
{
    cout << "Mention three flaws if you are a human " << endl;
    string flaws;
    for (int i = 1; i <= 3; i++)
    {
        cout << i <<". ";
        cin >> flaws;
        cout << flaws << endl;
    }
    return;
}

int main()
{
    ll x;
    cout << "r for rizvee so please input 114 : ";
    cin >> x;
    bool flaw = true;
    string your_saying;
    switch (x)
    {
    case 114:
        cout << "Perfect" << endl;
    case '0':
        cout << "Talented" << endl;
    case '1':
        cout << "Harworking" << endl;
    case '2':
        cout << "Polite" << endl;
    case '3':
        cout << "Beautiful" << endl;
        break;
    default:
        cout << "You dind't input 114 :) ";
        break;
    }

    while (flaw)
    {
        if (you_are_an_angel())
        {
            flaw = false;
            cout << "Dear Angel, I've met so many persons in my life but you seem just so different from all.\nPlease help me to get one step closer to become a better human being :) " << endl;
        }
        else
        {
            mention_three_of_your_flaws();
            cout << "Dear Human, I too have flaws, maybe a lot more than you.\nBut I think it's good to have flaws otherwise you wouldn't be more special than I am :)\nTo me, you are always relatively an angel." << endl;
            break;
        }
    }

    cout << "\nYou can always find me around you.\nI'm not a player.\nPlease don't forget to forgive me for my noob coding :3\nand yes, I'm the same person.\nAll I know is I was enchanted to meet you.\nAll the best sir." << endl;
    cout << "wanna say sth about me anonymously in three words?" << endl;

    for (int i = 1; i <= 3; i++)
    {
        cout << i <<". ";
        cin >> your_saying;
        cout << your_saying << endl;
    }
    return 0;
}
