#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string evaluatePostfix(vector<string> postfix)
{
    stack<string> s;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == "+" or postfix[i] == "-" or postfix[i] == "*" or postfix[i] == "/")
        {
            string op1 = s.top();
            int OP1 = atoi(op1.c_str());
            s.pop();
            string op2 = s.top();
            int OP2 = atoi(op2.c_str());
            s.pop();
            if (postfix[i] == "-")
            {
                s.push(to_string((OP2 - OP1)));
            }
            else if (postfix[i] == "/")
            {
                s.push(to_string((OP2 / OP1)));
            }
            else if (postfix[i] == "*")
            {
                s.push(to_string((OP2 * OP1)));
            }
            else
            {
                s.push(to_string((OP2 + OP1)));
            }
        }
        else
            s.push(postfix[i]);
    }
    return s.top();
}

vector<string> characterArrayToVectOfString(char c[])
{
    int i = 0;
    vector<string> v;
	string temp = "";
    while (c[i] != ' ' and i < strlen(c))
    {
        temp += c[i++];
        if (c[i] == ' ')
        {
            v.push_back(temp);
            i++ ;
            temp = "";
            
        }
    }
    return v;
}

int main()
{
	//input character arrays and convert them into vector of strings
    char post[1000];
    scanf("%[^\n]", post);
    vector<string> postfix = characterArrayToVectOfString(post);

    for (int i = 0; i < postfix.size(); i++)
    {
        cout<<postfix[i]<<" ";
    }
	cout<<endl;
	
	//input vector of strings directly
	// int n;
    // cin >> n;
	// vector<string> postfix(n);
	//  for (int i = 0; i < postfix.size(); i++)
 //   {
 //       cin>>postfix[i];
 //   }
 
    cout << evaluatePostfix(postfix) << endl;
    return 0;
}