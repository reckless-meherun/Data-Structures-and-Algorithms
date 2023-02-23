#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    stack<int> st; // Create a stack

    int j = 0; // Intialise one pointer pointing on popped array

    for (auto val : pushed)
    {
        st.push(val); // insert the values in stack
        while (st.size() > 0 && st.top() == popped[j])
        {             // if st.peek() values equal to popped[j];
            st.pop(); // then pop out
            j++;      // increment j
        }
    }
    return st.size() == 0; // check if stack is empty return true else false
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n;
    cin >> n;
    vector<int> pushed(n), popped(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pushed[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> popped[i];
    }
    cout << validateStackSequences(pushed, popped) << endl;
    return 0;
}